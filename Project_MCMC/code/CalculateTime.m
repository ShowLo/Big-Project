clear all;close all;clc;
tic;                                           %计时
N = 30000;                               %样本点数
times = 100;                             %进行估计的次数
coefficient = zeros(times,1);
for n = 1 : times
    coefficient(n) = CorrCoef(N);
end
coef_average = sum(coefficient) / times;
disp(['相关系数为：' num2str(coef_average)]);
disp(['相对误差为：' num2str(abs(0.5 - coef_average) / 0.5 * 100) '%']);
disp(['方差为：' num2str(sum((coefficient - coef_average).^2) / times)]);
disp(['平均运行时间为：' num2str(toc / times)]);