/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#include<string>
#include<iostream>
#include<fstream>
#include<sstream>
#include<cmath>
#include<intrin.h>
#include<vector>
#include "fileloader.h"
#include<iomanip>
#include <QtCore/QFileInfo>
#include <QtWidgets/QMessageBox>

//#define flat_correction_factor 1.0974f

using namespace std;

bool fileLoader::endianess = false; // -> little endian

fileLoader::fileLoader()
:darkRead(false),flatRead(false)
{};

fileLoader::fileLoader(unsigned short w,unsigned short h,float bhc_poly_coff,float flat_corr_factor,Ui::Dialog *uiDlg)
:darkRead(false),flatRead(false),
dimX(w),dimY(h),
bhc_polynom_coefficient(bhc_poly_coff),
flat_correction_factor(flat_corr_factor),
uiExt(uiDlg)
{};


fileLoader::~fileLoader()
{};

int fileLoader::loadDark(const string & filename){
	const unsigned int framesize=sizeU*sizeV;
	darkImage=(unsigned short *)malloc(framesize*sizeof(unsigned short));

	ifstream darkFile(filename.c_str(),ios::binary);

	if (!darkFile){
		cerr << "Dark File " << filename << " not found. Exiting" << endl;
		exit(0);
	}

	for (unsigned int iPix=0;iPix<framesize;iPix++){
		unsigned short data=0;
		darkFile.read(reinterpret_cast < char * > (&data), sizeof(data));

		if (endianess){
			darkImage[iPix]=_byteswap_ushort(data);
		} else {
			darkImage[iPix]=data;
		}
	}

	darkRead=true;

	cout << "Dark file " << filename << " read." << endl;

	return 0;
};


int fileLoader::loadFlat(const string & filename){
	const unsigned int framesize=sizeU*sizeV;
	flatImage=(unsigned short *)malloc(framesize*sizeof(unsigned short));

	ifstream flatFile(filename.c_str(),ios::binary);

	if (!flatFile){
		cerr << "Flat File " << filename << " not found. Exiting" << endl;
		exit(0);
	}

	for (unsigned int iPix=0;iPix<framesize;iPix++){
		unsigned short data=0;
		flatFile.read(reinterpret_cast < char * > (&data), sizeof(data));
		if (endianess){
			flatImage[iPix]=_byteswap_ushort(data);
		} else {
			flatImage[iPix]=data;
		}
	}

	flatRead=true;

	cout << "Flat file " << filename << " read." << endl;

	return 0;
};

int fileLoader::loadProjections(const string & filename, const string & outFilename){
	if (!(darkRead&&flatRead)){
		cerr << "Dark and Flat image not correctly read" << endl;
	}


	// Assumes that projection is already initialised

	ifstream projFile(filename.c_str(),ios::binary);

	if (!projFile){
		cerr << "Projection File " << filename << " not found. Exiting" << endl;
		exit(0);
	}


	//-ju- get file size and number of projections
	QFileInfo volFile(filename.c_str());
	size_t sz = volFile.size();
	size_t np = sz/(sizeU*sizeV*2); //-ju- data type unsigned short

	unsigned short projCounter=1;

	// image delimitors
	unsigned short minX=(sizeU-dimX)/2;
	unsigned short maxX=(sizeU+dimX)/2;
	unsigned short minY=(sizeV-dimY)/2;
	unsigned short maxY=(sizeV+dimY)/2;
	
	while (projFile.good()&&!projFile.eof())
	{
		unsigned short * inData=(unsigned short *)(malloc(sizeU*sizeV*sizeof(unsigned short)));
		projFile.read(reinterpret_cast < char * > (inData),sizeU*sizeV*sizeof(unsigned short));

		if (projFile.good()&&!projFile.eof())
		{
			float minImage=66000.0f; // larger than the highest value of the 16-bit range of the detector
			float maxImage=0.0f;

			vector<float> results;
			results.reserve(dimX*dimY);
		
			// for test only 
			int countOver=0;

			for (unsigned int iY=minY;iY<maxY;iY++)
			{
					for (unsigned int iX=minX;iX<maxX;iX++)
					{
						unsigned int ipos=iX+iY*sizeU;

					
						float dark=(float)(darkImage[ipos]);
						float flat=flat_correction_factor*(float)(flatImage[ipos]);
						// at this point just placeholder
						float value=0.0f;
						if (endianess)
						{
							// data are big-endian
							value=_byteswap_ushort(inData[ipos]);
						}
						else 
						{
							value=inData[ipos];
						}
						if (value>dark)
						{ 
							value=-(float)(logf(value-dark)
								-logf(flat-dark));
							
							// potential beamhardening could be added here
							if (value<0.0f){
								value=0.0f;
							} 
							else 
							{
								value=pow(value,bhc_polynom_coefficient)+value;
							}
							if (value <minImage){
								minImage=value;
							}
							if (value > maxImage){
								maxImage=value;
							};
						} 
						else 
						{
							value=1e10; // set to numerical upper limit arbitrarily chosen
							countOver+=1;
						};	

						results.push_back(value);
					}
			}

			// rescale image
			stringstream outFileName;
			outFileName.fill('0');
			outFileName << outFilename<< "_" << setw(4) << dec <<  projCounter << ".sin";

			cout << "Writing output to " << outFileName.str() << endl;

			ofstream fileOut(outFileName.str().c_str(),ios::binary);

			if (!fileOut)
			{
				cerr << "File " << outFileName.str() << " not created " << endl;
				QMessageBox::warning(0,"Error creating File",
					"Can not create File: " + QString(outFileName.str().c_str()));
				return -1;
			}

			const unsigned int sizer=results.size();
			//for (unsigned int ipos=0;ipos<sizer;ipos++){
			//	float data=results[ipos];

			//	// rescaling removed as unwanted
			//	/*if (data!=1e10){
			//		data=(data-minImage)/(maxImage-minImage)*65535.0f;
			//	} else {
			//		data=65535.0f;
			//		countOver-=1;
			//	}*/

			//	fileOut.write((char *)(& data),4);
			//}
			//-ju-12-july-2011
			fileOut.write((char *)&results[0],4*sizer);

			//-ju- update progress bar
			int val = (int)((float)(100*projCounter/np)+0.5f);
			uiExt->progressBar->setValue(val);

			projCounter+=1;
		} 
	}


	// 

	return 0;
};

int fileLoader::loadProjections(const std::string & darkFilename, const std::string & flatFilename, const std::string & projectionsFilename, const std::string & outputBaseFilename){
	// Just a wrapper function with out actual content
	
	// load dark field
	loadDark(darkFilename);

	// load flat field
	loadFlat(flatFilename);

	// Load projection data and save sinograms into projections
	loadProjections(projectionsFilename,outputBaseFilename);

	return 0;	
};

int fileLoader::loadAll(const std::string & basefilename, const std::string & outputBasename){
	stringstream merger;
	merger << basefilename << ".du" ; 
	string darkFilename=merger.str();
	merger.str("");
	merger.clear();
	merger << basefilename << ".wu";
	string flatFilename=merger.str();

	merger.str("");
	merger.clear();

	merger << basefilename << ".pru";
	string projFilename=merger.str();
	
	cout << darkFilename << endl << flatFilename << endl << projFilename << endl;

	loadProjections(darkFilename,flatFilename,projFilename,outputBasename);
	
	return 0;	
};