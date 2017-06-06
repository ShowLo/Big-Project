function binaryImage = binaryzation(image)
%二值化处理函数
%输入参数
%image:输入的图像
%输出参数
%binaryImage:二值化之后的图像
maxPixel = max(max(image));
minPixel = min(min(image));
%阈值设在图像灰度最大值和最小值中间
threhold = minPixel + (maxPixel - minPixel)/2;
%大于阈值置一，小于阈值置零，完成二值化处理
binaryImage = image > threhold;