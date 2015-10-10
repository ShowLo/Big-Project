//Score_Managment.cpp存放各类方法的实现及各种函数的定义
#include <iostream>
#include <iomanip>
#include<fstream>
#include "Score_Managment.h"
using namespace std;
//抽象基类Course类构造函数定义
Course::Course(char *cour, int c,int c_n, int c_t) :credit(c),course_number(c_n),course_time(c_t)
{                                                                                  //参数初始化表初始化数据成员
	strcpy_s(course_title, strlen(cour)+1,cour);
}
void Course::SetCourse_title(char *cour_nam)                                       //重新设置课程名称，cour_nam为新课程名称
{
	strcpy_s(course_title, strlen(cour_nam)+1,cour_nam);
}
void Course::SetCredit(int cred)                                                   //重新设置课程学分，cred为新学分
{
	credit = cred;
}
void Course::SetCourse_number(int c_n)                                             //重新设置课程序号，c_n为新序号
{
	course_number=c_n;
}
void Course::SetCourse_time(int c_t)                                               //重新设置课程学时，c_t为新学时
{
	course_time=c_t;
}
char* Course::GetCourse_title()                                                    //返回课程名称
{
	return course_title;
}
int Course::GetCredit()                                                            //返回课程学分
{
	return credit;
}
int Course::GetCourse_number()                                                     //返回课程序号
{
	return course_number;
}
int Course::GetCourse_time()                                                        //返回学时
{
	return course_time;
}

//派生类Score类构造函数定义
Score::Score(float s,char *cour, int c, int c_n, int c_t) : score(s), Course(cour, c, c_n, c_t) //用参数的初始化表对数据成员初始化
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
void Score::SetScore(float ss)                        //重新设置分数，ss为新分数
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
float Score::GetScore()                            //返回分数
{
	return score;
}
char Score::GetRank()                             //返回分数等级
{
	return rank;
}
char Score::GetPass_or_not()
{
	return pass_or_not;
}
void Score::SetScore_ranking(int ranking)         //设置分数排名
{
	score_ranking = ranking;
}
int Score::GetScore_ranking()                     //返回分数排名
{
	return score_ranking;
}

//派生类Student类构造函数定义
Student::Student(char *nam, long long num, char *cour, int c , int c_n, int c_t) :number(num), Course(cour, c, c_n, c_t)  
{                                                 //参数初始化表初始化数据成员
	strcpy_s(name, strlen(nam) + 1, nam);
}
void Student::display() const                     //对虚函数进行再定义，为输出函数
{
	cout<<"|" <<setw(7)<< name <<setw(4)<<"|"<<setw(11)<< number<<" ";
}
void Student::SetName(char *nam)                  //重新设置姓名，nam为新姓名
{
	strcpy_s(name, strlen(nam) + 1, nam);
}
void Student::SetNumber(long long num)            //重新设置学号，num为新学号
{
	number = num;
}
void Student::SetGPA_ranking(int ranking)         //设置GPA排名
{
	GPA_ranking = ranking;
}
void Student::SetFall_num(int f_n)
{
	fall_num = f_n;
}
char* Student::GetName()                         //返回学生姓名
{
	return name;
}
long long Student::GetNumber()                   //返回学号
{
	return number;
}
int Student::GetGPA_ranking()                    //返回GPA排名
{
	return GPA_ranking;
}
int Student::GetFall_num()                       //返回挂科数
{
	return fall_num;
}

//多重继承的派生类Information类构造函数定义
Information::Information(char *nam, long long num, char *cour, int c_n, int c_t, float s, int c) :
Student(nam, num, cour, c, c_n, c_t), Score(s, cour, c, c_n, c_t), Course(cour, c, c_n, c_t)      //参数初始化表初始化数据成员
{
	fall_num = 0;
}
void Information::display() const                                                                 //对虚函数进行再定义，为输出函数
{
	cout << "|" << setw(7) << name << setw(3)<<"|" << setw(11) << number << setw(2)<<"|" << setw(9) << course_title << setw(4)<<"|"
		<< setw(10) << course_number << setw(4)<<"|" << setw(3) << course_time << setw(2)<<"|" << setw(4) << score <<setw(3)<< "|" << setw(3) << credit <<setw(3)<<"|"<< endl;
}
void Information::Set_GPA(float gpa)                                                              //设置GPA
{
	GPA = gpa;
}
float Information::GetGPA()                                                                       //返回GPA
{
	return GPA;
}
void Information::Set_bool(bool s_g)                                                              //设置布尔变量
{
	Set_GPA_or_not = s_g;
}
bool Information::Get_bool()                                                                      //返回布尔变量
{
	return Set_GPA_or_not;
}
void Information::SetFall_course(int f_c)                                                         //设置课程挂科人数
{
	fall_course = f_c;
}
int Information::GetFall_course()                                                                 //返回课程挂科人数
{
	return fall_course;
}
void Information::SetAverage_score(float a_s)                                                     //设置课程平均分
{
	average_score = a_s;
}
float Information::GetAverage_score()                                                             //返回课程平均分
{
	return average_score;
}
//定义重载运算符”>>"函数
istream& operator >>(istream& input, Information& Info)
{
	char nam[20];                                                                                 //局部变量用以临时输入学生信息并作为实参，将学生信息传给类中成员
	long long num;
	char cour[10];
	int cour_num;
	int cour_tim;
	float sco;
	int cred;
	cout << "请输入学生姓名：";                                                                     //输入部分
	input >> nam;
	Info.SetName(nam);
	cout << "请输入学生学号：";
	input >> num;
	Info.SetNumber(num);
	cout << "请输入课程名称：";
	input >> cour;
	Info.SetCourse_title(cour);
	cout << "请输入课程序号：";
	input >> cour_num;
	Info.SetCourse_number(cour_num);
	cout << "请输入课程学时：";
	input >> cour_tim;
	Info.SetCourse_time(cour_tim);
	cout << "请输入学生分数：";
	input >> sco;
	Info.SetScore(sco);
	cout << "请输入课程学分：";
	input >> cred;
	Info.SetCredit(cred);
	return input;
}

//主函数体中各个函数的定义
//打印输出表头
void Display_title()
{
	cout << "|" << setw(6) << "学生姓名" << setw(2) << "|" << setw(8) << "学号" << setw(5) << "|" << setw(10) << "课程名称" << setw(3) << "|" << setw(11)
		<< "课程序号" << setw(3) << "|" << setw(3) << "学时" << setw(1) << "|" << setw(5) << "分数" << setw(2) << "|" << setw(3) << "学分" << setw(2) << "|" << endl;
}
//打印功能函数
void Display_Function()
{
	cout.width(47);
	cout << "学生成绩管理系统" << endl;
	cout.width(47);
	cout << "1、录入学生成绩信息" << endl;
	cout.width(47);
	cout << "2、修改学生成绩信息" << endl;
	cout.width(47);
	cout << "3、查询学生成绩信息" << endl;
	cout.width(51);
	cout << "4、统计某个科目成绩情况" << endl;
	cout.width(46);
	cout << "5、查询某个学生GPA" << endl;
	cout.width(50);
	cout << "6、统计所有学生GPA排名" << endl;
	cout.width(57);
	cout << "7、查询某个学生课程未通过情况" << endl;
	cout.width(63);
	cout << "8、查看某门课程的平均分及未通过情况" << endl;
	cout.width(39);
	cout << "9、退出系统" << endl;
}
//提前引用声明
void Input();
void Modify();
void Search();
void Statistics_subject();
void Search_GPA();
void Statistics_GPA();
void Fall_of_stu();
void Search_aver_fall();
//选择功能函数
void Choose_Function()                                                                                
{
	Display_Function();
	int choose_fun;
	cout << "请输入1~9的一个数字以选择一项功能：";
	cin >> choose_fun;
	switch (choose_fun)                                                    //根据用户输入数字调用相应的函数
	{
	case 1:Input(); break;
	case 2:Modify(); break;
	case 3:Search(); break;
	case 4:Statistics_subject(); break;
	case 5:Search_GPA(); break;
	case 6:Statistics_GPA(); break;
	case 7:Fall_of_stu(); break;
	case 8:Search_aver_fall(); break;
	case 9:cout << "谢谢使用！欢迎您再次使用。" << endl; break;
	default:cout << "输入有误！请输入1~9的整数!" << endl; Choose_Function();  //用户输入有误，重新输入
	}
}
//录入函数
void Input()                                                                                                                       
{
	int stu_num=0;                                                          //存放输入学生的人次
	Information *p = new Information;                                       //动态申请空间存放学生成绩信息
	ofstream outfile("Information.dat", ios::out | ios::app);               //将学生信息保存在文件里
	if (!outfile)                                                           //如果打开失败
	{
		cerr << "输入时文件打开出错！" << endl;
		exit(0);
	}
	bool continue_or_not = true;                                            //布尔变量判断是否继续输入
	for (int i = 0; continue_or_not; i++)                                   //输入部分
	{
		stu_num++;                                                          //每执行一次输入则学生人次加1
		cin >> *p;
		outfile << p->GetName() << " " << p->GetNumber() << " " << p->GetCourse_title() << " " << p->GetCourse_number() << " "
			<< p->GetCourse_time() << " " << p->GetScore() << " " << p->GetRank() << " " << p->GetCredit() << " ";
		outfile.clear();
		int choice_input;                                                   //用户输入数字以选择继续或者返回
		cout << "是否继续输入？输入0返回主菜单，其他数字键继续输入~^=^~" << endl;
		cin >> choice_input;
		if (choice_input != 0)
			continue_or_not = true;                                         //继续输入
		else
			continue_or_not = false;                                        //返回主菜单
	}
	outfile.close();
	delete p;                                                               //删除动态申请空间
	int former_num;                                                         //前一次输入时的学生人次，要求第一次使用时已经存在这个文件且其中保存的数字为0
	ifstream infiles("Stu_num.dat", ios::in);
	if (!infiles)                                                           //如果打开失败
	{
		cerr << "输入时打开Stu_num.dat文件以输出原来学生人次出错！" << endl;
		exit(0);
	}
	infiles >> former_num;                                                  //将前一次输入时的学生人次赋给变量
	infiles.close();
	ofstream outfiles("Stu_num.dat", ios::out);                             //将总的学生人次保存在文件里
	if (!outfiles)                                                          //如果打开失败
	{
		cerr << "输入时文件打开出错！" << endl;
		exit(0);
	}
	outfiles << (stu_num + former_num);                                     //清空文件中原有的内容，将新的总人次保存在文件里
	outfiles.close();
	Choose_Function();                                                      //返回主菜单
}
//读取学生人次函数
void Read_Stu_num(char *process, int &stu_num)
{
	ifstream infiles("Stu_num.dat", ios::in);                               //从文件中读取学生人次
	if (!infiles)                                                           //如果打开失败
	{
		cerr << process<<"时打开文件读入学生人次时出错！" << endl;
		exit(0);
	}
	infiles >> stu_num;                                                     //读入学生人次
	infiles.close();
}
//保存信息至临时申请空间函数
void Save_to_dynamic(char *process,int stu_num,Information *p)
{
	ifstream infile("Information.dat", ios::in);                            //从文件中读取学生信息
	if (!infile)                                                            //如果打开失败
	{
		cerr << process<<"时文件打开出错！" << endl;
		exit(0);
	}
	char nam[20];                                                           //局部变量用以临时输入学生信息
	long long num;
	char cour[10];
	int cour_num;
	int cour_tim;
	float sco;
	char rank;
	int cred;
	for (int i = 0; i < stu_num; i++)                                       //将文件中保存的学生信息先保存到临时申请的空间中
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
//判断继续与否函数
void Continue_or_not(char *process, int &input)
{
	char Yes_or_Not;                                                        //用户选择正确与否时输入的字符
	bool Judge_Yes_or_Not = true;                                           //布尔变量判断用户输入正确与否

	for (int i = 0; Judge_Yes_or_Not; i++)
	{
		cout << "是否继续" << process << "？按Y继续，按N返回主菜单：";
		cin >> Yes_or_Not;
		if (Yes_or_Not == 'Y' || Yes_or_Not == 'y')                         //继续
		{
			Judge_Yes_or_Not = false;
		}
		else if (Yes_or_Not == 'N' || Yes_or_Not == 'n')                    //返回主菜单
		{
			input = 0;
			Judge_Yes_or_Not = false;
		}
		else                                                                //重新输入
		{
			Judge_Yes_or_Not = true;
		}
	}
}
//修改函数
void Modify()
{
	int stu_num;
	Read_Stu_num("修改", stu_num);
	Information *p = new Information[stu_num];                              //动态申请空间以存放学生信息
	Save_to_dynamic("修改", stu_num, p);                                    //读取学生信息到动态申请空间中
	int choose_nam_or_num;                                                  //存放用户输入数字选项
	bool Input_judge = true;                                                //布尔变量，判断输入正确与否
	cout << "请选择姓名或学号以修改学生信息，输入1代表姓名，2代表学号：";
	for (int i = 0; Input_judge; i++)                                       //用户输入数字选择并判断输入合法与否
	{
		cin >> choose_nam_or_num;
		if (!(choose_nam_or_num == 1 || choose_nam_or_num == 2))
			cout << "输入有误，请输入数字1或2哦=^-^=" << endl;
		else
			Input_judge = false;
	}
	if (choose_nam_or_num == 1)                                             //按学生姓名为不变量修改
	{
		char nam[20];                                                       //临时输入学生信息
		long long num;
		char cour[10];
		int cour_num;
		int cour_tim;
		float sco;
		int cred;
		int choose_input_name = 1;                                          //系统中无该姓名的学生时用户选择的数字，非0代表继续输入学生姓名
		for (int i = 0; choose_input_name; i++)
		{
			cout << "请输入学生姓名：" << endl;
			cin >> nam;
			int Judge_existence = 0;                                        //变量Judge_existence判断该学生是否存在
			for (int j = 0; j < stu_num; j++)
			{
				if (strcmp(p[j].GetName(), nam) == 0)                       //查找到该学生然后修改信息
				{
					Judge_existence++;                                      //存在该学生则变量Judge_existence+1
					cout << "您所要修改的学生原来的信息为：" << endl;
					Display_title();
					p[j].display();                                         //显示所要修改学生原来的信息
					int choose_of_modify;                                   //用户输入数字以选择所要修改的信息
					bool Judge_choose_modify = true;                        //布尔变量判断用户输入正确与否
					bool Judge_output = true;                               //布尔变量判断是否输出修改后的信息
					for (int k = 0; Judge_choose_modify; k++)
					{
						cout << "请选择您要修改的学生信息，1代表学号，2代表课程名称，3代表课程序号，4代表学时，5代表分数，6代表学分，0代表不修改此条信息：";
						cin >> choose_of_modify;
						if (choose_of_modify == 0)                          //不修改此条信息，布尔变量为false，不用重复输入过程
						{
							Judge_choose_modify = false;
							Judge_output = false;                           //布尔变量为假，不输出修改后的信息，因为并没有修改
						}
						else if (choose_of_modify == 1)                     //修改学号，输入正确，故布尔变量为false，不用重复输入过程
						{
							Judge_choose_modify = false;
							cout << "请修改学号：";
							cin >> num;
							p[j].SetNumber(num);
						}
						else if (choose_of_modify == 2)                     //修改课程名称，输入正确，故布尔变量为false，不用重复输入过程
						{
							Judge_choose_modify = false;
							cout << "请修改课程名称：";
							cin >> cour;
							p[j].SetCourse_title(cour);
						}
						else if (choose_of_modify == 3)                     //修改课程序号，输入正确，故布尔变量为false，不用重复输入过程
						{
							Judge_choose_modify = false;
							cout << "请修改课程序号：";
							cin >> cour_num;
							p[j].SetCourse_number(cour_num);
						}
						else if (choose_of_modify == 4)                     //修改课程学时，输入正确，故布尔变量为false，不用重复输入过程
						{
							Judge_choose_modify = false;
							cout << "请修改课程学时：";
							cin >> cour_tim;
							p[j].SetCourse_time(cour_tim);
						}
						else if (choose_of_modify == 5)                     //修改分数，输入正确，故布尔变量为false，不用重复输入过程
						{
							Judge_choose_modify = false;
							cout << "请修改分数：";
							cin >> sco;
							p[j].SetScore(sco);
						}
						else if (choose_of_modify == 6)                     //修改课程学分，输入正确，故布尔变量为false，不用重复输入过程
						{
							Judge_choose_modify = false;
							cout << "请修改相应课程学分：";
							cin >> cred;
							p[j].SetCredit(cred);
						}
						else                                                //输入错误，故布尔变量为true，重复输入过程
						{
							Judge_choose_modify = true;
							cout << "对不起输入有误>o<请重新输入1~6的整数："<<endl;
						}
					}
					if (Judge_output)                                       //判断是否输出修改后的信息
					{
						cout << "修改后的学生信息为：" << endl;
						Display_title();
						p[j].display();
					}
				}
			}
			if (Judge_existence == 0)                                       //不存在该学生
			{
				cout << "对不起>~<不存在该学生，请按0返回主菜单或者其他数字键继续输入学生姓名：";
				cin >> choose_input_name;
			}
			else
			{
				ofstream outfile("Information.dat", ios::out);             //将文件中原来保存的信息情清空后再将修改后的学生信息保存在文件里
				if (!outfile)                                              //如果打开失败
				{
					cerr << "修改完成后保存时文件打开出错！" << endl;
					exit(0);
				}
				for (int i = 0; i < stu_num; i++)                          //逐条保存
				{
					outfile << p[i].GetName() << " " << p[i].GetNumber() << " " << p[i].GetCourse_title() << " " << p[i].GetCourse_number() << " "
						<< p[i].GetCourse_time() << " " << p[i].GetScore() << " " << p[i].GetRank() << " " << p[i].GetCredit() << " ";
					outfile.clear();
				}
				outfile.close();                                           //关闭文件
				Continue_or_not("修改", choose_input_name);                //判断是否继续修改
			}
		}
		delete p;                                                          //返回主菜单之前删除动态申请空间
		if (choose_input_name == 0)                                        //返回主菜单
			Choose_Function();
	}
	else if (choose_nam_or_num == 2)                                       //按学生学号为不变量修改
	{
		char nam[20];                                                      //临时输入学生信息
		long long num;
		char cour[10];
		int cour_num;
		int cour_tim;
		float sco;
		int cred;
		int choose_input_number = 1;                                       //系统中无该学号的学生时用户选择的数字，非0代表继续输入学生学号
		for (int i = 0; choose_input_number; i++)
		{
			cout << "请输入学生学号：" << endl;
			cin >> num;
			int Judge_existence = 0;                                       //变量Judge_existence判断该学生是否存在
			for (int j = 0; j < stu_num; j++)
			{
				if (p[j].GetNumber()== num)                                //查找到该学生然后修改信息
				{
					Judge_existence++;                                     //存在该学生则变量Judge_existence+1
					cout << "您所要修改的学生原来的信息为：" << endl;
					Display_title();
					p[j].display();                                        //显示所要修改学生原来的信息
					int choose_of_modify;                                  //用户输入数字以选择所要修改的信息
					bool Judge_choose_modify = true;                       //布尔变量判断用户输入正确与否
					bool Judge_output=true;                                //布尔变量判断是否输出修改后的信息
					for (int k = 0; Judge_choose_modify; k++)
					{
						cout << "请选择您要修改的学生信息，1代表姓名，2代表课程名称，3代表课程序号，4代表学时，5代表分数，6代表学分，0代表不修改：";
						cin >> choose_of_modify;
						if (choose_of_modify == 0)                         //不修改此条信息，布尔变量为false，不用重复输入过程
						{
							Judge_choose_modify = false;
							Judge_output = false;                          //布尔变量为假，不输出修改后的信息，因为并没有修改
						}
						else if (choose_of_modify == 1)                    //修改姓名，输入正确，故布尔变量为false，不用重复输入过程
						{
							Judge_choose_modify = false;
							cout << "请修改姓名：";
							cin >> nam;
							p[j].SetName(nam);
						}
						else if (choose_of_modify == 2)                    //修改课程名称，输入正确，故布尔变量为false，不用重复输入过程
						{
							Judge_choose_modify = false;
							cout << "请修改课程名称：";
							cin >> cour;
							p[j].SetCourse_title(cour);
						}
						else if (choose_of_modify == 3)                    //修改课程序号，输入正确，故布尔变量为false，不用重复输入过程
						{
							Judge_choose_modify = false;
							cout << "请修改课程序号：";
							cin >> cour_num;
							p[j].SetCourse_number(cour_num);
						}
						else if (choose_of_modify == 4)                    //修改课程学时，输入正确，故布尔变量为false，不用重复输入过程
						{
							Judge_choose_modify = false;
							cout << "请修改课程学时：";
							cin >> cour_tim;
							p[j].SetCourse_time(cour_tim);
						}
						else if (choose_of_modify == 5)                   //修改分数，输入正确，故布尔变量为false，不用重复输入过程
						{
							Judge_choose_modify = false;
							cout << "请修改分数：";
							cin >> sco;
							p[j].SetScore(sco);
						}
						else if (choose_of_modify == 6)                   //修改课程学分，输入正确，故布尔变量为false，不用重复输入过程
						{
							Judge_choose_modify = false;
							cout << "请修改相应课程学分：";
							cin >> cred;
							p[j].SetCredit(cred);
						}
						else                                              //输入错误，故布尔变量为true，重复输入过程
						{
							Judge_choose_modify = true;
							cout << "对不起，输入有误 >o< 请重新输入1~6的整数：" << endl;
						}
					}
					if (Judge_output)                                     //判断是否输出修改后的信息
					{
						cout << "修改后的学生信息为：" << endl;
						Display_title();
						p[j].display();
					}
				}
			}
			if (Judge_existence == 0)                                    //不存在该学生
			{
				cout << "对不起 >~< 不存在该学生，请按0返回主菜单或者其他数字键继续输入学生学号：";
				cin >> choose_input_number;
			}
			else
			{
				ofstream outfile("Information.dat", ios::out);          //将文件中原来保存的信息清空后再将修改后的学生信息保存在文件里
				if (!outfile)                                           //如果打开失败
				{
					cerr << "修改完成后保存时文件打开出错！" << endl;
					exit(0);
				}
				for (int i = 0; i < stu_num; i++)                       //逐条保存
				{
					outfile << p[i].GetName() << " " << p[i].GetNumber() << " " << p[i].GetCourse_title() << " " << p[i].GetCourse_number() << " "
						<< p[i].GetCourse_time() << " " << p[i].GetScore() << " " << p[i].GetRank() << " " << p[i].GetCredit() << " ";
					outfile.clear();
				}
				outfile.close();                                        //关闭文件
				Continue_or_not("修改", choose_input_number);           //判断是否继续修改
			}
		}
		delete p;                                                       //返回主菜单之前删除动态申请空间
		if (choose_input_number == 0)                                   //返回主菜单
			Choose_Function();
	}
}
//查询函数
void Search()
{
	int stu_num;
	Read_Stu_num("查询", stu_num);                                      //读取学生人次
	Information *p = new Information[stu_num];                          //动态申请空间以存放学生信息
	Save_to_dynamic("查询", stu_num, p);                                //读取学生信息到动态申请空间
	int choose_of_search;                                               //存放用户输入数字选项
	bool Input_judge = true;                                            //布尔变量，判断输入正确与否
	cout << "请选择姓名或学号以查询学生信息，输入1代表姓名，2代表学号：";
	for (int i = 0; Input_judge; i++)                                   //用户输入数字选择并判断输入合法与否
	{
		cin >> choose_of_search;
		if (!(choose_of_search == 1 || choose_of_search == 2))          //输入错误，重复输入
			cout << "输入有误，请输入数字1或2哦 =^-^= " << endl;
		else                                                            //输入正确跳出循环
			Input_judge = false;
	}
	if (choose_of_search == 1)                                          //按学生姓名查询
	{
		char nam[20];                                                   //局部变量用以临时输入学生姓名
		int *pp = new int[stu_num];                                     //动态申请空间以存放查找到的学生在对象数组中的位置
		int choose_input_name = 1;                                      //系统中无该姓名的学生时用户选择的数字，非0代表继续输入学生姓名
		for (int i = 0; choose_input_name; i++)
		{
			cout << "请输入学生姓名：" << endl;
			cin >> nam;
			int Judge_existence = 0;                                    //变量Judge_existence判断该学生是否存在
			for (int j = 0; j < stu_num; j++)
			{
				if (strcmp(p[j].GetName(), nam) == 0)                   //查找到该学生然后输出信息
				{
					Judge_existence++;                                  //存在该学生则变量Judge_existence+1
					pp[Judge_existence - 1] = j;                        //存放查找到的学生在对象数组中的位置
				}
			}
			if (Judge_existence == 0)                                   //不存在该学生
			{
				cout << "对不起 >~< 不存在该学生，请按0返回主菜单或者其他数字键继续输入学生姓名：";
				cin >> choose_input_name;
			}
			else
			{
				int i, j, k, t;
				for (i = 0; i < Judge_existence - 1; i++)               //用选择法排序
				{
					k = i;
					for (j = i + 1; j < Judge_existence; j++)
					{
						if (p[pp[j]].GetScore() < p[pp[k]].GetScore())  //按分数从高到低排序
							k = j;
						else if (p[pp[j]].GetScore() == p[pp[k]].GetScore())   //分数相同时按课程序号从小到大排序
							if (p[pp[j]].GetCourse_number() < p[pp[k]].GetCourse_number())
								k = j;
					}
					t = pp[k];
					pp[k] = pp[i];
					pp[i] = t;
				}
				cout << "您所要查询的学生的信息为：" << endl;
				Display_title();
				for (int i = 0; i < Judge_existence; i++)
					p[pp[i]].display();                                  //输出学生信息
				Continue_or_not("查询", choose_input_name);              //判断是否继续查询
			}
		}
		delete pp;                                                       //删除动态申请空间
		delete p;                                                        //返回主菜单之前删除动态申请空间
		if (choose_input_name == 0)
			Choose_Function();                                           //返回主菜单
	}
	else if (choose_of_search == 2)                                      //按学生学号查询
	{
       	long long num;                                                   //局部变量用以临时输入学生学号
		int *pp = new int[stu_num];                                      //动态申请空间以存放查找到的学生在对象数组中的位置
		int choose_input_number = 1;                                     //系统中无该学号的学生时用户选择的数字，非0代表继续输入学生学号
		for (int i = 0; choose_input_number; i++)
		{
			cout << "请输入学生学号：" << endl;
			cin >> num;
			int Judge_existence = 0;                                     //变量Judge_existence判断该学生是否存在
			for (int j = 0; j < stu_num; j++)
			{
				if (p[j].GetNumber() == num)                             //查找到该学生
				{
					Judge_existence++;                                   //存在该学生则变量Judge_existence+1
					pp[Judge_existence - 1] = j;                         //存放查找到的学生在对象数组中的位置
				}
			}
			if (Judge_existence == 0)                                    //不存在该学生
			{
				cout << "对不起 >~< 不存在该学生，请按0返回主菜单或者其他数字键继续输入学生学号：";
				cin >> choose_input_number;
			}
			else
			{
				int i, j, k, t;
				for (i = 0; i < Judge_existence - 1; i++)                //用选择法排序
				{
					k = i;
					for (j = i + 1; j < Judge_existence; j++)
					{
						if (p[pp[j]].GetScore() < p[pp[k]].GetScore())   //按分数从低到高排序
							k = j;
						else if (p[pp[j]].GetScore() == p[pp[k]].GetScore())    //分数相同的按课程号从小到大排序
							if (p[pp[j]].GetCourse_number() < p[pp[k]].GetCourse_number())
								k = j;
					}
					t = pp[k];
					pp[k] = pp[i];
					pp[i] = t;
				}
				cout << "您所要查询的学生的信息为：" << endl;
				Display_title();
				for (int i = 0; i < Judge_existence; i++)
					p[pp[i]].display();                                  //输出学生信息
				Continue_or_not("查询", choose_input_number);            //判断是否继续查询
			}
		}
		delete pp;                                                       //删除动态申请空间
		delete p;                                                        //返回主菜单之前删除动态申请空间
		if (choose_input_number == 0)                                    //返回主菜单
			Choose_Function();
	}
}
//统计科目成绩情况函数
void Statistics_subject()
{
	int stu_num;
	Read_Stu_num("统计科目成绩情况", stu_num);                             //读取学生人次
	Information *p = new Information[stu_num];                           //动态申请空间以存放学生信息
	Save_to_dynamic("统计科目成绩情况", stu_num, p);                      //保存学生信息到动态申请空间
	int choose_title_number;                                             //存放用户选择的数字
	bool Judge_title_number = true;                                      //判断用户输入的正确性
	cout << "请问您想通过课程名称还是课程序号来统计科目的成绩情况？" << endl;
	for (int i = 0; Judge_title_number; i++)
	{
		cout << "按1代表课程名称，按2代表课程序号，请输入：";
		cin >> choose_title_number;
		if (choose_title_number == 1 || choose_title_number == 2)       //输入正确，跳出循环
			Judge_title_number = false;
		else                                                            //输入有误，继续输入
		{
			cout << "输入有误 >o< 请重新输入哦" << endl;
		}
	}
	if (choose_title_number == 1)
	{
		int *pp = new int[stu_num];                                    //动态申请空间以存放查找到的课程名称对应的在对象数组中的位置
		int choose_input_title = 1;                                    //系统中无该课程名称时用户选择的数字，非0代表继续输入课程名称
		for (int i = 0; choose_input_title; i++)
		{
			char cour[10];
			cout << "请输入您要统计的科目：";
			cin >> cour;
			int Judge_existence = 0;                                   //变量Judge_existence判断该课程名称是否存在
			for (int j = 0; j < stu_num; j++)
			{
				if (strcmp(p[j].GetCourse_title(), cour) == 0)         //查找到该课程名称
				{
					Judge_existence++;                                 //存在该课程名称则变量Judge_existence+1
					pp[Judge_existence - 1] = j;                       //存放查找到的课程名称对应的在对象数组中的位置
				}
			}
			if (Judge_existence == 0)                                  //不存在该课程名称
			{
				cout << "对不起 >~< 不存在该课程名称，请按0返回主菜单或者其他数字键继续输入课程名称：";
				cin >> choose_input_title;
			}
			else
			{
				int i, j, k, t;
				for (i = 0; i < Judge_existence - 1; i++)              //用选择法排序
				{
					k = i;
					for (j = i + 1; j < Judge_existence; j++)
					{
						if (p[pp[j]].GetScore() > p[pp[k]].GetScore()) //按分数从高到低排序
							k = j;
						else if (p[pp[j]].GetScore() == p[pp[k]].GetScore())      //分数相同则按学号从小到大排序
							if (p[pp[j]].GetNumber() < p[pp[k]].GetNumber())
								k = j;
					}
					t = pp[k];
					pp[k] = pp[i];
					pp[i] = t;
				}
				for (i = 0; i < Judge_existence; i++)                  //设置分数排名
				{
					p[pp[0]].SetScore_ranking(1);                      //第一个分数最高，排名设置为1
					if (i >= 1)
					{
						if (p[pp[i]].GetScore() == p[pp[i - 1]].GetScore())       //分数相同则排名相同
							p[pp[i]].SetScore_ranking(p[pp[i - 1]].GetScore_ranking());
						else
							p[pp[i]].SetScore_ranking(i + 1);
					}
				}
				int choose_output;                                      //存放用户选择的输出方式
				bool Judge_choose_output = true;                        //布尔变量判断用户输入正确与否
				for (i = 0; Judge_choose_output; i++)
				{
					cout << "请问您想要哪种输出方式，1代表只输出分数、等级及排名，2代表同时还输出学生姓名及学号：";
					cin >> choose_output;
					if (choose_output == 1 || choose_output == 2)      //输入正确，跳出循环
						Judge_choose_output = false;
					else
						cout << "输入有误 >o< 请重新输入数字1或2哦" << endl;
				}
				if (choose_output == 1)
				{
					Score *output_score = new Score[Judge_existence];  //动态申请空间，返回Score类指针
					cout << "| " << setw(3) << "分数" << " | " << setw(2) << "等级" << " | " << setw(3) << "排名 |" << endl;
					for (i = 0; i < Judge_existence; i++)
					{
						output_score[i] = p[pp[i]];
						output_score[i].display();                     //调用Score类的display()函数
					}
					delete output_score;                               //删除申请的空间
				}
				else if (choose_output == 2)
				{
					Score *output_score = new Score[Judge_existence];  //动态申请空间，返回Score类指针
					Student *output_student = new Student[Judge_existence];      //动态申请空间，返回Student类指针
					cout << "| 学生姓名 |" << "    学号    | " << setw(3) << "分数" << " | " << setw(2) << "等级" << " | " << setw(3) << "排名 |" << endl;
					for (i = 0; i < Judge_existence; i++)
					{
						output_score[i] = p[pp[i]];
						output_student[i] = p[pp[i]];
						output_student[i].display();                   //调用Score类的display()函数
						output_score[i].display();                     //调用Student类的display()函数
					}
				}
				Continue_or_not("统计", choose_input_title);           //判断是否继续统计
			}
		}
		delete pp;                                                     //删除动态申请空间
		delete p;                                                      //返回主菜单之前删除动态申请空间
		if (choose_input_title == 0)
			Choose_Function();                                         //返回主菜单
	}
	if (choose_title_number == 2)
	{
		int *pp = new int[stu_num];                                    //动态申请空间以存放查找到的课程序号对应的在对象数组中的位置
		int choose_input_number = 1;                                   //系统中无该课程序号时用户选择的数字，非0代表继续输入课程序号
		for (int i = 0; choose_input_number; i++)
		{
			int cour_num;
			cout << "请输入您要统计的科目的课程序号：";
			cin >> cour_num;
			int Judge_existence = 0;                                  //变量Judge_existence判断该课程序号是否存在
			for (int j = 0; j < stu_num; j++)
			{
				if (p[j].GetCourse_number() == cour_num)              //查找到该课程序号
				{
					Judge_existence++;                                //存在该课程名称则变量Judge_existence+1
					pp[Judge_existence - 1] = j;                      //存放查找到的课程序号对应的在对象数组中的位置
				}
			}
			if (Judge_existence == 0)                                 //不存在该课程序号
			{
				cout << "对不起 >~< 不存在该课程序号，请按0返回主菜单或者其他数字键继续输入课程序号：";
				cin >> choose_input_number;
			}
			else
			{
				int i, j, k, t;
				for (i = 0; i < Judge_existence - 1; i++)             //用选择法排序
				{
					k = i;
					for (j = i + 1; j < Judge_existence; j++)
					{
						if (p[pp[j]].GetScore() > p[pp[k]].GetScore())       //按分数从高到低排序
							k = j;
						else if (p[pp[j]].GetScore() == p[pp[k]].GetScore()) //分数相同的按学号从小到大排序
							if (p[pp[j]].GetNumber() < p[pp[k]].GetNumber())
								k = j;
					}
					t = pp[k];
					pp[k] = pp[i];
					pp[i] = t;
				}
				for (i = 0; i < Judge_existence; i++)                        //设置分数排名
				{
					p[pp[0]].SetScore_ranking(1);                            //第一个分数最高，排名设置为1
					if (i >= 1)
					{
						if (p[pp[i]].GetScore() == p[pp[i - 1]].GetScore())  //分数相同则排名相同
							p[pp[i]].SetScore_ranking(p[pp[i - 1]].GetScore_ranking());
						else
							p[pp[i]].SetScore_ranking(i + 1);
					}
				}
				int choose_output;                                           //存放用户选择的输出方式
				bool Judge_choose_output = true;                             //布尔变量判断用户输入正确与否
				for (i = 0; Judge_choose_output; i++)
				{
					cout << "请问您想要哪种输出方式，1代表只输出分数、等级及排名，2代表同时还输出学生姓名及学号：";
					cin >> choose_output;
					if (choose_output == 1 || choose_output == 2)            //输入正确，跳出循环
						Judge_choose_output = false;
					else
						cout << "输入有误 >o< 请重新输入数字1或2哦" << endl;
				}
				if (choose_output == 1)
				{
					Score *output_score = new Score[Judge_existence];        //动态申请空间，返回Score类指针
					cout << "| " << setw(3) << "分数" << " | " << setw(2) << "等级" << " | " << setw(3) << "排名 |" << endl;
					for (i = 0; i < Judge_existence; i++)
					{
						output_score[i] = p[pp[i]];
						output_score[i].display();                           //调用Score类的display()函数
					}
					delete output_score;                                     //删除动态申请空间
				}
				else if (choose_output == 2)
				{
					Score *output_score = new Score[Judge_existence];        //动态申请空间，返回Score类指针
					Student *output_student = new Student[Judge_existence];  //动态申请空间，返回Student类指针
					cout << "| 学生姓名 |" << "    学号    | " << setw(3) << "分数" << " | " << setw(2) << "等级" << " | " << setw(3) << "排名 |" << endl;
					for (i = 0; i < Judge_existence; i++)
					{
						output_score[i] = p[pp[i]];
						output_student[i] = p[pp[i]];
						output_student[i].display();                        //调用Score类的display()函数
						output_score[i].display();                          //调用Student类的display()函数
					}
				}
				Continue_or_not("统计", choose_input_number);               //判断继续统计与否
			}
		}
		delete pp;                                                         //删除动态申请空间
		delete p;                                                          //返回主菜单之前删除动态申请空间
		if (choose_input_number == 0)
			Choose_Function();                                             //返回主菜单
	}
}
//计算GPA函数
int Calculate_GPA(int stu_num, Information *p)
{
	int *n = new int[stu_num];                                            //动态申请空间
	int time = 0;                                                         //此学号出现次数
	int num_of_stu = 0;                                                   //学生人数
	for (int i = 0; i < stu_num; i++)
	{
		time = 0;                                                         //每次都要初始化为0
		float total_score = 0;                                            //总成绩初始化为0
		int total_credit = 0;                                             //总学分初始为0
		if (p[i].Get_bool())                                              //如果此学号之前没有计算过GPA
		{
			num_of_stu++;                                                 //学生人数+1
			for (int j = i; j < stu_num; j++)
			{
				if (p[j].GetNumber() == p[i].GetNumber())                 //找到此学号
				{
					total_score += p[j].GetScore()*p[j].GetCredit();
					total_credit += p[j].GetCredit();                     //计算总学分
					n[time] = j;                                          //存放该学号对应的在数组中的位置
					time++;                                               //出现次数+1
					p[j].Set_bool(false);                                 //布尔变量设置为假，下次不会重复计算这个学号
				}
			}
			p[n[0]].Set_bool(true);                                       //第一个的布尔变量设置为真
			for (int k = 0; k < time; k++)                                //设置GPA
			{
				p[n[k]].Set_GPA(total_score / total_credit);
			}
		}
		else                                                              //如果此学号之前已经计算过GPA
		{
			for (int j = i; j >= 0; j--)
			{
				if (p[j].GetNumber() == p[i].GetNumber())                 //找到此学号
				{
					p[i].Set_GPA(p[j].GetGPA());                          //学号相同的GPA设置为相同
				}
			}
		}
	}
	delete n;                                                             //删除动态申请空间
	return num_of_stu;                                                    //返回学生人数，不计重复
}
//查询GPA函数
void Search_GPA()
{
	int stu_num;
	Read_Stu_num("查询GPA", stu_num);                                     //读取学生人次
	Information *p = new Information[stu_num];                           //动态申请空间以存放学生信息
	Save_to_dynamic("查询GPA", stu_num, p);                              //保存学生信息至动态申请空间
	bool Judge_title_number = true;                                      //判断用户输入的正确性
	Calculate_GPA(stu_num, p);                                           //计算GPA
	long long numb;                                                      //用户输入学号
	bool times = true;                                                   //判断是否输出了一次
	bool input_num = true;                                               //判断是否存在此学号
	int Judge_num = 1;                                                   //用户选择继续还是返回主菜单
	for (int i = 0; Judge_num; i++)
	{
		cout << "请输入您要查询的学号：";
		cin >> numb;
		int j;
		for (j = 0,times=true; j<stu_num&&times; j++)
		{
			if (p[j].GetNumber() == numb)                                //找到该学号，只输出一次
			{
				cout << "查询结果为：" << endl;
				cout << "|学生姓名|" << "    学号    |" << "  GPA  |"  << endl;
				cout << "|  " << setw(4) << p[j].GetName() << "  | " << setw(10) << p[j].GetNumber() << " |" << setw(7) << p[j].GetGPA() << "|" << endl;
				times = false;
			}
		}
		if (j==stu_num&&times==true)                                    //不存在该学号
		{
			cout << "对不起 >o< 系统中没有这个学号，请按0返回主菜单或其他数字键继续输入：";
			cin >> Judge_num;
		}
		else                                                            //存在该学号
		{
			cout << "是否继续查询？按0返回主菜单，按其他数字键继续查询：";
			cin >>Judge_num;
		}
	}
	delete p;                                                           //删除动态申请空间
	if (Judge_num == 0)
		Choose_Function();                                              //返回主菜单
}
//统计GPA排名函数
void Statistics_GPA()
{
	int stu_num;
	Read_Stu_num("统计GPA排名", stu_num);                               //读取学生人次
	Information *p = new Information[stu_num];                         //动态申请空间以存放学生信息
	Save_to_dynamic("统计GPA排名", stu_num, p);                         //将学生信息保存至动态申请空间
	bool Judge_title_number = true;                                    //判断用户输入的正确性
	int num_of_stu=Calculate_GPA(stu_num, p);                          //计算GPA并返回学生人数
	int *pp = new int[num_of_stu];                                     //动态申请空间
	for (int i = 0,j=0; i < stu_num; i++)
	{
		if (p[i].Get_bool())
		{
			pp[j] = i;                                                 //存放用来排序的学号对应的在数组中的位置
			j++;
		}
	}
	int i, j, k,t;
	for (i = 0; i < num_of_stu - 1; i++)
	{
		k = i;
		for (j = i + 1; j < num_of_stu; j++)
		{
			if (p[pp[j]].GetGPA() > p[pp[k]].GetGPA())                //按GPA从高到低排序
				k = j;
			else if (p[pp[j]].GetGPA() == p[pp[k]].GetGPA())          //GPA相同的按学号从小到大排序
				if (p[pp[j]].GetNumber() < p[pp[k]].GetNumber())
					k = j;
		}
		t = pp[k];
		pp[k] = pp[i];
		pp[i] = t;
	}
	for (i = 0; i < num_of_stu; i++)                                  //设置GPA排名
	{
		p[pp[0]].SetGPA_ranking(1);                                   //第一个GPA最高，排名设置为1
		if (i >= 1)
		{
			if (p[pp[i]].GetGPA() == p[pp[i - 1]].GetGPA())           //GPA相同则排名相同
				p[pp[i]].SetGPA_ranking(p[pp[i - 1]].GetGPA_ranking());
			else
				p[pp[i]].SetGPA_ranking(i + 1);
		}
	}
	if (num_of_stu > 0)                                               //系统中有学生信息
	{
		cout << "GPA排名如下：" << endl;
		cout <<  "|"<<setw(6)<<" 学生姓名"<<setw(2)<<"|" <<setw(8)<< "学号"<<setw(5)<<"|" << setw(5) << "GPA" << setw(3)<<"|" << setw(8) << "GPA排名"<<setw(2)<<"|" << endl;
		for (i = 0; i < num_of_stu; i++)
		{
			cout <<  "|" << setw(7) << p[pp[i]].GetName() <<setw(4)<< "|" << setw(11) << p[pp[i]].GetNumber() <<setw(2)<< "|" << setw(7) << p[pp[i]].GetGPA() << "|" <<setw(5)<< p[pp[i]].GetGPA_ranking() <<setw(5)<<"|"<< endl;
		}
	}
	else                                                              //系统中无学生信息
		cout << "对不起 >o< 系统中暂无学生信息" << endl;
	cout << "请按任意键返回主菜单 ^.^ :";
	delete pp;//删除动态申请空间
	delete p;                                                         //删除动态申请空间
	if (getchar() != -1)
	{
		getchar();
		Choose_Function();                                            //返回主菜单
	}
}
//查询某个学生未通过课程情况函数
void Fall_of_stu()
{
	int stu_num;
	Read_Stu_num("统计GPA排名", stu_num);                              //读取学生人次
	Information *p = new Information[stu_num];                        //动态申请空间以存放学生信息
	Save_to_dynamic("统计GPA排名", stu_num, p);                        //将学生信息保存至动态申请空间
	long long num;                                                    //局部变量用以临时输入学生学号
	int *pp = new int[stu_num];                                       //动态申请空间以存放查找到的学生在对象数组中的位置
	int choose_input_number = 1;                                      //系统中无该学号的学生时用户选择的数字，非0代表继续输入学生名称
	for (int i = 0; choose_input_number; i++)
	{
		cout << "请输入学生学号：" << endl;
		cin >> num;
		int Judge_existence = 0;                                      //变量Judge_existence判断该学生是否存在
		for (int j = 0; j < stu_num; j++)
		{
			if (p[j].GetNumber() == num)                              //查找到该学生
			{
				Judge_existence++;                                    //存在该学生则变量Judge_existence+1
				pp[Judge_existence - 1] = j;                          //存放查找到的学生在对象数组中的位置
			}
		}
		if (Judge_existence == 0)                                     //不存在该学生
		{
			cout << "对不起 >~< 不存在该学生，请按0返回主菜单或者其他数字键继续输入学生学号：";
			cin >> choose_input_number;
		}
		else
		{
			cout << "您所查询的学生是：" << p[pp[0]].GetName() << " (学号：" << p[pp[0]].GetNumber() << ")" << endl;
			int i, j, k, t, no_pass = 0;
			for (int i = 0; i < Judge_existence; i++)                //计算未通过课程数
			{
				if (p[pp[i]].GetPass_or_not() == 'N')
				{
					pp[no_pass] = pp[i];                             //记录该名学生未通过课程对应的在数组中的位置
					no_pass++;
				}
			}
			if (no_pass > 0)                                         //有未通过课程
			{
				for (i = 0; i < no_pass; i++)
				{
					p[pp[i]].SetFall_num(no_pass);
				}
				for (i = 0; i < no_pass - 1; i++)                    //用选择法排序
				{
					k = i;
					for (j = i + 1; j < no_pass; j++)
					{
						if (p[pp[j]].GetScore() > p[pp[k]].GetScore())        //按分数从高到低排序
							k = j;
						else if (p[pp[j]].GetScore() == p[pp[k]].GetScore())  //分数相同的按课程号从小到大排序
							if (p[pp[j]].GetCourse_number() < p[pp[k]].GetCourse_number())
								k = j;
					}
					t = pp[k];
					pp[k] = pp[i];
					pp[i] = t;
				}
				cout << "一共有" << p[pp[0]].GetFall_num() << "门课程未通过，具体情况如下：" << endl;
				cout << "|" << setw(7) << "课程名称" << setw(2) << "|" << setw(5) << "分数" << setw(2) << "|" << endl;
				for (int i = 0; i < no_pass; i++)
				{
					cout << "|" << setw(8) << p[pp[i]].GetCourse_title() << setw(2) << "|" << setw(5) << p[pp[i]].GetScore() << setw(2) << "|" << endl;
				}
				Continue_or_not("查询", choose_input_number);        //判断是否继续查询
			}
			else                                                    //没有未通过课程
			{
				cout << "该名学生没有未通过课程记录 ^_^ " << endl;
				cout << "请按0返回主菜单或其他数字键继续输入学号：";
				cin >> choose_input_number;
			}
		}
	}
	delete pp;                                                      //删除动态申请空间
	delete p;                                                       //返回主菜单之前删除动态申请空间
	if (choose_input_number == 0)                                   //返回主菜单
		Choose_Function();
}
//通过课程名称计算平均分函数
float Average_score(char *title, int stu_num, Information *p)
{
	float total_score = 0;                                         //总分
	int total_stu = 0;                                             //总人数
	for (int i = 0; i < stu_num; i++)
	{
		if (strcmp(p[i].GetCourse_title(), title) == 0)
		{
			total_score += p[i].GetScore();                        //将其中分数相加得到总分
			total_stu++;                                           //总人数加1
		}
	}
	if (total_stu != 0)                                            //存在该课程名
		return (total_score / total_stu);                          //返回平均分
	else                                                           //不存在该课程名
		return -1;                                                 //返回-1
}
//通过课程序号计算平均分函数
float Average_score(int cour_num, int stu_num, Information *p)
{
	float total_score = 0;                                         //总分
	int total_stu = 0;                                             //总人数
	for (int i = 0; i < stu_num; i++)
	{
		if (p[i].GetCourse_number() == cour_num)
		{
			total_score += p[i].GetScore();                        //将其中分数相加得到总分
			total_stu++;                                           //总人数加1
		}
	}
	if (total_stu != 0)                                            //存在该课程名
		return (total_score / total_stu);                          //返回平均分
	else                                                           //不存在该课程名
		return -1;                                                 //返回-1
}
//查询课程平均分及未通过情况函数
void Search_aver_fall()
{
	int stu_num;
	Read_Stu_num("统计GPA排名", stu_num);                           //读取学生人次
	Information *p = new Information[stu_num];                     //动态申请空间以存放学生信息
	Save_to_dynamic("统计GPA排名", stu_num, p);                     //将学生信息保存至动态申请空间
	int *pp = new int[stu_num];                                    //动态申请空间以存放查找到的课程在对象数组中的位置
	int choose_title_number;
	bool Judge_title_number = true;
	for (int i = 0; Judge_title_number; i++)
	{
		cout << "请问您想要通过课程名称或者是课程序号查询？输入1表示课程名称，输入2表示课程序号:";
		cin >> choose_title_number;
		if (choose_title_number == 1 || choose_title_number == 2)
			Judge_title_number = false;
	}
	if (choose_title_number == 1)
	{
		char title[10];                                            //局部变量用以临时输入课程名称
		int choose_input_title = 1;                                //系统中无该课程名称时用户选择的数字，非0代表继续输入课程名称
		for (int i = 0; choose_input_title; i++)
		{
			cout << "请输入课程名称：" ;
			cin >> title;
			int Judge_existence = 0;                               //变量Judge_existence判断该课程是否存在
			for (int j = 0; j < stu_num; j++)
			{
				if (strcmp(p[j].GetCourse_title(), title) == 0)    //查找到该课程
				{
					Judge_existence++;                             //存在该课程则变量Judge_existence+1
					pp[Judge_existence - 1] = j;                   //存放查找到的课程在对象数组中的位置
				}
			}
			if (Judge_existence == 0)                              //不存在该课程
			{
				cout << "对不起 >~< 不存在该课程名称，请按0返回主菜单或者其他数字键继续输入课程名称：";
				cin >> choose_input_title;
			}
			else
			{
				cout << "这门课程--" << p[pp[0]].GetCourse_title() << "的平均分为：" << Average_score(title, stu_num, p) << endl;
				int i, j, k, t, no_pass = 0;
				for (int i = 0; i < Judge_existence; i++)          //计算未通过课程数
				{
					if (p[pp[i]].GetPass_or_not() == 'N')
					{
						pp[no_pass] = pp[i];                       //记录该课程未通过的学生对应的在数组中的位置
						no_pass++;
					}
				}
				if (no_pass > 0)                                   //有未通过课程
				{
					for (i = 0; i < no_pass; i++)
					{
						p[pp[i]].SetFall_course(no_pass);
					}
					for (i = 0; i < no_pass - 1; i++)              //用选择法排序
					{
						k = i;
						for (j = i + 1; j < no_pass; j++)
						{
							if (p[pp[j]].GetScore() > p[pp[k]].GetScore())           //按分数从高到低排序
								k = j;
							else if (p[pp[j]].GetScore() == p[pp[k]].GetScore())     //分数相同的按学号从小到大排序
								if (p[pp[j]].GetNumber() < p[pp[k]].GetNumber())
									k = j;
						}
						t = pp[k];
						pp[k] = pp[i];
						pp[i] = t;
					}
					cout << "一共有" << p[pp[0]].GetFall_course() << "个学生未通过，具体情况如下：" << endl;
					cout << "|" << setw(8) << "学生姓名" << setw(2) << "|" << setw(8) << "学号" << setw(5) << "|" << setw(5) << "分数" << setw(2) << "|" << endl;
					for (int i = 0; i < no_pass; i++)
					{
						cout << "|" << setw(8) << p[pp[i]].GetName() << setw(2) << "|" << setw(11) << p[pp[i]].GetNumber() << setw(2) << "|" << setw(4) << p[pp[i]].GetScore() << setw(3) << "|" << endl;
					}
					Continue_or_not("查询", choose_input_title);                   //判断是否继续查询
				}
				else                                                              //没有未通过课程
				{
					cout << "该门课程没有未通过学生 ^_^ " << endl;
					cout << "请按0返回主菜单或其他数字键继续输入课程名称：";
					cin >> choose_input_title;
				}
			}
		}
		delete pp;                                                                //删除动态申请空间
		delete p;                                                                 //返回主菜单之前删除动态申请空间
		if (choose_input_title == 0)                                              //返回主菜单
			Choose_Function();
	}
	else if (choose_title_number == 2)
	{
		int cour_num;                                                             //局部变量用以临时输入课程序号
		int choose_input_number = 1;                                              //系统中无该课程序号时用户选择的数字，非0代表继续输入课程序号
		for (int i = 0; choose_input_number; i++)
		{
			cout << "请输入课程序号：";
			cin >> cour_num;
			int Judge_existence = 0;                                              //变量Judge_existence判断该课程是否存在
			for (int j = 0; j < stu_num; j++)
			{
				if (p[j].GetCourse_number() == cour_num)                          //查找到该课程
				{
					Judge_existence++;                                            //存在该课程则变量Judge_existence+1
					pp[Judge_existence - 1] = j;                                  //存放查找到的课程在对象数组中的位置
				}
			}
			if (Judge_existence == 0)                                             //不存在该课程
			{
				cout << "对不起 >~< 不存在该课程序号，请按0返回主菜单或者其他数字键继续输入课程序号：";
				cin >> choose_input_number;
			}
			else
			{
				cout << "这门课程--" << p[pp[0]].GetCourse_title() << "的平均分为：" << Average_score(cour_num, stu_num, p) << endl;
				int i, j, k, t, no_pass = 0;
				for (int i = 0; i < Judge_existence; i++)                         //计算未通过课程数
				{
					if (p[pp[i]].GetPass_or_not() == 'N')
					{
						pp[no_pass] = pp[i];                                      //记录该课程未通过的学生对应的在数组中的位置
						no_pass++;
					}
				}
				if (no_pass > 0)                                                  //有未通过课程
				{
					for (i = 0; i < no_pass; i++)
					{
						p[pp[i]].SetFall_course(no_pass);
					}
					for (i = 0; i < no_pass - 1; i++)                             //用选择法排序
					{
						k = i;
						for (j = i + 1; j < no_pass; j++)
						{
							if (p[pp[j]].GetScore() > p[pp[k]].GetScore())        //按分数从高到低排序
								k = j;
							else if (p[pp[j]].GetScore() == p[pp[k]].GetScore())  //分数相同的按学号从小到大排序
								if (p[pp[j]].GetNumber() < p[pp[k]].GetNumber())
									k = j;
						}
						t = pp[k];
						pp[k] = pp[i];
						pp[i] = t;
					}
					cout << "一共有" << p[pp[0]].GetFall_course() << "个学生未通过，具体情况如下：" << endl;
					cout << "|" << setw(8) << "学生姓名" << setw(2) << "|" << setw(8) << "学号" << setw(5) << "|" << setw(5) << "分数" << setw(2) << "|" << endl;
					for (int i = 0; i < no_pass; i++)
					{
						cout << "|" << setw(8) << p[pp[i]].GetName() << setw(2) << "|" << setw(11) << p[pp[i]].GetNumber() << setw(2) << "|" << setw(4) << p[pp[i]].GetScore() << setw(3) << "|" << endl;
					}
					Continue_or_not("查询", choose_input_number);                    //判断是否继续查询
				}
				else                                                                //没有未通过课程
				{
					cout << "该门课程没有未通过学生 ^_^ " << endl;
					cout << "请按0返回主菜单或其他数字键继续输入课程序号：";
					cin >> choose_input_number;
				}
			}
		}
		delete pp;                                                                   //删除动态申请空间
		delete p;                                                                    //返回主菜单之前删除动态申请空间
		if (choose_input_number == 0)                                                //返回主菜单
			Choose_Function();
	}
}