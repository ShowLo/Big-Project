//头文件User_Interface.h存放各种界面和键盘操作函数
#pragma once
#include <iostream>
#include <iomanip>
using namespace std;
void Display_Interface()                                                                                   //打印开始界面
{
	cout.fill('*');
	cout <<setw(50)<< "欢迎进入学生成绩管理系统" <<setw(30)<<'*'<< endl;
	cout.fill(' ');
	cout << setw(30) << "*" << setw(3) << "*" << setw(2) << "*" << setw(6) << "*" << setw(2) << "*" << setw(3) << "*" << endl;
	cout << setw(28) << "*" << setw(9) << "*" << setw(2) << "*" << setw(9) << "*" << endl;
	cout << setw(27) << "*" << setw(11) << "*" << setw(11) << "*" << endl;
	cout << setw(27) << "*" << setw(22) << "*" << endl;
	cout << setw(27) << "*" << setw(22) << "*" << endl;
	cout << setw(28) << "*" << setw(20) << "*" << endl;
	cout << setw(29) << "*" << setw(18) << "*" << endl;
	cout << setw(30) << "*" << setw(16) << "*" << endl;
	cout << setw(32) << "*" << setw(12) << "*" << endl;
	cout << setw(34) << "*" << setw(8) << "*" << endl;
	cout << setw(36) << "*" << setw(4) << "*" << endl;
	cout << setw(38) << "*" << endl << endl;
}
void SetColor()                                                                                               //设置背景色及前景色
{
	char choose_background_color[2];                                                             //选择背景色
	char choose_foreground_color[2];                                                              //选择前景色
	bool Judge_background_color = true;                                                        //判断输入正确与否
	bool Judge_foreground_color = true;                                                         //判断输入正确与否
	cout << "请选择您喜欢的背景色及前景色 ^o^ "<<endl;
	cout << "请选择背景色" << endl; 
	cout<<"0--黑色，1--蓝色，2--绿色，3--湖蓝色，4--红色，5--紫色，6--黄色，7--白色，8--灰色，9--淡蓝色：";
	for (int i = 0; Judge_background_color; i++)
	{
		cin >> choose_background_color;
		if (choose_background_color[0] < '0'|| choose_background_color[0]>'9') //输入有误，重复输入
		{
			cout << "对不起 >o< 输入有误，请输入0~9的整数：";
		}
		else                                                                                                        //输入正确，跳出循环
			Judge_background_color = false;
	}
	cout << "请选择前景色" << endl;
	cout<<"A--淡绿色，B--淡浅绿色，C--淡红色，D--淡紫色，E--淡黄色，F--亮白色：";
	for (int i = 0; Judge_foreground_color; i++)
	{
		cin >> choose_foreground_color;
		if (choose_foreground_color[0] < 'A' || choose_foreground_color[0]>'F')   //输入有误，重复输入
		{
			cout << "对不起 >o< 输入有误，请输入A~F的字母：";
		}
		else                                                                                                       //输入正确，跳出循环
			Judge_foreground_color = false;
	}
	char *color_num_word = new char[10];                                                      //动态申请空间
	memset(color_num_word, 0, sizeof(color_num_word));                               //初始化
	char *num_word = new char[2];                                                                //动态申请空间
	memset(num_word, 0, sizeof(num_word));                                                 //初始化
	num_word[0] = choose_background_color[0];
	num_word[1] = choose_foreground_color[0];
	char *color="color ";
	strcat_s(color_num_word, strlen(color) + 1, color);                                       //连接字符串
	strcat_s(color_num_word, strlen(color_num_word)+strlen(num_word) + 1, num_word);
	system(color_num_word);                                                                          //实现背景色及前景色的改变
}
//主函数用到的函数的声明
void Choose_Function();