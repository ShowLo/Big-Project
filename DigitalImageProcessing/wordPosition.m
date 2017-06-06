function wordCount = wordPosition(image)
%计算文字的出现位置情况
%输入参数
%image:输入的二值化图像
%输出参数
%wordCount:文字位置情况，出现的地方为1，没出现的地方为0
wordCount = sum(~image, 2);                           %统计每行出现的文字数
wordCount = wordCount > 0;                            %出现文字置1，否则置0