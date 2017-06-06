clear;close all;clc;
filePath = fullfile('images','1');
photos = dir(fullfile(filePath, '*.bmp'));               %所有碎片图像
photoNum = length(photos);                             %碎片图像数量
[height, width] = size(imread(fullfile(filePath, photos(1).name)));
%二值图像信息
leftBinary = zeros(height, photoNum);
rightBinary = zeros(height, photoNum);
%灰度图像信息
photosGray = zeros(height, width, photoNum);
leftGray = zeros(height, photoNum);
rightGray = zeros(height, photoNum);
%左右空白带宽度
leftLen = zeros(photoNum, 1);
rightLen = zeros(photoNum, 1);
for i = 1 : photoNum
    %读入图像，进行二值化处理
    photosGray(:, :, i) = imread(fullfile(filePath, photos(i).name));
    photo = binaryzation(photosGray(:, :, i));
    %记录左右空白带的宽度
    leftLen(i) = find(sum(photo) ~= height, 1, 'first') - 1;
    rightLen(i) = width - find(sum(photo) ~= height, 1, 'last');
    %保存左右边缘信息
    leftBinary(:, i) = double(photo(:, 1));
    rightBinary(:, i) = double(photo(:, end));
    leftGray(:, i) = photosGray(:, 1, i);
    rightGray(:, i) = photosGray(:, end, i);
end

[~, leftMost] = max(leftLen);                              %左边缘空白最宽的碎片也就是最左碎片
[~, rightMost] = max(rightLen);                         %右边缘空白最宽的碎片也就是最右碎片
%sortedId = match(left, right, leftMost, rightMost);%正确排列之后的序号
sortedId = match2(leftGray, rightGray, leftMost, rightMost);

joinPhoto = zeros(height, width * photoNum);
for i = 1 : photoNum
    photo = binaryzation(imread(fullfile(filePath, photos(sortedId(i)).name)));
    %拼接复原图像
    joinPhoto(:, (i - 1) * width +1 : i * width) = photo;
end

imwrite(joinPhoto, 'ex2_1.bmp');