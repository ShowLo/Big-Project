//主程序文件main.cpp
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#pragma comment(lib,"winmm.lib")
#include "Score_Managment.h"
#include "User_Interface.h"
using namespace std;
//主函数
int main()
{
	PlaySound(TEXT("天空之城.wav"), NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);         //为使得使用者有好的使用心情，循环播放音乐
	SetColor();                                                                                                                        //设置背景色及前景色
	Display_Interface();                                                             //打印封面
	Choose_Function();                                                               //选择功能
	cout << endl;
	system("pause 0");
	return 0;
}