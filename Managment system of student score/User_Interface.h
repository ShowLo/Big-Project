//ͷ�ļ�User_Interface.h��Ÿ��ֽ���ͼ��̲�������
#pragma once
#include <iostream>
#include <iomanip>
using namespace std;
void Display_Interface()                                                                                   //��ӡ��ʼ����
{
	cout.fill('*');
	cout <<setw(50)<< "��ӭ����ѧ���ɼ�����ϵͳ" <<setw(30)<<'*'<< endl;
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
void SetColor()                                                                                               //���ñ���ɫ��ǰ��ɫ
{
	char choose_background_color[2];                                                             //ѡ�񱳾�ɫ
	char choose_foreground_color[2];                                                              //ѡ��ǰ��ɫ
	bool Judge_background_color = true;                                                        //�ж�������ȷ���
	bool Judge_foreground_color = true;                                                         //�ж�������ȷ���
	cout << "��ѡ����ϲ���ı���ɫ��ǰ��ɫ ^o^ "<<endl;
	cout << "��ѡ�񱳾�ɫ" << endl; 
	cout<<"0--��ɫ��1--��ɫ��2--��ɫ��3--����ɫ��4--��ɫ��5--��ɫ��6--��ɫ��7--��ɫ��8--��ɫ��9--����ɫ��";
	for (int i = 0; Judge_background_color; i++)
	{
		cin >> choose_background_color;
		if (choose_background_color[0] < '0'|| choose_background_color[0]>'9') //���������ظ�����
		{
			cout << "�Բ��� >o< ��������������0~9��������";
		}
		else                                                                                                        //������ȷ������ѭ��
			Judge_background_color = false;
	}
	cout << "��ѡ��ǰ��ɫ" << endl;
	cout<<"A--����ɫ��B--��ǳ��ɫ��C--����ɫ��D--����ɫ��E--����ɫ��F--����ɫ��";
	for (int i = 0; Judge_foreground_color; i++)
	{
		cin >> choose_foreground_color;
		if (choose_foreground_color[0] < 'A' || choose_foreground_color[0]>'F')   //���������ظ�����
		{
			cout << "�Բ��� >o< ��������������A~F����ĸ��";
		}
		else                                                                                                       //������ȷ������ѭ��
			Judge_foreground_color = false;
	}
	char *color_num_word = new char[10];                                                      //��̬����ռ�
	memset(color_num_word, 0, sizeof(color_num_word));                               //��ʼ��
	char *num_word = new char[2];                                                                //��̬����ռ�
	memset(num_word, 0, sizeof(num_word));                                                 //��ʼ��
	num_word[0] = choose_background_color[0];
	num_word[1] = choose_foreground_color[0];
	char *color="color ";
	strcat_s(color_num_word, strlen(color) + 1, color);                                       //�����ַ���
	strcat_s(color_num_word, strlen(color_num_word)+strlen(num_word) + 1, num_word);
	system(color_num_word);                                                                          //ʵ�ֱ���ɫ��ǰ��ɫ�ĸı�
}
//�������õ��ĺ���������
void Choose_Function();