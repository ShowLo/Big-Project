function lnZ = RTS(W,a,b,visable_A,K,N)
%输出参数
%lnZ：归一化常数取ln值
%输入参数
%W：W_ij矩阵
%a：观测变量偏置项
%b：隐变量偏置项
%K：向量长度
%N：迭代次数

%%%___做一些准备工作___%%%
[visableCount,hiddenCount] = size(W);     %获取隐变量和观测变量的大小
b_A = visable_A;                                        %theta_A里面的b
a_B = a;                                                    %theta_B中的a
b_B = b;                                                    %theta_B中的b
beta = linspace(0,1,K);                               %生成beta_k，范围从0到1
Z = ones(1,K);                                            %初始化Z，全部置一                              

%计算lnZ_A
lnZ_A = hiddenCount * log(2) + sum(log(1 + exp(b_A)));

iterationNum = 250;
for iterationIndex = 1 : iterationNum
    c = zeros(1,K);                                         %初始化c为0
    x = zeros(1,visableCount);                       %初始化x为0
    for n = 1 : N
        beta_iter = beta(randi(K));                    %从之前的beta里面随机抽取一个数
        p_hB_x = g(beta_iter * (x * W + a_B));   %p(hj_B = 1|x)
        h_B = p_hB_x > rand(1,hiddenCount);  %采样得到h_B
        %然后借助隐变量作为中间跳板生成下一个x
        p_x_new_h = g((1 - beta_iter) * b_A + beta_iter * (h_B * W' + b_B));
        x = p_x_new_h > rand(1,visableCount);%采样得到x'
        ln_f = zeros(1,K);                                  %初始化f(x)取ln值的结果
        bA_x = x * b_A';                                   %计算(对i求和)bi_A * xi
        bB_x = x * b_B';                                    %计算(对i求和)bi_B * xi
        Wx_a = x * W + a_B;                            %计算(对i求和)Wij_B * xi + aj_B
        for k = 1 : K                                          %计算各个具体的ln(f_k(x)/Z_k)
            ln_f(k) = (1 - beta(k)) * bA_x + hiddenCount * log(2) + beta(k) * bB_x ...
                + sum(log(1 + exp(beta(k) * Wx_a))) - log(Z(k)) - (1 - beta(k)) * lnZ_A;
        end
        q_beta_x = exp(ln_f - logsum(ln_f));       %计算q(beta_k|x)
        c = c + q_beta_x / N;                             %更新c_k
    end
    Z = Z.*(c/c(1));                                           %更新Z_k_RTS
end
lnZ = log(Z(end));                                           %取最后一个Z并取ln值