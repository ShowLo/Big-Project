%此代码参考了作者Ruslan Salakhutdinov的开源代码
%网址为http://www.utstat.utoronto.ca/~rsalakhu/rbm_ais.html
%特此说明

function lnZ_theta = AIS(W,a,b,visable_A,K,runCount)
%输出参数
%lnZ_theta：归一化常数的ln值
%输入参数
%W：W_ij矩阵
%a：隐变量偏置项
%b：观测变量偏置项
%ln_Visual_A：theta_A里面的a
%K：要生成的beta的个数
%runCount：运行次数

%%%___做一些准备工作___%%%
[visiableCount,hiddenCount] = size(W);     %获取隐变量和观测变量的大小
b_A = repmat(visable_A,runCount,1);         %赋值runCount份theta_A里面的b
a_B = repmat(a,runCount,1);                     %复制runCount份theta_B中的a
b_B = repmat(b,runCount,1);                     %复制runCount份theta_B中的b
lnOmega = zeros(runCount,1);                  %Omega_AIS取ln对数后的值

%%%%%%%%%___开始AIS算法___%%%%%%%%%

%%%___先生成beta_k___%%%
beta = linspace(0,1,K);                              %生成beta(0)到beta(K)，范围从0到1

%%%___从"base-rate"RBM中采样___%%%
temp = repmat(g(visable_A),runCount,1);  %生成服从P_A的概率分布
x = temp > rand(runCount,visiableCount);%采样得到x
%计算的时候对Omege_AIS取ln对数之后得到的是lnP*_k-lnP*_(k-1)，所以这里先计算的是后面一项即lnP*_0
%这里注意theta_A的元素都取为零，且第一步beta(0)=0，以及有一项的数值是固定的在相减中消去了(下同)
lnOmega = lnOmega - (x * visable_A' + hiddenCount * log(2));

bA_x = x * visable_A';                                %计算(对i求和)bi_A * xi
bB_x = x * b';                                            %计算(对i求和)bi_B * xi
WBx_aB = x * W + a_B;                             %计算(对i求和)Wij_B * xi + aj_B

%%%___AIS的循环部分___%%%
for beta_k = beta(2 : K-1)
    expWBx_aB = exp(beta_k * WBx_aB);    %计算exp{beta_k*((对i求和)Wij_B * xi + aj_B)}
    %计算lnP*_k(x_k)
    lnOmega = lnOmega + (1 - beta_k) * bA_x +beta_k * bB_x + sum(log(1 + expWBx_aB),2);
    
    %%%___开始采样生成下一个x
    %先得到中间的隐变量
    p_hB_x = expWBx_aB./(expWBx_aB + 1);                                  %计算p(hj_B = 1|x)
    hj_B = p_hB_x > rand(runCount,hiddenCount);                         %采样得到hj_B
    %然后借助隐变量作为中间跳板生成下一个x
    p_x_new_h = g((1 - beta_k) * b_A + beta_k * (hj_B * W' + b_B)); %计算p(x' = 1|h)
    x = p_x_new_h > rand(runCount,visiableCount);                        %采样得到x'
    
    %更新数据
    bA_x = x * visable_A';                            %计算(对i求和)bi_A * xi
    bB_x = x * b';                                         %计算(对i求和)bi_B * xi
    WBx_aB = x * W + a_B;                          %计算(对i求和)Wij_B * xi + aj_B
    expWBx_aB = exp(beta_k * WBx_aB);     %计算exp{beta_k*((对i求和)Wij_B * xi + aj_B)}
    %计算lnP*_k(x_k+1)
    lnOmega = lnOmega - ((1 - beta_k) * bA_x +beta_k * bB_x + sum(log(1 + expWBx_aB),2));
end

%注意此时beta_k = 1,可简化计算如下
expWBx_aB = exp(WBx_aB);
lnOmega = lnOmega + x * b' + sum(log(1 + expWBx_aB),2);

%计算r_AIS取ln的结果
ln_r_AIS = log(sum(exp(lnOmega))) - log(runCount);
%计算Z_A取ln的结果
lnZ_A = sum(log(1 + exp(visable_A))) + hiddenCount * log(2);
%计算Z_theta取ln的结果
lnZ_theta = ln_r_AIS + lnZ_A;