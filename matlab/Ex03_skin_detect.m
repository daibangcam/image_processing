function [out bin] = Ex03_skin_detect(filename)
if nargin>1 | nargin<1
error('usage: Ex03_skin_detect(filename)');
end;
img_orig = imread(filename);
height = size(img_orig,1);
width = size(img_orig,2);
out = img_orig;
bin = zeros(height,width);
img = grayworld(img_orig);
img_ycbcr = rgb2ycbcr(img);
Cb = img_ycbcr(:,:,2);
Cr = img_ycbcr(:,:,3);
[r,c,v] = find(Cb>=77 & Cb<=127 & Cr>=133 & Cr<=173);
numind = size(r,1);
for i=1:numind
out(r(i),c(i),:) = [0 0 255];
bin(r(i),c(i)) = 1;
end
imshow(img_orig);
figure; imshow(out);
figure; imshow(bin);
end