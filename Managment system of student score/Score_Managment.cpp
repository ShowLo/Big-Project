//Score_Managment.cpp��Ÿ��෽����ʵ�ּ����ֺ����Ķ���
#include <iostream>
#include <iomanip>
#include<fstream>
#include "Score_Managment.h"
using namespace std;
//�������Course�๹�캯������
Course::Course(char *cour, int c,int c_n, int c_t) :credit(c),course_number(c_n),course_time(c_t)
{                                                                                  //������ʼ�����ʼ�����ݳ�Ա
	strcpy_s(course_title, strlen(cour)+1,cour);
}
void Course::SetCourse_title(char *cour_nam)                                       //�������ÿγ����ƣ�cour_namΪ�¿γ�����
{
	strcpy_s(course_title, strlen(cour_nam)+1,cour_nam);
}
void Course::SetCredit(int cred)                                                   //�������ÿγ�ѧ�֣�credΪ��ѧ��
{
	credit = cred;
}
void Course::SetCourse_number(int c_n)                                             //�������ÿγ���ţ�c_nΪ�����
{
	course_number=c_n;
}
void Course::SetCourse_time(int c_t)                                               //�������ÿγ�ѧʱ��c_tΪ��ѧʱ
{
	course_time=c_t;
}
char* Course::GetCourse_title()                                                    //���ؿγ�����
{
	return course_title;
}
int Course::GetCredit()                                                            //���ؿγ�ѧ��
{
	return credit;
}
int Course::GetCourse_number()                                                     //���ؿγ����
{
	return course_number;
}
int Course::GetCourse_time()                                                        //����ѧʱ
{
	return course_time;
}

//������Score�๹�캯������
Score::Score(float s,char *cour, int c, int c_n, int c_t) : score(s), Course(cour, c, c_n, c_t) //�ò����ĳ�ʼ��������ݳ�Ա��ʼ��
{                                                                                                                               
	if (s >= 90)
		rank = 'A';
	if (s >= 80 && s< 90)
		rank = 'B';
	if (s >= 60 && s < 80)
		rank = 'C';
	if (s < 60)
		rank = 'D';
}
void Score::display() const
{   
	cout << "|" << setw(4) << score << setw(3)<<"|" <<setw(4)<<rank <<setw(3)<<"|" <<setw(4)<<score_ranking<<setw(3)<<"|"<< endl;
}
void Score::SetScore(float ss)                        //�������÷�����ssΪ�·���
{
	score = ss;
	if (ss >= 90)
	{
		rank = 'A';
		pass_or_not = 'Y';
	}
	else if (ss >= 80 && ss < 90)
	{
		rank = 'B';
		pass_or_not = 'Y';
	}
	else if (ss >= 60 && ss < 80)
	{
		rank = 'C';
		pass_or_not = 'Y';
	}
	else if (ss < 60)
	{
		rank = 'D';
		pass_or_not = 'N';
	}
}
float Score::GetScore()                            //���ط���
{
	return score;
}
char Score::GetRank()                             //���ط����ȼ�
{
	return rank;
}
char Score::GetPass_or_not()
{
	return pass_or_not;
}
void Score::SetScore_ranking(int ranking)         //���÷�������
{
	score_ranking = ranking;
}
int Score::GetScore_ranking()                     //���ط�������
{
	return score_ranking;
}

//������Student�๹�캯������
Student::Student(char *nam, long long num, char *cour, int c , int c_n, int c_t) :number(num), Course(cour, c, c_n, c_t)  
{                                                 //������ʼ�����ʼ�����ݳ�Ա
	strcpy_s(name, strlen(nam) + 1, nam);
}
void Student::display() const                     //���麯�������ٶ��壬Ϊ�������
{
	cout<<"|" <<setw(7)<< name <<setw(4)<<"|"<<setw(11)<< number<<" ";
}
void Student::SetName(char *nam)                  //��������������namΪ������
{
	strcpy_s(name, strlen(nam) + 1, nam);
}
void Student::SetNumber(long long num)            //��������ѧ�ţ�numΪ��ѧ��
{
	number = num;
}
void Student::SetGPA_ranking(int ranking)         //����GPA����
{
	GPA_ranking = ranking;
}
void Student::SetFall_num(int f_n)
{
	fall_num = f_n;
}
char* Student::GetName()                         //����ѧ������
{
	return name;
}
long long Student::GetNumber()                   //����ѧ��
{
	return number;
}
int Student::GetGPA_ranking()                    //����GPA����
{
	return GPA_ranking;
}
int Student::GetFall_num()                       //���عҿ���
{
	return fall_num;
}

//���ؼ̳е�������Information�๹�캯������
Information::Information(char *nam, long long num, char *cour, int c_n, int c_t, float s, int c) :
Student(nam, num, cour, c, c_n, c_t), Score(s, cour, c, c_n, c_t), Course(cour, c, c_n, c_t)      //������ʼ�����ʼ�����ݳ�Ա
{
	fall_num = 0;
}
void Information::display() const                                                                 //���麯�������ٶ��壬Ϊ�������
{
	cout << "|" << setw(7) << name << setw(3)<<"|" << setw(11) << number << setw(2)<<"|" << setw(9) << course_title << setw(4)<<"|"
		<< setw(10) << course_number << setw(4)<<"|" << setw(3) << course_time << setw(2)<<"|" << setw(4) << score <<setw(3)<< "|" << setw(3) << credit <<setw(3)<<"|"<< endl;
}
void Information::Set_GPA(float gpa)                                                              //����GPA
{
	GPA = gpa;
}
float Information::GetGPA()                                                                       //����GPA
{
	return GPA;
}
void Information::Set_bool(bool s_g)                                                              //���ò�������
{
	Set_GPA_or_not = s_g;
}
bool Information::Get_bool()                                                                      //���ز�������
{
	return Set_GPA_or_not;
}
void Information::SetFall_course(int f_c)                                                         //���ÿγ̹ҿ�����
{
	fall_course = f_c;
}
int Information::GetFall_course()                                                                 //���ؿγ̹ҿ�����
{
	return fall_course;
}
void Information::SetAverage_score(float a_s)                                                     //���ÿγ�ƽ����
{
	average_score = a_s;
}
float Information::GetAverage_score()                                                             //���ؿγ�ƽ����
{
	return average_score;
}
//���������������>>"����
istream& operator >>(istream& input, Information& Info)
{
	char nam[20];                                                                                 //�ֲ�����������ʱ����ѧ����Ϣ����Ϊʵ�Σ���ѧ����Ϣ�������г�Ա
	long long num;
	char cour[10];
	int cour_num;
	int cour_tim;
	float sco;
	int cred;
	cout << "������ѧ��������";                                                                     //���벿��
	input >> nam;
	Info.SetName(nam);
	cout << "������ѧ��ѧ�ţ�";
	input >> num;
	Info.SetNumber(num);
	cout << "������γ����ƣ�";
	input >> cour;
	Info.SetCourse_title(cour);
	cout << "������γ���ţ�";
	input >> cour_num;
	Info.SetCourse_number(cour_num);
	cout << "������γ�ѧʱ��";
	input >> cour_tim;
	Info.SetCourse_time(cour_tim);
	cout << "������ѧ��������";
	input >> sco;
	Info.SetScore(sco);
	cout << "������γ�ѧ�֣�";
	input >> cred;
	Info.SetCredit(cred);
	return input;
}

//���������и��������Ķ���
//��ӡ�����ͷ
void Display_title()
{
	cout << "|" << setw(6) << "ѧ������" << setw(2) << "|" << setw(8) << "ѧ��" << setw(5) << "|" << setw(10) << "�γ�����" << setw(3) << "|" << setw(11)
		<< "�γ����" << setw(3) << "|" << setw(3) << "ѧʱ" << setw(1) << "|" << setw(5) << "����" << setw(2) << "|" << setw(3) << "ѧ��" << setw(2) << "|" << endl;
}
//��ӡ���ܺ���
void Display_Function()
{
	cout.width(47);
	cout << "ѧ���ɼ�����ϵͳ" << endl;
	cout.width(47);
	cout << "1��¼��ѧ���ɼ���Ϣ" << endl;
	cout.width(47);
	cout << "2���޸�ѧ���ɼ���Ϣ" << endl;
	cout.width(47);
	cout << "3����ѯѧ���ɼ���Ϣ" << endl;
	cout.width(51);
	cout << "4��ͳ��ĳ����Ŀ�ɼ����" << endl;
	cout.width(46);
	cout << "5����ѯĳ��ѧ��GPA" << endl;
	cout.width(50);
	cout << "6��ͳ������ѧ��GPA����" << endl;
	cout.width(57);
	cout << "7����ѯĳ��ѧ���γ�δͨ�����" << endl;
	cout.width(63);
	cout << "8���鿴ĳ�ſγ̵�ƽ���ּ�δͨ�����" << endl;
	cout.width(39);
	cout << "9���˳�ϵͳ" << endl;
}
//��ǰ��������
void Input();
void Modify();
void Search();
void Statistics_subject();
void Search_GPA();
void Statistics_GPA();
void Fall_of_stu();
void Search_aver_fall();
//ѡ���ܺ���
void Choose_Function()                                                                                
{
	Display_Function();
	int choose_fun;
	cout << "������1~9��һ��������ѡ��һ��ܣ�";
	cin >> choose_fun;
	switch (choose_fun)                                                    //�����û��������ֵ�����Ӧ�ĺ���
	{
	case 1:Input(); break;
	case 2:Modify(); break;
	case 3:Search(); break;
	case 4:Statistics_subject(); break;
	case 5:Search_GPA(); break;
	case 6:Statistics_GPA(); break;
	case 7:Fall_of_stu(); break;
	case 8:Search_aver_fall(); break;
	case 9:cout << "ллʹ�ã���ӭ���ٴ�ʹ�á�" << endl; break;
	default:cout << "��������������1~9������!" << endl; Choose_Function();  //�û�����������������
	}
}
//¼�뺯��
void Input()                                                                                                                       
{
	int stu_num=0;                                                          //�������ѧ�����˴�
	Information *p = new Information;                                       //��̬����ռ���ѧ���ɼ���Ϣ
	ofstream outfile("Information.dat", ios::out | ios::app);               //��ѧ����Ϣ�������ļ���
	if (!outfile)                                                           //�����ʧ��
	{
		cerr << "����ʱ�ļ��򿪳���" << endl;
		exit(0);
	}
	bool continue_or_not = true;                                            //���������ж��Ƿ��������
	for (int i = 0; continue_or_not; i++)                                   //���벿��
	{
		stu_num++;                                                          //ÿִ��һ��������ѧ���˴μ�1
		cin >> *p;
		outfile << p->GetName() << " " << p->GetNumber() << " " << p->GetCourse_title() << " " << p->GetCourse_number() << " "
			<< p->GetCourse_time() << " " << p->GetScore() << " " << p->GetRank() << " " << p->GetCredit() << " ";
		outfile.clear();
		int choice_input;                                                   //�û�����������ѡ��������߷���
		cout << "�Ƿ�������룿����0�������˵����������ּ���������~^=^~" << endl;
		cin >> choice_input;
		if (choice_input != 0)
			continue_or_not = true;                                         //��������
		else
			continue_or_not = false;                                        //�������˵�
	}
	outfile.close();
	delete p;                                                               //ɾ����̬����ռ�
	int former_num;                                                         //ǰһ������ʱ��ѧ���˴Σ�Ҫ���һ��ʹ��ʱ�Ѿ���������ļ������б��������Ϊ0
	ifstream infiles("Stu_num.dat", ios::in);
	if (!infiles)                                                           //�����ʧ��
	{
		cerr << "����ʱ��Stu_num.dat�ļ������ԭ��ѧ���˴γ���" << endl;
		exit(0);
	}
	infiles >> former_num;                                                  //��ǰһ������ʱ��ѧ���˴θ�������
	infiles.close();
	ofstream outfiles("Stu_num.dat", ios::out);                             //���ܵ�ѧ���˴α������ļ���
	if (!outfiles)                                                          //�����ʧ��
	{
		cerr << "����ʱ�ļ��򿪳���" << endl;
		exit(0);
	}
	outfiles << (stu_num + former_num);                                     //����ļ���ԭ�е����ݣ����µ����˴α������ļ���
	outfiles.close();
	Choose_Function();                                                      //�������˵�
}
//��ȡѧ���˴κ���
void Read_Stu_num(char *process, int &stu_num)
{
	ifstream infiles("Stu_num.dat", ios::in);                               //���ļ��ж�ȡѧ���˴�
	if (!infiles)                                                           //�����ʧ��
	{
		cerr << process<<"ʱ���ļ�����ѧ���˴�ʱ����" << endl;
		exit(0);
	}
	infiles >> stu_num;                                                     //����ѧ���˴�
	infiles.close();
}
//������Ϣ����ʱ����ռ亯��
void Save_to_dynamic(char *process,int stu_num,Information *p)
{
	ifstream infile("Information.dat", ios::in);                            //���ļ��ж�ȡѧ����Ϣ
	if (!infile)                                                            //�����ʧ��
	{
		cerr << process<<"ʱ�ļ��򿪳���" << endl;
		exit(0);
	}
	char nam[20];                                                           //�ֲ�����������ʱ����ѧ����Ϣ
	long long num;
	char cour[10];
	int cour_num;
	int cour_tim;
	float sco;
	char rank;
	int cred;
	for (int i = 0; i < stu_num; i++)                                       //���ļ��б����ѧ����Ϣ�ȱ��浽��ʱ����Ŀռ���
	{
		infile >> nam;
		p[i].SetName(nam);
		infile >> num;
		p[i].SetNumber(num);
		infile >> cour;
		p[i].SetCourse_title(cour);
		infile >> cour_num;
		p[i].SetCourse_number(cour_num);
		infile >> cour_tim;
		p[i].SetCourse_time(cour_tim);
		infile >> sco;
		p[i].SetScore(sco);
		infile >> rank;
		infile >> cred;
		p[i].SetCredit(cred);
	}
	infile.close();
}
//�жϼ��������
void Continue_or_not(char *process, int &input)
{
	char Yes_or_Not;                                                        //�û�ѡ����ȷ���ʱ������ַ�
	bool Judge_Yes_or_Not = true;                                           //���������ж��û�������ȷ���

	for (int i = 0; Judge_Yes_or_Not; i++)
	{
		cout << "�Ƿ����" << process << "����Y��������N�������˵���";
		cin >> Yes_or_Not;
		if (Yes_or_Not == 'Y' || Yes_or_Not == 'y')                         //����
		{
			Judge_Yes_or_Not = false;
		}
		else if (Yes_or_Not == 'N' || Yes_or_Not == 'n')                    //�������˵�
		{
			input = 0;
			Judge_Yes_or_Not = false;
		}
		else                                                                //��������
		{
			Judge_Yes_or_Not = true;
		}
	}
}
//�޸ĺ���
void Modify()
{
	int stu_num;
	Read_Stu_num("�޸�", stu_num);
	Information *p = new Information[stu_num];                              //��̬����ռ��Դ��ѧ����Ϣ
	Save_to_dynamic("�޸�", stu_num, p);                                    //��ȡѧ����Ϣ����̬����ռ���
	int choose_nam_or_num;                                                  //����û���������ѡ��
	bool Input_judge = true;                                                //�����������ж�������ȷ���
	cout << "��ѡ��������ѧ�����޸�ѧ����Ϣ������1����������2����ѧ�ţ�";
	for (int i = 0; Input_judge; i++)                                       //�û���������ѡ���ж�����Ϸ����
	{
		cin >> choose_nam_or_num;
		if (!(choose_nam_or_num == 1 || choose_nam_or_num == 2))
			cout << "������������������1��2Ŷ=^-^=" << endl;
		else
			Input_judge = false;
	}
	if (choose_nam_or_num == 1)                                             //��ѧ������Ϊ�������޸�
	{
		char nam[20];                                                       //��ʱ����ѧ����Ϣ
		long long num;
		char cour[10];
		int cour_num;
		int cour_tim;
		float sco;
		int cred;
		int choose_input_name = 1;                                          //ϵͳ���޸�������ѧ��ʱ�û�ѡ������֣���0�����������ѧ������
		for (int i = 0; choose_input_name; i++)
		{
			cout << "������ѧ��������" << endl;
			cin >> nam;
			int Judge_existence = 0;                                        //����Judge_existence�жϸ�ѧ���Ƿ����
			for (int j = 0; j < stu_num; j++)
			{
				if (strcmp(p[j].GetName(), nam) == 0)                       //���ҵ���ѧ��Ȼ���޸���Ϣ
				{
					Judge_existence++;                                      //���ڸ�ѧ�������Judge_existence+1
					cout << "����Ҫ�޸ĵ�ѧ��ԭ������ϢΪ��" << endl;
					Display_title();
					p[j].display();                                         //��ʾ��Ҫ�޸�ѧ��ԭ������Ϣ
					int choose_of_modify;                                   //�û�����������ѡ����Ҫ�޸ĵ���Ϣ
					bool Judge_choose_modify = true;                        //���������ж��û�������ȷ���
					bool Judge_output = true;                               //���������ж��Ƿ�����޸ĺ����Ϣ
					for (int k = 0; Judge_choose_modify; k++)
					{
						cout << "��ѡ����Ҫ�޸ĵ�ѧ����Ϣ��1����ѧ�ţ�2����γ����ƣ�3����γ���ţ�4����ѧʱ��5���������6����ѧ�֣�0�����޸Ĵ�����Ϣ��";
						cin >> choose_of_modify;
						if (choose_of_modify == 0)                          //���޸Ĵ�����Ϣ����������Ϊfalse�������ظ��������
						{
							Judge_choose_modify = false;
							Judge_output = false;                           //��������Ϊ�٣�������޸ĺ����Ϣ����Ϊ��û���޸�
						}
						else if (choose_of_modify == 1)                     //�޸�ѧ�ţ�������ȷ���ʲ�������Ϊfalse�������ظ��������
						{
							Judge_choose_modify = false;
							cout << "���޸�ѧ�ţ�";
							cin >> num;
							p[j].SetNumber(num);
						}
						else if (choose_of_modify == 2)                     //�޸Ŀγ����ƣ�������ȷ���ʲ�������Ϊfalse�������ظ��������
						{
							Judge_choose_modify = false;
							cout << "���޸Ŀγ����ƣ�";
							cin >> cour;
							p[j].SetCourse_title(cour);
						}
						else if (choose_of_modify == 3)                     //�޸Ŀγ���ţ�������ȷ���ʲ�������Ϊfalse�������ظ��������
						{
							Judge_choose_modify = false;
							cout << "���޸Ŀγ���ţ�";
							cin >> cour_num;
							p[j].SetCourse_number(cour_num);
						}
						else if (choose_of_modify == 4)                     //�޸Ŀγ�ѧʱ��������ȷ���ʲ�������Ϊfalse�������ظ��������
						{
							Judge_choose_modify = false;
							cout << "���޸Ŀγ�ѧʱ��";
							cin >> cour_tim;
							p[j].SetCourse_time(cour_tim);
						}
						else if (choose_of_modify == 5)                     //�޸ķ�����������ȷ���ʲ�������Ϊfalse�������ظ��������
						{
							Judge_choose_modify = false;
							cout << "���޸ķ�����";
							cin >> sco;
							p[j].SetScore(sco);
						}
						else if (choose_of_modify == 6)                     //�޸Ŀγ�ѧ�֣�������ȷ���ʲ�������Ϊfalse�������ظ��������
						{
							Judge_choose_modify = false;
							cout << "���޸���Ӧ�γ�ѧ�֣�";
							cin >> cred;
							p[j].SetCredit(cred);
						}
						else                                                //������󣬹ʲ�������Ϊtrue���ظ��������
						{
							Judge_choose_modify = true;
							cout << "�Բ�����������>o<����������1~6��������"<<endl;
						}
					}
					if (Judge_output)                                       //�ж��Ƿ�����޸ĺ����Ϣ
					{
						cout << "�޸ĺ��ѧ����ϢΪ��" << endl;
						Display_title();
						p[j].display();
					}
				}
			}
			if (Judge_existence == 0)                                       //�����ڸ�ѧ��
			{
				cout << "�Բ���>~<�����ڸ�ѧ�����밴0�������˵������������ּ���������ѧ��������";
				cin >> choose_input_name;
			}
			else
			{
				ofstream outfile("Information.dat", ios::out);             //���ļ���ԭ���������Ϣ����պ��ٽ��޸ĺ��ѧ����Ϣ�������ļ���
				if (!outfile)                                              //�����ʧ��
				{
					cerr << "�޸���ɺ󱣴�ʱ�ļ��򿪳���" << endl;
					exit(0);
				}
				for (int i = 0; i < stu_num; i++)                          //��������
				{
					outfile << p[i].GetName() << " " << p[i].GetNumber() << " " << p[i].GetCourse_title() << " " << p[i].GetCourse_number() << " "
						<< p[i].GetCourse_time() << " " << p[i].GetScore() << " " << p[i].GetRank() << " " << p[i].GetCredit() << " ";
					outfile.clear();
				}
				outfile.close();                                           //�ر��ļ�
				Continue_or_not("�޸�", choose_input_name);                //�ж��Ƿ�����޸�
			}
		}
		delete p;                                                          //�������˵�֮ǰɾ����̬����ռ�
		if (choose_input_name == 0)                                        //�������˵�
			Choose_Function();
	}
	else if (choose_nam_or_num == 2)                                       //��ѧ��ѧ��Ϊ�������޸�
	{
		char nam[20];                                                      //��ʱ����ѧ����Ϣ
		long long num;
		char cour[10];
		int cour_num;
		int cour_tim;
		float sco;
		int cred;
		int choose_input_number = 1;                                       //ϵͳ���޸�ѧ�ŵ�ѧ��ʱ�û�ѡ������֣���0�����������ѧ��ѧ��
		for (int i = 0; choose_input_number; i++)
		{
			cout << "������ѧ��ѧ�ţ�" << endl;
			cin >> num;
			int Judge_existence = 0;                                       //����Judge_existence�жϸ�ѧ���Ƿ����
			for (int j = 0; j < stu_num; j++)
			{
				if (p[j].GetNumber()== num)                                //���ҵ���ѧ��Ȼ���޸���Ϣ
				{
					Judge_existence++;                                     //���ڸ�ѧ�������Judge_existence+1
					cout << "����Ҫ�޸ĵ�ѧ��ԭ������ϢΪ��" << endl;
					Display_title();
					p[j].display();                                        //��ʾ��Ҫ�޸�ѧ��ԭ������Ϣ
					int choose_of_modify;                                  //�û�����������ѡ����Ҫ�޸ĵ���Ϣ
					bool Judge_choose_modify = true;                       //���������ж��û�������ȷ���
					bool Judge_output=true;                                //���������ж��Ƿ�����޸ĺ����Ϣ
					for (int k = 0; Judge_choose_modify; k++)
					{
						cout << "��ѡ����Ҫ�޸ĵ�ѧ����Ϣ��1����������2����γ����ƣ�3����γ���ţ�4����ѧʱ��5���������6����ѧ�֣�0�����޸ģ�";
						cin >> choose_of_modify;
						if (choose_of_modify == 0)                         //���޸Ĵ�����Ϣ����������Ϊfalse�������ظ��������
						{
							Judge_choose_modify = false;
							Judge_output = false;                          //��������Ϊ�٣�������޸ĺ����Ϣ����Ϊ��û���޸�
						}
						else if (choose_of_modify == 1)                    //�޸�������������ȷ���ʲ�������Ϊfalse�������ظ��������
						{
							Judge_choose_modify = false;
							cout << "���޸�������";
							cin >> nam;
							p[j].SetName(nam);
						}
						else if (choose_of_modify == 2)                    //�޸Ŀγ����ƣ�������ȷ���ʲ�������Ϊfalse�������ظ��������
						{
							Judge_choose_modify = false;
							cout << "���޸Ŀγ����ƣ�";
							cin >> cour;
							p[j].SetCourse_title(cour);
						}
						else if (choose_of_modify == 3)                    //�޸Ŀγ���ţ�������ȷ���ʲ�������Ϊfalse�������ظ��������
						{
							Judge_choose_modify = false;
							cout << "���޸Ŀγ���ţ�";
							cin >> cour_num;
							p[j].SetCourse_number(cour_num);
						}
						else if (choose_of_modify == 4)                    //�޸Ŀγ�ѧʱ��������ȷ���ʲ�������Ϊfalse�������ظ��������
						{
							Judge_choose_modify = false;
							cout << "���޸Ŀγ�ѧʱ��";
							cin >> cour_tim;
							p[j].SetCourse_time(cour_tim);
						}
						else if (choose_of_modify == 5)                   //�޸ķ�����������ȷ���ʲ�������Ϊfalse�������ظ��������
						{
							Judge_choose_modify = false;
							cout << "���޸ķ�����";
							cin >> sco;
							p[j].SetScore(sco);
						}
						else if (choose_of_modify == 6)                   //�޸Ŀγ�ѧ�֣�������ȷ���ʲ�������Ϊfalse�������ظ��������
						{
							Judge_choose_modify = false;
							cout << "���޸���Ӧ�γ�ѧ�֣�";
							cin >> cred;
							p[j].SetCredit(cred);
						}
						else                                              //������󣬹ʲ�������Ϊtrue���ظ��������
						{
							Judge_choose_modify = true;
							cout << "�Բ����������� >o< ����������1~6��������" << endl;
						}
					}
					if (Judge_output)                                     //�ж��Ƿ�����޸ĺ����Ϣ
					{
						cout << "�޸ĺ��ѧ����ϢΪ��" << endl;
						Display_title();
						p[j].display();
					}
				}
			}
			if (Judge_existence == 0)                                    //�����ڸ�ѧ��
			{
				cout << "�Բ��� >~< �����ڸ�ѧ�����밴0�������˵������������ּ���������ѧ��ѧ�ţ�";
				cin >> choose_input_number;
			}
			else
			{
				ofstream outfile("Information.dat", ios::out);          //���ļ���ԭ���������Ϣ��պ��ٽ��޸ĺ��ѧ����Ϣ�������ļ���
				if (!outfile)                                           //�����ʧ��
				{
					cerr << "�޸���ɺ󱣴�ʱ�ļ��򿪳���" << endl;
					exit(0);
				}
				for (int i = 0; i < stu_num; i++)                       //��������
				{
					outfile << p[i].GetName() << " " << p[i].GetNumber() << " " << p[i].GetCourse_title() << " " << p[i].GetCourse_number() << " "
						<< p[i].GetCourse_time() << " " << p[i].GetScore() << " " << p[i].GetRank() << " " << p[i].GetCredit() << " ";
					outfile.clear();
				}
				outfile.close();                                        //�ر��ļ�
				Continue_or_not("�޸�", choose_input_number);           //�ж��Ƿ�����޸�
			}
		}
		delete p;                                                       //�������˵�֮ǰɾ����̬����ռ�
		if (choose_input_number == 0)                                   //�������˵�
			Choose_Function();
	}
}
//��ѯ����
void Search()
{
	int stu_num;
	Read_Stu_num("��ѯ", stu_num);                                      //��ȡѧ���˴�
	Information *p = new Information[stu_num];                          //��̬����ռ��Դ��ѧ����Ϣ
	Save_to_dynamic("��ѯ", stu_num, p);                                //��ȡѧ����Ϣ����̬����ռ�
	int choose_of_search;                                               //����û���������ѡ��
	bool Input_judge = true;                                            //�����������ж�������ȷ���
	cout << "��ѡ��������ѧ���Բ�ѯѧ����Ϣ������1����������2����ѧ�ţ�";
	for (int i = 0; Input_judge; i++)                                   //�û���������ѡ���ж�����Ϸ����
	{
		cin >> choose_of_search;
		if (!(choose_of_search == 1 || choose_of_search == 2))          //��������ظ�����
			cout << "������������������1��2Ŷ =^-^= " << endl;
		else                                                            //������ȷ����ѭ��
			Input_judge = false;
	}
	if (choose_of_search == 1)                                          //��ѧ��������ѯ
	{
		char nam[20];                                                   //�ֲ�����������ʱ����ѧ������
		int *pp = new int[stu_num];                                     //��̬����ռ��Դ�Ų��ҵ���ѧ���ڶ��������е�λ��
		int choose_input_name = 1;                                      //ϵͳ���޸�������ѧ��ʱ�û�ѡ������֣���0�����������ѧ������
		for (int i = 0; choose_input_name; i++)
		{
			cout << "������ѧ��������" << endl;
			cin >> nam;
			int Judge_existence = 0;                                    //����Judge_existence�жϸ�ѧ���Ƿ����
			for (int j = 0; j < stu_num; j++)
			{
				if (strcmp(p[j].GetName(), nam) == 0)                   //���ҵ���ѧ��Ȼ�������Ϣ
				{
					Judge_existence++;                                  //���ڸ�ѧ�������Judge_existence+1
					pp[Judge_existence - 1] = j;                        //��Ų��ҵ���ѧ���ڶ��������е�λ��
				}
			}
			if (Judge_existence == 0)                                   //�����ڸ�ѧ��
			{
				cout << "�Բ��� >~< �����ڸ�ѧ�����밴0�������˵������������ּ���������ѧ��������";
				cin >> choose_input_name;
			}
			else
			{
				int i, j, k, t;
				for (i = 0; i < Judge_existence - 1; i++)               //��ѡ������
				{
					k = i;
					for (j = i + 1; j < Judge_existence; j++)
					{
						if (p[pp[j]].GetScore() < p[pp[k]].GetScore())  //�������Ӹߵ�������
							k = j;
						else if (p[pp[j]].GetScore() == p[pp[k]].GetScore())   //������ͬʱ���γ���Ŵ�С��������
							if (p[pp[j]].GetCourse_number() < p[pp[k]].GetCourse_number())
								k = j;
					}
					t = pp[k];
					pp[k] = pp[i];
					pp[i] = t;
				}
				cout << "����Ҫ��ѯ��ѧ������ϢΪ��" << endl;
				Display_title();
				for (int i = 0; i < Judge_existence; i++)
					p[pp[i]].display();                                  //���ѧ����Ϣ
				Continue_or_not("��ѯ", choose_input_name);              //�ж��Ƿ������ѯ
			}
		}
		delete pp;                                                       //ɾ����̬����ռ�
		delete p;                                                        //�������˵�֮ǰɾ����̬����ռ�
		if (choose_input_name == 0)
			Choose_Function();                                           //�������˵�
	}
	else if (choose_of_search == 2)                                      //��ѧ��ѧ�Ų�ѯ
	{
       	long long num;                                                   //�ֲ�����������ʱ����ѧ��ѧ��
		int *pp = new int[stu_num];                                      //��̬����ռ��Դ�Ų��ҵ���ѧ���ڶ��������е�λ��
		int choose_input_number = 1;                                     //ϵͳ���޸�ѧ�ŵ�ѧ��ʱ�û�ѡ������֣���0�����������ѧ��ѧ��
		for (int i = 0; choose_input_number; i++)
		{
			cout << "������ѧ��ѧ�ţ�" << endl;
			cin >> num;
			int Judge_existence = 0;                                     //����Judge_existence�жϸ�ѧ���Ƿ����
			for (int j = 0; j < stu_num; j++)
			{
				if (p[j].GetNumber() == num)                             //���ҵ���ѧ��
				{
					Judge_existence++;                                   //���ڸ�ѧ�������Judge_existence+1
					pp[Judge_existence - 1] = j;                         //��Ų��ҵ���ѧ���ڶ��������е�λ��
				}
			}
			if (Judge_existence == 0)                                    //�����ڸ�ѧ��
			{
				cout << "�Բ��� >~< �����ڸ�ѧ�����밴0�������˵������������ּ���������ѧ��ѧ�ţ�";
				cin >> choose_input_number;
			}
			else
			{
				int i, j, k, t;
				for (i = 0; i < Judge_existence - 1; i++)                //��ѡ������
				{
					k = i;
					for (j = i + 1; j < Judge_existence; j++)
					{
						if (p[pp[j]].GetScore() < p[pp[k]].GetScore())   //�������ӵ͵�������
							k = j;
						else if (p[pp[j]].GetScore() == p[pp[k]].GetScore())    //������ͬ�İ��γ̺Ŵ�С��������
							if (p[pp[j]].GetCourse_number() < p[pp[k]].GetCourse_number())
								k = j;
					}
					t = pp[k];
					pp[k] = pp[i];
					pp[i] = t;
				}
				cout << "����Ҫ��ѯ��ѧ������ϢΪ��" << endl;
				Display_title();
				for (int i = 0; i < Judge_existence; i++)
					p[pp[i]].display();                                  //���ѧ����Ϣ
				Continue_or_not("��ѯ", choose_input_number);            //�ж��Ƿ������ѯ
			}
		}
		delete pp;                                                       //ɾ����̬����ռ�
		delete p;                                                        //�������˵�֮ǰɾ����̬����ռ�
		if (choose_input_number == 0)                                    //�������˵�
			Choose_Function();
	}
}
//ͳ�ƿ�Ŀ�ɼ��������
void Statistics_subject()
{
	int stu_num;
	Read_Stu_num("ͳ�ƿ�Ŀ�ɼ����", stu_num);                             //��ȡѧ���˴�
	Information *p = new Information[stu_num];                           //��̬����ռ��Դ��ѧ����Ϣ
	Save_to_dynamic("ͳ�ƿ�Ŀ�ɼ����", stu_num, p);                      //����ѧ����Ϣ����̬����ռ�
	int choose_title_number;                                             //����û�ѡ�������
	bool Judge_title_number = true;                                      //�ж��û��������ȷ��
	cout << "��������ͨ���γ����ƻ��ǿγ������ͳ�ƿ�Ŀ�ĳɼ������" << endl;
	for (int i = 0; Judge_title_number; i++)
	{
		cout << "��1����γ����ƣ���2����γ���ţ������룺";
		cin >> choose_title_number;
		if (choose_title_number == 1 || choose_title_number == 2)       //������ȷ������ѭ��
			Judge_title_number = false;
		else                                                            //�������󣬼�������
		{
			cout << "�������� >o< ����������Ŷ" << endl;
		}
	}
	if (choose_title_number == 1)
	{
		int *pp = new int[stu_num];                                    //��̬����ռ��Դ�Ų��ҵ��Ŀγ����ƶ�Ӧ���ڶ��������е�λ��
		int choose_input_title = 1;                                    //ϵͳ���޸ÿγ�����ʱ�û�ѡ������֣���0�����������γ�����
		for (int i = 0; choose_input_title; i++)
		{
			char cour[10];
			cout << "��������Ҫͳ�ƵĿ�Ŀ��";
			cin >> cour;
			int Judge_existence = 0;                                   //����Judge_existence�жϸÿγ������Ƿ����
			for (int j = 0; j < stu_num; j++)
			{
				if (strcmp(p[j].GetCourse_title(), cour) == 0)         //���ҵ��ÿγ�����
				{
					Judge_existence++;                                 //���ڸÿγ����������Judge_existence+1
					pp[Judge_existence - 1] = j;                       //��Ų��ҵ��Ŀγ����ƶ�Ӧ���ڶ��������е�λ��
				}
			}
			if (Judge_existence == 0)                                  //�����ڸÿγ�����
			{
				cout << "�Բ��� >~< �����ڸÿγ����ƣ��밴0�������˵������������ּ���������γ����ƣ�";
				cin >> choose_input_title;
			}
			else
			{
				int i, j, k, t;
				for (i = 0; i < Judge_existence - 1; i++)              //��ѡ������
				{
					k = i;
					for (j = i + 1; j < Judge_existence; j++)
					{
						if (p[pp[j]].GetScore() > p[pp[k]].GetScore()) //�������Ӹߵ�������
							k = j;
						else if (p[pp[j]].GetScore() == p[pp[k]].GetScore())      //������ͬ��ѧ�Ŵ�С��������
							if (p[pp[j]].GetNumber() < p[pp[k]].GetNumber())
								k = j;
					}
					t = pp[k];
					pp[k] = pp[i];
					pp[i] = t;
				}
				for (i = 0; i < Judge_existence; i++)                  //���÷�������
				{
					p[pp[0]].SetScore_ranking(1);                      //��һ��������ߣ���������Ϊ1
					if (i >= 1)
					{
						if (p[pp[i]].GetScore() == p[pp[i - 1]].GetScore())       //������ͬ��������ͬ
							p[pp[i]].SetScore_ranking(p[pp[i - 1]].GetScore_ranking());
						else
							p[pp[i]].SetScore_ranking(i + 1);
					}
				}
				int choose_output;                                      //����û�ѡ��������ʽ
				bool Judge_choose_output = true;                        //���������ж��û�������ȷ���
				for (i = 0; Judge_choose_output; i++)
				{
					cout << "��������Ҫ���������ʽ��1����ֻ����������ȼ���������2����ͬʱ�����ѧ��������ѧ�ţ�";
					cin >> choose_output;
					if (choose_output == 1 || choose_output == 2)      //������ȷ������ѭ��
						Judge_choose_output = false;
					else
						cout << "�������� >o< ��������������1��2Ŷ" << endl;
				}
				if (choose_output == 1)
				{
					Score *output_score = new Score[Judge_existence];  //��̬����ռ䣬����Score��ָ��
					cout << "| " << setw(3) << "����" << " | " << setw(2) << "�ȼ�" << " | " << setw(3) << "���� |" << endl;
					for (i = 0; i < Judge_existence; i++)
					{
						output_score[i] = p[pp[i]];
						output_score[i].display();                     //����Score���display()����
					}
					delete output_score;                               //ɾ������Ŀռ�
				}
				else if (choose_output == 2)
				{
					Score *output_score = new Score[Judge_existence];  //��̬����ռ䣬����Score��ָ��
					Student *output_student = new Student[Judge_existence];      //��̬����ռ䣬����Student��ָ��
					cout << "| ѧ������ |" << "    ѧ��    | " << setw(3) << "����" << " | " << setw(2) << "�ȼ�" << " | " << setw(3) << "���� |" << endl;
					for (i = 0; i < Judge_existence; i++)
					{
						output_score[i] = p[pp[i]];
						output_student[i] = p[pp[i]];
						output_student[i].display();                   //����Score���display()����
						output_score[i].display();                     //����Student���display()����
					}
				}
				Continue_or_not("ͳ��", choose_input_title);           //�ж��Ƿ����ͳ��
			}
		}
		delete pp;                                                     //ɾ����̬����ռ�
		delete p;                                                      //�������˵�֮ǰɾ����̬����ռ�
		if (choose_input_title == 0)
			Choose_Function();                                         //�������˵�
	}
	if (choose_title_number == 2)
	{
		int *pp = new int[stu_num];                                    //��̬����ռ��Դ�Ų��ҵ��Ŀγ���Ŷ�Ӧ���ڶ��������е�λ��
		int choose_input_number = 1;                                   //ϵͳ���޸ÿγ����ʱ�û�ѡ������֣���0�����������γ����
		for (int i = 0; choose_input_number; i++)
		{
			int cour_num;
			cout << "��������Ҫͳ�ƵĿ�Ŀ�Ŀγ���ţ�";
			cin >> cour_num;
			int Judge_existence = 0;                                  //����Judge_existence�жϸÿγ�����Ƿ����
			for (int j = 0; j < stu_num; j++)
			{
				if (p[j].GetCourse_number() == cour_num)              //���ҵ��ÿγ����
				{
					Judge_existence++;                                //���ڸÿγ����������Judge_existence+1
					pp[Judge_existence - 1] = j;                      //��Ų��ҵ��Ŀγ���Ŷ�Ӧ���ڶ��������е�λ��
				}
			}
			if (Judge_existence == 0)                                 //�����ڸÿγ����
			{
				cout << "�Բ��� >~< �����ڸÿγ���ţ��밴0�������˵������������ּ���������γ���ţ�";
				cin >> choose_input_number;
			}
			else
			{
				int i, j, k, t;
				for (i = 0; i < Judge_existence - 1; i++)             //��ѡ������
				{
					k = i;
					for (j = i + 1; j < Judge_existence; j++)
					{
						if (p[pp[j]].GetScore() > p[pp[k]].GetScore())       //�������Ӹߵ�������
							k = j;
						else if (p[pp[j]].GetScore() == p[pp[k]].GetScore()) //������ͬ�İ�ѧ�Ŵ�С��������
							if (p[pp[j]].GetNumber() < p[pp[k]].GetNumber())
								k = j;
					}
					t = pp[k];
					pp[k] = pp[i];
					pp[i] = t;
				}
				for (i = 0; i < Judge_existence; i++)                        //���÷�������
				{
					p[pp[0]].SetScore_ranking(1);                            //��һ��������ߣ���������Ϊ1
					if (i >= 1)
					{
						if (p[pp[i]].GetScore() == p[pp[i - 1]].GetScore())  //������ͬ��������ͬ
							p[pp[i]].SetScore_ranking(p[pp[i - 1]].GetScore_ranking());
						else
							p[pp[i]].SetScore_ranking(i + 1);
					}
				}
				int choose_output;                                           //����û�ѡ��������ʽ
				bool Judge_choose_output = true;                             //���������ж��û�������ȷ���
				for (i = 0; Judge_choose_output; i++)
				{
					cout << "��������Ҫ���������ʽ��1����ֻ����������ȼ���������2����ͬʱ�����ѧ��������ѧ�ţ�";
					cin >> choose_output;
					if (choose_output == 1 || choose_output == 2)            //������ȷ������ѭ��
						Judge_choose_output = false;
					else
						cout << "�������� >o< ��������������1��2Ŷ" << endl;
				}
				if (choose_output == 1)
				{
					Score *output_score = new Score[Judge_existence];        //��̬����ռ䣬����Score��ָ��
					cout << "| " << setw(3) << "����" << " | " << setw(2) << "�ȼ�" << " | " << setw(3) << "���� |" << endl;
					for (i = 0; i < Judge_existence; i++)
					{
						output_score[i] = p[pp[i]];
						output_score[i].display();                           //����Score���display()����
					}
					delete output_score;                                     //ɾ����̬����ռ�
				}
				else if (choose_output == 2)
				{
					Score *output_score = new Score[Judge_existence];        //��̬����ռ䣬����Score��ָ��
					Student *output_student = new Student[Judge_existence];  //��̬����ռ䣬����Student��ָ��
					cout << "| ѧ������ |" << "    ѧ��    | " << setw(3) << "����" << " | " << setw(2) << "�ȼ�" << " | " << setw(3) << "���� |" << endl;
					for (i = 0; i < Judge_existence; i++)
					{
						output_score[i] = p[pp[i]];
						output_student[i] = p[pp[i]];
						output_student[i].display();                        //����Score���display()����
						output_score[i].display();                          //����Student���display()����
					}
				}
				Continue_or_not("ͳ��", choose_input_number);               //�жϼ���ͳ�����
			}
		}
		delete pp;                                                         //ɾ����̬����ռ�
		delete p;                                                          //�������˵�֮ǰɾ����̬����ռ�
		if (choose_input_number == 0)
			Choose_Function();                                             //�������˵�
	}
}
//����GPA����
int Calculate_GPA(int stu_num, Information *p)
{
	int *n = new int[stu_num];                                            //��̬����ռ�
	int time = 0;                                                         //��ѧ�ų��ִ���
	int num_of_stu = 0;                                                   //ѧ������
	for (int i = 0; i < stu_num; i++)
	{
		time = 0;                                                         //ÿ�ζ�Ҫ��ʼ��Ϊ0
		float total_score = 0;                                            //�ܳɼ���ʼ��Ϊ0
		int total_credit = 0;                                             //��ѧ�ֳ�ʼΪ0
		if (p[i].Get_bool())                                              //�����ѧ��֮ǰû�м����GPA
		{
			num_of_stu++;                                                 //ѧ������+1
			for (int j = i; j < stu_num; j++)
			{
				if (p[j].GetNumber() == p[i].GetNumber())                 //�ҵ���ѧ��
				{
					total_score += p[j].GetScore()*p[j].GetCredit();
					total_credit += p[j].GetCredit();                     //������ѧ��
					n[time] = j;                                          //��Ÿ�ѧ�Ŷ�Ӧ���������е�λ��
					time++;                                               //���ִ���+1
					p[j].Set_bool(false);                                 //������������Ϊ�٣��´β����ظ��������ѧ��
				}
			}
			p[n[0]].Set_bool(true);                                       //��һ���Ĳ�����������Ϊ��
			for (int k = 0; k < time; k++)                                //����GPA
			{
				p[n[k]].Set_GPA(total_score / total_credit);
			}
		}
		else                                                              //�����ѧ��֮ǰ�Ѿ������GPA
		{
			for (int j = i; j >= 0; j--)
			{
				if (p[j].GetNumber() == p[i].GetNumber())                 //�ҵ���ѧ��
				{
					p[i].Set_GPA(p[j].GetGPA());                          //ѧ����ͬ��GPA����Ϊ��ͬ
				}
			}
		}
	}
	delete n;                                                             //ɾ����̬����ռ�
	return num_of_stu;                                                    //����ѧ�������������ظ�
}
//��ѯGPA����
void Search_GPA()
{
	int stu_num;
	Read_Stu_num("��ѯGPA", stu_num);                                     //��ȡѧ���˴�
	Information *p = new Information[stu_num];                           //��̬����ռ��Դ��ѧ����Ϣ
	Save_to_dynamic("��ѯGPA", stu_num, p);                              //����ѧ����Ϣ����̬����ռ�
	bool Judge_title_number = true;                                      //�ж��û��������ȷ��
	Calculate_GPA(stu_num, p);                                           //����GPA
	long long numb;                                                      //�û�����ѧ��
	bool times = true;                                                   //�ж��Ƿ������һ��
	bool input_num = true;                                               //�ж��Ƿ���ڴ�ѧ��
	int Judge_num = 1;                                                   //�û�ѡ��������Ƿ������˵�
	for (int i = 0; Judge_num; i++)
	{
		cout << "��������Ҫ��ѯ��ѧ�ţ�";
		cin >> numb;
		int j;
		for (j = 0,times=true; j<stu_num&&times; j++)
		{
			if (p[j].GetNumber() == numb)                                //�ҵ���ѧ�ţ�ֻ���һ��
			{
				cout << "��ѯ���Ϊ��" << endl;
				cout << "|ѧ������|" << "    ѧ��    |" << "  GPA  |"  << endl;
				cout << "|  " << setw(4) << p[j].GetName() << "  | " << setw(10) << p[j].GetNumber() << " |" << setw(7) << p[j].GetGPA() << "|" << endl;
				times = false;
			}
		}
		if (j==stu_num&&times==true)                                    //�����ڸ�ѧ��
		{
			cout << "�Բ��� >o< ϵͳ��û�����ѧ�ţ��밴0�������˵����������ּ��������룺";
			cin >> Judge_num;
		}
		else                                                            //���ڸ�ѧ��
		{
			cout << "�Ƿ������ѯ����0�������˵������������ּ�������ѯ��";
			cin >>Judge_num;
		}
	}
	delete p;                                                           //ɾ����̬����ռ�
	if (Judge_num == 0)
		Choose_Function();                                              //�������˵�
}
//ͳ��GPA��������
void Statistics_GPA()
{
	int stu_num;
	Read_Stu_num("ͳ��GPA����", stu_num);                               //��ȡѧ���˴�
	Information *p = new Information[stu_num];                         //��̬����ռ��Դ��ѧ����Ϣ
	Save_to_dynamic("ͳ��GPA����", stu_num, p);                         //��ѧ����Ϣ��������̬����ռ�
	bool Judge_title_number = true;                                    //�ж��û��������ȷ��
	int num_of_stu=Calculate_GPA(stu_num, p);                          //����GPA������ѧ������
	int *pp = new int[num_of_stu];                                     //��̬����ռ�
	for (int i = 0,j=0; i < stu_num; i++)
	{
		if (p[i].Get_bool())
		{
			pp[j] = i;                                                 //������������ѧ�Ŷ�Ӧ���������е�λ��
			j++;
		}
	}
	int i, j, k,t;
	for (i = 0; i < num_of_stu - 1; i++)
	{
		k = i;
		for (j = i + 1; j < num_of_stu; j++)
		{
			if (p[pp[j]].GetGPA() > p[pp[k]].GetGPA())                //��GPA�Ӹߵ�������
				k = j;
			else if (p[pp[j]].GetGPA() == p[pp[k]].GetGPA())          //GPA��ͬ�İ�ѧ�Ŵ�С��������
				if (p[pp[j]].GetNumber() < p[pp[k]].GetNumber())
					k = j;
		}
		t = pp[k];
		pp[k] = pp[i];
		pp[i] = t;
	}
	for (i = 0; i < num_of_stu; i++)                                  //����GPA����
	{
		p[pp[0]].SetGPA_ranking(1);                                   //��һ��GPA��ߣ���������Ϊ1
		if (i >= 1)
		{
			if (p[pp[i]].GetGPA() == p[pp[i - 1]].GetGPA())           //GPA��ͬ��������ͬ
				p[pp[i]].SetGPA_ranking(p[pp[i - 1]].GetGPA_ranking());
			else
				p[pp[i]].SetGPA_ranking(i + 1);
		}
	}
	if (num_of_stu > 0)                                               //ϵͳ����ѧ����Ϣ
	{
		cout << "GPA�������£�" << endl;
		cout <<  "|"<<setw(6)<<" ѧ������"<<setw(2)<<"|" <<setw(8)<< "ѧ��"<<setw(5)<<"|" << setw(5) << "GPA" << setw(3)<<"|" << setw(8) << "GPA����"<<setw(2)<<"|" << endl;
		for (i = 0; i < num_of_stu; i++)
		{
			cout <<  "|" << setw(7) << p[pp[i]].GetName() <<setw(4)<< "|" << setw(11) << p[pp[i]].GetNumber() <<setw(2)<< "|" << setw(7) << p[pp[i]].GetGPA() << "|" <<setw(5)<< p[pp[i]].GetGPA_ranking() <<setw(5)<<"|"<< endl;
		}
	}
	else                                                              //ϵͳ����ѧ����Ϣ
		cout << "�Բ��� >o< ϵͳ������ѧ����Ϣ" << endl;
	cout << "�밴������������˵� ^.^ :";
	delete pp;//ɾ����̬����ռ�
	delete p;                                                         //ɾ����̬����ռ�
	if (getchar() != -1)
	{
		getchar();
		Choose_Function();                                            //�������˵�
	}
}
//��ѯĳ��ѧ��δͨ���γ��������
void Fall_of_stu()
{
	int stu_num;
	Read_Stu_num("ͳ��GPA����", stu_num);                              //��ȡѧ���˴�
	Information *p = new Information[stu_num];                        //��̬����ռ��Դ��ѧ����Ϣ
	Save_to_dynamic("ͳ��GPA����", stu_num, p);                        //��ѧ����Ϣ��������̬����ռ�
	long long num;                                                    //�ֲ�����������ʱ����ѧ��ѧ��
	int *pp = new int[stu_num];                                       //��̬����ռ��Դ�Ų��ҵ���ѧ���ڶ��������е�λ��
	int choose_input_number = 1;                                      //ϵͳ���޸�ѧ�ŵ�ѧ��ʱ�û�ѡ������֣���0�����������ѧ������
	for (int i = 0; choose_input_number; i++)
	{
		cout << "������ѧ��ѧ�ţ�" << endl;
		cin >> num;
		int Judge_existence = 0;                                      //����Judge_existence�жϸ�ѧ���Ƿ����
		for (int j = 0; j < stu_num; j++)
		{
			if (p[j].GetNumber() == num)                              //���ҵ���ѧ��
			{
				Judge_existence++;                                    //���ڸ�ѧ�������Judge_existence+1
				pp[Judge_existence - 1] = j;                          //��Ų��ҵ���ѧ���ڶ��������е�λ��
			}
		}
		if (Judge_existence == 0)                                     //�����ڸ�ѧ��
		{
			cout << "�Բ��� >~< �����ڸ�ѧ�����밴0�������˵������������ּ���������ѧ��ѧ�ţ�";
			cin >> choose_input_number;
		}
		else
		{
			cout << "������ѯ��ѧ���ǣ�" << p[pp[0]].GetName() << " (ѧ�ţ�" << p[pp[0]].GetNumber() << ")" << endl;
			int i, j, k, t, no_pass = 0;
			for (int i = 0; i < Judge_existence; i++)                //����δͨ���γ���
			{
				if (p[pp[i]].GetPass_or_not() == 'N')
				{
					pp[no_pass] = pp[i];                             //��¼����ѧ��δͨ���γ̶�Ӧ���������е�λ��
					no_pass++;
				}
			}
			if (no_pass > 0)                                         //��δͨ���γ�
			{
				for (i = 0; i < no_pass; i++)
				{
					p[pp[i]].SetFall_num(no_pass);
				}
				for (i = 0; i < no_pass - 1; i++)                    //��ѡ������
				{
					k = i;
					for (j = i + 1; j < no_pass; j++)
					{
						if (p[pp[j]].GetScore() > p[pp[k]].GetScore())        //�������Ӹߵ�������
							k = j;
						else if (p[pp[j]].GetScore() == p[pp[k]].GetScore())  //������ͬ�İ��γ̺Ŵ�С��������
							if (p[pp[j]].GetCourse_number() < p[pp[k]].GetCourse_number())
								k = j;
					}
					t = pp[k];
					pp[k] = pp[i];
					pp[i] = t;
				}
				cout << "һ����" << p[pp[0]].GetFall_num() << "�ſγ�δͨ��������������£�" << endl;
				cout << "|" << setw(7) << "�γ�����" << setw(2) << "|" << setw(5) << "����" << setw(2) << "|" << endl;
				for (int i = 0; i < no_pass; i++)
				{
					cout << "|" << setw(8) << p[pp[i]].GetCourse_title() << setw(2) << "|" << setw(5) << p[pp[i]].GetScore() << setw(2) << "|" << endl;
				}
				Continue_or_not("��ѯ", choose_input_number);        //�ж��Ƿ������ѯ
			}
			else                                                    //û��δͨ���γ�
			{
				cout << "����ѧ��û��δͨ���γ̼�¼ ^_^ " << endl;
				cout << "�밴0�������˵����������ּ���������ѧ�ţ�";
				cin >> choose_input_number;
			}
		}
	}
	delete pp;                                                      //ɾ����̬����ռ�
	delete p;                                                       //�������˵�֮ǰɾ����̬����ռ�
	if (choose_input_number == 0)                                   //�������˵�
		Choose_Function();
}
//ͨ���γ����Ƽ���ƽ���ֺ���
float Average_score(char *title, int stu_num, Information *p)
{
	float total_score = 0;                                         //�ܷ�
	int total_stu = 0;                                             //������
	for (int i = 0; i < stu_num; i++)
	{
		if (strcmp(p[i].GetCourse_title(), title) == 0)
		{
			total_score += p[i].GetScore();                        //�����з�����ӵõ��ܷ�
			total_stu++;                                           //��������1
		}
	}
	if (total_stu != 0)                                            //���ڸÿγ���
		return (total_score / total_stu);                          //����ƽ����
	else                                                           //�����ڸÿγ���
		return -1;                                                 //����-1
}
//ͨ���γ���ż���ƽ���ֺ���
float Average_score(int cour_num, int stu_num, Information *p)
{
	float total_score = 0;                                         //�ܷ�
	int total_stu = 0;                                             //������
	for (int i = 0; i < stu_num; i++)
	{
		if (p[i].GetCourse_number() == cour_num)
		{
			total_score += p[i].GetScore();                        //�����з�����ӵõ��ܷ�
			total_stu++;                                           //��������1
		}
	}
	if (total_stu != 0)                                            //���ڸÿγ���
		return (total_score / total_stu);                          //����ƽ����
	else                                                           //�����ڸÿγ���
		return -1;                                                 //����-1
}
//��ѯ�γ�ƽ���ּ�δͨ���������
void Search_aver_fall()
{
	int stu_num;
	Read_Stu_num("ͳ��GPA����", stu_num);                           //��ȡѧ���˴�
	Information *p = new Information[stu_num];                     //��̬����ռ��Դ��ѧ����Ϣ
	Save_to_dynamic("ͳ��GPA����", stu_num, p);                     //��ѧ����Ϣ��������̬����ռ�
	int *pp = new int[stu_num];                                    //��̬����ռ��Դ�Ų��ҵ��Ŀγ��ڶ��������е�λ��
	int choose_title_number;
	bool Judge_title_number = true;
	for (int i = 0; Judge_title_number; i++)
	{
		cout << "��������Ҫͨ���γ����ƻ����ǿγ���Ų�ѯ������1��ʾ�γ����ƣ�����2��ʾ�γ����:";
		cin >> choose_title_number;
		if (choose_title_number == 1 || choose_title_number == 2)
			Judge_title_number = false;
	}
	if (choose_title_number == 1)
	{
		char title[10];                                            //�ֲ�����������ʱ����γ�����
		int choose_input_title = 1;                                //ϵͳ���޸ÿγ�����ʱ�û�ѡ������֣���0�����������γ�����
		for (int i = 0; choose_input_title; i++)
		{
			cout << "������γ����ƣ�" ;
			cin >> title;
			int Judge_existence = 0;                               //����Judge_existence�жϸÿγ��Ƿ����
			for (int j = 0; j < stu_num; j++)
			{
				if (strcmp(p[j].GetCourse_title(), title) == 0)    //���ҵ��ÿγ�
				{
					Judge_existence++;                             //���ڸÿγ������Judge_existence+1
					pp[Judge_existence - 1] = j;                   //��Ų��ҵ��Ŀγ��ڶ��������е�λ��
				}
			}
			if (Judge_existence == 0)                              //�����ڸÿγ�
			{
				cout << "�Բ��� >~< �����ڸÿγ����ƣ��밴0�������˵������������ּ���������γ����ƣ�";
				cin >> choose_input_title;
			}
			else
			{
				cout << "���ſγ�--" << p[pp[0]].GetCourse_title() << "��ƽ����Ϊ��" << Average_score(title, stu_num, p) << endl;
				int i, j, k, t, no_pass = 0;
				for (int i = 0; i < Judge_existence; i++)          //����δͨ���γ���
				{
					if (p[pp[i]].GetPass_or_not() == 'N')
					{
						pp[no_pass] = pp[i];                       //��¼�ÿγ�δͨ����ѧ����Ӧ���������е�λ��
						no_pass++;
					}
				}
				if (no_pass > 0)                                   //��δͨ���γ�
				{
					for (i = 0; i < no_pass; i++)
					{
						p[pp[i]].SetFall_course(no_pass);
					}
					for (i = 0; i < no_pass - 1; i++)              //��ѡ������
					{
						k = i;
						for (j = i + 1; j < no_pass; j++)
						{
							if (p[pp[j]].GetScore() > p[pp[k]].GetScore())           //�������Ӹߵ�������
								k = j;
							else if (p[pp[j]].GetScore() == p[pp[k]].GetScore())     //������ͬ�İ�ѧ�Ŵ�С��������
								if (p[pp[j]].GetNumber() < p[pp[k]].GetNumber())
									k = j;
						}
						t = pp[k];
						pp[k] = pp[i];
						pp[i] = t;
					}
					cout << "һ����" << p[pp[0]].GetFall_course() << "��ѧ��δͨ��������������£�" << endl;
					cout << "|" << setw(8) << "ѧ������" << setw(2) << "|" << setw(8) << "ѧ��" << setw(5) << "|" << setw(5) << "����" << setw(2) << "|" << endl;
					for (int i = 0; i < no_pass; i++)
					{
						cout << "|" << setw(8) << p[pp[i]].GetName() << setw(2) << "|" << setw(11) << p[pp[i]].GetNumber() << setw(2) << "|" << setw(4) << p[pp[i]].GetScore() << setw(3) << "|" << endl;
					}
					Continue_or_not("��ѯ", choose_input_title);                   //�ж��Ƿ������ѯ
				}
				else                                                              //û��δͨ���γ�
				{
					cout << "���ſγ�û��δͨ��ѧ�� ^_^ " << endl;
					cout << "�밴0�������˵����������ּ���������γ����ƣ�";
					cin >> choose_input_title;
				}
			}
		}
		delete pp;                                                                //ɾ����̬����ռ�
		delete p;                                                                 //�������˵�֮ǰɾ����̬����ռ�
		if (choose_input_title == 0)                                              //�������˵�
			Choose_Function();
	}
	else if (choose_title_number == 2)
	{
		int cour_num;                                                             //�ֲ�����������ʱ����γ����
		int choose_input_number = 1;                                              //ϵͳ���޸ÿγ����ʱ�û�ѡ������֣���0�����������γ����
		for (int i = 0; choose_input_number; i++)
		{
			cout << "������γ���ţ�";
			cin >> cour_num;
			int Judge_existence = 0;                                              //����Judge_existence�жϸÿγ��Ƿ����
			for (int j = 0; j < stu_num; j++)
			{
				if (p[j].GetCourse_number() == cour_num)                          //���ҵ��ÿγ�
				{
					Judge_existence++;                                            //���ڸÿγ������Judge_existence+1
					pp[Judge_existence - 1] = j;                                  //��Ų��ҵ��Ŀγ��ڶ��������е�λ��
				}
			}
			if (Judge_existence == 0)                                             //�����ڸÿγ�
			{
				cout << "�Բ��� >~< �����ڸÿγ���ţ��밴0�������˵������������ּ���������γ���ţ�";
				cin >> choose_input_number;
			}
			else
			{
				cout << "���ſγ�--" << p[pp[0]].GetCourse_title() << "��ƽ����Ϊ��" << Average_score(cour_num, stu_num, p) << endl;
				int i, j, k, t, no_pass = 0;
				for (int i = 0; i < Judge_existence; i++)                         //����δͨ���γ���
				{
					if (p[pp[i]].GetPass_or_not() == 'N')
					{
						pp[no_pass] = pp[i];                                      //��¼�ÿγ�δͨ����ѧ����Ӧ���������е�λ��
						no_pass++;
					}
				}
				if (no_pass > 0)                                                  //��δͨ���γ�
				{
					for (i = 0; i < no_pass; i++)
					{
						p[pp[i]].SetFall_course(no_pass);
					}
					for (i = 0; i < no_pass - 1; i++)                             //��ѡ������
					{
						k = i;
						for (j = i + 1; j < no_pass; j++)
						{
							if (p[pp[j]].GetScore() > p[pp[k]].GetScore())        //�������Ӹߵ�������
								k = j;
							else if (p[pp[j]].GetScore() == p[pp[k]].GetScore())  //������ͬ�İ�ѧ�Ŵ�С��������
								if (p[pp[j]].GetNumber() < p[pp[k]].GetNumber())
									k = j;
						}
						t = pp[k];
						pp[k] = pp[i];
						pp[i] = t;
					}
					cout << "һ����" << p[pp[0]].GetFall_course() << "��ѧ��δͨ��������������£�" << endl;
					cout << "|" << setw(8) << "ѧ������" << setw(2) << "|" << setw(8) << "ѧ��" << setw(5) << "|" << setw(5) << "����" << setw(2) << "|" << endl;
					for (int i = 0; i < no_pass; i++)
					{
						cout << "|" << setw(8) << p[pp[i]].GetName() << setw(2) << "|" << setw(11) << p[pp[i]].GetNumber() << setw(2) << "|" << setw(4) << p[pp[i]].GetScore() << setw(3) << "|" << endl;
					}
					Continue_or_not("��ѯ", choose_input_number);                    //�ж��Ƿ������ѯ
				}
				else                                                                //û��δͨ���γ�
				{
					cout << "���ſγ�û��δͨ��ѧ�� ^_^ " << endl;
					cout << "�밴0�������˵����������ּ���������γ���ţ�";
					cin >> choose_input_number;
				}
			}
		}
		delete pp;                                                                   //ɾ����̬����ռ�
		delete p;                                                                    //�������˵�֮ǰɾ����̬����ռ�
		if (choose_input_number == 0)                                                //�������˵�
			Choose_Function();
	}
}