clear all;close all;clc;
startup;                                                    %设置路径
load('question1.mat');                              %载入训练数据和测试数据
%已经经过训练得到的复合核函数
covfunc = {'covProd',{{'covSum',{{'covProd',{{'covSum',{@covSEiso,@covLINiso}},@covConst}},@covRQiso}},@covPeriodic}};
hypNum = str2num(feval(covfunc{:}));
%设置两个超参数
hyp.cov = zeros(1,hypNum); 
hyp.lik = log(0.1);
likfunc = @likGauss;                                %指定似然函数的形式
inf = @infGaussLik;                                  %指定贝叶斯推断近似方法

%通过最小化似然来优化超参数
hyp = minimize(hyp, @gp, -2500, inf, [], covfunc, likfunc, xtrain, ytrain);
%用训练好的高斯过程回归器来对测试数据进行估算
[ytest,~] = gp(hyp, inf, [], covfunc, likfunc, xtrain, ytrain, xtest);
%计算均方误差
mse = MSE_question2(ytest);