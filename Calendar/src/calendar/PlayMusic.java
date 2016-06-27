package calendar;

import java.applet.Applet;
import java.applet.AudioClip;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.net.MalformedURLException;
import java.text.SimpleDateFormat;
import java.util.Date;

import javax.swing.*;


public class PlayMusic extends JFrame implements ActionListener,Runnable
{
	int year,month,day,hour,minute,second;
	boolean isClose=false;
	String clockName,musicName;
	JFrame alarmMusic=new JFrame("到钟啦");
	JTextArea showClockName=new JTextArea();
	JButton close=new JButton();
	
	public AudioClip music;
	
	public PlayMusic(int year,int month,int day,int hour,int minute,int second,
			String clockName,String musicName)
	{
		//设置闹钟时间
		this.year=year;
		this.month=month;
		this.day=day;
		this.hour=hour;
		this.minute=minute;
		this.second=second;
		//设置闹钟名称及音乐文件路径
		this.clockName=clockName;
		this.musicName=musicName;
	}
	
	//时间到了播放音乐
	public void play()
	{
		ImageIcon musicImage=new ImageIcon("./src/images/star.jpg");           //获取背景图片
		alarmMusic.setSize(musicImage.getIconWidth(), musicImage.getIconHeight());//设置长宽
		Dimension dimension=Toolkit.getDefaultToolkit().getScreenSize();       //获得屏幕尺寸
		alarmMusic.setLocation((dimension.width-musicImage.getIconWidth())/2, 
						(dimension.height-musicImage.getIconHeight())/2);      //调整到屏幕中间
		alarmMusic.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);          //设置关闭方式
		
		//设置背景图片
		JLayeredPane alarmMusicPane=new JLayeredPane();
		JPanel jPanel=new JPanel();											   //新建面板容器
		JLabel jLabel=new JLabel();											   //新建标签
		jPanel.setBounds(0, -5, musicImage.getIconWidth(), musicImage.getIconHeight());//设置面板大小
		jLabel=new JLabel(musicImage);										   //创建具有指定图像的JLabel实例
		jPanel.add(jLabel);													   //将标签加到面板容器中去
		alarmMusicPane.add(jPanel, JLayeredPane.DEFAULT_LAYER);          	   //再将面板容器放到层次面板的底层，即背景图      
		
		//显示闹钟名称
		showClockName.setText(this.clockName);
		showClockName.setForeground(Color.ORANGE);
		showClockName.setFont(new Font("楷书",Font.BOLD,25));
		showClockName.setLineWrap(true);
		showClockName.setOpaque(false);
		showClockName.setBounds(10, 10, 400, 100);							   //放在上边
		alarmMusicPane.add(showClockName, JLayeredPane.MODAL_LAYER);
		
		//添加关闭音乐按钮
		close=new JButton();									   			   //新建"关闭"的按钮
		close.setBorderPainted(false);							  			   //边框不可见				
		close.setContentAreaFilled(false);						 			   //透明
		close.setIcon(new ImageIcon("./src/images/close.png"));				   //设置图标
		close.setToolTipText("点击关闭闹钟");								   	   //设置提醒信息
		close.setBounds(350,230,120,120);									   //放在右下方
		alarmMusicPane.add(close, JLayeredPane.MODAL_LAYER);
		
		close.addActionListener(this);										   //为关闭按钮注册监听器
		
		alarmMusic.add(alarmMusicPane);
		alarmMusic.setVisible(true);
	}
	
	public void actionPerformed(ActionEvent e) 
	{
		//点击了关闭按钮，关闭音乐
		if(e.getSource()==close)
		{
			isClose=true;
			music.stop();
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
						try
						{
							//创建闹钟窗口并循环播放音乐
							play();
							music=Applet.newAudioClip(new File(musicName).toURI().toURL());
							music.play();
							music.loop();
						}
						catch(MalformedURLException e)
						{}
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
