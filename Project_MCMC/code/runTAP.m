clear all;close all;clc;
tic;
iteration_num = 12000;      %迭代次数
%估计各个RBM模型下的归一化常数
load('data/h10.mat');
lnZ_theta_h10 = TAP(parameter_W,parameter_b,parameter_a,iteration_num);
load('data/h20.mat');
lnZ_theta_h20 = TAP(parameter_W,parameter_b,parameter_a,iteration_num);
load('data/h100.mat');
lnZ_theta_h100 = TAP(parameter_W,parameter_b,parameter_a,iteration_num);
load('data/h500.mat');
lnZ_theta_h500 = TAP(parameter_W,parameter_b,parameter_a,iteration_num);
toc;