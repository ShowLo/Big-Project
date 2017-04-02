//�������ļ�Main.cpp�����в���
#include <iostream>
#include <stdio.h>
#include "Matrix.h"
using namespace std;
int main()
{
	system("color 5F");
	Matrix A(3, 4);
	A.SetArray(9.0, 7.8, 7.0, 5.6, 4.5, 3.4, 2.3, 1.2, 0.1, 3.4, 5.2, 1.6);
	cout << "����A=" << endl;
	A.display();
	Matrix B(3,4);
	B.SetArray(1.0, 2.2, 3.0, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 6.6, 4.8, 8.4);
	cout << "����B=" << endl;
	B.display();
	Matrix C(4, 3);
	C.SetArray(3.3, 4.0, 5.2, 1.0, 5.0, 6.3, 2.2, 1.1, 5.5, 4.0, 9.8, 7.5);
	cout << "����C=" << endl;
	C.display();
	Matrix D(3, 4);
	D = A + B;
	cout << "A+B=" << endl << D;
	D = A - B;
	cout << "A-B=" << endl<<D;
	Matrix E(3, 3);
	E = A*C;
	cout << "A*C=" << endl<<E;
	Matrix AT(4, 3);
	AT = A.transposition();
	cout << "A^T=" << endl<<AT;
	Matrix F(3, 3);
	F.SetArray(1.0, 2.0, 3.0, 4.0, 5.0, 6.0, 7.0, 8.0, 9.0);
	cout << "����F=" << endl << F;
	cout << "��С����F���棬���Ϊ��" << endl;
	inv_small_matrix(F);
	Matrix G(3, 3);
	G.SetArray(2.0, 5.0, 3.0, 5.0, 1.0, 3.0, 8.0, 9.0, 7.0);
	cout << "����G=" << endl << G;
	cout << "��С����G���棬���Ϊ��" << endl;
	inv_small_matrix(G);
	Matrix M(5, 5);
	M.SetArray(1., 2., 3., 4., 5., 
		0., 2., 3., 4.,5.,
		0.,0.,4.,5.,6.,
		0.,0.,0.,5.,6.,
		0.,0.,0.,0.,2.);
	cout << "����M=" << endl<<M;
	cout << "����M������ʽΪ��"<< det(M) << endl;
	cout << "�Ծ���M���棬���Ϊ��" << endl;
	inv(M);
	Save_Matrix(M);
	double b[5] = { 3., 5., 4., 5.5, 7.3 };
	cout << "��������b=(";
	for (int i = 0; i < sizeof(b) / sizeof(b[0]) - 1; i++)
		cout << b[i] << ",";
	cout << b[sizeof(b) / sizeof(b[0]) - 1] << ")" << endl;
	if (gauss_solve(M, b) != 0)
	{
		cout << "Mx=b�Ľ�����Ϊ:x=(";
		for (int i = 0; i < sizeof(b) / sizeof(b[0]) - 1; i++)
			cout << b[i] << ",";
		cout << b[sizeof(b) / sizeof(b[0])-1] << ")" << endl;
	}
	system("pause 0");
	return 0;
}