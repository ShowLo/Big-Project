//Matrix.cpp��Ÿ��෽����ʵ�ּ����ֺ����Ķ���
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <stdarg.h>
#include <assert.h>
#include "Matrix.h"
using namespace std;

//Number���Ա��������
Number::Number(int row, int col) :row(row), column(col){}

//Array���Ա��������
Array::Array(int row, int col) : Number(row, col)
{
	if (row == col)                                                    //�ж��Ƿ���
		square_or_not = true;
	else
		square_or_not = false;
	array = new double*[row];                                          //��̬�����ά����
	for (int i = 0; i < row; i++)
		array[i] = new double[col];
}
Array::~Array()
{
	for (int i = 0; i < row; i++)                                      //ɾ����̬����Ķ�ά����
	{
		delete[] array[i];
	}
	delete[] array;
}
//��ȡ��ά�����i+1�е�j+1�е�Ԫ��
double Array::GetArray(int i, int j) const                             
{
	assert(i >= 0 && i < row && j >= 0 && j < column);

	return array[i][j];
}
//��ӡ��ά��������Ԫ��
void Array::display() const                                            
{
	for (int i = 0; i < row; i++)
	{
		for (int j = 0; j < column; j++)
		{
			cout << setw(8) << GetArray(i, j) << " ";
		}
		cout << endl;
	}
}
//���ö�ά����Ԫ��,���ÿɱ����
void Array::SetArray(double a, ...)                                    
{
	array[0][0] = a;
	va_list argptr;
	va_start(argptr, a);                                              //��ʼ����Ԫָ��
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
		{
			if (!(i == 0 && j == 0))
				array[i][j] = va_arg(argptr, double);                 //������һ������
		}
	va_end(argptr);                                                   //�ͷ�argptr
}

//Matrix���Ա��������
Matrix::Matrix(int row, int col) :Array(row, col){}
//���þ���Ԫ��,���ÿɱ����
void Matrix::SetArray(double a, ...)
{
	array[0][0] = a;
	va_list argptr;
	va_start(argptr, a);                                              //��ʼ����Ԫָ��
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
		{
			if (!(i == 0 && j == 0))
				array[i][j] = va_arg(argptr, double);                 //������һ������
		}
	va_end(argptr);                                                   //�ͷ�argptr
	if (row == column)
		determinant = det(*this);                                     //��������ʽ
}
//��������ʽ
double Matrix::GetDet()                                              
{
	return determinant;
}
//������캯��
Matrix::Matrix(Matrix &M)                                             
{
	int former_row = row;
	row = M.row;                                                      //���������Ա
	column = M.column;
	for (int i = 0; i < former_row; i++)                              //�ͷ�ԭ�е��ڴ���Դ
	{
		delete[] array[i];
	}
	delete[] array;
	array = new double*[M.row];                                       //�����µ��ڴ���Դ
	for (int i = 0; i < M.row; i++)
		array[i] = new double[M.column];
	for (int i = 0; i < M.row; i++)                                   //��������Ԫ��
		for (int j = 0; j < M.column; j++)
			array[i][j] = M.array[i][j];
}
//�����������=��
Matrix& Matrix::operator =(const Matrix& M)                           
{
	assert(row == M.row);                                             //�����������С��ͬ���
	assert(column == M.column);

	if (this == &M)                                                   //����Ը���
		return *this;
	for (int i = 0; i < row; i++)                                     //�ͷ�ԭ�е��ڴ���Դ
	{
		delete[] array[i];
	}
	delete[] array;
	array = new double*[M.row];                                       //�����µ��ڴ���Դ
	for (int i = 0; i < row; i++)
		array[i] = new double[M.column];
	for (int i = 0; i < M.row; i++)                                   //��������Ԫ��
		for (int j = 0; j < M.column; j++)
			array[i][j] = M.array[i][j];
	return *this;
}
//�����������+��
Matrix Matrix::operator +(const Matrix &M2)                           
{
	assert(row == M2.row);                                            //�����������С��ͬ���
	assert(column == M2.column);

	Matrix M(M2.row, M2.column);                                      //�����ֲ�����
	for (int i = 0; i < M2.row; i++)
		for (int j = 0; j < M2.column; j++)
			M.array[i][j] = array[i][j] + M2.array[i][j];
	return M;
}
//�����������-��
Matrix Matrix::operator -(const Matrix &M2)                           
{
	assert(row == M2.row);                                            //�����������С��ͬ���
	assert(column == M2.column);

	Matrix M(M2.row, M2.column);                                      //�����ֲ�����
	for (int i = 0; i < M2.row; i++)
		for (int j = 0; j < M2.column; j++)
			M.array[i][j] = array[i][j] - M2.array[i][j];
	return M;
}
//�����������*��
Matrix Matrix::operator *(const Matrix &M2)                           
{
	assert(column == M2.row);                                         //�����������ܷ����

	Matrix M(row, M2.column);                                         //�����ֲ�����
	for (int i = 0; i < row; i++)                                     //����Ԫ�س�ʼ��Ϊ0
		for (int j = 0; j < M2.column; j++)
			M.array[i][j] = 0;
	for (int i = 0; i < row; i++)                                     //һ��һ�еؼ��������Ԫ��
		for (int k = 0; k < column; k++)
			if (array[i][k])                                          //array[i][j]Ϊ0ʱ���ý�����˲���
				for (int j = 0; j < M2.column; j++)
					M.array[i][j] += array[i][k] * M2.array[k][j];
	return M;
}
//�����������()����ʵ�־���������±����
double & Matrix::operator()(int ROW, int COL)
{
	assert(ROW >= 0 && ROW < row);                                    //�����±��Ƿ�Խ��
	assert(COL >= 0 && COL < column);

	return array[ROW][COL];
}
//�����������������<<��
ostream& operator <<(ostream& output, Matrix& M)                      
{ 
	for (int i = 0; i < M.row; i++)
	{
		for (int j = 0; j < M.column; j++)
		{
			cout << setw(8) << M.GetArray(i, j) << " ";
		}
		cout << endl;
	}
	return output;
}
void Save_Matrix(const Matrix &M)                                     //���������
{
	ofstream outfile("Matrix.dat", ios::out | ios::app);              //���ļ�
	if (!outfile)
	{
		cerr << "�������ʱ���ļ�ʧ�ܣ�" << endl;
		exit(1);
	}
	for (int i = 0; i < M.row; i++)                                   //�������Ԫ��
		for (int j = 0; j < M.column; j++)
			outfile << M.GetArray(i, j) << " ";
	outfile << "#"<<" ";                                              //��ͬ����֮��ķָ���
	outfile.close();
}
//����ת�ú���
Matrix Matrix::transposition()                                        
{
	Matrix M(column, row);
	for (int i = 0; i < column; i++)
		for (int j = 0; j < row; j++)
			M.array[i][j] = array[j][i];
	return M;
}
//���������ʽ����
double cofactor(const Matrix &M, int x, int y)                        
{
	assert(M.square_or_not);                                          //ֻ�о���Ϊ����ʱ���м����������

	int order = M.row;                                                //����Ľ���
	int i = 0, j = 0;
	int ROW, COL;
	Matrix *p = new Matrix(order - 1, order - 1);                     //�½�һ�����󣬴�ų�ȥM.array[x][y]Ԫ�����ڵ������к�ʣ�µ�Ԫ��
	for (i = 0, ROW = 0; i < order; i++)
		if (i != x)
		{
			for (j = 0, COL = 0; j < order; j++)
				if (j != y)
					p->array[ROW][COL++] = M.array[i][j];
			ROW++;
		}
	double cofactor = pow(-1, x + y)*det(*p);                         //�����������ʽ
	delete p;
	return cofactor;
}
//����������ʽ����
double det(const Matrix &M)
{
	assert(M.square_or_not);                                          //�����������ʽ

	int order = M.row;                                                //�������
	switch (order)
	{
	case 1:return M.array[0][0]; break;
	case 2:return (M.array[0][0] * M.array[1][1] - M.array[0][1] * M.array[1][0]); break;
	default:
	{
		double determinant = 0;
		for (int i = 0; i < order; i++)
			if (M.array[0][i])
				determinant += M.array[0][i] * cofactor(M, 0, i);     //��������ʽ�����໥�ݹ����
		return determinant;
	}
	}
}
//�������溯��,ѡ��ȫѡ��Ԫ��˹-��������ȥ��
void inv(const Matrix &M)
{
	assert(M.square_or_not);                                          //ֻ�ʺ��ڷ��������

	if (M.determinant == 0)
	{
		cerr << "���󲻿��棡" << endl;
	}
	else
	{
		int order = M.row;
		Matrix *A = new Matrix(order, order);
		*A = M;
		int *change_col = new int[order];                             //��̬����ռ��Դ���н�����Ϣ
		int *change_row = new int[order];                             //�����н�����Ϣ
		int i, j, k;
		double pivot, tmp;
		for (k = 0; k < order; k++)
		{
			pivot = 0.0;
			for (i = k; i < order; i++)                               //ȫѡ��Ԫ
				for (j = k; j < order; j++)
				{
					tmp = fabs((*A)(i, j));
					if (tmp > pivot)
					{
						pivot = tmp;
						change_row[k] = i;                            //�����н�����Ϣ
						change_col[k] = j;                            //�����н�����Ϣ
					}
				}
			if (change_row[k] != k)
				for (j = 0; j < order; j++)                           //�����н���
				{
					tmp = (*A)(k, j);
					A->array[k][j] = (*A)(change_row[k], j);
					A->array[change_row[k]][j] = tmp;
				}
			if (change_col[k] != k)
				for (i = 0; i < order; i++)                           //�����н���
				{
					tmp = (*A)(i, k);
					A->array[i][k] = (*A)(i, change_col[k]);
					A->array[i][change_col[k]] = tmp;
				}
			A->array[k][k] = 1.0 / (*A)(k, k);                        //��һ������
			for (j = 0; j < order; j++)                               //��һ������
				if (j != k)
					A->array[k][j] = ((*A)(k, j))*((*A)(k, k));
			for (i = 0; i < order; i++)                               //��Ԫ����
				if (i != k)
					for (j = 0; j < order; j++)
						if (j != k)
							A->array[i][j] = (*A)(i, j) - ((*A)(i, k))*((*A)(k, j));
			for (i = 0; i < order; i++)                               //��Ԫ����
				if (i != k)
					A->array[i][k] = -((*A)(i, k))*((*A)(k, k));
		}
		for (k = order - 1; k >= 0; k--)                              //�ָ����õ�����
		{
			if (change_col[k] != k)                                   //�ָ��У������н���
				for (j = 0; j < order; j++)
				{
					tmp = (*A)(k, j);
					A->array[k][j] = (*A)(change_col[k], j);
					A->array[change_col[k]][j] = tmp;
				}
			if (change_row[k] != k)                                   //�ָ��У������н���
				for (i = 0; i < order; i++)
				{
					tmp = (*A)(i, k);
					A->array[i][k] = (*A)(i, change_row[k]);
					A->array[i][change_row[k]] = tmp;
				}
		}
		cout << "�������Ϊ��" << endl;
		cout << *A;
		delete A;
		delete[] change_col;
		delete[] change_row;
	}
}
//����С��������溯��
void inv_small_matrix(const Matrix &M)
{
	assert(M.square_or_not);                                          //ֻ�ʺ��ڷ��������

	if (M.determinant == 0)
	{
		cerr << "���󲻿��棡" << endl;
	}
	else
	{
		int order = M.row;
		Matrix *inv_M = new Matrix(order, order);
		for (int i = 0; i < order; i++)                               //���ð������ķ�������
			for (int j = 0; j < order; j++)
				inv_M->array[i][j] = cofactor(M, j, i) / M.determinant;
		cout << "�������Ϊ��" << endl;
		cout<<*inv_M;
		delete inv_M;
	}
}
//����ȫѡ��Ԫ��˹��ȥ�����ʵϵ�����Դ���������
int gauss_solve(const Matrix &M, double *b)
{
	if (M.square_or_not == false)
	{
		cerr << "���ʧ�ܣ��˾����Ƿ���" << endl;
		return 0;
	}
	else
	{
		int order = M.row;
		Matrix *A = new Matrix(order, order);
		*A = M;
		int *change_col = new int[order];                         //��̬����ռ��Դ���н�����Ϣ
		int change_row;                                           //�����н���
		int i, j, k;
		int judge_singular = 1;                                   //������������־
		double pivot, tmp;
		for (k = 0; k < order - 1; k++)
		{
			pivot = 0.0;
			for (i = k; i < order; i++)                           //ȫѡ��Ԫ
				for (j = k; j < order; j++)
				{
					tmp = fabs((*A)(i, j));
					if (tmp > pivot)
					{
						pivot = tmp;
						change_col[k] = j;                        //�����н�����Ϣ
						change_row = i;                           //�����н�����Ϣ
					}
				}
			if (pivot == 0.0)                                     //��������
				judge_singular = 0;
			else
			{
				if (change_col[k] != k)
					for (i = 0; i < order; i++)                   //�����н���
					{
						tmp = (*A)(i, k);
						A->array[i][k] = (*A)(i, change_col[k]);
						A->array[i][change_col[k]] = tmp;
					}
				if (change_row != k)
				{
					for (j = k; j < order; j++)                   //�����н���
					{
						tmp = (*A)(k, j);
						A->array[k][j] = (*A)(change_row, j);
						A->array[change_row][j] = tmp;
					}
					tmp = b[k];
					b[k] = b[change_row];
					b[change_row] = tmp;
				}
			}
			if (judge_singular == 0)                              //��������
			{
				delete A;
				delete[] change_col;
				cerr << "���ʧ�ܣ����󲻿��档" << endl;
				return 0;
			}
			else
			{
				pivot = (*A)(k, k);
				for (j = k + 1; j < order; j++)                   //��һ������
					A->array[k][j] = (*A)(k, j) / pivot;
				b[k] = b[k] / pivot;
				for (i = k + 1; i < order; i++)                   //��Ԫ����
				{
					for (j = k + 1; j < order; j++)
						A->array[i][j] = (*A)(i, j) - ((*A)(i, k))*((*A)(k, j));
					b[i] = b[i] - ((*A)(i, k))*b[k];
				}
			}
		}
		pivot = (*A)(order - 1, order - 1);
		if (fabs(pivot) == 0.0)                                   //��������
		{
			delete A;
			delete[] change_col;
			cerr << "���ʧ�ܣ����󲻿��档" << endl;
			return 0;
		}
		b[order - 1] = b[order - 1] / pivot;                      //�����������һ��Ԫ��
		for (i = order - 2; i >= 0; i--)                          //�ش�����
		{
			tmp = 0.0;
			for (j = i + 1; j < order; j++)
				tmp += (*A)(i, j)*b[j];
			b[i] = b[i] - tmp;
		}
		change_col[order - 1] = order - 1;
		for (k = order - 1; k >= 0; k--)                          //�ָ�������
			if (change_col[k] != k)                               //�����н���
			{
				tmp = b[k];
				b[k] = b[change_col[k]];
				b[change_col[k]] = tmp;
			}
		delete A;
		delete[] change_col;
		return 1;                                                 //��������
	}
}