I = rgb2gray(imread('Display.bmp'));
imshow(I)
%BW = im2bw(I);
BW = edge(I,'log')
figure
imshow(BW)
dim = size(BW)
col = round(dim(2)/2)-90;
row = min(find(BW(:,col)))
boundary = bwtraceboundary(BW,[row, col],'N');
figure
imshow(I)
hold on;
plot(boundary(:,2),boundary(:,1),'g','LineWidth',3);