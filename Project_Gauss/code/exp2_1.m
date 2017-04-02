clear all;close all;clc;
startup;                                                      %设置路径
load('planecontrol.mat');                           %载入训练数据和测试数据

optiNum = 500;                                        %最大优化次数
kenelNum = 4;                                           %核函数个数
trainNum = 1000;                                      %选择的训练数据行数

%选择的4个基本核函数
covFunctions = {@covSEiso,@covLINiso,@covRQiso,@covConst};
mse = zeros(kenelNum,1);
likfunc = @likGauss;                                  %指定似然函数的形式
inf = @infGaussLik;                                    %指定贝叶斯推断近似方法

for m = 1 : kenelNum                                %进行循环选择一个基本核函数
    covfunc = covFunctions(m);                  %选择核函数
    hypNum = str2num(feval(covfunc{:}));  %超参数的cov个数
    %设置超参数
    hyp.cov = zeros(1,hypNum); 
    hyp.lik = log(0.1);
    
    %通过最小化似然来优化超参数
    hyp = minimize(hyp, @gp, -optiNum, inf, [], covfunc, likfunc, xtrain(1:trainNum,:), ytrain(1:trainNum,:));
    %用训练好的高斯过程回归器来对测试数据进行估算
    [ytest , ~] = gp(hyp, inf, [], covfunc, likfunc, xtrain(1:trainNum,:), ytrain(1:trainNum,:), xtest);
    %计算均方误差
    mse(m) = MSE_plane_control(ytest);
end
[MSE,index] = min(mse);
covfunc = covFunctions(index);