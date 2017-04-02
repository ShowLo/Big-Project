clear all;close all;clc;
startup;                                                      %设置路径
load('planecontrol.mat');                           %载入训练数据和测试数据

optiNum = 500;                                         %最大优化次数
trainNum = 8000;                                      %选择的训练数据行数
covfunc = @covSEiso;                               %选择的核函数

likfunc = @likGauss;                                  %指定似然函数的形式
inf = @infLaplace;                                      %指定贝叶斯推断近似方法

hypNum = str2num(feval(covfunc));         %超参数的cov个数
%设置超参数
hyp.cov = zeros(1,hypNum); 
hyp.lik = log(0.1);
    
%通过最小化似然来优化超参数
hyp = minimize(hyp, @gp, -optiNum, inf, [], covfunc, likfunc, xtrain(1:trainNum,:), ytrain(1:trainNum,:));
%用训练好的高斯过程回归器来对测试数据进行估算
[ytest , ~] = gp(hyp, inf, [], covfunc, likfunc, xtrain(1:trainNum,:), ytrain(1:trainNum,:), xtest);
%计算均方误差
mse = MSE_plane_control(ytest);