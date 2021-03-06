﻿clear all;close all;clc;
tic;
K = 100;
N = 100;
load('data/test.mat');
%先得到theta_A的观测变量偏置项
visable_A = train_A(testbatchdata)';  

load('data/h10.mat');
parameter_W_h10 = parameter_W;
parameter_a_h10 = parameter_a;
parameter_b_h10 = parameter_b;
load('data/h20.mat');
parameter_W_h20 = parameter_W;
parameter_a_h20 = parameter_a;
parameter_b_h20 = parameter_b;
load('data/h100.mat');
parameter_W_h100 = parameter_W;
parameter_a_h100 = parameter_a;
parameter_b_h100 = parameter_b;
load('data/h500.mat');
parameter_W_h500 = parameter_W;
parameter_a_h500 = parameter_a;
parameter_b_h500 = parameter_b;

times = 32;
lnZ_theta_h10 = zeros(times,1);
lnZ_theta_h20 = zeros(times,1);
lnZ_theta_h100 = zeros(times,1);
lnZ_theta_h500 = zeros(times,1);
%多次运行以求得均值和方差
for n = 1 : times
    lnZ_theta_h10(n) = RTS(parameter_W_h10,parameter_a_h10,parameter_b_h10,visable_A,K,N);
    lnZ_theta_h20(n) = RTS(parameter_W_h20,parameter_a_h20,parameter_b_h20,visable_A,K,N);
    lnZ_theta_h100(n) = RTS(parameter_W_h100,parameter_a_h100,parameter_b_h100,visable_A,K,N);
    lnZ_theta_h500(n) = RTS(parameter_W_h500,parameter_a_h500,parameter_b_h500,visable_A,K,N);
    disp(n);
end
%各个模型下的均值
lnZ_theta_h10_ave = mean(lnZ_theta_h10);
lnZ_theta_h20_ave = mean(lnZ_theta_h20);
lnZ_theta_h100_ave = mean(lnZ_theta_h100);
lnZ_theta_h500_ave = mean(lnZ_theta_h500);
%各个模型下的方差
lnZ_theta_h10_var = var(lnZ_theta_h10,1);
lnZ_theta_h20_var = var(lnZ_theta_h20,1);
lnZ_theta_h100_var = var(lnZ_theta_h100,1);
lnZ_theta_h500_var = var(lnZ_theta_h500,1);
toc;