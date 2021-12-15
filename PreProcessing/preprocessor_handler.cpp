#include "preprocessor_handler.h"

void PreprocParamHandler::CreateParameterFile(QString filename, MSG_CODE &retCode, QString &msgStr)
{
	using boost::property_tree::ptree;

	//-ju-set to default error (< 0 is error)
	//////////////////////////////////////////
	retCode = ERR_UNKNOWN;

	QFile file(filename);

	//-ju-do not overwrite file
	////////////////////////////
	if (file.exists())
	{
		char buffer[256];
		QByteArray bStr = filename.toUtf8();
		std::string str = bStr.data();
		sprintf_s(buffer, "File >> %s << already exists.\nChoose another file.", str.c_str());
		::MessageBoxA(0, buffer, "ERROR", MB_OK | MB_ICONEXCLAMATION);
		retCode = INF_FILE_EXISTS;
		return;
	}
	QFileInfo finfo(filename);
	QDir dir;
	QString directory = finfo.absolutePath();
	if (!dir.mkpath(directory))
	{
		char buffer[256];
		QByteArray bStr = directory.toUtf8();
		std::string str = bStr.data();
		sprintf_s(buffer, "Can not create directory >> %s <<", str.c_str());
		::MessageBoxA(0, buffer, "ERROR", MB_OK | MB_ICONEXCLAMATION);
		retCode = ERR_CREATE_DIR;
		return;
	}

	ptree paramtree;
	// project settings
	paramtree.add("Project.Name", string("---")); //type: string
	char nameBuffer[256];
	DWORD size = 256;
	GetUserNameA((char*)nameBuffer, &size);
	paramtree.add("Project.Owner", string(nameBuffer));
	QString dateTimeStr = QDateTime::currentDateTime().toString();
	QByteArray bStr = dateTimeStr.toUtf8();
	string dateTimeString = bStr.data();
	boost::algorithm::replace_all(dateTimeString, " ", "/");
	paramtree.add("Project.Creation", dateTimeString);
	paramtree.add("Project.LastModification", string("---"));
	paramtree.add("Directory.InputDir", string("./"));
	paramtree.add("Directory.OutputDir", string("./"));
	paramtree.add("File.InputDataType", _USHORT16);
	paramtree.add("File.OutputDataType", _REAL32);
	paramtree.add("File.FilePatternIn", string("Seq_01_Sino_"));
	paramtree.add("File.FilePatternOut", string("Sino_***"));
	paramtree.add("File.FileTypeIn", TIFF);
	paramtree.add("File.FileTypeOut", RAW);
	paramtree.add("File.FlatFile", string("./Init_Flat.tiff"));
	paramtree.add("File.DarkFile", string("./Init_Dark.tiff"));
	paramtree.add("Projection.ImgWidth", 1024);
	paramtree.add("Projection.ImgHeight", 1024);
	paramtree.add("Projection.NumberOfProjections", 721);
	paramtree.add("Projection.NumberOfTiles", 1);
	paramtree.add("Projection.TileHeight", 1);
	paramtree.add("Execute.DoReduceOutlier", 1);
	paramtree.add("Execute.DoReduceStripes", 0);
	paramtree.add("Execute.DoNormalisation", 0);
	paramtree.add("Execute.DoBeamhardeningReduction", 0);
	paramtree.add("ProcessOption.SigmaOutlier", 6);
	paramtree.add("ProcessOption.BeamHardingCoeff", 0.2);
	paramtree.add("ProcessOption.PaddMultiplicator", 2);
	paramtree.add("ProcessOption.NumberOfThreads", 6);
	paramtree.add("Window.NormelizeWinWidth", 64);
	paramtree.add("Window.NormelizeWinHeight", 64);
	paramtree.add("Window.NormelizeWinPosX", 5);
	paramtree.add("Window.NormelizeWinPosY", 5);

	try
	{
		QByteArray p = filename.toUtf8();
		std::string str = p.data();
		boost::property_tree::write_ini(str, paramtree);
	}
	catch (boost::property_tree::ini_parser_error &err)
	{
		msgStr = QString(err.what());
		char buffer[256];
		QByteArray bStr = msgStr.toUtf8();
		std::string str = bStr.data();
		sprintf_s(buffer,
			"Parameter file >> %s <<",
			str.c_str());
		::MessageBoxA(0, buffer, "ERROR", MB_OK | MB_ICONEXCLAMATION);
		retCode = ERR_CREATE_PARAM_FILE;
		QFile file(filename);
		file.remove();
	}
}

void PreprocParamHandler::SaveParameter(QString filename, MSG_CODE &retCode, QString &msgStr)
{
	//-ju-set to default error (< 0 is error)
	//////////////////////////////////////////
	retCode = ERR_UNKNOWN;

	using boost::property_tree::ptree;
	ptree param;

	QString nn = "-nn-";
	if (m_parameter.projectName != nn)
	{
		QByteArray bStr = m_parameter.projectName.toUtf8();
		std::string str = bStr.data();
		param.put("Project.Name", str);
	}
	if (m_parameter.ownerName != nn)
	{
		QByteArray bStr = m_parameter.ownerName.toUtf8();
		std::string str = bStr.data();
		param.put("Project.Owner", str);
	}
	if (m_parameter.creationDate != nn)
	{
		QByteArray bStr = m_parameter.creationDate.toUtf8();
		std::string str = bStr.data();
		param.put("Project.Creation", str);
	}
	if (m_parameter.modificationDate != nn)
	{
		QByteArray bStr = m_parameter.modificationDate.toUtf8();
		std::string str = bStr.data();
		param.put("Project.LastModification", str);
	}
	if (m_parameter.inputDir != nn)
	{
		QByteArray bStr = m_parameter.inputDir.toUtf8();
		std::string str = bStr.data();
		param.put("Directory.InputDir", str);
	}
	if (m_parameter.outputDir != nn)
	{
		QByteArray bStr = m_parameter.outputDir.toUtf8();
		std::string str = bStr.data();
		param.put("Directory.OutputDir", str);
	}
	if (m_parameter.inDataType != _NULLTYPE)
	{
		param.put("File.InputDataType", m_parameter.inDataType);
	}
	if (m_parameter.outDataType != _NULLTYPE)
	{
		param.put("File.OutputDataType", m_parameter.outDataType);
	}
	if (m_parameter.inFilePattern != nn)
	{
		QByteArray bStr = m_parameter.inFilePattern.toUtf8();
		std::string str = bStr.data();
		param.put("File.FilePatternIn", str);
	}
	if (m_parameter.outFilePattern != nn)
	{
		QByteArray bStr = m_parameter.outFilePattern.toUtf8();
		std::string str = bStr.data();
		param.put("File.FilePatternOut", str);
	}
	if (m_parameter.inFileType != UNKNOWN)
	{
		param.put("File.FileTypeIn", m_parameter.inFileType);
	}
	if (m_parameter.outFileType != UNKNOWN)
	{
		param.put("File.FileTypeOut", m_parameter.outFileType);
	}
	if (m_parameter.flatFile != nn)
	{
		QByteArray bStr = m_parameter.flatFile.toUtf8();
		std::string str = bStr.data();
		param.put("File.FlatFile", str);
	}
	if (m_parameter.darkFile != nn)
	{
		QByteArray bStr = m_parameter.darkFile.toUtf8();
		std::string str = bStr.data();
		param.put("File.DarkFile", str);
	}
	if (m_parameter.imgX > 0)
	{
		param.put("Projection.ImgWidth", m_parameter.imgX);
	}
	if (m_parameter.imgY > 0)
	{
		param.put("Projection.ImgHeight", m_parameter.imgY);
	}
	if (m_parameter.projectionCnt > 0)
	{
		param.put("Projection.NumberOfProjections", m_parameter.projectionCnt);
	}
	if (m_parameter.tileCnt > 0)
	{
		param.put("Projection.NumberOfTiles", m_parameter.tileCnt);
	}
	if (m_parameter.tileHeight > 0)
	{
		param.put("Projection.TileHeight", m_parameter.tileHeight);
	}
	if (m_parameter.doMedian == 0 || m_parameter.doMedian == 1)
	{
		param.put("Execute.DoReduceOutlier", m_parameter.doMedian);
	}
	if (m_parameter.doFFT == 0 || m_parameter.doFFT == 1)
	{
		param.put("Execute.DoReduceStripes", m_parameter.doFFT);
	}
	if (m_parameter.doNormalisation == 0 || m_parameter.doNormalisation == 1)
	{
		param.put("Execute.DoNormalisation", m_parameter.doNormalisation);
	}
	if (m_parameter.doBeamHard == 0 || m_parameter.doBeamHard == 1)
	{
		param.put("Execute.DoBeamhardeningReduction", m_parameter.doBeamHard);
	}
	if (m_parameter.sigmaOutlier > 1.0) // at least 1 sigma
	{
		param.put("ProcessOption.SigmaOutlier", m_parameter.sigmaOutlier);
	}
	if (m_parameter.beamHardeningCoeff > 0)
	{
		param.put("ProcessOption.BeamHardingCoeff", m_parameter.beamHardeningCoeff);
	}
	if (m_parameter.paddMulti > 0) // at least image size
	{
		param.put("ProcessOption.PaddMultiplicator", m_parameter.paddMulti);
	}
	if (m_parameter.numberOfThreads > 0)
	{
		param.put("ProcessOption.NumberOfThreads", m_parameter.numberOfThreads);
	}
	if (m_parameter.normWinWidth >= 0)
	{
		param.put("Window.NormelizeWinWidth", m_parameter.normWinWidth);
	}
	if (m_parameter.normWinHeight >= 0)
	{
		param.put("Window.NormelizeWinHeight", m_parameter.normWinHeight);
	}
	if (m_parameter.normWinPosX >= 0)
	{
		param.put("Window.NormelizeWinPosX", m_parameter.normWinPosX);
	}
	if (m_parameter.normWinPosY >= 0)
	{
		param.put("Window.NormelizeWinPosY", m_parameter.normWinPosY);
	}

	try
	{
		QByteArray p = filename.toUtf8();
		std::string str = p.data();
		boost::property_tree::write_ini(str, param);
	}
	catch (boost::property_tree::ini_parser_error &err)
	{
		msgStr = QString(err.what());
		char buffer[256];
		QByteArray bStr = msgStr.toUtf8();
		std::string str = bStr.data();
		sprintf_s(buffer,
			"Parameter file >> %s <<",
			str.c_str());
		::MessageBoxA(0, buffer, "ERROR", MB_OK | MB_ICONEXCLAMATION);
		retCode = ERR_WRITE_PARAM_FILE;
	}
}

void PreprocParamHandler::LoadParameter(QString filename, MSG_CODE &retCode, QString &msgStr)
{
	//-ju-set to default error (< 0 is error)
	//////////////////////////////////////////
	retCode = ERR_UNKNOWN;

	QFile file(filename);

	//-ju-check if parameter file exists
	/////////////////////////////////////
	if (!file.exists())
	{
		char buffer[256];
		QByteArray bStr = filename.toUtf8();
		std::string str = bStr.data();
		sprintf_s(buffer, "File >> %s << does not exists.", str.c_str());
		::MessageBoxA(0, buffer, "ERROR", MB_OK | MB_ICONEXCLAMATION);
		retCode = ERR_PARAM_FILE_NOT_EXISTS;
		return;
	}

	using boost::property_tree::ptree;
	ptree param;

	try
	{
		QByteArray p = filename.toUtf8();
		std::string str = p.data();
		boost::property_tree::read_ini(str, param);
	}
	catch (boost::property_tree::ini_parser_error &err)
	{
		msgStr = QString(err.what());
		char buffer[256];
		QByteArray bStr = msgStr.toUtf8();
		std::string str = bStr.data();
		sprintf_s(buffer,
			"Parameter file >> %s <<",
			str.c_str());
		::MessageBoxA(0, buffer, "ERROR", MB_OK | MB_ICONEXCLAMATION);
		retCode = ERR_READ_PARAM_FILE;
	}

	m_parameter.projectName = QString(param.get<string>("Project.Name", string("-nn-")).c_str());
	if (m_parameter.projectName == QString("-nn-"))
	{
		msgStr = QString("invalid project name");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.ownerName = QString(param.get<string>("Project.Owner").c_str());
	if (m_parameter.ownerName == QString("-nn-"))
	{
		msgStr = QString("invalid owner name");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.creationDate = QString(param.get<string>("Project.Creation", string("-nn-")).c_str());
	if (m_parameter.creationDate == QString("-nn-"))
	{
		msgStr = QString("invalid creation date string");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.modificationDate = QString(param.get<string>("Project.LastModification", string("-nn-")).c_str());
	if (m_parameter.modificationDate == QString("-nn-"))
	{
		msgStr = QString("invalid modification date string");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.inputDir = QString(param.get<string>("Directory.InputDir", string("-nn-")).c_str());
	if (m_parameter.inputDir == QString("-nn-"))
	{
		msgStr = QString("inalid input directory");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.outputDir = QString(param.get<string>("Directory.OutputDir", string("-nn-")).c_str());
	if (m_parameter.outputDir == QString("-nn-"))
	{
		msgStr = QString("inalid output directory");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.inDataType = param.get<int32_t>("File.InputDataType", _NULLTYPE);
	if (m_parameter.inDataType == _NULLTYPE)
	{
		msgStr = QString("invalid input data type");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.outDataType = param.get<int32_t>("File.OutputDataType", _NULLTYPE);
	if (m_parameter.outDataType == _NULLTYPE)
	{
		msgStr = QString("invalid output data type");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.inFilePattern = QString(param.get<string>("File.FilePatternIn", string("-nn-")).c_str());
	if (m_parameter.inFilePattern == QString("-nn-"))
	{
		msgStr = QString("invalid in file pattern");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.outFilePattern = QString(param.get<string>("File.FilePatternOut", string("-nn-")).c_str());
	if (m_parameter.outFilePattern == QString("-nn-"))
	{
		msgStr = QString("invalid out file pattern");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.inFileType = param.get<int32_t>("File.FileTypeIn", UNKNOWN);
	if (m_parameter.inFileType == UNKNOWN)
	{
		msgStr = QString("invalid input file type");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.outFileType = param.get<int32_t>("File.FileTypeOut", UNKNOWN);
	if (m_parameter.outFileType == UNKNOWN)
	{
		msgStr = QString("invalid output file type");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.flatFile = QString(param.get<string>("File.FlatFile", string("-nn-")).c_str());
	if (m_parameter.flatFile == QString("-nn-"))
	{
		msgStr = QString("invalid flat file");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.darkFile = QString(param.get<string>("File.DarkFile", string("-nn-")).c_str());
	if (m_parameter.darkFile == QString("-nn-"))
	{
		msgStr = QString("invalid dark file");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.imgX = param.get<uint64_t>("Projection.ImgWidth", 0);
	if (m_parameter.imgX == 0)
	{
		msgStr = QString("invalid projection width");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.imgY = param.get<uint64_t>("Projection.ImgHeight", 0);
	if (m_parameter.imgY == 0)
	{
		msgStr = QString("invalid projection height");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.projectionCnt = param.get<uint64_t>("Projection.NumberOfProjections", 0);
	if (m_parameter.projectionCnt == 0)
	{
		msgStr = QString("invalid count of projections");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.tileCnt = param.get<uint64_t>("Projection.NumberOfTiles", 0);
	if (m_parameter.tileCnt == 0)
	{
		msgStr = QString("invalid count of tiles");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.tileHeight = param.get<uint64_t>("Projection.TileHeight", 0);
	if (m_parameter.tileHeight == 0)
	{
		msgStr = QString("invalid tile height");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.doMedian = param.get<int32_t>("Execute.DoReduceOutlier", -1);
	if (m_parameter.doMedian == -1)
	{
		msgStr = QString("outlier filter parameter invalid");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.doFFT = param.get<int32_t>("Execute.DoReduceStripes", -1);
	if (m_parameter.doFFT == -1)
	{
		msgStr = QString("stripe filter parameter invalid");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.doNormalisation = param.get<int32_t>("Execute.DoNormalisation", -1);
	if (m_parameter.doNormalisation == -1)
	{
		msgStr = QString("invalid do normalization parameter");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.doBeamHard = param.get<int32_t>("Execute.DoBeamhardeningReduction", -1);
	if (m_parameter.doBeamHard == -1)
	{
		msgStr = QString("invalid do beamharding reduction parameter");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.sigmaOutlier = param.get<float>("ProcessOption.SigmaOutlier", -1.0f);
	if (m_parameter.sigmaOutlier <= -1.0f)
	{
		msgStr = QString("invalid sigma outlier parameter");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.beamHardeningCoeff = param.get<float>("ProcessOption.BeamHardingCoeff", -1.0f);
	if (m_parameter.beamHardeningCoeff <= -1.0f)
	{
		msgStr = QString("invalid beamharding coefficient");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.paddMulti = param.get<uint32_t>("ProcessOption.PaddMultiplicator", 0);
	if (m_parameter.paddMulti == 0)
	{
		msgStr = QString("invalid padding multiplier");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.numberOfThreads = param.get<uint32_t>("ProcessOption.NumberOfThreads", 0);
	if (m_parameter.numberOfThreads == 0)
	{
		msgStr = QString("invalid number of threads");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.normWinWidth = param.get<uint32_t>("Window.NormelizeWinWidth", -1);
	if (m_parameter.normWinWidth == -1)
	{
		msgStr = QString("invalid normalization window width");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.normWinHeight = param.get<uint32_t>("Window.NormelizeWinHeight", -1);
	if (m_parameter.normWinHeight == -1)
	{
		msgStr = QString("invalid normalization window height");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.normWinPosX = param.get<int32_t>("Window.NormelizeWinPosX", -1);
	if (m_parameter.normWinPosX == -1)
	{
		msgStr = QString("invalid normalization window X position");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	m_parameter.normWinPosY = param.get<int32_t>("Window.NormelizeWinPosY", -1);
	if (m_parameter.normWinPosY == -1)
	{
		msgStr = QString("invalid normalization window X position");
		retCode = ERR_PARAM_ITEM;
		return;
	}
	retCode = IS_OK;
}