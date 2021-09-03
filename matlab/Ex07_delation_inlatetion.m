f = imread('D:\test_delate.jpg');
se  = strel('square', 3);
fo = imopen(f,se);
figure(1)
imshow(fo)
hold
foc = imclose(fo,se);
figure(2);
imshow(foc)
hold
ftotal = fo - foc;
figure(3);
imshow(1- ftotal)
hold;