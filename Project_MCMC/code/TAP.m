function lnZ = TAP(W,a,b,iteration_num)
%输出参数
%lnZ：归一化系数Z取ln值
%输入参数
%W：W_ij矩阵
%a：观测变量偏置项
%b：隐变量偏置项
%iteration_num：迭代次数

%%%___做一些准备工作___%%%
[visableCount,hiddenCount] = size(W);      %获取隐变量和观测变量的大小
sigma = @g;                                             %sigma(x)函数也即g(x)函数
m_v = 0.05 * ones(1,visableCount);            %初始化m_v
m_h = 0.05 * ones(1,hiddenCount);            %初始化m_h
for n = 1 : iteration_num                            %迭代
    m_h = sigma(b + m_v * W - ((m_v - m_v.^2) * (W.^2)).*(m_h - 1/2));      %计算m_h[t+1]
    m_v = sigma(a + m_h * W' - ((m_h - m_h.^2) * (W'.^2)).*(m_v - 1/2));    %计算m_v[t+1]
end
%计算S(m_v,m_h)
S_mv_mh = m_v * log(m_v)' + (1 - m_v) * log(1 - m_v)' + m_h * log(m_h)' + (1 - m_h) * log(1 - m_h)';
%计算lnZ
lnZ = -S_mv_mh + a * m_v' + b * m_h' + m_v * W * m_h' + (m_v - m_v.^2) * ((W.^2)/2) * (m_h - m_h.^2)';