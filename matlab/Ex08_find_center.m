function g = vi_tri_mat_bao(f,w)
f = imread('a.jpg');
f = rgb2gray(f);
f = im2bw(f,0.9);
f = imcomplement(f);
w = imread('b.jpg');
w = rgb2gray(w);
w = im2bw(w,0.9);
w = imcomplement(w);

[M, N] = size(f);
f = fft2(f);
w = conj(fft2(w,M, N));
g = real(ifft2(w.*f));
end
