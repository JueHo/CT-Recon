***
### **Compiler and libraries:**  
Modules are build under Windows 10 with **MS Visual Studio 2017**
compiled, linked and tested using the following libraries:
+ boost 1.69 (or newer): <https://www.boost.org>
+ opencv 4.5.x: <https://opencv.org>
+ qt 5.15.x: <https://www.qt.io/download>
+ qwt 6.1.2 (or newer): <https://sourceforge.net/projects/qwt/files/qwt/>
+ Cuda toolkit 10.1: <https://developer.nvidia.com/cuda-10.1-download-archive-update2>
+ eigen 3.4: <https://eigen.tuxfamily.org>
+ arrayfire 3.7 (or newer): <https://arrayfire.com/download/>

(Programs may run with other versions of the libraries but are not tested)
***

### **Setup of environment:**
The following variables need to be defined during comilation. Adapt according your libraries installation directories. They are needed during compilation.
1. set QTDIR=C:\Qt\Qt-5.15.1
2. set QWTDIR=D:\lib\qwt-6.1.2
3. set BOOST_DIR=D:\lib\boost_1_69_0
4. set EIGEN_DIR=D:\lib\eigen
5. set CUDA_HELPER=C:\ProgramData\NVIDIA Corporation\CUDA Samples\v10.1
6. set OPENCV_DIR=D:\lib\OpenCV-4.5.4\opencv\build
7. set AF_PATH=C:\Program Files\ArrayFire\v3

QWT need to be compiled with installed Qt version. The liberies qwt.lib and qwtd.lib should be copied to %QTDIR%\lib. qwt.dll and qwtd.dll to %QTDIR%\bin
***
### **Build:**
Open recon_tools.sln in directory recon_tools with Visual Studio and build projects.
Executables are located in recon_tools\x64\Release  
***

### **Running:**
Add directory with executables to PATH variable.
Setup PATH variable to locations of all used dll's.
***