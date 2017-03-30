function correlation_coefficient = CorrCoef(N)
%输入参数
%N：样本点总数
%输出参数
%correlation_coefficient：估计的相关系数
x0 = [0,0];                    %初始状态
x_origin = x0;
X = zeros(N,2);             %记录整个链的状态
miu1 = 5;                     %X1的理论均值
miu2 = 10;                   %X2的理论均值
sigma1 = 1;                  %X1的理论标准差
sigma2 = 2;                  %X2的理论标准差
x1 = unifrnd(miu1 - 3.8 * sigma1,miu1 + 3.8 * sigma1,N,1); %对于X1，大致根据正态分布的3sigma原则生成随机分布的N个数
x2 = unifrnd(miu2 - 3.8 * sigma2,miu2 + 3.8 * sigma2,N,1); %对于X2，大致根据正态分布的3sigma原则生成随机分布的N个数
u = rand(N,1);                                                                     %生成在（0,1）范围内均匀分布的N个数
for n = 1 : N
    x_new = [x1(n),x2(n)];                                                      %生成新的状态
    %计算接收概率
    accept_prob = min(1,Normal(x_new(1),x_new(2)) / Normal(x_origin(1),x_origin(2)));
    if(u(n) <= accept_prob)                                                   %接受转移
        X(n,:) = x_new;                                                            %转移到新的状态
        x_origin = x_new;
    else                                                                                %拒绝转移
        X(n,:) = x_origin;                                                         %保留在原状态
    end
end
miu1_estimation = sum(X(:,1)) / N;                                      %计算X1的均值
miu2_estimation = sum(X(:,2)) / N;                                      %计算X2的均值
%计算相关系数
correlation_coefficient = sum((X(:,1) - miu1_estimation).*(X(:,2) - miu2_estimation)) /...
    (sqrt(sum((X(:,1) - miu1_estimation).^2)) * sqrt(sum((X(:,2) - miu2_estimation).^2)));
