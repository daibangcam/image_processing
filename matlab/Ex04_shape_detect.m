close all
format long
i=imread('01.bmp');
figure;imshow(i);
a=rgb2gray(i);
bw=edge(a,'canny');
bw = bwareaopen(bw,30);
se = strel('disk',2);
bw = imclose(bw,se);
bw = imfill(bw,'holes');
L = bwlabel(bw);
s  = regionprops(L, 'centroid');
dt  = regionprops(L, 'area');
cv = regionprops(L, 'perimeter');
dim = size(s)
BW_filled = imfill(bw,'holes');
boundaries = bwboundaries(BW_filled);
[B,L] = bwboundaries(BW_filled,'noholes');
figure;imshow(i);
hold on;
for k=1:length(B)
    b= boundaries{k};
    dim = size(b)
    for i=1:dim(1)
        khoangcach{k}(1,i) = sqrt ( ( b(i,2) - s(k).Centroid(1) )^2 + ( b(i,1) - s(k).Centroid(2) )^2 )
    end 
    a=max(khoangcach{k});
    b=min(khoangcach{k});
    c=dt(k).Area;
    vuong = c/(4*b^2)
    chunhat=c/(4*b*(a^2-b^2)^0.5);
    tamgiacdeu=(c*3^0.5)/((a+b)^2);
 boundary = B{k};
    if (vuong < 1.05 ) & (vuong > 0.95 )
            text(s(k).Centroid(1)-20,s(k).Centroid(2),'Tu Giac')
            plot(boundary(:,2), boundary(:,1), 'g', 'LineWidth', 4) 
%     elseif (thoi < 1.05 ) & (thoi > 0.95 )
%             text(s(k).Centroid(1)-20,s(k).Centroid(2),'Tu Giac')
            plot(boundary(:,2), boundary(:,1), 'g', 'LineWidth', 4) 
    elseif ((chunhat <1.05) & (chunhat >0.95))
            text(s(k).Centroid(1)-20,s(k).Centroid(2),'Tu Giac')
            plot(boundary(:,2), boundary(:,1), 'g', 'LineWidth', 4) 
    elseif  (tamgiacdeu < 1.05 ) & (tamgiacdeu > 0.95 )
            text(s(k).Centroid(1)-20,s(k).Centroid(2),'Tam Giac')
            plot(boundary(:,2), boundary(:,1), 'g', 'LineWidth', 4) 
    end
end