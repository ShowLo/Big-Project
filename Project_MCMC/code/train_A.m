%此代码参考了作者Ruslan Salakhutdinov的开源代码
%网址为http://www.utstat.utoronto.ca/~rsalakhu/rbm_ais.html
%特此说明

function ln_Visable_A = train_A(testbatchdata)
%输出参数
%ln_Visable_A：取ln值之后的theta_A的b_A
%输入参数
%testbatchdata：训练数据
[a,visableCount,b] = size(testbatchdata);
total = zeros(visableCount,1);
for n = 1 : b
    temp = sum(testbatchdata(:,:,n));
    total = total + temp';
end

lp = 5;
p = (total + lp * b)/(a * b + lp * b);
ln_Visable_A = log(p) - log(1 - p);