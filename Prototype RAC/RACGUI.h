#pragma once
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <QtWidgets/QMainWindow>
#include <QColor>
#include "ui_RACGUI.h"
#include <filesystem>
#include <string>
#include <windows.h>

namespace fs = std::filesystem;


class RACGUI : public QMainWindow
{
    Q_OBJECT

public:
    RACGUI(QWidget *parent = nullptr);
    ~RACGUI();

private:
    Ui::RACGUIClass ui;

private slots:
    void SelectTifFiles();
    void SelectTifOutputDir();
    void ReadTifImages();
	//void ApplyBadPixelCorr();

    void SelectRawFiles();
    void SelectRawOutputDir();
    void ReadRawFiles();

	void CheckFilterlen();
	void CheckNumThreads();
	void RunRAC();

	void CheckMemory();

private: 
    QStringList tif_file_list_;
    QString tif_input_dir_;
    QString tif_output_dir_;
    uint32_t number_of_projection_;
    uint32_t tif_img_width_;
    uint32_t tif_img_height_;

    QStringList raw_file_list_;
    QString raw_input_dir_;
    QString raw_output_dir_;
    int32_t raw_type_index_;
    uint32_t raw_img_width_;
    uint32_t raw_img_height_;

	cv::Mat projection_sum_tifimg_;
	cv::Mat bad_pixel_mat_;

    // used for image processing
    /////////////////////////////
    std::vector<cv::Mat> image_stack_;

private:
    // helper functions
    /////////////////////
	template<typename T> void ReadRawImages(T type);

	template<typename T> void WriteRawImages(T type);
	void WriteTifImages(); // current only 16 Bit data type supported

    bool FileExists(const std::string& filename)
    {
        return fs::exists(filename);
    }

	void GetAvailMemory(uint64_t& avail_mem, uint64_t unit)
	{
		MEMORYSTATUSEX memStatEx;
		memStatEx.dwLength = sizeof(memStatEx);
		GlobalMemoryStatusEx(&memStatEx);
		avail_mem = memStatEx.ullAvailPhys / unit;
	}

	void SegmentForOutliers();
	void FindBadPixels(cv::Mat binOutlierImage, std::vector<cv::Vec2i>& outlierPixelList);
	void BadPixelCorrection(std::vector<cv::Mat>& img_stack);
	void BadPixelReplaceByMedian9(cv::Mat& projection, cv::Vec2i& pixCoord);

	template<typename T>
	std::vector<T> MedianFilter(std::vector<T> vec_in, uint filter_len)
	{
		std::vector<T> kernel(filter_len);
		std::vector<T> vec_ret(vec_in.size());
		std::vector<T> vec_pad(filter_len + vec_in.size() - 1);
		uint start_idx = (filter_len - 1) / 2;
		uint end_idx = start_idx + static_cast<uint>(vec_in.size()) - 1;

		// pad vector
		for (uint i = 0; i < vec_pad.size(); i++)
		{
			if (i < start_idx)
			{
				vec_pad.at(i) = vec_in.at(0);
			}
			else if (i >= end_idx)
			{
				vec_pad.at(i) = vec_in.at(vec_in.size() - 1);
			}
			else
			{
				vec_pad.at(i) = vec_in.at(i - start_idx);
			}
		}

		// apply median filter
		for (int i = 0; i < vec_ret.size(); i++)
		{
			for (int ik = 0; ik < kernel.size(); ik++)
			{
				// affected pixel in padded vector
				kernel.at(ik) = vec_pad.at(i + ik);
			}
			std::sort(kernel.begin(), kernel.end());
			vec_ret.at(i) = kernel.at(start_idx);
		}
		return vec_ret;
	}

	// Check resources disk space and memory
	/////////////////////////////////////////
	const long long GB_ = 1024 * 1024 * 1024;
	const long long MB_ = 1024 * 1024;
	const long long KB_ = 1024;

	const uint32_t FLOAT_TYPE = 0;
	const uint32_t UINT16_TYPE = 1;

	// palette & colors
	QPalette disk_space_bg_color_;
	QPalette disk_tif_space_bg_color_;
	QPalette text_editor_bg_color_;
	QColor error_red_;
	QColor ErrorColor()
	{
		error_red_ = QColor(250, 110, 70);
		return error_red_;
	}

	// resources missing
	bool insufficient_ram_;
	bool insufficient_disk_space_;

	// RAC Processing
	//////////////////
	uint32_t max_number_threads_;
	uint32_t number_of_threads_;
	uint32_t median_filter_len_;

	template<typename T>
	void RACProcessing(T type, 
		std::vector<cv::Mat>& img_stack, 
		const uint& num_proj,
		const uint& img_width, 
		const uint& img_height, 
		//const uint& img_size, 
		const uint& filter_len, 
		const uint& num_threads);

};
