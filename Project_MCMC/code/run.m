﻿clear all;close all;clc;
runCount = 100;
K = 10000;
load('data/test.mat');
%先得到theta_A的观测变量偏置项
visable_A = train_A(testbatchdata)'; 
load('data/h10.mat');
lnZ_h10 = AIS(parameter_W,parameter_a,parameter_b,visable_A,K,runCount);
likelihood_h10 = Calculatelikelihood(parameter_W,parameter_a,parameter_b,testbatchdata,lnZ_h10);
load('data/h20.mat');
lnZ_h20 = AIS(parameter_W,parameter_a,parameter_b,visable_A,K,runCount);
likelihood_h20 = Calculatelikelihood(parameter_W,parameter_a,parameter_b,testbatchdata,lnZ_h20);
load('data/h100.mat');
lnZ_h100 = AIS(parameter_W,parameter_a,parameter_b,visable_A,K,runCount);
likelihood_h100 = Calculatelikelihood(parameter_W,parameter_a,parameter_b,testbatchdata,lnZ_h100);
load('data/h500.mat');
lnZ_h500 = AIS(parameter_W,parameter_a,parameter_b,visable_A,K,runCount);
likelihood_h500 = Calculatelikelihood(parameter_W,parameter_a,parameter_b,testbatchdata,lnZ_h500);
z = [lnZ_h10;lnZ_h20;lnZ_h100;lnZ_h500;likelihood_h10;likelihood_h20;likelihood_h100;likelihood_h500];
disp(['h10 -- 归一化常数：' num2str(z(1)) '  似然值：' num2str(z(5))]);
disp(['h20 -- 归一化常数：' num2str(z(2)) '  似然值：' num2str(z(6))]);
disp(['h100 -- 归一化常数：' num2str(z(3)) '  似然值：' num2str(z(7))]);
disp(['h500 -- 归一化常数：' num2str(z(4)) '  似然值：' num2str(z(8))]);
save('z.mat','z');