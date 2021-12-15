%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Copyright © [2020], Empa
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% Bronnikov Aided Correction/ Modified Bronnikov algorithm
clear all, clc; close all
cd C:\Rawprojections %folder
newdir='C:\Rawprojections\ProjBAC';mkdir(newdir); %folder for BAC filtered images
newdir1='C:\Rawprojections\ProjMBA';mkdir(newdir); %folder for MBA filtered images
opt.overwrite=true;
files = dir('*.tif');

% Loop through each projection image 
alp=0.025;gam=2.4;% setting the BAC parameters
for id =1:length(files)
 % Get the file name 
 im=single(imread(files(id).name));
 [rows, cols]=size(im);
 u=-(cols)/2:(cols)/2-1;u=u*(2*pi/(cols));
 v=-(rows)/2:(rows)/2-1;v=v*(2*pi/(rows));
 [u,v]=meshgrid(u,v);
 
 % next two line are use to normalize raw images if they are not
 % take a ROI from upper left 50pix by 50pix corner of images
 % modify according to your image if needed to avoid objects part in the
 % ROI
 norm=im(1:50,1:50);
 norm=mean(norm(:));
 im1=fft2(im/norm-1);
 h=fftshift(alp+(u.^2+v.^2));
 imB=real(ifft2(im1./h));%im=max(im,1e-10);
 imBAC=im./(1-gam*del2(imB));
 
 % saving processed projection images as 16 bit tiff
 saveastiff(uint16(imBAC),[newdir '\' files(id).name],opt); %BAC method 
 saveastiff(uint16(imB),[newdir1 '\' files(id).name],opt); % MBA method
  
end

