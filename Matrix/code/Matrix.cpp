//Matrix.cpp存放各类方法的实现及各种函数的定义
#include <iostream>
#include <iomanip>
#include <cmath>
#include <fstream>
#include <stdarg.h>
#include <assert.h>
#include "Matrix.h"
using namespace std;

//Number类成员函数定义
Number::Number(int row, int col) :row(row), column(col){}

//Array类成员函数定义
Array::Array(int row, int col) : Number(row, col)
{
	if (row == col)                                                    //判断是否方阵
		square_or_not = true;
	else
		square_or_not = false;
	array = new double*[row];                                          //动态申请二维数组
	for (int i = 0; i < row; i++)
		array[i] = new double[col];
}
Array::~Array()
{
	for (int i = 0; i < row; i++)                                      //删除动态申请的二维数组
	{
		delete[] array[i];
	}
	delete[] array;
}
//读取二维数组第i+1行第j+1列的元素
double Array::GetArray(int i, int j) const                             
{
	assert(i >= 0 && i < row && j >= 0 && j < column);

	return array[i][j];
}
//打印二维数组所有元素
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
//设置二维数组元素,采用可变参数
void Array::SetArray(double a, ...)                                    
{
	array[0][0] = a;
	va_list argptr;
	va_start(argptr, a);                                              //初始化变元指针
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
		{
			if (!(i == 0 && j == 0))
				array[i][j] = va_arg(argptr, double);                 //返回下一个参数
		}
	va_end(argptr);                                                   //释放argptr
}

//Matrix类成员函数定义
Matrix::Matrix(int row, int col) :Array(row, col){}
//设置矩阵元素,采用可变参数
void Matrix::SetArray(double a, ...)
{
	array[0][0] = a;
	va_list argptr;
	va_start(argptr, a);                                              //初始化变元指针
	for (int i = 0; i < row; i++)
		for (int j = 0; j < column; j++)
		{
			if (!(i == 0 && j == 0))
				array[i][j] = va_arg(argptr, double);                 //返回下一个参数
		}
	va_end(argptr);                                                   //释放argptr
	if (row == column)
		determinant = det(*this);                                     //计算行列式
}
//返回行列式
double Matrix::GetDet()                                              
{
	return determinant;
}
//深拷贝构造函数
Matrix::Matrix(Matrix &M)                                             
{
	int former_row = row;
	row = M.row;                                                      //拷贝常规成员
	column = M.column;
	for (int i = 0; i < former_row; i++)                              //释放原有的内存资源
	{
		delete[] array[i];
	}
	delete[] array;
	array = new double*[M.row];                                       //分配新的内存资源
	for (int i = 0; i < M.row; i++)
		array[i] = new double[M.column];
	for (int i = 0; i < M.row; i++)                                   //复制数组元素
		for (int j = 0; j < M.column; j++)
			array[i][j] = M.array[i][j];
}
//重载运算符“=”
Matrix& Matrix::operator =(const Matrix& M)                           
{
	assert(row == M.row);                                             //检验两矩阵大小相同与否
	assert(column == M.column);

	if (this == &M)                                                   //检查自复制
		return *this;
	for (int i = 0; i < row; i++)                                     //释放原有的内存资源
	{
		delete[] array[i];
	}
	delete[] array;
	array = new double*[M.row];                                       //分配新的内存资源
	for (int i = 0; i < row; i++)
		array[i] = new double[M.column];
	for (int i = 0; i < M.row; i++)                                   //复制数组元素
		for (int j = 0; j < M.column; j++)
			array[i][j] = M.array[i][j];
	return *this;
}
//重载运算符“+”
Matrix Matrix::operator +(const Matrix &M2)                           
{
	assert(row == M2.row);                                            //检验两矩阵大小相同与否
	assert(column == M2.column);

	Matrix M(M2.row, M2.column);                                      //建立局部对象
	for (int i = 0; i < M2.row; i++)
		for (int j = 0; j < M2.column; j++)
			M.array[i][j] = array[i][j] + M2.array[i][j];
	return M;
}
//重载运算符“-”
Matrix Matrix::operator -(const Matrix &M2)                           
{
	assert(row == M2.row);                                            //检验两矩阵大小相同与否
	assert(column == M2.column);

	Matrix M(M2.row, M2.column);                                      //建立局部对象
	for (int i = 0; i < M2.row; i++)
		for (int j = 0; j < M2.column; j++)
			M.array[i][j] = array[i][j] - M2.array[i][j];
	return M;
}
//重载运算符“*”
Matrix Matrix::operator *(const Matrix &M2)                           
{
	assert(column == M2.row);                                         //检验两矩阵能否相乘

	Matrix M(row, M2.column);                                         //建立局部对象
	for (int i = 0; i < row; i++)                                     //所有元素初始化为0
		for (int j = 0; j < M2.column; j++)
			M.array[i][j] = 0;
	for (int i = 0; i < row; i++)                                     //一行一行地计算出所有元素
		for (int k = 0; k < column; k++)
			if (array[i][k])                                          //array[i][j]为0时不用进行相乘操作
				for (int j = 0; j < M2.column; j++)
					M.array[i][j] += array[i][k] * M2.array[k][j];
	return M;
}
//重载运算符“()”，实现矩阵类多重下标访问
double & Matrix::operator()(int ROW, int COL)
{
	assert(ROW >= 0 && ROW < row);                                    //检验下标是否越界
	assert(COL >= 0 && COL < column);

	return array[ROW][COL];
}
//重载流插入运算符“<<”
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
void Save_Matrix(const Matrix &M)                                     //保存矩阵函数
{
	ofstream outfile("Matrix.dat", ios::out | ios::app);              //打开文件
	if (!outfile)
	{
		cerr << "保存矩阵时打开文件失败！" << endl;
		exit(1);
	}
	for (int i = 0; i < M.row; i++)                                   //保存矩阵元素
		for (int j = 0; j < M.column; j++)
			outfile << M.GetArray(i, j) << " ";
	outfile << "#"<<" ";                                              //不同矩阵之间的分隔符
	outfile.close();
}
//定义转置函数
Matrix Matrix::transposition()                                        
{
	Matrix M(column, row);
	for (int i = 0; i < column; i++)
		for (int j = 0; j < row; j++)
			M.array[i][j] = array[j][i];
	return M;
}
//求代数余子式函数
double cofactor(const Matrix &M, int x, int y)                        
{
	assert(M.square_or_not);                                          //只有矩阵为方阵时进行计算才有意义

	int order = M.row;                                                //矩阵的阶数
	int i = 0, j = 0;
	int ROW, COL;
	Matrix *p = new Matrix(order - 1, order - 1);                     //新建一个矩阵，存放除去M.array[x][y]元素所在的行与列后剩下的元素
	for (i = 0, ROW = 0; i < order; i++)
		if (i != x)
		{
			for (j = 0, COL = 0; j < order; j++)
				if (j != y)
					p->array[ROW][COL++] = M.array[i][j];
			ROW++;
		}
	double cofactor = pow(-1, x + y)*det(*p);                         //计算代数余子式
	delete p;
	return cofactor;
}
//定义求行列式函数
double det(const Matrix &M)
{
	assert(M.square_or_not);                                          //方阵才有行列式

	int order = M.row;                                                //方阵阶数
	switch (order)
	{
	case 1:return M.array[0][0]; break;
	case 2:return (M.array[0][0] * M.array[1][1] - M.array[0][1] * M.array[1][0]); break;
	default:
	{
		double determinant = 0;
		for (int i = 0; i < order; i++)
			if (M.array[0][i])
				determinant += M.array[0][i] * cofactor(M, 0, i);     //与求行列式函数相互递归调用
		return determinant;
	}
	}
}
//方阵求逆函数,选用全选主元高斯-若尔当消去法
void inv(const Matrix &M)
{
	assert(M.square_or_not);                                          //只适合于方阵的求逆

	if (M.determinant == 0)
	{
		cerr << "矩阵不可逆！" << endl;
	}
	else
	{
		int order = M.row;
		Matrix *A = new Matrix(order, order);
		*A = M;
		int *change_col = new int[order];                             //动态申请空间以存放列交换信息
		int *change_row = new int[order];                             //记忆行交换信息
		int i, j, k;
		double pivot, tmp;
		for (k = 0; k < order; k++)
		{
			pivot = 0.0;
			for (i = k; i < order; i++)                               //全选主元
				for (j = k; j < order; j++)
				{
					tmp = fabs((*A)(i, j));
					if (tmp > pivot)
					{
						pivot = tmp;
						change_row[k] = i;                            //记忆行交换信息
						change_col[k] = j;                            //记忆列交换信息
					}
				}
			if (change_row[k] != k)
				for (j = 0; j < order; j++)                           //进行行交换
				{
					tmp = (*A)(k, j);
					A->array[k][j] = (*A)(change_row[k], j);
					A->array[change_row[k]][j] = tmp;
				}
			if (change_col[k] != k)
				for (i = 0; i < order; i++)                           //进行列交换
				{
					tmp = (*A)(i, k);
					A->array[i][k] = (*A)(i, change_col[k]);
					A->array[i][change_col[k]] = tmp;
				}
			A->array[k][k] = 1.0 / (*A)(k, k);                        //归一化计算
			for (j = 0; j < order; j++)                               //归一化计算
				if (j != k)
					A->array[k][j] = ((*A)(k, j))*((*A)(k, k));
			for (i = 0; i < order; i++)                               //消元计算
				if (i != k)
					for (j = 0; j < order; j++)
						if (j != k)
							A->array[i][j] = (*A)(i, j) - ((*A)(i, k))*((*A)(k, j));
			for (i = 0; i < order; i++)                               //消元计算
				if (i != k)
					A->array[i][k] = -((*A)(i, k))*((*A)(k, k));
		}
		for (k = order - 1; k >= 0; k--)                              //恢复所得的逆阵
		{
			if (change_col[k] != k)                                   //恢复行，进行行交换
				for (j = 0; j < order; j++)
				{
					tmp = (*A)(k, j);
					A->array[k][j] = (*A)(change_col[k], j);
					A->array[change_col[k]][j] = tmp;
				}
			if (change_row[k] != k)                                   //恢复列，进行列交换
				for (i = 0; i < order; i++)
				{
					tmp = (*A)(i, k);
					A->array[i][k] = (*A)(i, change_row[k]);
					A->array[i][change_row[k]] = tmp;
				}
		}
		cout << "方阵的逆为：" << endl;
		cout << *A;
		delete A;
		delete[] change_col;
		delete[] change_row;
	}
}
//定义小矩阵的求逆函数
void inv_small_matrix(const Matrix &M)
{
	assert(M.square_or_not);                                          //只适合于方阵的求逆

	if (M.determinant == 0)
	{
		cerr << "矩阵不可逆！" << endl;
	}
	else
	{
		int order = M.row;
		Matrix *inv_M = new Matrix(order, order);
		for (int i = 0; i < order; i++)                               //采用伴随矩阵的方法求逆
			for (int j = 0; j < order; j++)
				inv_M->array[i][j] = cofactor(M, j, i) / M.determinant;
		cout << "矩阵的逆为：" << endl;
		cout<<*inv_M;
		delete inv_M;
	}
}
//利用全选主元高斯消去法求解实系数线性代数方程组
int gauss_solve(const Matrix &M, double *b)
{
	if (M.square_or_not == false)
	{
		cerr << "求解失败，此矩阵不是方阵。" << endl;
		return 0;
	}
	else
	{
		int order = M.row;
		Matrix *A = new Matrix(order, order);
		*A = M;
		int *change_col = new int[order];                         //动态申请空间以存放列交换信息
		int change_row;                                           //记忆行交换
		int i, j, k;
		int judge_singular = 1;                                   //方阵奇异与否标志
		double pivot, tmp;
		for (k = 0; k < order - 1; k++)
		{
			pivot = 0.0;
			for (i = k; i < order; i++)                           //全选主元
				for (j = k; j < order; j++)
				{
					tmp = fabs((*A)(i, j));
					if (tmp > pivot)
					{
						pivot = tmp;
						change_col[k] = j;                        //记忆列交换信息
						change_row = i;                           //记忆行交换信息
					}
				}
			if (pivot == 0.0)                                     //方阵奇异
				judge_singular = 0;
			else
			{
				if (change_col[k] != k)
					for (i = 0; i < order; i++)                   //进行列交换
					{
						tmp = (*A)(i, k);
						A->array[i][k] = (*A)(i, change_col[k]);
						A->array[i][change_col[k]] = tmp;
					}
				if (change_row != k)
				{
					for (j = k; j < order; j++)                   //进行行交换
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
			if (judge_singular == 0)                              //方阵奇异
			{
				delete A;
				delete[] change_col;
				cerr << "求解失败，方阵不可逆。" << endl;
				return 0;
			}
			else
			{
				pivot = (*A)(k, k);
				for (j = k + 1; j < order; j++)                   //归一化操作
					A->array[k][j] = (*A)(k, j) / pivot;
				b[k] = b[k] / pivot;
				for (i = k + 1; i < order; i++)                   //消元操作
				{
					for (j = k + 1; j < order; j++)
						A->array[i][j] = (*A)(i, j) - ((*A)(i, k))*((*A)(k, j));
					b[i] = b[i] - ((*A)(i, k))*b[k];
				}
			}
		}
		pivot = (*A)(order - 1, order - 1);
		if (fabs(pivot) == 0.0)                                   //方阵奇异
		{
			delete A;
			delete[] change_col;
			cerr << "求解失败，方阵不可逆。" << endl;
			return 0;
		}
		b[order - 1] = b[order - 1] / pivot;                      //解向量的最后一个元素
		for (i = order - 2; i >= 0; i--)                          //回代操作
		{
			tmp = 0.0;
			for (j = i + 1; j < order; j++)
				tmp += (*A)(i, j)*b[j];
			b[i] = b[i] - tmp;
		}
		change_col[order - 1] = order - 1;
		for (k = order - 1; k >= 0; k--)                          //恢复解向量
			if (change_col[k] != k)                               //进行行交换
			{
				tmp = b[k];
				b[k] = b[change_col[k]];
				b[change_col[k]] = tmp;
			}
		delete A;
		delete[] change_col;
		return 1;                                                 //正常返回
	}
}