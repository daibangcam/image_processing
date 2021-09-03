f = imread('a.jpg');

 f = rgb2gray(f);
 f = im2bw(f,0.9);
 a = imcomplement(f);

% a = imcomplement(im2bw(f));

[L,n] =  bwlabel(a);
imshow(f)
hold on
for k = 1:n
    [r,c] =  find(L==k);
    rbar = mean(r);
    cbar = mean(c);
    plot(cbar, rbar,'X');
end