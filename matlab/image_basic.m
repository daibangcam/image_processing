% initial setup
clc; close all; clear all;
% read image
img_1 = imread('3.jpg');
img_2 = imread('1.png');
% % show images in multiple figures
% figure;
% imshow(img_1);
% title('Image 1');
% figure;
% imshow(img_2);
% title('Image 2');
% % show images in 1 figure
% % 1 row 2 col
% figure;
% subplot(1,2,1);
% imshow(img_1);
% title('Image 1');
% subplot(1,2,2);
% imshow(img_2);
% title('Image 2');
% % 2 row 1 col
% figure;
% subplot(2,1,1);
% imshow(img_1);
% title('Image 1');
% subplot(2,1,2);
% imshow(img_2);
% title('Image 2');
% % convert to gray
% img_gray = rgb2gray(img_1);
% imshow(img_gray);
% title('Gray Image');
% % convert to bw
% % threshold = graythresh(img_gray);
% % img_bw = imbinarize(img_gray,threshold);
% img_bw = im2bw(img_1,0.5);
% imshow(img_bw);
% title('BW Image');
% % flip image
% img_flip_1 = flipdim(img_1,1);
% img_flip_2 = flipdim(img_1,2);
% figure;
% imshow(img_flip_1);
% title('Flip Image 1');
% figure;
% imshow(img_flip_2);
% title('Flip Image 2');
% % resize image
% img_resize = imresize(img_1,0.1);
% figure;
% imshow(img_resize);
% title('Resize Image');
% % rotate image
% img_rotate = imrotate(img_1,-90);
% figure;
% imshow(img_rotate);
% title('Rotate Image');
% % crop image w: 200-300, h: 100-200 
% img_crop = imcrop(img_1,[200 100 100 100]);
% figure;
% imshow(img_crop);
% title('Crop Image');
% % save image
% imwrite(img_crop,'out.jpg');
% get properties of image
whos img_1
size(img_1)






























