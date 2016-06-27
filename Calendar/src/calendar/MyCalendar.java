package calendar;

import java.util.Calendar;
//日历类
public class MyCalendar 
{
	int year;
	int month;
	int day;
	
	//各种构造方法
	public MyCalendar()
	{
		Calendar c=Calendar.getInstance(); //获取当前日历
		year=c.get(Calendar.YEAR);         //获取当前年份
		month=c.get(Calendar.MONTH)+1;     //获取当前月份
		day=c.get(Calendar.DATE);          //获取当前天数
	}
	public MyCalendar(int year,int month)
	{
		setYear(year);
		setMonth(month);
	}
	public MyCalendar(int year,int month,int day)
	{
		setYear(year);
		setMonth(month);
		setDay(day);
	}
	
	//Setter和Getter方法
	public void setYear(int year)
	{
		this.year=year;
	}
	public int getYear() 
	{
		return year;
	}
	public void setMonth(int month) 
	{
		this.month = month;
	}
	public int getMonth() 
	{
		return month;
	}
	public int getDay() {
		return day;
	}
	public void setDay(int day) {
		this.day = day;
	}
	
	//获取某一月份的所有天并存在一个数组里
	public String[] getDayNum()
	{
		String allDay[]=new String[42];							 //存放这个月份的所有天
		Calendar calendar=Calendar.getInstance();
		calendar.set(year,month-1,1);							 //设置为要求的日期
		int day1_frist_week=calendar.get(Calendar.DAY_OF_WEEK)-1;//第一天在第一周中的位置
		int dayNum=calendar.getActualMaximum(Calendar.DATE);     //获取这个月份的总天数
		for(int i=day1_frist_week;i<day1_frist_week+dayNum;++i)  //设置这个月的所有天
		{
			allDay[i]=String.valueOf(i-day1_frist_week+1);
		}
		return allDay;
	}
}
