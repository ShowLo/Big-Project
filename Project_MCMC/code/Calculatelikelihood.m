%此代码参考了作者Ruslan Salakhutdinov的开源代码
%网址为http://www.utstat.utoronto.ca/~rsalakhu/rbm_ais.html
%特此说明

function likelihood = Calculatelikelihood(W,a,b,testbatchdata,lnZ)
%输出参数
%likelihood：似然值
%W：W_ij矩阵
%a：观测变量偏置项
%b：隐变量偏置项
%testbatcdata：测试数据
%lnZ：归一化系数的ln值

[M,visableCount,N] = size(testbatchdata);                             %获得测试数据的规模
batchdata = zeros(M * N,visableCount);;
for n = 1 : N
    batchdata(M * (n - 1) + 1 : M * n,:) = testbatchdata(:,:,n);  %重整为二维矩阵
end
p = batchdata * b' + sum(log(1+exp(ones(M * N,1) * a + batchdata * W)),2);
likelihood = sum(p)/(M * N)  - lnZ;                                        %似然值