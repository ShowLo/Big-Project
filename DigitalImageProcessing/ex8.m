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
        %i�ص������
        mixPic = alpha * carrier + (1 - alpha) * mixPic;
    end
    mixPic = uint8(mixPic);                                   %i�ص��������ɣ�תΪ������ʾ��ͼ��
    subplot(2, iterationNum, i);
    imshow(mixPic);
    title([int2str(i), '�ص������ͼ��'])
    recoverPic = double(mixPic);                          %����i�ص������ͼ��
    for k = 1 : i
        %�ָ�ͼ��
        recoverPic = (recoverPic - alpha * carrier)./(1 - alpha);
    end
    recoverPic = uint8(recoverPic);                       %�ָ���ɣ�תΪ������ʾ��ͼ��
    subplot(2, iterationNum, i + iterationNum);
    imshow(recoverPic);
    title([int2str(i), '�ص����ָ�ͼ��']);
    %����ָ�ͼ�������ͼ��ľ��������
    MSE(i) = sqrt(sum(sum((double(recoverPic) - toHide).^2))/N);
    %disp([int2str(i),'�ص����ָ�ͼ��ľ��������Ϊ',num2str(MSE)]);
end

figure;
plot(iter, MSE);
title('�ָ�ͼ��ľ������������������仯���');
xlabel('��������');
ylabel('���������');

alpha = 0 : 0.01 : 1;
MSE_carrier = zeros(size(alpha));
MSE_recover = zeros(size(alpha));
for i = 1 : length(alpha)
    %���ͼ��
    mixPic = uint8(alpha(i) * carrier + (1 - alpha(i)) * toHide);
    %�ָ�ͼ��
    recoverPic = (double(mixPic) - alpha(i) * carrier)./(1 - alpha(i));
    %��������ͼ����������
    MSE_carrier(i) = sqrt(sum(sum((double(mixPic) - carrier).^2))/N);
    %����ָ�ͼ����������
    MSE_recover(i) = sqrt(sum(sum((double(recoverPic) - toHide).^2))/N);
end
figure;
subplot(1, 2, 1);
plot(alpha, MSE_carrier);
title('����ͼ����������');
subplot(1, 2, 2);
plot(alpha, MSE_recover);
title('�ָ�ͼ����������');

figure;
plot(alpha, MSE_carrier + MSE_recover);
title('���ͼ����ָ�ͼ��ľ���������');