clear;close all;clc;
lena = imread('images/Lena.bmp');
[height, width] = size(lena);
xLen = height * 2;
yLen = width * 2;
lenaWithAxis = zeros(xLen, yLen, 'uint8');                              %建立坐标轴,高度方向为x轴,宽度方向为y轴
lena_x = 0.5 * height : 1.5 * height - 1;
lena_y = 0.5 * width : 1.5 * width - 1;
lenaWithAxis(lena_x, lena_y) = lena;                                      %把lena图放到坐标轴上去

%%平移
lena_T = zeros(xLen, yLen, 'uint8');
Tx = -100;
Ty = -50;
T = [1, 0, Tx; 0, 1, Ty; 0, 0, 1];                                                 %平移变换矩阵

% 太慢了还不如循环快。。。
% x_before = reshape(repmat(x, width, 1), 1, height * width);
% y_before = repmat(y, 1, height);
% xy_after = T * [x_before; y_before; ones(1, height * width)];
% lena_T(xy_after(1, :), xy_after(2, :)) = lenaWithAxis(x_before, y_before);

for x = lena_x
    for y = lena_y
        newAxis = T * [x; y; 1];                                                      %变换后的坐标
        lena_T(newAxis(1), newAxis(2)) = lenaWithAxis(x, y);       %将图像移动到变换后的坐标处
    end
end

figure;
subplot(1, 2, 1);
imshow(lenaWithAxis);
title('平移之前');
subplot(1, 2, 2);
imshow(lena_T);
title('平移之后');

%%放缩
Sx = 1.25;
Sy = 1.25;
S = [Sx, 0, 0; 0, Sy, 0; 0, 0, 1];                                                 %放缩矩阵
S_inv = S^(-1);
xMin = lena_x(1);
xMax = lena_x(end);
yMin = lena_y(1);
yMax = lena_y(end);
lena_S_nearest = zeros(xLen, yLen, 'uint8');
lena_S_bilinear = zeros(xLen, yLen, 'uint8');
for x = 1 : xLen
    for y = 1 : yLen
        xy_before = S_inv * [x; y; 1];                                             %后向映射
        x_before = xy_before(1);
        y_before = xy_before(2);
        %判断后向映射之后的点是否位于图像中
        if(x_before >= xMin && x_before <= xMax && y_before >= yMin && y_before <= yMax)
            %采用最近邻插值
            lena_S_nearest(x, y) = lenaWithAxis(round(x_before), round(y_before));
            %采用双线性插值
            A = lenaWithAxis(floor(x_before), floor(y_before));
            B = lenaWithAxis(ceil(x_before), floor(y_before));
            C = lenaWithAxis(floor(x_before), ceil(y_before));
            D = lenaWithAxis(ceil(x_before), ceil(y_before));
            E = (x_before - floor(x_before)) * (B - A) + A;
            F = (x_before - floor(x_before)) * (D - C) + C;
            lena_S_bilinear(x, y) = (y_before - floor(y_before)) * (F - E) + E;
        end
    end
end

figure;
% subplot(1, 3, 1);
% imshow(lenaWithAxis);
% title('放缩之前');
subplot(1, 2, 1);
imshow(lena_S_nearest);
title('放缩并采用最近邻插值');
subplot(1, 2, 2);
imshow(lena_S_bilinear);
title('放缩并采用双线性插值');

%%旋转
gamma = -pi/10;
%旋转矩阵
R = [cos(gamma), sin(gamma), 0; -sin(gamma), cos(gamma), 0; 0, 0, 1];
R_inv = R^(-1);
lena_R_nearest = zeros(xLen, yLen, 'uint8');
lena_R_bilinear = zeros(xLen, yLen, 'uint8');
for x = 1 : xLen
    for y = 1 : yLen
        xy_before = R_inv * [x; y; 1];                                             %后向映射
        x_before = xy_before(1);
        y_before = xy_before(2);
        %判断后向映射之后的点是否位于图像中
        if(x_before >= xMin && x_before <= xMax && y_before >= yMin && y_before <= yMax)
            %采用最近邻插值
            lena_R_nearest(x, y) = lenaWithAxis(round(x_before), round(y_before));
            %采用双线性插值
            A = lenaWithAxis(floor(x_before), floor(y_before));
            B = lenaWithAxis(ceil(x_before), floor(y_before));
            C = lenaWithAxis(floor(x_before), ceil(y_before));
            D = lenaWithAxis(ceil(x_before), ceil(y_before));
            E = (x_before - floor(x_before)) * (B - A) + A;
            F = (x_before - floor(x_before)) * (D - C) + C;
            lena_R_bilinear(x, y) = (y_before - floor(y_before)) * (F - E) + E;
        end
    end
end
figure;
% subplot(1, 3, 1);
% imshow(lenaWithAxis);
% title('放缩之前');
subplot(1, 2, 1);
imshow(lena_R_nearest);
title('旋转并采用最近邻插值');
subplot(1, 2, 2);
imshow(lena_R_bilinear);
title('旋转并采用双线性插值');