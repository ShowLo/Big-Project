//ͷ�ļ�Matrix.h��Ÿ��������
#pragma once
#include <iostream>
using namespace std;
//�������Number��
class Number
{
public:
	Number(int row = 0, int col = 0);
	virtual void display() const = 0;                      //���麯��
	virtual void SetArray(double a, ...) = 0;
protected:
	int row;
	int column;
};

//������Array��
class Array :public Number
{
public:
	Array(int row = 1, int col = 1);
	~Array();
	double GetArray(int row, int col) const;	           //��ȡ����Ԫ�غ���
	virtual void display() const;
	virtual void SetArray(double a, ...);                  //�ɱ��������
protected:
	double **array;
	bool square_or_not;
};

//������Matrix��
class Matrix :public Array
{
public:
	Matrix(int row = 1, int col = 1);
	virtual void SetArray(double a, ...);
	double GetDet();
	Matrix(Matrix &M);                                     //�������캯��
	Matrix &operator =(const Matrix& M);                   //�����������������
	Matrix operator +(const Matrix &M2);
	Matrix operator -(const Matrix &M2);
	Matrix operator *(const Matrix &M2);
	double & operator()(int ROW, int COL);
	friend ostream& operator <<(ostream&, Matrix&);
	friend void Save_Matrix(const Matrix &M);              //���������
	Matrix transposition();                                //����ת�ú���
	friend double cofactor(const Matrix &M, int x, int y); //�������������ʽ����
	friend double det(const Matrix &M);                    //����������ʽ����
	friend void inv(const Matrix &M);                      //�������溯��
	friend void inv_small_matrix(const Matrix &M);         //����С��������溯��
	friend int gauss_solve(const Matrix &M, double *b);    //���������������
protected:
	double determinant;
};