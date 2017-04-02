//主程序文件Main.cpp，进行测试
#include <iostream>
#include <stdio.h>
#include "Matrix.h"
using namespace std;
int main()
{
	system("color 5F");
	Matrix A(3, 4);
	A.SetArray(9.0, 7.8, 7.0, 5.6, 4.5, 3.4, 2.3, 1.2, 0.1, 3.4, 5.2, 1.6);
	cout << "矩阵A=" << endl;
	A.display();
	Matrix B(3,4);
	B.SetArray(1.0, 2.2, 3.0, 4.4, 5.5, 6.6, 7.7, 8.8, 9.9, 6.6, 4.8, 8.4);
	cout << "矩阵B=" << endl;
	B.display();
	Matrix C(4, 3);
	C.SetArray(3.3, 4.0, 5.2, 1.0, 5.0, 6.3, 2.2, 1.1, 5.5, 4.0, 9.8, 7.5);
	cout << "矩阵C=" << endl;
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
	cout << "矩阵F=" << endl << F;
	cout << "对小矩阵F求逆，结果为：" << endl;
	inv_small_matrix(F);
	Matrix G(3, 3);
	G.SetArray(2.0, 5.0, 3.0, 5.0, 1.0, 3.0, 8.0, 9.0, 7.0);
	cout << "矩阵G=" << endl << G;
	cout << "对小矩阵G求逆，结果为：" << endl;
	inv_small_matrix(G);
	Matrix M(5, 5);
	M.SetArray(1., 2., 3., 4., 5., 
		0., 2., 3., 4.,5.,
		0.,0.,4.,5.,6.,
		0.,0.,0.,5.,6.,
		0.,0.,0.,0.,2.);
	cout << "矩阵M=" << endl<<M;
	cout << "矩阵M的行列式为："<< det(M) << endl;
	cout << "对矩阵M求逆，结果为：" << endl;
	inv(M);
	Save_Matrix(M);
	double b[5] = { 3., 5., 4., 5.5, 7.3 };
	cout << "常数向量b=(";
	for (int i = 0; i < sizeof(b) / sizeof(b[0]) - 1; i++)
		cout << b[i] << ",";
	cout << b[sizeof(b) / sizeof(b[0]) - 1] << ")" << endl;
	if (gauss_solve(M, b) != 0)
	{
		cout << "Mx=b的解向量为:x=(";
		for (int i = 0; i < sizeof(b) / sizeof(b[0]) - 1; i++)
			cout << b[i] << ",";
		cout << b[sizeof(b) / sizeof(b[0])-1] << ")" << endl;
	}
	system("pause 0");
	return 0;
}