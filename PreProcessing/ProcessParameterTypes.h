/**
*  Copyright © [2015], Empa, Juergen Hofmann
*/

#ifndef _PROCESS_PARAMETER_TYPES_H
#define _PROCESS_PARAMETER_TYPES_H

#include <QtCore/QString>
#include <cstdint>
#include <QtCore/QVector>

struct TileInfo
{
	uint64_t from; // incl.
	uint64_t to;   // excl.
	uint64_t height;
	uint64_t offsetSegStart;	// which address in array
	uint64_t length;			// length of array to write
};

struct ProcessParameter
{
	// project sttings
	QString		projectName;
	QString		projectFileName;
	QString		projectOwner;
	QString		projectDate;
	// file & projection settings
	QString		inputDiretory;
	QString		inputFilepattern;
	QString		outputDirectory;
	QString		outputFilepattern;
	uint32_t	fileType;
	uint64_t	imgWidth;
	uint64_t	imgHeight;
	uint64_t	cntProj;
	int32_t		dataTypeIn;
	int32_t		dataTypeOut; // 0 -> 32 Bit float, 1 -> 16 Bit uint
	QStringList selectedImages;
	// methods normalize
	uint32_t	useNormalisation;
	uint32_t	useFlatFieldFileNormalisation; // use file for normalization
	QString		flatFieldImageFile;
	QString		darkFieldImageFile;
	uint32_t	useWinNormalisation; // use selected window
	uint32_t	xWinPos;
	uint32_t	yWinPos;
	uint32_t	widthWin;
	uint32_t	heightWin;
	bool		noLog;
	// method outlier
	uint32_t	useOutlierSupRAC;
	uint32_t	useOutlierSup;
	uint32_t	useRAC;
	uint32_t	correctAlgo; // 0 -> median9, 1 -> mean9
	double		outlierSigmaMedian9;
	double		outlierSigmaMean9;
	// method BHC
	uint32_t	useBHC;
	double		coeffBHC;
	double		constCoeffBHC_A;
	double		constCoeffBHC_B;
	// strip reduction	
	uint32_t	useStripReduction;
	uint32_t	padFac; // 1, 2, 4, 8 (index: 0, 1, 2, 3)
	uint32_t	multiThread;
	// misc
	uint64_t	array3DSize;
	uint64_t	memAllocSize;
	uint64_t	imgWidthScaled;
	uint64_t	imgHeightScaled;
	bool		saveOnly;
	// memory tiling
	uint32_t	numOfTiles;
	bool		applyMemTiling;
	uint32_t	runningTileNo;
	uint64_t	tileArray3DMaxSize;
	QVector<TileInfo> tilesSegmentProperties;
	QVector<double> winNormValueVector; // storage vector for normalization values
	//-ju-10-Apr-2017 Lorentz Filter
	bool		useLorentzFilter;
	double		alphaValue;
	//-ju-15-Feb-2018 add anti clockwise rotation direction flag
	int32_t		antiClockWise;
	//-ju-23-Feb-2018 already dark/flat corrected projections
	uint32_t	isDarkFlatCorrected;
	double		maxGreyInStack;
	//-ju-24-June-2024 local tomography
	uint32_t roiPrecentageExt;
	uint32_t extentedProjectionWidth;
	uint32_t roiPadSize;
	uint32_t totalPadLocTomoSize;
	uint32_t useROIPadding;
	uint32_t locTomoAVGRange;
	float sigmoidSlope;
	std::vector<float> localTomoWeights;
};

#endif // _PROCESS_PARAMETER_TYPES_H
