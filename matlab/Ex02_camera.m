clear all; clear all; clc
%% Basic code
% imaqhwinfo
% imaqhwinfo('winvideo')
% imaqhwinfo('winvideo',1)

%% Connect camera
% vid = videoinput('winvideo',1,'RGB24_640x480')
% set(vid,'ReturnedColorSpace','rgb');
% preview(vid);

%% Connect camera, then Snapshot & delete video
% vid = videoinput('winvideo',1,'RGB24_640x480')
% set(vid,'ReturnedColorSpace','rgb');
% preview(vid);
% frame = getsnapshot(vid);
% image(frame);
% delete(vid);

%% Camera Read
% v = videoinput('winvideo', 1,'RGB24_320x240');
% v.FramesPerTrigger = 1;
% preview(v);
% start(v);
% wait(v,Inf);
% set(v,'ReturnedColorSpace','rgb');
% l=1;
% for l=1:20
% rgbImage = getsnapshot(v);
% image(rgbImage);
% pause(1);
% end
% stop(v);
% delete(v);