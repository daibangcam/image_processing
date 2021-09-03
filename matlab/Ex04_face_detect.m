clear all;
close all;
clc;
img_orig=imread('02.png');
%figure
%imshow(img_orig)
img = img_orig;
hsv=rgb2hsv(img);
h=hsv(:,:,1);
s=hsv(:,:,2);
v_=hsv(:,:,3);
[r c v]=find(h>0.25 | s<=0.15 | s>0.68); %non skin
numid=size(r,1);
for i=1:numid
img(r(i),c(i),:)=0;
end
%figure
%imshow(img);
I = rgb2gray(img);
%figure
%imshow(I)
threshold = graythresh(I);
bw = im2bw(I,threshold);
bw = bwareaopen(bw,500);
%figure
%imshow(bw)
s = regionprops(bw,'Centroid','EquivDiameter');
%figure
%imshow(img_orig);
figure
subplot(2,2,1), imshow(img)
subplot(2,2,2), imshow(I)
subplot(2,2,3), imshow(bw)
subplot(2,2,4), imshow(img_orig)
viscircles(s.Centroid, s.EquivDiameter/2 ,'EdgeColor','b');