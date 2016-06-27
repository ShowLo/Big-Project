package calendar;

import javax.swing.*;

import java.awt.Color;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Toolkit;
import java.awt.event.*;
import java.io.FileWriter;
import java.io.IOException;
import java.text.SimpleDateFormat;
import java.util.Date;

public class SpeakWords extends JFrame implements ActionListener,Runnable
{
	int year,month,day,hour,minute,second;
	boolean isClose=false;
	String clockName,remindWords,fileName;
	JFrame speakWords=new JFrame("到钟啦");
	JTextArea showClockName=new JTextArea();
	JButton close=new JButton();
	
	public SpeakWords(int year,int month,int day,int hour,int minute,int second,
			String clockName,String remindWords)
	{
		//设置闹钟时间
		this.year=year;
		this.month=month;
		this.day=day;
		this.hour=hour;
		this.minute=minute;
		this.second=second;
		//设置闹钟名称及提醒语
		this.clockName=clockName;
		this.remindWords=remindWords;
		//设置vbs脚本的路径
		this.fileName="./src/vbs/speak.vbs";
	}
	
	//时间到了播放提示语
	public void speak()
	{
		ImageIcon musicImage=new ImageIcon("./src/images/starrySky.jpg");         //获取背景图片
		speakWords.setSize(musicImage.getIconWidth(), musicImage.getIconHeight());//设置长宽
		Dimension dimension=Toolkit.getDefaultToolkit().getScreenSize();          //获得屏幕尺寸
		speakWords.setLocation((dimension.width-musicImage.getIconWidth())/2, 
				(dimension.height-musicImage.getIconHeight())/2);      			  //调整到屏幕中间
		speakWords.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);             //设置关闭方式

		//设置背景图片
		JLayeredPane speakWordsPane=new JLayeredPane();
		JPanel jPanel=new JPanel();											  	  //新建面板容器
		JLabel jLabel=new JLabel();											  	  //新建标签
		jPanel.setBounds(0, -5, musicImage.getIconWidth(), musicImage.getIconHeight());//设置面板大小
		jLabel=new JLabel(musicImage);											  //创建具有指定图像的JLabel实例
		jPanel.add(jLabel);													 	  //将标签加到面板容器中去
		speakWordsPane.add(jPanel, JLayeredPane.DEFAULT_LAYER);          	  	  //再将面板容器放到层次面板的底层，即背景图      

		//显示闹钟名称
		showClockName.setText(this.clockName);
		showClockName.setForeground(Color.ORANGE);
		showClockName.setFont(new Font("楷书",Font.BOLD,25));
		showClockName.setLineWrap(true);
		showClockName.setOpaque(false);
		showClockName.setBounds(10, 10, 400, 100);							  	  //放在上边
		speakWordsPane.add(showClockName, JLayeredPane.MODAL_LAYER);

		//添加关闭音乐按钮
		close=new JButton();									   			 	  //新建"关闭"的按钮
		close.setBorderPainted(false);							  			  	  //边框不可见				
		close.setContentAreaFilled(false);						 			 	  //透明
		close.setIcon(new ImageIcon("./src/images/close.png"));				 	  //设置图标
		close.setToolTipText("点击关闭闹钟");								   	 	  //设置提醒信息
		close.setBounds(350,230,120,120);									  	  //放在右下方
		speakWordsPane.add(close, JLayeredPane.MODAL_LAYER);

		close.addActionListener(this);										      //为关闭按钮注册监听器

		speakWords.add(speakWordsPane);
		speakWords.setVisible(true);
	}
	
	public void actionPerformed(ActionEvent e) 
	{
		//点击了关闭按钮，关闭提示语
		if(e.getSource()==close)
		{
			isClose=true;
		}
	}
		
	public void run()
	{
		while(true)
		{
			MyCalendar current=new MyCalendar();
			
			//获取当前年月日
			int currentYear=current.getYear();
			int currentMonth=current.getMonth();
			int currentDay=current.getDay();
			
			//获取当前时分秒
			SimpleDateFormat getHour=new SimpleDateFormat("HH");
			SimpleDateFormat getMinute=new SimpleDateFormat("mm");
			SimpleDateFormat getSecond=new SimpleDateFormat("ss");
			
			Date now=new Date();
			int currentHour=Integer.parseInt(getHour.format(now));
			int currentMinute=Integer.parseInt(getMinute.format(now));
			int currentSecond=Integer.parseInt(getSecond.format(now));
			
			//判断是否触发闹钟
			if(this.year==currentYear&&this.month==currentMonth&&this.day==currentDay)
			{
				if(this.hour==currentHour)
				{
					if(this.minute==currentMinute&&this.second==currentSecond)
					{
						speak();
						try 
						{
							FileWriter writer=new FileWriter(fileName);           //获取文件位置
							String source="CreateObject(\"SAPI.SpVoice\").Speak\""+remindWords+"\"";
							writer.write(source);								  //将上面的vbs脚本代码写入文件
							writer.close();
						}
						catch (IOException ioe)
						{
							JOptionPane.showMessageDialog(null, "写入文件时出错");
						}
						String path="C://windows//system32//wscript.exe";		  //脚本语言解释器的路径，利用它执行vbs脚本
						String command=path+" "+fileName;
						while(true&&!isClose)									  //循环执行直至关闭按钮被按下
						{
							try 
							{
								Process pro=Runtime.getRuntime().exec(command);   //利用当前Java应用程序的运行时对象执行系统命令
								pro.waitFor();									  //等待命令执行完毕继续循环
							} 
							catch (IOException | InterruptedException e) 
							{
								JOptionPane.showMessageDialog(null, "出错啦");
							}
						}
					}
				}
			}
			try
			{
				//每秒判断一次
				Thread.sleep(1000);
			}
			catch(InterruptedException e)
			{}
		}
	}
}