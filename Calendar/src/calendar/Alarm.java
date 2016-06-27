package calendar;

import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;

import javax.swing.*;
import javax.swing.border.LineBorder;
import javax.swing.filechooser.FileFilter;

//闹钟类
public class Alarm extends JFrame implements ActionListener
{
	JFrame setAlarm=new JFrame("设置闹钟");
	JLabel setClockName=new JLabel("设置闹钟名称");
	JTextField clockName=new JTextField(20);
	JRadioButton choice1=new JRadioButton("选择音乐作为提醒音");
	JRadioButton choice2=new JRadioButton("输入一段话作为提醒音");
	ButtonGroup buttonGroup=new ButtonGroup();
	JButton chooseMusic=new JButton("选择音乐");
	JTextField showMusic=new JTextField(20);
	JTextArea inputRemind=new JTextArea(3,30);
	JLabel year,month,day,hour,minute,second;
	JTextField inputYear,inputMonth,inputDay,inputHour,inputMinute,inputSecond;
	JButton add;
	
	int alarmYear,alarmMonth,alarmDay,alarmHour,alarmMinute,alarmSecond;
	
	public Alarm()
	{
		ImageIcon alarmImage=new ImageIcon("./src/images/seaside.jpg");        //获取背景图片
		setAlarm.setSize(alarmImage.getIconWidth(), alarmImage.getIconHeight());//设置长宽
		Dimension dimension=Toolkit.getDefaultToolkit().getScreenSize();       //获得屏幕尺寸
		setAlarm.setLocation((dimension.width-alarmImage.getIconWidth())/2, 
						(dimension.height-alarmImage.getIconHeight())/2);      //调整到屏幕中间
		setAlarm.setDefaultCloseOperation(JFrame.HIDE_ON_CLOSE);               //设置关闭隐藏
		
		//设置背景图片
		JLayeredPane alarmLayeredPane=new JLayeredPane();
		JPanel jPanel=new JPanel();											   //新建面板容器
		JLabel jLabel=new JLabel();											   //新建标签
		jPanel.setBounds(0, -5, alarmImage.getIconWidth(), alarmImage.getIconHeight());//设置面板大小
		jLabel=new JLabel(alarmImage);										   //创建具有指定图像的JLabel实例
		jPanel.add(jLabel);													   //将标签加到面板容器中去
		alarmLayeredPane.add(jPanel, alarmLayeredPane.DEFAULT_LAYER);          //再将面板容器放到层次面板的底层，即背景图      
		
		//添加设置闹钟名称组块
		setClockName.setForeground(Color.YELLOW);
		setClockName.setFont(new Font("楷体",Font.BOLD,22));
		setClockName.setBounds(10,10,150,40);								   //放在左上角
		alarmLayeredPane.add(setClockName, JLayeredPane.MODAL_LAYER);
		clockName.setFont(new Font("楷体",Font.BOLD,22));
		clockName.setForeground(Color.YELLOW);
		clockName.setBounds(170,10,380,40);									   //放在setClockName的右边
		clockName.setOpaque(false);
		alarmLayeredPane.add(clockName, JLayeredPane.MODAL_LAYER);
		
		//添加两个单选项
		choice1.setBounds(10,60,300,20);									   //放在左上
		choice2.setBounds(10,180,300,20);									   //放在左中
		choice1.setForeground(Color.ORANGE);
		choice2.setForeground(Color.ORANGE);
		choice1.setFont(new Font("楷书",Font.BOLD+Font.HANGING_BASELINE,20));
		choice2.setFont(new Font("楷书",Font.BOLD+Font.HANGING_BASELINE,20));
		choice1.setOpaque(false);
		choice2.setOpaque(false);
		
		buttonGroup.add(choice1);											   //为上面两个choice创建一个多斥作用域
		buttonGroup.add(choice2);
		
		alarmLayeredPane.add(choice1, JLayeredPane.MODAL_LAYER);
		alarmLayeredPane.add(choice2,JLayeredPane.MODAL_LAYER);
		
		//添加"选择音乐"按钮
		chooseMusic.setBackground(Color.WHITE);
		chooseMusic.setFont(new Font("华文行楷",Font.CENTER_BASELINE,22));
		chooseMusic.setForeground(Color.DARK_GRAY);
		chooseMusic.setBorder(BorderFactory.createRaisedBevelBorder()); 
		chooseMusic.setBounds(10,90,130,50);								   //放在choice1的下面
		alarmLayeredPane.add(chooseMusic, JLayeredPane.MODAL_LAYER);
		
		//添加文本框以显示选择的音乐名
		showMusic.setOpaque(false);
		showMusic.setFont(new Font("楷书",Font.CENTER_BASELINE,20));
		showMusic.setForeground(Color.DARK_GRAY);
		showMusic.setBorder(new LineBorder(Color.CYAN, 1, true));
		showMusic.setBounds(150,90,400,50);									   //放在"选择音乐"按钮的右边
		alarmLayeredPane.add(showMusic, JLayeredPane.MODAL_LAYER);
		
		//添加输入文本框
		inputRemind.setOpaque(false);
		inputRemind.setBorder(new LineBorder(Color.CYAN, 1, true));			   //设置边框
		inputRemind.setLineWrap(true);										   //设置自动换行
		inputRemind.setFont(new Font("楷书",Font.LAYOUT_LEFT_TO_RIGHT,20));
		inputRemind.setForeground(Color.YELLOW);
		inputRemind.setCaretColor(Color.BLACK);         				   	   //设置光标颜色
		inputRemind.setBounds(10,200,570,90);								   //放在choice2的下边
		alarmLayeredPane.add(inputRemind, JLayeredPane.MODAL_LAYER);
		
		//获取当前系统时间
		MyCalendar myCalendar=new MyCalendar();
		
		//添加设置闹钟组件
		inputYear=new JTextField(Integer.toString(myCalendar.getYear()));      //设置默认年份为今年
		inputYear.setOpaque(false);
		inputYear.setFont(new Font("楷书",Font.BOLD,20));
		inputYear.setForeground(Color.BLACK);
		inputYear.setBounds(10,300,60,40);									   //放在文本输入框的下边
		alarmLayeredPane.add(inputYear, JLayeredPane.MODAL_LAYER);
		
		year=new JLabel("年");
		year.setFont(new Font("楷书",Font.BOLD,20));
		year.setForeground(Color.BLACK);
		year.setBounds(80, 300, 30, 40);									   //放在inputYear的右边
		alarmLayeredPane.add(year, JLayeredPane.MODAL_LAYER);
		
		inputMonth=new JTextField(Integer.toString(myCalendar.getMonth()));    //设置默认月份为本月
		inputMonth.setOpaque(false);
		inputMonth.setFont(new Font("楷书",Font.BOLD,20));
		inputMonth.setForeground(Color.BLACK);
		inputMonth.setBounds(120,300,60,40);								   //放在year的右边
		alarmLayeredPane.add(inputMonth, JLayeredPane.MODAL_LAYER);
		
		month=new JLabel("月");
		month.setFont(new Font("楷书",Font.BOLD,20));
		month.setForeground(Color.BLACK);
		month.setBounds(190, 300, 30, 40);									   //放在inputMonth的右边
		alarmLayeredPane.add(month, JLayeredPane.MODAL_LAYER);
		
		inputDay=new JTextField(Integer.toString(myCalendar.getDay()));		   //设置默认天为今天
		inputDay.setOpaque(false);
		inputDay.setFont(new Font("楷书",Font.BOLD,20));
		inputDay.setForeground(Color.BLACK);
		inputDay.setBounds(230,300,60,40);									   //放在month的右边
		alarmLayeredPane.add(inputDay, JLayeredPane.MODAL_LAYER);
		
		day=new JLabel("日");
		day.setFont(new Font("楷书",Font.BOLD,20));
		day.setForeground(Color.BLACK);
		day.setBounds(300, 300, 30, 40);									   //放在inputDay的右边
		alarmLayeredPane.add(day, JLayeredPane.MODAL_LAYER);
		
		inputHour=new JTextField();
		inputHour.setOpaque(false);
		inputHour.setFont(new Font("楷书",Font.BOLD,20));
		inputHour.setForeground(Color.BLACK);
		inputHour.setBounds(10,350,60,40);									   //放在inputYear的下边
		alarmLayeredPane.add(inputHour, JLayeredPane.MODAL_LAYER);
		
		hour=new JLabel("点");
		hour.setFont(new Font("楷书",Font.BOLD,20));
		hour.setForeground(Color.BLACK);
		hour.setBounds(80, 350, 30, 40);									   //放在inputHour的右边
		alarmLayeredPane.add(hour, JLayeredPane.MODAL_LAYER);
		
		inputMinute=new JTextField();
		inputMinute.setOpaque(false);
		inputMinute.setFont(new Font("楷书",Font.BOLD,20));
		inputMinute.setForeground(Color.BLACK);
		inputMinute.setBounds(120,350,60,40);								   //放在Hour的右边
		alarmLayeredPane.add(inputMinute, JLayeredPane.MODAL_LAYER);
		
		minute=new JLabel("分");
		minute.setFont(new Font("楷书",Font.BOLD,20));
		minute.setForeground(Color.BLACK);
		minute.setBounds(190, 350, 30, 40); 								   //放在inputMinute的右边
		alarmLayeredPane.add(minute, JLayeredPane.MODAL_LAYER);
		
		inputSecond=new JTextField(myCalendar.getYear());
		inputSecond.setOpaque(false);
		inputSecond.setFont(new Font("楷书",Font.BOLD,20));
		inputSecond.setForeground(Color.BLACK);
		inputSecond.setBounds(230,350,60,40);								   //放在minute的右边
		alarmLayeredPane.add(inputSecond, JLayeredPane.MODAL_LAYER);
		
		second=new JLabel("秒");
		second.setFont(new Font("楷书",Font.BOLD,20));
		second.setForeground(Color.BLACK);
		second.setBounds(300, 350, 30, 40); 								   //放在inputSecond的右边
		alarmLayeredPane.add(second, JLayeredPane.MODAL_LAYER);
		
		//添加确定按钮
		add=new JButton();									   				   //新建"确定"的按钮
		add.setBorderPainted(false);							  			   //边框不可见				
		add.setContentAreaFilled(false);						 			   //透明
		add.setIcon(new ImageIcon("./src/images/add.png"));					   //设置图标
		add.setToolTipText("点击确定添加闹钟");									   //设置提醒信息
		add.setBounds(330,300,100,100);										   //放在右下方
		alarmLayeredPane.add(add, JLayeredPane.MODAL_LAYER);
		
		//注册监听器
		choice1.addActionListener(this);
		choice2.addActionListener(this);
		chooseMusic.addActionListener(this);
		add.addActionListener(this);
		
		setAlarm.add(alarmLayeredPane);
		
		setAlarm.setVisible(true);
	}
	public void actionPerformed(ActionEvent e)
	{
		//如果点击的是添加音乐按钮
		if(e.getSource()==chooseMusic)
		{
			JFileChooser chooser=new JFileChooser();						   //建立文件选择器
			chooser.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);  //指示显示文件和目录
			chooser.setCurrentDirectory(new File("."));						   //以当前目录生成一个文件目录实例，然后设置为当前的工作目录
			chooser.setFileFilter(new FileFilter()
					{
						public boolean accept(File file)					   //设置可接受的文件类型
						{
							String fileName=file.getName().toLowerCase();
							return fileName.endsWith(".wav")||
									fileName.endsWith(".au")||
									fileName.endsWith(".mid")||
									file.isDirectory();
						}
						public String getDescription()						   //文件描述
						{
							return "音乐文件(*.wav,*.au,*.mid)";
						}
					});
			if (chooser.showOpenDialog(Alarm.this) == JFileChooser.APPROVE_OPTION)// 弹出文件选择器,并判断是否点击了打开按钮 
			{ 
			     String fileName = chooser.getSelectedFile().getAbsolutePath();// 得到选择文件或目录的绝对路径
			     showMusic.setText(fileName);
			}
		}
		else if(e.getSource()==add)
		{
			JOptionPane.showMessageDialog(null, "成功添加闹钟");
			//JDialog showMessage=new JDialog(this,"成功添加闹钟");
			//showMessage.setModal(false);
			//showMessage.setVisible(true);
			//读取输入的闹钟时间
			alarmYear=Integer.parseInt(inputYear.getText());
			alarmMonth=Integer.parseInt(inputMonth.getText());
			alarmDay=Integer.parseInt(inputDay.getText());
			alarmHour=Integer.parseInt(inputHour.getText());
			alarmMinute=Integer.parseInt(inputMinute.getText());
			alarmSecond=Integer.parseInt(inputSecond.getText());
			
			//选择了添加音乐
			if(choice1.isSelected())
			{
				//建立播放音乐界面
				PlayMusic playMusic=new PlayMusic(alarmYear,alarmMonth,alarmDay,alarmHour,alarmMinute,alarmSecond,
						clockName.getText(),showMusic.getText());
				Thread t1=new Thread(playMusic);         				     
				t1.start();         				    				       //启动线程
			}
			//选择了添加一段话
			else if(choice2.isSelected())
			{
				//建立播放提示语界面
				SpeakWords speakWords=new SpeakWords(alarmYear,alarmMonth,alarmDay,alarmHour,alarmMinute,alarmSecond,
						clockName.getText(),inputRemind.getText());
				Thread t2=new Thread(speakWords);
				t2.start();         					  				       //启动线程
			}
		}
	}
}
