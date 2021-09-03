BW = imread('a.jpg');
 BW = rgb2gray(BW);
 BW = im2bw(BW,0.9);
 a = imcomplement(BW);

% BW= imcomplement(im2bw(BW));
SE = ones(5); 
BW2 = imdilate(BW,SE); 
increase = (bwarea(BW2) -bwarea(BW))/bwarea(BW);
imshow(BW2);
increase



