function newList = supplement(numList, len0, len1, error)
%补足文字出现模型
%输入参数
%numList: 需要进行补足的文字出现模型数组
%len0: 连0个数
%len1: 连1个数
%error: 允许的误差
numLen = length(numList);
num0 = 0;
num1 = 0;

i = 1;
%先消除顶部文字中间可能出现的空隙
if(numList(1) == 1)
    while(numList(i) == 1)                                    %先遍历到第一个0处
        i = i + 1;
        num1 = num1 + 1;
    end
    if(abs(len1 - num1) > error)                           %第一处连1的长度不足，有可能出现空隙
        while(numList(i) == 0)                                %计算第一处连0的长度
            i = i + 1;
            num0 = num0 + 1;
        end
        if(len0 > num0 * 2)                                     %连0的长度过小，说明是空隙
            numList(i - num0 : i - 1) = 1;                  %将空隙补上
        end
    end
end

%补顶部缺失的文字
i = find(numList == 0, 1, 'first');                          %找到第一个零的地方
num0 = 0;
while(numList(i) == 0)                                        %然后找到从这里开始的第一个1
    i = i + 1;
    num0 = num0 + 1;
end
if(abs(num0 - len0) > error)                               %如果在此之前有太多连0说明顶部文字缺失，补上连1                         
    numList(max(1, i - len0 - len1) : i - len0) = 1;
end

%补中部及底部缺失的文字及可能出现的空隙
num1 = 1;
while(i <= numLen)
    if(numList(i) == 0)                                          %当前为0
        if(numList(i - 1) == 0)                                 %前一个为0
            num0 = num0 + 1;
            if(num0 - len0 > error)                           %连0太多了，要开始有文字缺失，得开始连1
                numList(i) = 1;
                num0 = 0;
                num1 = num1 + 1;
            end
        else                                                             %前一个为1
            if(len1 - num1 > error)                           %连1还不够，要出现空隙，得继续补1
                numList(i) = 1;
                num1 = num1 + 1;
            else                                                         %1够了，开始连0
                num1 = 0;
                num0 = 1;
            end
        end
    else
        num1 = num1 + 1;
    end
    i = i + 1;
end
newList = numList;