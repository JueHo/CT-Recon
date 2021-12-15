/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#ifndef __FILELOADER_H
#define __FILELOADER_H

#include <QtWidgets/QDialog>
#include "ui_ImportDetectData.h"

#include<string>

class fileLoader 
{
public:
	fileLoader();
	fileLoader(unsigned short w,unsigned short h,float bhc_poly_coff,float flat_corr_factor,Ui::Dialog *uiDlg);
	~fileLoader();

	int loadDark(const std::string & filename);

	int loadFlat(const std::string & filename);

	int loadProjections(const std::string & filename, 
						const std::string & outFilename);

	int loadProjections(const std::string & darkFilename, 
						const std::string & flatFilename, 
						const std::string & projectionsFilename, 
						const std::string & outputBaseFilename);

	int loadAll(const std::string & inputBaseName, 
				const std::string & outputBaseName);
private:
	Ui::Dialog *uiExt;
	unsigned short * darkImage;
	unsigned short * flatImage;

	bool darkRead;
	bool flatRead;

	float bhc_polynom_coefficient;
	float flat_correction_factor;

	unsigned short dimX;
	unsigned short dimY;
	static const unsigned short sizeU=2184;
	static const unsigned short sizeV=1472;
	static bool endianess; // true -> big endian; false -> little endian
};



#endif