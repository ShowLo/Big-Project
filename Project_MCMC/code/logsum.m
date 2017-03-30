%此代码参考了作者Ruslan Salakhutdinov的开源代码
%网址为http://www.utstat.utoronto.ca/~rsalakhu/rbm_ais.html
%特此说明

%计算log(sum(exp(x))
%为了避免溢出
%根据log(sum(exp(x))) = alpha + log(sum(exp(x-alpha)));
function log_sum = logsum(x)
%输出参数
%log_sum：log(sum(exp(x))
%输入参数
%x：一个向量x

if(length(x) == 1)                                              %只有一个数的话直接返回
    log_sum = x; 
    return; 
end

alpha = max(x) - log(realmax)/2;                       %取一个合适的alpha值
log_sum = alpha + log(sum(exp(x - alpha)));     %计算结果