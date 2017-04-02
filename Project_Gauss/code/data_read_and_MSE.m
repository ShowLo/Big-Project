clear
%% 问题1
clear;
load('question1.mat');
% 下面写处理问题1的代码
%添加路径
startup;
%选择的复合核函数
covfunc = {'covProd',{{'covSum',{{'covProd',{{'covSum',{@covSEiso,@covLINiso}},@covConst}},@covRQiso}},@covPeriodic}};
%优化好了的超参数
hyp.cov = [5.415588;4.185325;4.345935;-0.160610;5.566283;2.862116;-13.169638;2.838082;-0.000369;2.701506];
hyp.lik = -1.493367;
%指定似然函数和贝叶斯推断近似方法
likfunc = @likGauss;
inf = @infGaussLik;
%进行预测
[ytest,~] = gp(hyp, inf, [], covfunc, likfunc, xtrain, ytrain, xtest);

%  计算MSE
mse = MSE_question2(ytest);

%% 问题2
clear;
load('planecontrol.mat');
% 下面写处理问题2的代码
%训练数据量
trainNum = 8000;
%选择的核函数
covfunc = @covSEiso;
%优化好了的参数
hyp.cov = [7.741201;9.171663];
hyp.lik = -1.779549;
%指定似然函数和贝叶斯推断近似方法
likfunc = @likGauss;
inf = @infLaplace;
%在测试数据上进行预测
[ytest , ~] = gp(hyp, inf, [], covfunc, likfunc, xtrain(1:trainNum,:), ytrain(1:trainNum,:), xtest);
%  计算MSE
mse = MSE_plane_control(ytest);
