function sortedId = match(left, right, leftId, rightId)
%利用同或和为匹配程度度量方法的碎片重排
%输入参数
%left: 碎片左边缘
%right: 碎片右边缘
%leftId: 最左碎片序号
%rightId: 最右碎片序号
%输出参数
%sortedId: 正确排列的碎片序号
[~, photoNum] = size(left);
added = zeros(photoNum, 1);                           %记录是否已被加入了
rightEdge = right(:, leftId);                                 %待匹配右边缘
leftEdge = left(:, rightId);                                    %待匹配左边缘
sortedId = zeros(photoNum, 1);
sortedId(1) = leftId;                                            %最左的碎片的序号放入正确排列序号序列的最左边
sortedId(end) = rightId;                                     %最右的碎片的序号放入正确排列序号序列的最右边
added(leftId) = 1;                                               %最左的碎片被记录为已加入
added(rightId) = 1;                                             %最右的碎片被记录为已加入

frontId = 2;                                                         %加入与待匹配右边缘匹配的碎片在碎片序列中的正确序号
backId = photoNum - 1;                                    %加入与待匹配左边缘匹配的碎片在碎片序列中的正确序号
for i = 1 : photoNum - 2
    LmatchR = zeros(photoNum, 1);
    RmatchL = zeros(photoNum, 1);
    for j = 1 : photoNum
        if(~added(j))                                               %只对于尚未加入序列的碎片做以下操作
            %用同或和的方法计算其他碎片的左边缘与待匹配右边缘的匹配程度
            LmatchR(j) = sum(~xor(left(:, j), rightEdge));
        end
    end
    for j = 1 : photoNum
        if(~added(j))                                               %只对于尚未加入序列的碎片做以下操作
            %用同或和的方法计算其他碎片的右边缘与待匹配左边缘的匹配程度
            RmatchL(j) = sum(~xor(right(:, j), leftEdge));
        end
    end

    [LRvalue, nextRight] = max(LmatchR);            %与待匹配右边缘匹配程度最大的左边缘
    [RLvalue, nextLeft] = max(RmatchL);              %与待匹配左边缘匹配程度最大的右边缘

    if(LRvalue > RLvalue)                                      %与待匹配右边缘匹配程度更大，下一张碎片加到右边
        next = nextRight;
	else                                                                 %与待匹配左边缘匹配程度更大，下一张碎片加到左边
        next = nextLeft;
    end

    if(next == nextRight)
        rightEdge = right(:, next);                           %当前右边缘更新为下一张碎片的右边缘
        added(next) = 1;                                         %标记已加入
        sortedId(frontId) = next;                            %加入到序号序列中去
        frontId = frontId + 1;
    else
        leftEdge = left(:, next);                                %当前左边缘更新为下一张碎片的左边缘
        added(next) = 1;                                         %标记已加入
        sortedId(backId) = next;                             %加入到序号序列中去
        backId = backId - 1;
    end
end