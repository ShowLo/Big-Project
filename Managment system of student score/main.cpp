//�������ļ�main.cpp
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#pragma comment(lib,"winmm.lib")
#include "Score_Managment.h"
#include "User_Interface.h"
using namespace std;
//������
int main()
{
	PlaySound(TEXT("���֮��.wav"), NULL, SND_FILENAME | SND_ASYNC|SND_LOOP);         //Ϊʹ��ʹ�����кõ�ʹ�����飬ѭ����������
	SetColor();                                                                                                                        //���ñ���ɫ��ǰ��ɫ
	Display_Interface();                                                             //��ӡ����
	Choose_Function();                                                               //ѡ����
	cout << endl;
	system("pause 0");
	return 0;
}