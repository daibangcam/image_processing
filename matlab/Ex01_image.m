clc; clear all; close all;

%%  Doc anh
% a = imread('C:\Users\Administrator\Desktop\Project\TGMT\Matlab\Images\01.png');
% size(a);                            % kich th??c ?nh
% whos a;                             % thông s? ?nh
% imshow(a,[ ]);                      % hi?n th? ?nh

%% Doi ma tran ra anh xam + luu anh
% s = [1 2 3;4 5 6;7 8 9];
% i = mat2gray(s,[1 10])
% imshow(i)
% imwrite(i,'ex01_ouput1.jpg','jpg')
% imshow('ex01_output1.jpg')

%% Giam kich thuoc anh
% a = imread('C:\Users\Administrator\Desktop\Project\TGMT\Matlab\Images\01.png');
% b = a(1:10:end,1:10:end,:);
% imshow(b)

%% Lat anh theo chieu doc
% a = imread('C:\Users\Administrator\Desktop\Project\TGMT\Matlab\Images\01.png');
% b = a(end:-1:1,:,: );
% imshow(b)

%% Crop Image Using Submatrix Operation
% a = imread('C:\Users\Administrator\Desktop\Project\TGMT\Matlab\Images\01.png');         %read image
% [m n]= size(a);                                                                         %get no of rows and column of the image matrix
% imshow(a)
% [y,x] = ginput(2);                                                                      %select two cursor points
% r1 = x(1,1); c1 = y(1,1);                                                               %get first cursor point = first corner of the rectangle
% r2 = x(2,1); c2 = y(2,1);                                                               %get second cursor point = second corner of the rectangle
% b = a(r1:r2,c1:c2,:); figure;                                                          %create the sub-matrix
% imshow(b)                                                                               %display croped image

%% Crop Image Using function m
% function s=subim1(f,m,n,rx,cy)
% rowhigh=rx+m-1;
% colhigh=cy+n-1;
% s=f(rx:rowhigh,cy:colhigh,:);
% 
% a = imread('C:\Users\Administrator\Desktop\Project\TGMT\Matlab\Images\01.png');         %read image
% imshow(a)
% s= subim1(a,200,500,100,100);
% figure;
% imshow(s);

%%