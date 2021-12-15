/**
*  Copyright © [2016], Empa, Juergen Hofmann
*/

//////////////////////////////////////////////////////////////////////////////
//
//	Phase stepping Program using least square fitting
//	Juergen Hofmann Empa Duebendorf (C) 2016
//
//////////////////////////////////////////////////////////////////////////////
#include <arrayfire.h>
#include <cstdio>
#include <cstdlib>
#include <omp.h>
#include <vector>
#include <fstream>
#include <memory>
#include <string>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

//ju-03-July-2017
#include <iostream>
#include <Eigen/Dense>


//using namespace af;
using namespace Eigen;

// some constants not specified yet
///////////////////////////////////

struct Params
{
	std::string indir;
	std::string outdir;
	std::string rImg;
	std::string fImg;
	std::string dImg;
	int startIdx;
	int numImg;
	int numDark;
	int numUse;
	int col;
	int row;
	int win_width;
	int win_height;
};

bool ReadParameters(Params &parm, char* param_file)
{
	std::ifstream ioParam;
	ioParam.open(param_file);
	if (!ioParam.is_open())
	{
		std::cerr << "Error opening: " << param_file << std::endl;
		return false;
	}
	std::string text;
	printf("Print content of parameter file\n-------------------------------\n");
	while(getline(ioParam, text))
	{
		boost::trim(text);
		if (text.length() == 0)continue;
		if (text[0] == '#') continue;
		std::cout << "  > "  << text << std::endl;
		std::vector<std::string> key_val;
		boost::split(key_val, text, boost::is_any_of("="));
		boost::trim(key_val[0]);
		boost::trim(key_val[1]);
		if (key_val[0] == "input_directory")
			parm.indir = key_val[1];
		if (key_val[0] == "output_directory")
			parm.outdir = key_val[1];
		if (key_val[0] == "raw_image_name")
			parm.rImg = key_val[1];
		if (key_val[0] == "flat_image_name")
			parm.fImg = key_val[1];
		if (key_val[0] == "dark_image_name")
			parm.dImg = key_val[1];
		if (key_val[0] == "start_index")
			parm.startIdx = boost::lexical_cast<int>(key_val[1]);
		if (key_val[0] == "number_image")
			parm.numImg = boost::lexical_cast<int>(key_val[1]);
		if (key_val[0] == "number_dark")
			parm.numDark = boost::lexical_cast<int>(key_val[1]);
		if (key_val[0] == "number_use")
			parm.numUse = boost::lexical_cast<int>(key_val[1]);
		if (key_val[0] == "window_col")
			parm.col = boost::lexical_cast<int>(key_val[1]);
		if (key_val[0] == "window_row")
			parm.row = boost::lexical_cast<int>(key_val[1]);
		if (key_val[0] == "window_width")
			parm.win_width = boost::lexical_cast<int>(key_val[1]);
		if (key_val[0] == "window_height")
			parm.win_height = boost::lexical_cast<int>(key_val[1]);


	}
	printf("\n");
	return true;
}

int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		std::cerr << "Usage: PhaseStep.exe parameter_file\n";
		return -1;
	}
	af::timer start1 = af::timer::start();
	Params params;
	ReadParameters(params, argv[1]);

    try {


        // Select a device and display arrayfire info
        //int device = argc > 1 ? atoi(argv[1]) : 0;
        //af::setDevice(device);
        af::info();

		// system matrix for f(x) = a0 + a1*sin(x) + a2*cos(x)
		//////////////////////////////////////////////////////
		// calculate delta Pi
		//////////////////////
		double dPi = static_cast<double>(2 * af::Pi / (params.numImg)); // if 0° to 360° including --> params.numImg-1 else params.numImg
		printf("\nInterpolation values\n"
			"--------------------\nDelta Pi = %f\nInterpolation value phi:\n", dPi*360.0 / af::Pi);
		for (int i = 0; i < params.numUse; i++)
		{
			printf("%02d.)  phi = % 7.2f\n", i,  (i*dPi - af::Pi)*360.0/ af::Pi);
		}
		printf("\n");
		// 0 --> 2*Pi
		/////////////
		// calculate system matrix for LSQF
		// --> versions
		////////////////////////////////////
		//-ju-11-July-2017 from -pi -> +pi
		std::vector<double> coefmat(3 * params.numUse);
		for (int i = 0; i < params.numUse; i++)
		{
			coefmat[i] = 1.0;
		}
		int idx = 0;
		for (int i = params.numUse; i < 2 * params.numUse; i++)
		{
			coefmat[i] = sin(idx*dPi - af::Pi);
			idx++;
		}
		idx = 0;
		for (int i = 2 * params.numUse; i < 3 * params.numUse; i++)
		{
			coefmat[i] = cos(idx*dPi - af::Pi);
			idx++;
		}

		// create coeffient matrix for solving LSQF problem from C-array
		/////////////////////////////////////////////////////////////////
		af::array CoefMat(params.numUse, 3, coefmat.data());
		af_print(CoefMat);

		// Create 3D matrices
		// using window selection, defined in input file
		/////////////////////////////////////////////////
		af::array RawImg(params.win_height, params.win_width, params.numUse);
		RawImg = 0.0f;
		af::array FlatImg(params.win_height, params.win_width, params.numUse);
		FlatImg = 0.0f;
		af::array DarkImg(params.win_height, params.win_width); // only 2D image may be averaged over more
		DarkImg = 0.0f;

		//read flat field images and crop to windows selection
		///////////////////////////////////////////////////////
		///timer startFlat = timer::start();
		printf("\nReading flat field images:\n--------------------------\n");
		for (int i = params.startIdx; i < params.numUse + params.startIdx; i++)
		{
			char filename_buffer[260];
			// assume tif files as input (*.tif)
			sprintf_s(filename_buffer, "%s/%s%d.tif", params.indir.c_str(), params.fImg.c_str(), i);
			printf_s("%02d)    %s\n", i, filename_buffer);
			// load image
			af::array FIm = af::loadImageNative(filename_buffer);
			// array indixing needs 0-indexing
			// apply cropping of image
			FlatImg(af::span, af::span, i - params.startIdx) = FIm.cols(params.col, params.col + params.win_width - 1).rows(params.row, params.row + params.win_height - 1).as(f64);
		}
		///printf("\n\n\tRead flat: %g s\n", timer::stop(startFlat));

		//read raw images and crop to windows selection
		////////////////////////////////////////////////
		printf("\nReading raw images:\n-------------------\n");
		for (int i = params.startIdx; i < params.numUse + params.startIdx; i++)
		{
			char filename_buffer[260];
			// assume tif files as input (*.tif)
			sprintf_s(filename_buffer, "%s/%s%d.tif", params.indir.c_str(), params.rImg.c_str(), i);
			printf_s("%02d)    %s\n", i, filename_buffer);
			// load image
			af::array RIm = af::loadImageNative(filename_buffer);
			// array indixing needs 0-indexing
			// apply cropping of image
			RawImg(af::span, af::span, i - params.startIdx) = RIm.cols(params.col, params.col + params.win_width - 1).rows(params.row, params.row + params.win_height - 1).as(f64);
		}

		//read dark images and crop to windows selection
		////////////////////////////////////////////////
		printf("\nReading dark field images:\n--------------------------\n");
		for (int i = params.startIdx; i < params.numDark + params.startIdx; i++)
		{
			char filename_buffer[260];
			// assume tif files as input (*.tif)
			sprintf_s(filename_buffer, "%s/%s%d.tif", params.indir.c_str(), params.dImg.c_str(), i);
			printf_s("%02d)    %s\n", i, filename_buffer);
			// load image
			af::array DIm = af::loadImageNative(filename_buffer);
			// array indixing needs 0-indexing
			// apply cropping of image
			DarkImg += DIm.cols(params.col, params.col + params.win_width - 1).rows(params.row, params.row + params.win_height - 1).as(f64);
		}

		// avarage dark field image if necessary (more than one)
		/////////////////////////////////////////////////////////
		DarkImg /= static_cast<double>(params.numDark);
		// create an dark array with the same size raw image array by tiling
		/////////////////////////////////////////////////////////////////////
		af::array DarkImg3D = af::tile(DarkImg, 1, 1, params.numUse);
		// do dark field correction of raw images
		//////////////////////////////////////////
		af::array RawImgDFC = RawImg - DarkImg3D;

		// do dark field correction of flat images
		//////////////////////////////////////////
		af::array FlatImgDFC = FlatImg - DarkImg3D;

		// solving LSQF of raw images
		//////////////////////////////
		printf("\nStart processing:\n-----------------\n");
		printf("\n\tSolving LSQF problem for raw images ...");
		af::array RResVec(params.numUse);
		RResVec = 0.0f;
		af::array RawArgsMatrix(params.win_height, params.win_width, 3);
		RawArgsMatrix = 0.0f;
		//-ju-add-MT-support
		for (int y = 0; y < params.win_height; y++) //j
		{
			for (int x = 0; x < params.win_width; x++) //i
			{
				//////////////////////
				// get result vector from raw image stack (reslice)
				///////////////////////////////////////////////////
				RResVec = RawImgDFC(y, x, af::span);
				RResVec = af::reorder(RResVec, 1, 2, 0, 3).T();
				af::array RArgs = af::solve(CoefMat, RResVec);
				RawArgsMatrix(y, x, af::span) = RArgs;
				//if (x == 500 && y == 500)
				//{
				//	af::print("RArgs", RArgs);
				//}

			}
		}
		printf(" done.\n");

		// calulate phase shift of raw image
		/////////////////////////////////////
		printf("\n\tCalculating phases of raw images ...");
		af::array PhiRaw = af::atan2(RawArgsMatrix(af::span, af::span, 1), RawArgsMatrix(af::span, af::span, 2));
		printf(" done.\n");

		// solving LSQF of flat images
		//////////////////////////////
		///timer startFlatProc = timer::start();
		printf("\n\tSolving LSQF problem for flat images ...");
		af::array FResVec(params.numUse);
		FResVec = 0.0f;
		af::array FlatArgsMatrix(params.win_height, params.win_width, 3);
		FlatArgsMatrix = 0.0f;
		for (int y = 0; y < params.win_height; y++) //j
		{
			for (int x = 0; x < params.win_width; x++) //i
			{
				//////////////////////
				// get result vector from raw image stack (reslice)
				///////////////////////////////////////////////////
				FResVec = FlatImgDFC(y, x, af::span);
				FResVec = af::reorder(FResVec, 1, 2, 0, 3).T();
				/* test mit Eigen*/
				double *data = FResVec.host<double>();
	
				Map<VectorXd> v2(data,FResVec.elements());

				af::array FArgs = af::solve(CoefMat, FResVec);
				FlatArgsMatrix(y, x, af::span) = FArgs;
			}
		}
		printf(" done.\n");
		// calulate phase shift of flat image
		/////////////////////////////////////
		printf("\n\tCalculating phases of flat images and phase shift image ...");
		af::array PhiFlat = af::atan2(FlatArgsMatrix(af::span, af::span, 1), FlatArgsMatrix(af::span, af::span, 2));

		// calculat phase diffrence
		/////////////////////////////
		af::array PhiDiff = (PhiRaw % (2.0*af::Pi)) - (PhiFlat % (2.0*af::Pi));
		printf(" done.\n");

		// calculate absorption image
		//////////////////////////////
		af::array AbsorptionImage = RawArgsMatrix(af::span, af::span, 0) / FlatArgsMatrix(af::span, af::span, 0);

		// calculate scatter image
		///////////////////////////
		printf("\n\tCalculating scatter and absorption image ...");
		af::array ScatAmpRaw = af::sqrt(RawArgsMatrix(af::span, af::span, 1)*RawArgsMatrix(af::span, af::span, 1) + RawArgsMatrix(af::span, af::span, 2)*RawArgsMatrix(af::span, af::span, 2));
		af::array ScatAmpFlat = af::sqrt(FlatArgsMatrix(af::span, af::span, 1)*FlatArgsMatrix(af::span, af::span, 1) + FlatArgsMatrix(af::span, af::span, 2)*FlatArgsMatrix(af::span, af::span, 2));
		af::array ScatImage = ScatAmpRaw / ScatAmpFlat;
		//-ju-21-June-2016 add division Amplitude/Mean --> dark-field image
		ScatImage = ScatImage / AbsorptionImage;
		//-ju-21-June-2016 <--
		printf(" done.\n");

		// save phase, scatter and absorption image
		////////////////////////////////////////////
		printf("\nSaving images:\n--------------\n");
		char outfilename[260];
		sprintf_s(outfilename, "%s/%02d_of_%02d_PhaseImage.tif", params.outdir.c_str(), params.numUse, params.numImg);
		printf("    %s\n", outfilename);
		af::saveImageNative(outfilename, PhiDiff);
		sprintf_s(outfilename, "%s/%02d_of_%02d_ScatterImage.tif", params.outdir.c_str(), params.numUse, params.numImg);
		printf("    %s\n", outfilename);
		af::saveImageNative(outfilename, ScatImage);
		sprintf_s(outfilename, "%s/%02d_of_%02d_AbsorptionImage.tif", params.outdir.c_str(), params.numUse, params.numImg);
		printf("    %s\n", outfilename);
		af::saveImageNative(outfilename, AbsorptionImage);

		printf("\n\n\tTotal runtime: %g s\n", af::timer::stop(start1));

		
		// visualization
		// rescale image to 0 ... 255
		/////////////////////////////
		
		////af::dim4 dim = PhiDiff.dims();
		////double min_phase = af::min<double>(PhiDiff);
		////double max_phase = af::max<double>(PhiDiff);
		////double dev_phase = 255.0f / (max_phase - min_phase);
		////array PHASE_IMG = PhiDiff*dev_phase;

		////double min_scat = af::min<double>(ScatImage.cols(3 * dim[0] / 8, 3 * dim[0] / 8 + dim[0] / 4).rows(3 * dim[1] / 8, 3 * dim[1] / 8 + dim[1] / 4));
		////double max_scat = af::max<double>(ScatImage.cols(3 * dim[0] / 8, 3 * dim[0] / 8 + dim[0] / 4).rows(3 * dim[1] / 8, 3 * dim[1] / 8 + dim[1] / 4));
		////double dev_scat = 255.0f / (max_scat - min_scat);
		////array SCATTER_IMG = /*af::log*/(ScatImage)*dev_scat;

		////double min_abso = af::min<double>(af::log(AbsorptionImage));
		////double max_abso = af::max<double>(af::log(AbsorptionImage));
		////double dev_abso = 255.0f / (max_abso - min_abso);
		////array ABSO_IMG = af::log(AbsorptionImage)*dev_abso;

		////const static int width = 1200, height = 800;
		////af::Window window(width, height, "Phase Stepping");
		////window.grid(1, 3);
		////do
		////{
		////	window(0, 0).image(PHASE_IMG.as(u8), "Phase image");
		////	window(0, 1).image(SCATTER_IMG.as(u8), "Scatter image");
		////	window(0, 2).image(ABSO_IMG.as(u8), "Absorption image (log)");
		////	window.show();
		////}
		////while (!window.close());
		
    } catch (af::exception& e) {
        fprintf(stderr, "%s\n", e.what());
        throw;
    }


    #ifdef WIN32 // pause in Windows
    if (!(argc == 2 && argv[1][0] == '-')) {
        printf("hit [enter]...");
        fflush(stdout);
        getchar();
		exit(0);
    }
    #endif
    return 0;
}