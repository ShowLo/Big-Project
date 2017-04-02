clear all;close all;clc;
startup;                                                      %设置路径
load('question1.mat');                                %载入训练数据和测试数据

optiNum = 2500;                                       %最大优化次数

%五个基本核函数
covFunctions = {@covSEiso,@covPeriodic,@covLINiso,@covRQiso,@covConst};
mse = zeros(5,1);
likfunc = @likGauss;                                  %指定似然函数的形式为高斯的

for m = 1 : 5                                              %进行第一次循环选择一个基本核函数
    covfunc = covFunctions(m);                  %选择核函数
    hypNum = str2num(feval(covfunc{:}));  %超参数的cov个数
    %设置超参数
    hyp.cov = zeros(1,hypNum); 
    hyp.lik = log(0.1);
    
    %通过最小化负的对数边际似然来优化超参数
    hyp = minimize(hyp, @gp, -optiNum, @infGaussLik, [], covfunc, likfunc, xtrain, ytrain);
    %用训练好的高斯过程回归器来对测试数据进行估算
    [ytest , ~] = gp(hyp, @infGaussLik, [], covfunc, likfunc, xtrain, ytrain, xtest);
    %计算均方误差
    mse(m) = MSE_question2(ytest);
end

[~,minIndex] = min(mse);                          %找到MSE最小的
covfunction = covFunctions(minIndex);     %作为基本的核函数
index = 1 : 5;
index(minIndex) = [];                                  %然后从索引中除去已经加入的核函数

%再进行4次大循环以选出剩余的4个核函数的合适组合方式
for m = 1 : 4
    num = 0;                                                 %记录组合方式总数
    tempcovfunc = cell(2 * length(index),1); %临时记录各种组合方式
    mse = zeros(2 * length(index),1);            %记录各种组合方式的MSE
    for n = index(1:end)                                %从剩下的几种核函数中选择
        num = num + 1;
        %先尝试加
        tempcovfunc{num} = {'covSum',{covfunction,covFunctions(n)}};
        hypNum = str2num(feval(tempcovfunc{num}{:}));
        hyp.cov = zeros(1,hypNum); 
        hyp.lik = log(0.1);
        
        hyp = minimize(hyp, @gp, -optiNum, @infGaussLik, [], tempcovfunc{num}, likfunc, xtrain, ytrain);
        [ytest , ~] = gp(hyp, @infGaussLik, [], tempcovfunc{num}, likfunc, xtrain, ytrain, xtest);
        mse(num) = MSE_question2(ytest);
        
        num = num + 1;
        %再尝试乘
        tempcovfunc{num} = {'covProd',{covfunction,covFunctions(n)}};
        hypNum = str2num(feval(tempcovfunc{num}{:}));
        hyp.cov = zeros(1,hypNum); 
        hyp.lik = log(0.1);
        
        hyp = minimize(hyp, @gp, -optiNum, @infGaussLik, [], tempcovfunc{num}, likfunc, xtrain, ytrain);
        [ytest , ~] = gp(hyp, @infGaussLik, [], tempcovfunc{num}, likfunc, xtrain, ytrain, xtest);
        mse(num) = MSE_question2(ytest);
    end
    [~,minIndex] = min(mse);                       %找出MSE最小的
    covfunction = tempcovfunc{minIndex};  %并以这个最小的MSE对应的核函数组合方式为最终结果的一部分
    index(ceil(minIndex/2)) = [];                    %从索引中除去已经加入的核函数
end