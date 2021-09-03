vid=mmreader('01.avi');
n=vid.numberofframes;
for k=1:n
    vid1=read(vid,k);
    vid2( : , : , k )=rgb2gray(vid1);
end
implay(vid2)
