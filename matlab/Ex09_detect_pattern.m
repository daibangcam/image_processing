close all;
% doc hinh vuong vao de nhan dang
square1 = imread('vuong3.jpg');
square = rgb2gray(square1);
figure(1);
subplot(121);
imshow(square1);
title('Image of a square');
%% doc hinh goc vao de tim kiem va nhan dang
Imagesoure1 = imread('Imgsource.jpg');
Imagesource = rgb2gray(Imagesoure1);
% xac dinh trong tam cua cac vat the nam trong anh goc
level = graythresh(Imagesoure1); % phep toan chuyen thang xám [0..255] v? thang [0…1]
bw = im2bw(Imagesoure1,level);% chuy?n sang ?nh ?en tr?ng v?i level ?ã tính ? trên
I2 = 1 - bw;
I2 = bwareaopen(I2, 200); % remove t?t c? các vùng mà s? pixels < 200
I3 = imfill(I2, 'holes');
s  = regionprops(I3, 'centroid');
     centroids = cat(1, s.Centroid);
     subplot(122);
     imshow(Imagesoure1);
title('Image of a source');
%% tim diem dac tinh trong khung hinh vuong va anh goc
squarepoints = detectSURFFeatures(square);
sourcepoints = detectSURFFeatures(Imagesource);
   
% plot khung anh can nhan dang da duoc tim dac tinh
       figure(2);
      subplot(121);
      imshow(square);
title('300 Strongest Feature Points from square');
      hold on;
      plot(squarepoints.selectStrongest(300)); % lúc này m?i v?
%plot khung anh goc da duoc tim dac tinh
      subplot(122); 
      imshow(Imagesource);
title('300 Strongest Feature Points from source');
%% 
      hold on;
      plot(sourcepoints.selectStrongest(300));  % lúc này m?i v?
%mo ta nhung dac diem tuong quan giua 2 anh
      [squareFeatures, squarepoints] = extractFeatures(square, squarepoints);
      [sourceFeatures, sourcepoints] = extractFeatures(Imagesource, sourcepoints);
%tim nhung diem duoc cho la giong nhau giua anh nhan dang va anh can nhan
%dang
        squarePairs = matchFeatures(squareFeatures, sourceFeatures);
        matchedsquarePoints = squarepoints(squarePairs(:, 1), :);
        matchedsourcePoints = sourcepoints(squarePairs(:, 2), :);
        figure(3);
        subplot(121);
        showMatchedFeatures(square, Imagesource, matchedsquarePoints, ...
        matchedsourcePoints, 'montage');
title('Putatively Matched Points (Including Outliers)');
%% xac dinh lai cac diem dac tinh nam tren cac vat the da duoc xac dinh o
%tren
        [tform, inliersquarePoints, inliersquarePoints] = ...
        estimateGeometricTransform(matchedsquarePoints, matchedsourcePoints, 'affine');

        subplot(122);
        showMatchedFeatures(square, Imagesource, inliersquarePoints, ...
        inliersquarePoints, 'montage');
title('Matched Points (Inliers Only)');

        boxPolygon = [1, 1;...                           % top-left
        size(square, 2), 1;...                           % top-right
        size(square, 2), size(square, 1);...               % bottom-right
        1, size(square, 1);...                              % bottom-left
        1, 1];                                              % top-left again to close the polygon
    % xac dinh khung cua vat the va ve lai khung cho vao dung vat the trong
    % source
        newsquarePolygon = transformPointsForward(tform, boxPolygon);
        img = imread('Imgsource.jpg');                      % read the image
        imgbw = ~im2bw(img,graythresh(img));            % convert to grayscale

        stats  = regionprops(bwlabel(imgbw), 'centroid','area'); % call regionprops to find centroid and area of all connected objects
        area = [stats.Area];                            % extract area
        centre = cat(1,stats.Centroid);                 % extract centroids
        centre = centre(area>10,:); 
        centre = round(centre);
        s = newsquarePolygon;
        sx = s(:,1);
        sy = s(:,2);
        len = length(centre(:,2));
        xc = centre(:,1);
        yc = centre(:,2);
        for l = 1:len,
            if (xc(l) < max(sx)&& xc(l) > min(sx)),
            if (yc(l) < max(sy)&& yc(l) > min(sy)),
            xck = xc(l);
            yck = yc(l);
            end;
            end;
        end;

        x = xck - 40;
        y = yck + 90;
     
        htxtins = vision.TextInserter(['x =' int2str(xck) ': y =' num2str(yck)]);
        htxtins.Color = [0, 0, 255]; % [red, green, blue]
        htxtins.FontSize = 15;
        htxtins.Location = [x y]; % [x y]
        Imagesource2 = step(htxtins, Imagesoure1);
  
 %   chi ra vi tri cua anh mau trong khung anh goc
%         newsquarePolygon = transformPointsForward(tform, boxPolygon);
        figure(4);
        subplot(121); 
        imshow(Imagesource);
        hold on;
        line(newsquarePolygon(:, 1), newsquarePolygon(:, 2), 'Color', 'g');
title('Detected square');
%% 

        Img1 = imread('tamgiac1.jpg');
        Img =rgb2gray(Img1);
        subplot(122); imshow(Img1);
title('Image of an Tringle');

        tringlePoints = detectSURFFeatures(Img);
        figure(5);
        subplot(121); imshow(Img);
        hold on;
        plot(tringlePoints.selectStrongest(100));
title('100 Strongest Feature Points from Tringle Image');

        [tringleFeatures, tringlePoints] = extractFeatures(Img, tringlePoints);

         tringlePairs = matchFeatures(tringleFeatures, sourceFeatures);

         matchedtringlePoints = tringlePoints(tringlePairs(:, 1), :);
         matchedsourcePoints = sourcepoints(tringlePairs(:, 2), :);
         subplot(122);
         showMatchedFeatures(Img, Imagesource, matchedtringlePoints, ...
         matchedsourcePoints, 'montage');
 title('Putatively Matched Points (Including Outliers)');

        [tform, inliertringlePoints, inliersquarePoints] = ...
         estimateGeometricTransform(matchedtringlePoints, matchedsourcePoints, 'affine');
         figure(6);
%           subplot(121);
         showMatchedFeatures(Img, Imagesource, inliertringlePoints, ...
         inliersquarePoints, 'montage');
 title('Matched Points (Inliers Only)');
 %% 
        tringlePolygon = [1, 1;...                                 % top-left
        size(Img, 2), 1;...                       % top-right
        size(Img, 2), size(Img, 1);...  % bottom-right
        1, size(Img, 1);...                       % bottom-left
        1,1];                         % top-left again to close the polygon

        newtringlePolygon = transformPointsForward(tform, tringlePolygon);
 
        s1 = newtringlePolygon;
        sx1 = s1(:,1);
        sy1 = s1(:,2);
        len1 = length(centre(:,1));
        xc1 = centre(:,1);
        yc1 = centre(:,2);
        for j = 1:len1,
            if (xc1(j) < max(sx1)&& xc1(j) > min(sx1)),
            if (yc1(j) < max(sy1)&& yc1(j) > min(sy1)),
            xck1 = xc1(j);
            yck1 = yc1(j);
            end;
            end;
        end;                
        imgbw = ~im2bw(img,graythresh(img));            % convert to grayscale

        stats  = regionprops(bwlabel(imgbw), 'centroid','area'); % call regionprops to find centroid and area of all connected objects
        area = [stats.Area];                            % extract area
        centre = cat(1,stats.Centroid);                 % extract centroids

        centre = centre(area>10,:); 
        centre = round(centre);
            x1 = xck1-40;
            y1 = yck1 +80;
 
     
            htxtins = vision.TextInserter(['x =' int2str(xck1) ': y =' num2str(yck1)]);
            htxtins.Color = [0, 0, 255]; % [red, green, blue]
            htxtins.FontSize = 15;
            htxtins.Location = [x1 y1]; % [x y]
            Imagesource = step(htxtins, Imagesource2);
            figure(7);
%             subplot(122);
            imshow(Imagesource);
            hold on;
            plot(centroids(:,1), centroids(:,2), 'm*');
            line(newsquarePolygon(:, 1), newsquarePolygon(:, 2), 'Color', 'b');
            line(newtringlePolygon(:, 1), newtringlePolygon(:, 2), 'Color', 'r');

title('Detected Tringle and square');
            hold off;

