package calendar;

import java.awt.*;
import javax.swing.*;
import javax.swing.filechooser.FileFilter;

import java.awt.event.*;
import java.io.File;
import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.StringTokenizer;

//主日历类
public class MainCalendar extends JFrame implements ActionListener
{
	int currentYear;		//当前年月日
	int currentMonth;
	int currentDay;
	int showYear;			//显示的年月
	int showMonth;
	MyCalendar showDate;
	
	String dayNum[]=new String[42];
	String weekdayName[]={"日","一","二","三","四","五","六"};
	
	JLabel allDay[]=new JLabel[42];
	JLabel nextMonth,previousMonth;
	JLabel message=new JLabel("",JLabel.CENTER);
	JLabel prompt=new JLabel("在此输入查询年月:");
	JLabel currentDate;
	JLabel jLabel;
	JLabel time=new JLabel();
	
	JTextField inputYear=new JTextField(10);
	
	JButton weekday[]=new JButton[7];
	JButton confirm=new JButton();
	JButton nextMonthIcon,previousMonthIcon;
	JButton alarm;
	JButton changeBackground;
	
	JLayeredPane layeredPane;
	
	JPanel jPanel;
	JPanel centerPanel;
	
	ImageIcon imageIcon;
	
	JFrame frame;
	
	//私有类，实现时间的实时显示
	private class DisplayTime extends Thread								   //利用线程实现实时显示
	{
		SimpleDateFormat sdf=new SimpleDateFormat("HH:mm:ss");     			   //24小时制,精确到秒
		public void run()
		{
			while(true)
			{
				time.setText(sdf.format(new Date()));
				try
				{
					Thread.sleep(1000);										   //线程休眠一秒
				}
				catch(InterruptedException e)
				{}
			}
		}
	}
	
	//Gettter和setter方法
	public int getCurrentYear() 
	{
		return currentYear;
	}
	public void setCurrentYear(int currentYear) 
	{
		this.currentYear = currentYear;
	}
	public int getCurrentMonth() 
	{
		return currentMonth;
	}
	public void setCurrentMonth(int currentMonth) 
	{
		this.currentMonth = currentMonth;
	}
	public int getCurrentDay() 
	{
		return currentDay;
	}
	public void setCurrentDay(int currentDay) 
	{
		this.currentDay = currentDay;
	}
	public int getShowYear() 
	{
		return showYear;
	}
	public void setShowYear(int showYear) 
	{
		this.showYear = showYear;
	}
	public int getShowMonth() 
	{
		return showMonth;
	}
	public void setShowMonth(int showMonth) 
	{
		this.showMonth = showMonth;
	}

	
	public MainCalendar()
	{
		//默认年月日为现在的年月日
		MyCalendar myCalendar=new MyCalendar();
		setCurrentYear(myCalendar.getYear());
		setCurrentMonth(myCalendar.getMonth());
		setCurrentDay(myCalendar.getDay());
		//默认显示年月为现在的年月
		setShowYear(myCalendar.getYear());
		setShowMonth(myCalendar.getMonth());
		showDate=new MyCalendar(getShowYear(),getShowMonth());
	}
	
	//画主界面
	public void drawCalendar()
	{
		imageIcon=new ImageIcon("./src/images/sea.jpg");                       //获取背景图片
		
		//设置主框架
		JFrame.setDefaultLookAndFeelDecorated(true);						   //用当前LookAndFeel提供的Window装饰
		frame=new JFrame("日历");										   		   //标题名
		frame.setSize(imageIcon.getIconWidth(), imageIcon.getIconHeight());    //设置长宽
		Dimension dimension=Toolkit.getDefaultToolkit().getScreenSize();       //获得屏幕尺寸
		frame.setLocation((dimension.width-imageIcon.getIconWidth())/2, 
						(dimension.height-imageIcon.getIconHeight())/2);       //调整到屏幕中间
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);                  //设置默认关闭窗口操作
		
		//设置背景图片
		layeredPane=new JLayeredPane();          							   //新建层次面板
		jPanel=new JPanel();												   //新建面板容器
		jLabel=new JLabel();												   //新建标签
		jPanel.setBounds(0, -5, imageIcon.getIconWidth(), imageIcon.getIconHeight());//设置面板大小
		jLabel=new JLabel(imageIcon);										   //创建具有指定图像的JLabel实例
		jPanel.add(jLabel);													   //将标签加到面板容器中去
		layeredPane.add(jPanel, JLayeredPane.DEFAULT_LAYER);                   //再将面板容器放到层次面板的底层，即背景图      
		
		//添加日历组件
		centerPanel=new JPanel();								      	       //新建面板容器以放置日期信息
		centerPanel.setLayout(new GridLayout(7,7));                            //设置为7行7列的布局
		for(int i=0;i<7;++i)												   //添加星期几		   
		{
			weekday[i]=new JButton(weekdayName[i]);                            //从星期日到星期六
			weekday[i].setContentAreaFilled(false);                            //设为透明的
			weekday[i].setBorderPainted(false);								   //去掉边框
			weekday[i].setForeground(Color.YELLOW);							   //设置字体颜色
			weekday[i].setFont(new Font("华文行楷",Font.BOLD,28));				   //设置字体格式
			centerPanel.add(weekday[i]);									   //加入到面板中去
		}
		dayNum=showDate.getDayNum();										   //获取显示月份的总天数
		for(int i=0;i<42;++i)
		{
			allDay[i]=new JLabel(dayNum[i],JLabel.CENTER);
			allDay[i].setForeground(Color.CYAN);				 			   //设置字体颜色
			allDay[i].setFont(new Font("Courier",Font.BOLD,20));			   //设置字体格式
			centerPanel.add(allDay[i]);										   //加入到面板中去
		}
		centerPanel.setOpaque(false);										   //设置面板为透明的
		centerPanel.setBounds(10, 70, 450, 350);							   //设置面板位置居左中
		layeredPane.add(centerPanel, JLayeredPane.MODAL_LAYER);          	   //放置到层次面板的上层
		
		//添加当前年月日信息
		JLabel today=new JLabel("今天");
		today.setFont(new Font("楷书",Font.BOLD+Font.PLAIN,24));
		today.setForeground(Color.ORANGE);									   //设置字体颜色
		today.setBounds(535,10,100,25);										   //放置在右上方
		layeredPane.add(today, JLayeredPane.MODAL_LAYER);
		currentDate=new JLabel();
		currentDate.setText(getCurrentYear()+"年"+getCurrentMonth()+
				"月"+getCurrentDay()+"日");
		currentDate.setFont(new Font("楷书",Font.BOLD+Font.PLAIN,24));
		currentDate.setForeground(Color.ORANGE);
		currentDate.setBounds(480, 50, 200, 35);							   //放置在右上方
		layeredPane.add(currentDate,JLayeredPane.MODAL_LAYER);
		
		//添加提示年月信息
		message.setText(showDate.getYear()+"年"+showDate.getMonth()+"月");      //设置提示年月
		message.setFont(new Font("楷书",Font.BOLD+Font.HANGING_BASELINE,30));	   //设置提示字体
		message.setForeground(Color.LIGHT_GRAY);
		message.setBounds(15, 10, 200, 50);									   //放置在左上角
		layeredPane.add(message, JLayeredPane.MODAL_LAYER);					   //放置到层次容器的顶层
		
		//添加上个月按钮
		previousMonthIcon=new JButton();									   //新建"上个月"的按钮
		previousMonthIcon.setBorderPainted(false);							   //边框不可见				
		previousMonthIcon.setContentAreaFilled(false);						   //透明
		previousMonthIcon.setIcon(new ImageIcon("./src/images/previousMonth.png"));//设置图标
		previousMonthIcon.setToolTipText("点击查看上个月日历");
		previousMonth=new JLabel("上个月");   				       			   //新建"上个月"的提示标签
		previousMonth.setFont(new Font("楷书",Font.HANGING_BASELINE+Font.BOLD,15));
		previousMonth.setForeground(Color.WHITE);
		previousMonth.setOpaque(false);										   //透明
		JPanel previousMonthPanel=new JPanel();             				   //新建"上个月"面板容器
		previousMonthPanel.add(previousMonthIcon, BorderLayout.NORTH);		   //按钮放在上边
		previousMonthPanel.add(previousMonth, BorderLayout.SOUTH);			   //提示标签放在下边
		previousMonthPanel.setBounds(270,0,50,300);                            //整个面板放到日历右上方
		previousMonthPanel.setOpaque(false);								   //透明
		layeredPane.add(previousMonthPanel,JLayeredPane.MODAL_LAYER);          //加到层次面板的上层
		
		//添加下个月按钮
		nextMonthIcon=new JButton();										   //新建"下个月"的按钮
		nextMonthIcon.setBorderPainted(false);
		nextMonthIcon.setContentAreaFilled(false);
		nextMonthIcon.setIcon(new ImageIcon("./src/images/nextMonth.png"));    //设置图标
		nextMonthIcon.setToolTipText("点击查看下个月日历");
		nextMonth=new JLabel("下个月");   				       			       //新建"下个月"的提示标签
		nextMonth.setFont(new Font("楷书",Font.HANGING_BASELINE+Font.BOLD,15));
		nextMonth.setForeground(Color.WHITE);
		nextMonth.setOpaque(false);
		JPanel nextMonthPanel=new JPanel();             				       //新建"下个月"面板容器
		nextMonthPanel.add(nextMonthIcon, BorderLayout.NORTH);		           //按钮放在上边
		nextMonthPanel.add(nextMonth, BorderLayout.SOUTH);			 		   //提示标签放在下边
		nextMonthPanel.setBounds(380,0,50,300);                      	       //整个面板放到日历右上方
		nextMonthPanel.setOpaque(false);									   //透明
		layeredPane.add(nextMonthPanel,JLayeredPane.MODAL_LAYER);       	   //加到层次面板的上层
		
		JPanel southPanel=new JPanel();										   //新建一个面板容器以放在日历面板的下方
		southPanel.setLayout(new GridLayout(1,3));							   //设置布局
		
		//添加查询提示信息
		prompt.setOpaque(false);											 
		prompt.setFont(new Font("楷书",Font.PLAIN+Font.BOLD,17));
		prompt.setForeground(Color.GRAY);
		southPanel.add(prompt);												   //放在面板容器的最左边
		
		//添加文本框
		inputYear.setOpaque(false);
		inputYear.setForeground(Color.ORANGE);
		inputYear.setCaretColor(Color.ORANGE);         						   //设置光标颜色
		inputYear.setFont(new Font("Arial",Font.ROMAN_BASELINE,20));
		inputYear.setToolTipText("年和月请用空格分开");							   //提示信息
		southPanel.add(inputYear);											   //放在面板容器的中间
		
		//添加确定按钮
		confirm.setBorderPainted(false);							   		   //边框不可见				
		confirm.setContentAreaFilled(false);						   	   	   //透明
		confirm.setIcon(new ImageIcon("./src/images/click.png"));			   //设置图标
		confirm.setToolTipText("点击确定");
		southPanel.add(confirm);											   //放在面板容器的最右边
		southPanel.setBounds(10, 410, 450, 50);								   //放在日历下面
		southPanel.setOpaque(false);
		layeredPane.add(southPanel, JLayeredPane.MODAL_LAYER);				   //加到层次面板中去
		
		//添加时钟组件
		time.setBounds(500, 90, 150, 50);									   //放在当前年月日信息的下边
		time.setForeground(Color.WHITE);
		time.setFont(new Font("Courier",Font.CENTER_BASELINE,28));
		layeredPane.add(time, JLayeredPane.MODAL_LAYER);
		DisplayTime displayTime=new DisplayTime();
		displayTime.start();												   //开启线程
		
		//添加闹钟组件
		alarm=new JButton();									   			   //新建"闹钟"的按钮
		alarm.setBorderPainted(false);							  			   //边框不可见				
		alarm.setContentAreaFilled(false);						  			   //透明
		alarm.setIcon(new ImageIcon("./src/images/alarm.png"));				   //设置图标
		alarm.setToolTipText("点击添加闹钟");
		alarm.setBounds(520,140,100,100);									   //位置居右中
		layeredPane.add(alarm, JLayeredPane.MODAL_LAYER);
		
		//添加更改背景图片按钮
		changeBackground=new JButton();
		changeBackground.setBorderPainted(false);							   //边框不可见				
		changeBackground.setContentAreaFilled(false);						   //透明
		changeBackground.setIcon(new ImageIcon("./src/images/changeBackground.png"));//设置图标
		changeBackground.setToolTipText("点击更改背景图案");
		changeBackground.setBounds(520, 300, 100, 100);						   //放在闹钟下面
		changeBackground.setOpaque(false);
		layeredPane.add(changeBackground, JLayeredPane.MODAL_LAYER);		   //加到层次面板中去
		
		nextMonthIcon.addActionListener(this);								   //为"下个月"按钮注册监听器
		previousMonthIcon.addActionListener(this);							   //为"上个月"按钮注册监听器
		confirm.addActionListener(this);							           //为"确定"按钮注册监听器
		alarm.addActionListener(this);										   //为"闹钟"按钮注册监听器
		changeBackground.addActionListener(this);							   //为"更改背景图案"注册监听器
		
		frame.add(layeredPane);												   //将层次面板加到总框架中去
		
		frame.setVisible(true);												   //设置可见
	}
	
	//实现接收操作事件的侦听器接口
	public void actionPerformed(ActionEvent e)
	{
		//点击的是上个月按钮
		if(e.getSource()==previousMonthIcon)
		{
			if(getShowMonth()==1)       									   //1月为特殊情况
			{
				setShowMonth(12);											   //上个月即12月
				setShowYear(getShowYear()-1);								   //年数也要减一
				showDate.setYear(getShowYear());
				showDate.setMonth(12);
			}
			else
			{
				setShowMonth(getShowMonth()-1);               				   //其他情况直接月数减一
				showDate.setMonth(getShowMonth());
			}
			dayNum=showDate.getDayNum();									   //更新
			for(int i=0;i<42;++i)
			{
				allDay[i].setText(dayNum[i]);
			}
			message.setText(showDate.getYear()+"年"+showDate.getMonth()+"月");  //更新显示年月
			layeredPane.repaint();											   //刷新
		}
		//点击的是下个月按钮
		else if(e.getSource()==nextMonthIcon)
		{
			if(getShowMonth()==12)       									   //12月为特殊情况
			{
				setShowMonth(1);											   //下个月即1月
				setShowYear(getShowYear()+1);								   //年数也要加一
				showDate.setYear(getShowYear());
				showDate.setMonth(1);
			}
			else
			{
				setShowMonth(getShowMonth()+1);               				   //其他情况直接月数加一
				showDate.setMonth(getShowMonth());
			}
			dayNum=showDate.getDayNum();									   //更新
			for(int i=0;i<42;++i)
			{
				allDay[i].setText(dayNum[i]);
			}
			message.setText(showDate.getYear()+"年"+showDate.getMonth()+"月");  //更新显示年月
			layeredPane.repaint();											   //刷新
		}
		//点击的是确定按钮
		else if(e.getSource()==confirm)
		{
			String text=inputYear.getText();								   //获取文本框中的内容
			StringTokenizer str=new StringTokenizer(text," ");				   //以空格分隔年份和月份
			int yearAndMonth[]=new int[2];
			yearAndMonth[0]=getShowYear();
			yearAndMonth[1]=getShowMonth();
			for(int i=0;str.hasMoreTokens();++i)
			{
				if(i<2)														   //获取年份和月份
				{
					yearAndMonth[i]=Integer.parseInt(str.nextToken());
				}
				else
					break;
			}
			setShowYear(yearAndMonth[0]);									   //设置显示的年月
			setShowMonth(yearAndMonth[1]);
			showDate.setYear(getShowYear());
			showDate.setMonth(getShowMonth());
			dayNum=showDate.getDayNum();									   //更新
			for(int i=0;i<42;++i)
			{
				allDay[i].setText(dayNum[i]);
			}
			message.setText(showDate.getYear()+"年"+showDate.getMonth()+"月");  //更新显示年月
			layeredPane.repaint();											   //刷新
		}
		//点击的是闹钟按钮
		else if(e.getSource()==alarm)
		{
			Alarm alarm=new Alarm();										   //建立闹钟界面
		}
		//点击的是更改背景图案按钮
		else if(e.getSource()==changeBackground)
		{
			JFileChooser chooser=new JFileChooser();						   //建立文件选择器
			chooser.setFileSelectionMode(JFileChooser.FILES_AND_DIRECTORIES);  //指示显示文件和目录
			chooser.setCurrentDirectory(new File("."));						   //以当前目录生成一个文件目录实例，然后设置为当前的工作目录
			chooser.setFileFilter(new FileFilter()
					{
						public boolean accept(File file)					   //设置可接受的文件类型
						{
							String fileName=file.getName().toLowerCase();
							return fileName.endsWith(".jpg")||
									fileName.endsWith(".jpeg")||
									fileName.endsWith(".png")||
									fileName.endsWith(".gif")||
									file.isDirectory();
						}
						public String getDescription()						   //文件描述
						{
							return "图像文件(*.jpg,*.jpeg,*.png,*.gif)";
						}
					});
			if (chooser.showOpenDialog(this) == JFileChooser.APPROVE_OPTION)// 弹出文件选择器,并判断是否点击了打开按钮 
			{ 
			     String fileName = chooser.getSelectedFile().getAbsolutePath();//得到选择文件或目录的绝对路径
			     ImageIcon newImage=new ImageIcon(fileName);				   //以选择的图像文件建立一个新的ImageIcon
			     imageIcon.setImage(newImage.getImage());					   //设置新背景图
			}
		}
	}
}
