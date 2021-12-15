/**
*  Copyright © [2011], Empa, Juergen Hofmann
*/

#ifndef _RAWFILE_2_IMAGE_H
#define _RAWFILE_2_IMAGE_H


inline float ROUND(float x)
{
	return x > 0.0f ? x + 0.5f : x - 0.5f;
}

class RangeMapUC8
{
public:
	RangeMapUC8(float mapFactor, float f32min)
		:m_mapFactor(mapFactor),m_f32min(f32min){}
	unsigned char operator() (float inVal)
	{
		return static_cast<unsigned char>(ROUND((inVal - m_f32min)*m_mapFactor));
	}
private:
	float m_mapFactor;
	float m_f32min;
};

template <typename T>
bool rawFile2Image(QString filename, std::vector<unsigned char> &data, 
				   int &width, int &height,
				   const T &MAX_TYPE_VAL, const T &MIN_TYPE_VAL)
{

	data.resize(width*height);
	QFile imageFile(filename);
	QFileInfo info(filename);
	int bytes =  sizeof(T);
	if(info.size() != width*height*bytes)
	{
		QString msg(("Check file.\nFile size not correct"));
		QMessageBox::warning(0,("File size not correct.\nCheck File Parameters."),msg);
		return false;
	}
	if(info.exists())
	{
		std::ifstream sinFile(filename.toStdString().c_str(),std::ios::binary);
		std::vector<T> genericTypeArray(width*height);
		if(sinFile.is_open())
		{
			sinFile.read((char*)&genericTypeArray[0], width*height*sizeof(T));
			sinFile.close();
			T max_val = MIN_TYPE_VAL;
			T min_val = MAX_TYPE_VAL;
			max_val = std::max(max_val,
				*(std::max_element(genericTypeArray.begin(),genericTypeArray.end())));
			min_val = std::min(min_val,
				*(std::min_element(genericTypeArray.begin(),genericTypeArray.end())));
			float mapRange = (float)UCHAR_MAX/((float)max_val -(float)min_val);
			data.resize(genericTypeArray.size());
			std::transform(genericTypeArray.begin(), 
				genericTypeArray.end(), 
				data.begin(), 
				RangeMapUC8(mapRange, min_val));
		}
	}
	return true;
}

#endif
