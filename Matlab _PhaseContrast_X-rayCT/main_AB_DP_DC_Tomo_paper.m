%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Copyright © [2020], Empa
%%%%%%%%%%%%%%%%%%%%%%%%%%%%

%This script generates the Absorption, Dark field and Differential Phase
%Contrast projection images from a set of raw grating-based PCI projection images. 

clear all;clc;close all
proj_dir = ('....\'); %Directory of the tomography images
addpath(proj_dir);
%create spearate folders for abs, dpc and dfi projections images using FFT
%based and least-square fitted retrieval methods
mkdir(strcat(proj_dir,'AB_FFT\'));mkdir(strcat(proj_dir,'DPC_FFT\'));mkdir(strcat(proj_dir,'DFI_FFT\')); % folder for FFT images
mkdir(strcat(proj_dir,'AB_LLS\'));mkdir(strcat(proj_dir,'DPC_LLS\'));mkdir(strcat(proj_dir,'DFI_LLS\')); % folder for LLS images 


%% PARAMETERS
%file naming convention for raw projection files: name_projnr_stepnr.
%file naming convention for dark images: name_dark_stepnr.
%file naming convention for flat files: name_flatstep_flat_stepnr.
%raw images in tiff format are assumed here but can be changed easily
N_projections = 181; %total number of projections
flat_step = 50; %Step to acquire flat field images
N_ps = 7; %total number of phase stepping steps
name_data = '...'; %Naming of the projection files
%% prepare dark image
dark=0;
for ii = 1:N_ps
dark =dark+single(imread(strcat(proj_dir,name_data,'_dark_',int2str(ii)),'tif')); % one Dark image
end
dark=dark/N_ps;
%% prepare flat images

flat_f=single(zeros(size(dark,1),size(dark,2),N_ps,fix(N_projections/flat_step)));
for i=1:fix(N_projections/flat_step)
 for ii = 1:N_ps
 flat_f(:,:,ii,i) = single(imread(strcat(proj_dir,name_data,'_',int2str(i*flat_step),'_flat_',int2str(ii)),'tif'))-dark;
 end
end

row=size(flat_f,1)-mod(size(flat_f,1),2);

%%
%initialize abs, dpc, dfi image data arrays
AB=single(zeros(size(dark,1),size(dark,2),N_projections));DPC=single(zeros(size(dark,1),size(dark,2),N_projections));
DFI=single(zeros(size(dark,1),size(dark,2),N_projections));


for i=1:N_projections
%for i = 1:2
i
char=sprintf('%04d',i);
%data_f = single(zeros(size(dark,1),size(dark,2),N_ps)); %Initialization of data array
for k = 1:N_ps
  data_f(:,:,k) =single(imread(strcat(proj_dir,name_data,'_',int2str(i),'_',int2str(k),'.tif')))-dark;
end

%% GENERATION OF THE ABS, DFI AND DPC IMAGES USING FOURIER COEFFICIENTS !!!
 if (fix(i/flat_step)+1)>size(flat_f,4)                 % adjust flat image for each flat_step 
  flat_ff = fft(flat_f(:,:,:,fix(i/flat_step)),[],3);
 else
  flat_ff = fft(flat_f(:,:,:,fix(i/flat_step)+1),[],3);
 end
 data_f = fft(data_f,[],3);

    ABt = abs(data_f(:,:,1)) ./ abs(flat_ff(:,:,1));ABt=min(ABt,1);ABt=max(ABt,0);
    DPCt = wrap(angle(data_f(:,:,2)) - angle(flat_ff(:,:,2)),2);DPCt=DPCt-mean(DPCt(:));
    DFIt= abs(data_f(:,:,2)) .* abs(flat_ff(:,:,1)) ./ abs(flat_ff(:,:,2)) ./ abs(data_f(:,:,1));DFIt=min(DFIt,1);DFIt=max(DFIt,0);
       
    % IMAGING visibility map
  vis_tomo(:,:,i) = abs(flat_ff(:,:,2)) ./ abs(flat_ff(:,:,1))*2;

  %writing the procesed projection images into 16 bit tiffs
imwrite(uint16(rescale(ABt(1:row,:),0,2^16-1)),strcat(proj_dir,'AB_FFT\abs_',char,'.tif')); % for reconstruction
imwrite(uint16(rescale(DPCt(1:row,:),0,2^16-1)),strcat(proj_dir,'DPC_FFT\dpc_',char,'.tif'));
imwrite(uint16(rescale(DFIt(1:row,:),0,2^16-1,'InputMin',2*min(DFIt(:)),'InputMax',1.3*max(DFIt(:)))),strcat(proj_dir,'DFI_FFT\dfi_',char,'.tif'));

end
%%
 %% GENERATION OF THE ABS, DFI AND DPC IMAGES USING Linearized Least-Square FIT !!!
 p1 = 2.92; % period of G1 is 2.92 um
 p2 = 3.24; % period of G2 is 3.24 um
 delt=p1/N_ps;positions=0:delt:(p1-delt); %stepping locations of G1 

 for i = 1:N_projections
  % for i = 1:2
 i
 char=sprintf('%04d',i);
 
     if (fix(i/flat_step)+1)>size(flat_f,4)
     flat_fl = flat_f(:,:,:,fix(i/flat_step));
     else
     flat_fl = flat_f(:,:,:,fix(i/flat_step)+1);
     end
      
 %reading raw pojections
for k = 1:N_ps
  data_f(:,:,k) =single(imread(strcat(proj_dir,name_data,'_',int2str(i),'_',int2str(k),'.tif')))-dark;
end

   %analytical LS solution to S=M+c_1*sin(x)+c_2*cos(x)
   stepss=sind(positions*360/p1);stepsc=cosd(positions*360/p1);
  
   A=[ones(N_ps,1),stepss',stepsc'];Ain=pinv(A);        % pinv: Moore-Penrose pseudo inverse

   M_flat=reshape(flat_fl,size(flat_fl,1)*size(flat_fl,2),size(flat_fl,3))*Ain(1,:)';
   M_data=reshape(data_f,size(data_f,1)*size(data_f,2),size(data_f,3))*Ain(1,:)';
   c1_flat=reshape(flat_fl,size(flat_fl,1)*size(flat_fl,2),size(flat_fl,3))*Ain(2,:)';
   c1_data=reshape(data_f,size(data_f,1)*size(data_f,2),size(data_f,3))*Ain(2,:)';
   c2_flat=reshape(flat_fl,size(flat_fl,1)*size(flat_fl,2),size(flat_fl,3))*Ain(3,:)';
   c2_data=reshape(data_f,size(data_f,1)*size(data_f,2),size(data_f,3))*Ain(3,:)';
  
   M_flat=reshape(M_flat,size(flat_fl,1),size(flat_fl,2));
   M_data=reshape(M_data,size(data_f,1),size(data_f,2));
   c1_flat=reshape(c1_flat,size(flat_fl,1),size(flat_fl,2));
   c1_data=reshape(c1_data,size(data_f,1),size(data_f,2));
   c2_flat=reshape(c2_flat,size(flat_fl,1),size(flat_fl,2));
   c2_data=reshape(c2_data,size(data_f,1),size(data_f,2));
 

  %A=sqrt(c1^2+c2^2) and fi=atan(c2/c1)
  fi_flat=atan2(c1_flat,c2_flat);fi_data=atan2(c1_data,c2_data);
  A_flat=sqrt(c1_flat.^2+c2_flat.^2);A_data=sqrt(c1_data.^2+c2_data.^2);
    

    
    ABt_fit(:,:,i) = abs(M_data)./abs(M_flat);ABt_fit=min(ABt_fit,1);ABt_fit=max(ABt_fit,0);
    DFIt_fit(:,:,i) =(abs(A_data)./abs(M_data))./(abs(A_flat)./abs(M_flat));
    DFIt_fit=min(DFIt_fit,1);DFIt_fit=max(DFIt_fit,0);
    DPCt_fit(:,:,i)= wrap(fi_flat-fi_data,2);DPCt_fit=DPCt_fit-mean(DPCt_fit(:));
    vis_fit(:,:,i) = (A_flat./M_flat)*2;
     
  %writing the procesed projection images into 16 bit tiffs
  imwrite(uint16(rescale(ABt_fit(1:row,:),0,2^16-1)),strcat(proj_dir,'AB_LLS\abs_',char,'.tif')); % for reconstruction
  imwrite(uint16(rescale(DPCt_fit(1:row,:),0,2^16-1)),strcat(proj_dir,'DPC_LLS\dpc_',char,'.tif'));
  imwrite(uint16(rescale(DFIt_fit(1:row,:),0,2^16-1)), strcat(proj_dir,'DFI_LLS\dfi_',char,'.tif'));
 
 end 
