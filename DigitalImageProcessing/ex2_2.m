clear;close all;clc;
filePath = fullfile('images','2');
photos = dir(fullfile(filePath, '*.bmp'));               %所有碎片图像
photoNum = length(photos);                             %碎片图像数量
[height, width] = size(imread(fullfile(filePath, photos(1).name)));

wordCount = zeros(height, photoNum);
count0 = zeros(photoNum, 1);
count1 = zeros(photoNum, 1);

%二值化图像
photosBinary = zeros(height, width, photoNum);
leftBinary = zeros(height, photoNum);
rightBinary = zeros(height, photoNum);

%灰度图像
photosGray = zeros(height, width, photoNum); 
leftGray = zeros(height, photoNum);
rightGray = zeros(height, photoNum);

%%读入图像进行一些初步的计算
for i = 1 : photoNum
    %读入灰度图像
    photosGray(:, :, i) = imread(fullfile(filePath, photos(i).name));
    %进行二值化处理
    photo = binaryzation(imread(fullfile(filePath, photos(i).name)));
    photosBinary(:, :, i) = photo;

    %保存左右边缘信息
    leftBinary(:, i) = double(photo(:, 1));
    rightBinary(:, i) = double(photo(:, end));
    leftGray(:, i) = photosGray(:, 1, i);
    rightGray(:, i) = photosGray(:, end, i);

    %计算文字出现模型
    wordCount(:, i) = double(wordPosition(photo));
    %计算连0和连1长度
    [count0(i),count1(i)] = continuousNum(wordCount(:, i));
end

%统计得出真正的连0和连1长度
table0 = tabulate(count0);
[~, id] = max(table0(:, 2));
len0 = table0(id);
table1 = tabulate(count1);
[~, id] = max(table1(:, 2));
len1 = table0(id);

suppleCount = zeros(size(wordCount));
for i = 1 : photoNum
    %对文字出现模型进行修补
    suppleCount(:, i) = supplement(wordCount(:, i), len0, len1, 0);
end


%%先对行进行匹配，按行的匹配程度将所有碎片先分成11类
portraitNum = 11;                                              %横切数
transverseNum = 19;                                          %纵切数

matchLine = zeros(photoNum, photoNum);
for i = 1 : photoNum
    for j = 1 : photoNum
        %计算行匹配程度，依据为文字出现模型的匹配程度
        matchLine(i, j) = sum(~xor(suppleCount(:, i), suppleCount(:, j)));
    end
end
sameLine = zeros(portraitNum, transverseNum);
added = zeros(photoNum, 1);
count = 1;
for i = 1 : photoNum
    if(added(i))                                                      %如果当前碎片已被加入，跳过
        continue;
    end
    %从匹配矩阵中找到匹配程度最大的19个碎片，认为是同一行的
    %matchMost = find(matchLine(i, :) > height * 0.9);
    %sameLine(count, 1 : length(matchMost)) = matchMost;
    [~, matchMost] = sort(matchLine(i, :), 'descend');
    sameLine(count, 1 : transverseNum) = matchMost(1 : transverseNum);
    count = count + 1;
    added(matchMost(1 : transverseNum)) = 1;
end


%%找出最左和最右的各11个碎片
leftSum = sum(leftBinary);
rightSum = sum(rightBinary);
leftId = find(leftSum == height);                        %左边缘为空白的碎片序号
rightId = find(rightSum == height);                   %右边缘为空白的碎片序号
leftEdge = photosBinary(:, :, leftId);                    %左边缘为空白的碎片
rightEdge = photosBinary(:, :, rightId);               %右边缘为空白的碎片
leftLen = zeros(length(leftId));
for i = 1 : length(leftId)
    %左边缘为空白的碎片其空白的宽度
    leftLen(i) = find(sum(leftEdge(:, :, i)) ~= height, 1, 'first') - 1;
end
[~, id] = sort(leftLen, 'descend');
leftIndex = leftId(id(1 : portraitNum));                %找出真正的11个最左碎片
rightLen = zeros(length(rightId));
for i = 1 : length(rightId)
    %右边缘为空白的碎片其空白的宽度
    rightLen(i) = width - find(sum(rightEdge(:, :, i)) ~= height, 1, 'last');
end
[~, id] = sort(rightLen, 'descend');
rightIndex = rightId(id(1 : portraitNum));           %找出真正的11个最右碎片


%%对每行分别进行排列
sortedIndex = zeros(portraitNum, transverseNum);
%先把当前行的最左最右碎片找出来然后再做排列
for i = 1 : portraitNum
    realIndex = sameLine(i, :);
    for j = 1 : transverseNum
        if(ismember(realIndex(j), leftIndex))           %找到当前行的最左碎片
            leftMost = j;
            break;
        end
    end
    for j = 1 : transverseNum
        if(ismember(realIndex(j), rightIndex))         %找到当前行的最左碎片
            rightMost = j;
            break;
        end
    end
    %对本行做碎片排列
    %sortedIndex(i, :) = match(left(:, realIndex), right(:, realIndex), leftMost, rightMost);
    sortedIndex(i, :) = match2(leftGray(:, realIndex), rightGray(:, realIndex), leftMost, rightMost);
    sortedIndex(i, :) = realIndex(sortedIndex(i, :));
end

%%人工干预，处理未正确排列的行，每行各有两个块需要互换位置
% sortedIndex(3, :) = [sortedIndex(3, 1 : 7), sortedIndex(3, 10 : 14), sortedIndex(3, 8 : 9), sortedIndex(3, 15 : end)];
% sortedIndex(5, :) = [sortedIndex(5, 1 : 7), sortedIndex(5, 11 : 16), sortedIndex(5, 8 : 10), sortedIndex(5, 17 : end)];
% sortedIndex(7, :) = [sortedIndex(7, 1 : 10), sortedIndex(7, 16 : 17), sortedIndex(7, 11 : 15), sortedIndex(7, 18 : end)];
% sortedIndex(9, :) = [sortedIndex(9, 1 : 2), sortedIndex(9, 13 : 15), sortedIndex(9, 8 : 12), sortedIndex(9, 3 : 7), sortedIndex(9, 16 : end)];
% sortedIndex(10, :) = [sortedIndex(10, 1 : 2), sortedIndex(10, 7 : 9), sortedIndex(10, 6), sortedIndex(10, 3 : 5), sortedIndex(10, 10 : end)];
% sortedIndex(11, :) = [sortedIndex(11, 1 : 9), sortedIndex(11, 16 : 17), sortedIndex(11, 13 : 15), sortedIndex(11, 10 : 12), sortedIndex(11, 18 : end)];
sortedIndex(3, :) = [sortedIndex(3, 1 : 8), sortedIndex(3, 11 : 14), sortedIndex(3, 10), sortedIndex(3, 9), sortedIndex(3, 15 : end)];
sortedIndex(7, :) = [sortedIndex(7, 1 : 10), sortedIndex(7,  13), sortedIndex(7, 12), sortedIndex(7, 11), sortedIndex(7, 14 : end)];
sortedIndex(9, :) = [sortedIndex(9, 1 : 2), sortedIndex(9, 13 : 15), sortedIndex(9, 8 : 12), sortedIndex(9, 3 : 7), sortedIndex(9, 16 : end)];
sortedIndex(10, :) = [sortedIndex(10, 1 : 2), sortedIndex(10, 7 : 9), sortedIndex(10, 6), sortedIndex(10, 3 : 5), sortedIndex(10, 10 : end)];
sortedIndex(11, :) = [sortedIndex(11, 1 : 9), sortedIndex(11, 14 : 18), sortedIndex(11, 10 : 13), sortedIndex(11, 19)];

%%将排列好的各行中所有碎片整合成一个横切片，然后对横切片进行上下排列
%二值化图像
linePhotoBinary = zeros(height, width * transverseNum, portraitNum);
topBinary = zeros(width * transverseNum, portraitNum);
bottomBinary = zeros(width * transverseNum, portraitNum);
%灰度图像
linePhotoGray = zeros(height, width * transverseNum, portraitNum);
topGray = zeros(width * transverseNum, portraitNum);
bottomGray = zeros(width * transverseNum, portraitNum);
%空白宽度
topBlank = zeros(portraitNum, 1);
bottomBlank = zeros(portraitNum, 1);

for i = 1 : portraitNum
    for j = 1 : transverseNum
        %先保存整理好的各行碎片
        linePhotoBinary(:, (j - 1) * width + 1 : j * width, i) = photosBinary(:, :, sortedIndex(i, j));
        linePhotoGray(:, (j - 1) * width + 1 : j * width, i) = photosGray(:, :, sortedIndex(i, j));
    end

    %保存上下边缘信息
    topBinary(:, i) = linePhotoBinary(1, :, i);
    bottomBinary(:, i) = linePhotoBinary(end, :, i);
    topGray(:, i) = linePhotoGray(1, :, i);
    bottomGray(:, i) = linePhotoGray(end, :, i);

    %记录各行的顶部和底部空白高度
    topBlank(i) = find(sum(linePhotoBinary(:, :, i), 2) ~= width * transverseNum, 1, 'first') - 1;
    bottomBlank(i) = height - find(sum(linePhotoBinary(:, :, i), 2) ~= width * transverseNum, 1, 'last');
end
%找出顶部和底部的横切片
[~, topId] = max(topBlank);
[~, bottomId] = max(bottomBlank);

%对所有横切片进行一次上下排列
%top2bottomId = match(topBinary, bottomBinary, topId, bottomId)';
top2bottomId = match2(topGray, bottomGray, topId, bottomId)';

%人工干预，有两个块需要互换位置
top2bottomId = [top2bottomId(1 : 4), top2bottomId(7), top2bottomId(5 : 6), top2bottomId(8 : end)];

%最终的重排序号
rearrange = sortedIndex(top2bottomId, :);

%%复原完成，保存复原图
joinPhoto = zeros(height * portraitNum, width * transverseNum);
for i = 1 : portraitNum
    %复原图片
    joinPhoto((i - 1) * height + 1 : i * height, :) = linePhotoBinary(:, :, top2bottomId(i));
end
imwrite(joinPhoto, 'ex2_2.bmp');