//头文件Matrix.h存放各类的声明
#pragma once
#include <iostream>
using namespace std;
//抽象基类Number类
class Number
{
public:
	Number(int row = 0, int col = 0);
	virtual void display() const = 0;                      //纯虚函数
	virtual void SetArray(double a, ...) = 0;
protected:
	int row;
	int column;
};

//派生类Array类
class Array :public Number
{
public:
	Array(int row = 1, int col = 1);
	~Array();
	double GetArray(int row, int col) const;	           //读取数组元素函数
	virtual void display() const;
	virtual void SetArray(double a, ...);                  //可变参数函数
protected:
	double **array;
	bool square_or_not;
};

//派生类Matrix类
class Matrix :public Array
{
public:
	Matrix(int row = 1, int col = 1);
	virtual void SetArray(double a, ...);
	double GetDet();
	Matrix(Matrix &M);                                     //拷贝构造函数
	Matrix &operator =(const Matrix& M);                   //重载运算符函数声明
	Matrix operator +(const Matrix &M2);
	Matrix operator -(const Matrix &M2);
	Matrix operator *(const Matrix &M2);
	double & operator()(int ROW, int COL);
	friend ostream& operator <<(ostream&, Matrix&);
	friend void Save_Matrix(const Matrix &M);              //保存矩阵函数
	Matrix transposition();                                //声明转置函数
	friend double cofactor(const Matrix &M, int x, int y); //声明求代数余子式函数
	friend double det(const Matrix &M);                    //声明求行列式函数
	friend void inv(const Matrix &M);                      //声明求逆函数
	friend void inv_small_matrix(const Matrix &M);         //声明小方阵的求逆函数
	friend int gauss_solve(const Matrix &M, double *b);    //声明求解向量函数
protected:
	double determinant;
};