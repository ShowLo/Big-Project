function [max0num, max1num] = continuousNum(numList)
%计算二值化数组中连0和连1的最大次数
%输入参数
%numList: 二值化数组
%输出参数
%max0num: 0在数组中连续出现的最多次数
%max1num: 1在数组中连续出现的最多次数
numLen = length(numList);
max0num = 0;
max1num = 0;
count0 = 1;
count1 = 1;
for i = 2 : numLen
    if(numList(i) == 0)
        if(numList(i - 1) == 0)
            count0 = count0 + 1;
            max0num = max(max0num, count0);
        else
            count1 = 0;
            count0 = 1;
        end
    else
        if(numList(i - 1) == 1)
            count1 = count1 + 1;
            max1num = max(max1num, count1);
        else
            count0 = 0;
            count1 = 1;
        end
    end
end