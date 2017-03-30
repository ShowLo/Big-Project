%计算二维随机变量(X1,X2)的联合分布密度
function density = Normal(x1,x2)
%输入参数
%x1：变量X1
%x2：变量X2
%输出参数
%density：概率密度
miu1 = 5;                           %X1的均值
miu2 = 10;                         %X2的均值
variance1 = 1;                    %X1的方差
variance2 = 4;                    %X2的方差
sigma1 = sqrt(variance1);   %计算X1的标准差
sigma2 = sqrt(variance2);   %计算X2的标准差
correlation = 1/2;               %X1,X2的理论相关系数
%X1,X2的联合分布密度
density = exp((2 * correlation * (x1 - miu1) * (x2 - miu2) / (sigma1 * sigma2) - (x1 - miu1)^2 / variance1 ...
                - (x2 - miu2)^2 / variance2) / (2 * (1 - correlation^2))) / (2 * pi * sigma1 *sigma2 * sqrt(1 - correlation^2));