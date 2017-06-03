clear;close all;clc;
carrier = double(imread('images/Girl.bmp'));
toHide = double(imread('images/Couple.bmp'));
[height, width] = size(carrier);
N = height * width;
alpha = 0.7;
iterationNum = 6;
iter = 1 : iterationNum;
MSE = zeros(iterationNum, 1);

figure;
for i = iter
    mixPic = toHide;
    for j = 1 : i
        %i重迭代混合
        mixPic = alpha * carrier + (1 - alpha) * mixPic;
    end
    mixPic = uint8(mixPic);                                   %i重迭代混合完成，转为可以显示的图像
    subplot(2, iterationNum, i);
    imshow(mixPic);
    title([int2str(i), '重迭代混合图像'])
    recoverPic = double(mixPic);                          %读入i重迭代混合图像
    for k = 1 : i
        %恢复图像
        recoverPic = (recoverPic - alpha * carrier)./(1 - alpha);
    end
    recoverPic = uint8(recoverPic);                       %恢复完成，转为可以显示的图像
    subplot(2, iterationNum, i + iterationNum);
    imshow(recoverPic);
    title([int2str(i), '重迭代恢复图像']);
    %计算恢复图像和隐藏图像的均方根误差
    MSE(i) = sqrt(sum(sum((double(recoverPic) - toHide).^2))/N);
    %disp([int2str(i),'重迭代恢复图像的均方根误差为',num2str(MSE)]);
end

figure;
plot(iter, MSE);
title('恢复图像的均方根误差随迭代次数变化情况');
xlabel('迭代次数');
ylabel('均方根误差');

alpha = 0 : 0.01 : 1;
MSE_carrier = zeros(size(alpha));
MSE_recover = zeros(size(alpha));
for i = 1 : length(alpha)
    %混合图像
    mixPic = uint8(alpha(i) * carrier + (1 - alpha(i)) * toHide);
    %恢复图像
    recoverPic = (double(mixPic) - alpha(i) * carrier)./(1 - alpha(i));
    %计算载体图像均方根误差
    MSE_carrier(i) = sqrt(sum(sum((double(mixPic) - carrier).^2))/N);
    %计算恢复图像均方根误差
    MSE_recover(i) = sqrt(sum(sum((double(recoverPic) - toHide).^2))/N);
end
figure;
subplot(1, 2, 1);
plot(alpha, MSE_carrier);
title('载体图像均方根误差');
subplot(1, 2, 2);
plot(alpha, MSE_recover);
title('恢复图像均方根误差');

figure;
plot(alpha, MSE_carrier + MSE_recover);
title('混合图像与恢复图像的均方根误差和');