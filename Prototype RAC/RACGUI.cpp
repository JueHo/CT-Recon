#include <QtWidgets/QFileDialog>
#include <QDir>
#include <QProgressDialog>
#include <QMessageBox>
#include <QStorageInfo>
#include "RACGUI.h"
#include <opencv2/opencv.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgcodecs.hpp>
#include <fstream>
#include <chrono>
#include <windows.h>
#include <omp.h>
#include <QTextStream>

RACGUI::RACGUI(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    // get max. number of cores = threads
    max_number_threads_ = std::thread::hardware_concurrency();
    median_filter_len_ = ui.spinBox_filter_length->value();
    number_of_threads_ = ui.spinBox_number_of_threads->value();

    QString threshold_str = ui.label_thres_bad_pixel->text();
    QString sigma = QChar(0x03C3);
    threshold_str = threshold_str + "( " + sigma + " )";
    ui.label_thres_bad_pixel->setText(threshold_str);

    QString core_thread_str;
    QTextStream(&core_thread_str) << "Found " << max_number_threads_ << " cores => max. number of threads";
    ui.lineEdit_max_threads_based_on_cores->setText(core_thread_str);

    // tif files
    connect(ui.pushButton_tif_file_selection,&QPushButton::clicked, this, &RACGUI::SelectTifFiles);
    connect(ui.pushButton_tif_output_directory, &QPushButton::clicked, this, &RACGUI::SelectTifOutputDir);
    connect(ui.pushButton_load_tif_files, &QPushButton::clicked, this, &RACGUI::ReadTifImages);
    //connect(ui.checkBox_apply_bad_pixel_correction, &QCheckBox::stateChanged, this, &RACGUI::ApplyBadPixelCorr);

    // raw files
    connect(ui.pushButton_raw_select_input_directory, &QPushButton::clicked, this, &RACGUI::SelectRawFiles);
    connect(ui.pushButton_raw_select_output_directory, &QPushButton::clicked, this, &RACGUI::SelectRawOutputDir);
    connect(ui.pushButton_raw_load_files, &QPushButton::clicked, this, &RACGUI::ReadRawFiles);

    // RAC processing
#ifdef _QT68
    connect(ui.spinBox_filter_length, &QSpinBox::valueChanged, this, &RACGUI::CheckFilterlen);
    connect(ui.spinBox_number_of_threads, &QSpinBox::valueChanged, this, &RACGUI::CheckNumThreads);
    connect(ui.pushButton_start_rac, &QPushButton::clicked, this, &RACGUI::RunRAC);
#else
    void (QSpinBox:: * signalSpin)(int) = &QSpinBox::valueChanged;
    connect(ui.spinBox_filter_length, signalSpin, this, &RACGUI::CheckFilterlen);
    connect(ui.spinBox_number_of_threads, signalSpin, this, &RACGUI::CheckNumThreads);
    connect(ui.pushButton_start_rac, &QPushButton::clicked, this, &RACGUI::RunRAC);
#endif

    // memory check
    connect(ui.pushButton_check_memory, &QPushButton::clicked, this, &RACGUI::CheckMemory);
 }

// slots
/////////

// Tif files handling
///////////////////////
void RACGUI::SelectTifFiles()
{
    QStringList file_list = QFileDialog::getOpenFileNames(this, tr("Select all projection files (CTRL a)"),
        QDir::rootPath(),
        tr("Projection File (*.tif *.tiff)"));
    // clear file list
    tif_file_list_.clear();
    if (file_list.isEmpty())
    {
        ui.textEdit_logging_output->append("No tif file selected.");
        return;
    }
    // store name of files
    tif_file_list_ = file_list;

    // Get info of tif file
    cv::Mat tif_img = cv::imread(file_list[0].toStdString(), cv::IMREAD_GRAYSCALE | cv::IMREAD_ANYDEPTH);
    uint32_t width = tif_img.cols;
    uint32_t height = tif_img.rows;
    QString tif_type(cv::typeToString(tif_img.type()).c_str());
    QString msg;
    if (tif_type != QString("CV_16UC1"))
    {
        QTextStream(&msg) << "File type unkown (" << tif_type << ").";
        ui.textEdit_logging_output->append(msg);
        ui.textEdit_logging_output->append("Only tif files unsigned 16 Bit supported.");
        tif_file_list_.clear();
        return;
    }
    QTextStream(&msg) << "Select " << file_list.count() << " files.";
    ui.textEdit_logging_output->append(msg);

    QString number_str;
    QTextStream(&number_str) << width;
    ui.lineEdit_tif_image_width->setText(number_str);
    tif_img_width_ = width;
    number_str.clear();
    QTextStream(&number_str) << height;
    ui.lineEdit_tif_image_height->setText(number_str);
    tif_img_height_ = height;
    number_str.clear();

    // store and show path
    QFileInfo tif_input_directory(file_list[0]);
    tif_input_dir_ = tif_input_directory.absoluteDir().path();
    ui.lineEdit_tif_dir_in->setText(tif_input_dir_);

    // message
    ui.textEdit_logging_output->append(tif_input_dir_);

    // number of projections
    number_of_projection_ = tif_file_list_.size();
    // show
    QTextStream(&number_str) << number_of_projection_;
    ui.lineEdit_tif_number_proj->setText(number_str);
    number_str.clear();

    // disable Run RAC Button to enforce re-loading
    ui.pushButton_start_rac->setEnabled(false);

    // Alloc sum projection mat
    ////////////////////////////
    projection_sum_tifimg_.release(); // dealloc data
    projection_sum_tifimg_ = cv::Mat::zeros(tif_img_height_, tif_img_width_, CV_32F);
}

void RACGUI::SelectTifOutputDir()
{
    QString tif_out_dir =
        QFileDialog::getExistingDirectory(0,
            tr("Select output directory"),
            QDir::rootPath(),
            QFileDialog::ShowDirsOnly);
    if (tif_out_dir.isEmpty())
    {
        return;
    }
    ui.lineEdit_tif_output_directory->setText(tif_out_dir);
    tif_output_dir_ = tif_out_dir;
    QPalette palette = ui.lineEdit_disk_space_avail->palette();
    // save old palette
    disk_tif_space_bg_color_ = palette;
 
    uint64_t avail_phys_mem;
    GetAvailMemory(avail_phys_mem, GB_);
    QString mem_avail_str;
    QTextStream(&mem_avail_str) << avail_phys_mem << "GB";
    ui.lineEdit_memory_avail->setText(mem_avail_str);
    //disk usage info
    // to edit
    // only 2 Byte unsigned supported; stack size only approx. due to unkown internal tiff file size
    // add 5% margin
    long long stack_space_size = static_cast<long long>(tif_img_width_)
        * static_cast<long long>(tif_img_height_)
        * static_cast<long long>(number_of_projection_)
        * sizeof(uint16_t) / GB_;
    // add 5% margin
    long long margin = static_cast<long long>(static_cast<float>(stack_space_size) * 0.05f);
    stack_space_size += margin;

    // init error state
    insufficient_ram_ = false;
    insufficient_disk_space_ = false;

    QStorageInfo storage(tif_output_dir_);
    if (storage.isValid() && storage.isReady())
    {
        long long disk_space_avail = storage.bytesAvailable() / GB_;
        long long disk_space_remain = disk_space_avail - stack_space_size;
        if (disk_space_remain <= 0)
        {
            QString disk_space;
            QTextStream(&disk_space) << "Current available disk space: " << disk_space_avail << "GB" << "; insufficient disk space: " << disk_space_remain << "GB";
            ui.lineEdit_disk_space_avail->setText(disk_space);        
            palette.setColor(QPalette::Base, ErrorColor());
            ui.lineEdit_disk_space_avail->setPalette(palette);
            insufficient_disk_space_ = true;
        }
        else
        {
            QString disk_space;
            QTextStream(&disk_space) << "Current available disk space: " << disk_space_avail << "GB" << "; disk space remain: " << disk_space_remain << "GB";
            ui.lineEdit_disk_space_avail->setText(disk_space);
            palette.setColor(QPalette::Base, Qt::green);
            ui.lineEdit_disk_space_avail->setPalette(palette);
            insufficient_disk_space_ = false;
        }
        // memory handling
        long long memory_needed = static_cast<long long>(tif_img_width_)
            * static_cast<long long>(tif_img_height_)
            * static_cast<long long>(number_of_projection_)
            * sizeof(uint16_t) / GB_;
        long long memory_remain = avail_phys_mem - memory_needed;
        if (memory_remain <= 0)
        {
            QString mem_space;
            QTextStream(&mem_space) << "Memory needed: " << memory_needed << "GB" << "; missing: " << -memory_remain << "GB";
            ui.lineEdit_memory_needed->setText(mem_space);
            palette.setColor(QPalette::Base, ErrorColor());
            ui.lineEdit_memory_needed->setPalette(palette);
            insufficient_ram_ = true;
        }
        else
        {
            QString mem_space;
            QTextStream(&mem_space) << "Memory needed: " << memory_needed << "GB";
            ui.lineEdit_memory_needed->setText(mem_space);
            palette.setColor(QPalette::Base, Qt::green);
            ui.lineEdit_memory_needed->setPalette(palette);
            insufficient_ram_ = false;
        }
    }
}

void RACGUI::ReadTifImages()
{
    if (ui.lineEdit_tif_output_directory->text().isEmpty())
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setWindowIcon(QIcon("ico_attention.png"));
        msgBox.setText("Please specify output directory!");
        msgBox.exec();
        return;
    }

    image_stack_.clear();

    if (number_of_projection_ == 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        QIcon dlgicon = QIcon("ico_attention.png");
        msgBox.setWindowIcon(dlgicon);
        msgBox.setText("No files were selected!");
        msgBox.exec();
        return;
    }

    // check of resources
    /////////////////////
    if (insufficient_ram_)
    {
        QMessageBox::StandardButton ret = 
            QMessageBox::critical(nullptr,
                                 "Not Enough Memory",                             
            "Not enough memory available to load images. "\
            "Close application to free memory or abort program. "\
            "Still continue?",
            QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::No)
            return;
    }
    if (insufficient_disk_space_)
    {
        QMessageBox::StandardButton ret =
            QMessageBox::critical(nullptr,
                "Not Enough Disk Space",
                "Not enough disk space available to to store the processed images. "\
                "Select another drive or abort program. "\
                "Still continue?",
                QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::No)
            return;
    }
 
    QProgressDialog progress("Reading Tif Files...", "Cancel", 0, number_of_projection_, this);
    progress.setWindowTitle("Loading TIF Files");
    //QIcon dlgicon = QIcon::fromTheme(QIcon::ThemeIcon::DialogInformation);
    QIcon dlgicon = QIcon("ico_note.png");
    progress.setWindowIcon(dlgicon);
    progress.setWindowModality(Qt::WindowModal);

    cv::Mat img_mat;
    bool aborted = false;
    for (uint32_t i = 0; i < number_of_projection_; i++)
    {
        img_mat = cv::imread(tif_file_list_[i].toStdString(), cv::IMREAD_GRAYSCALE | cv::IMREAD_ANYDEPTH);
        image_stack_.push_back(img_mat);
        progress.setValue(i);
        if (progress.wasCanceled())
        {
            image_stack_.clear();
            aborted = true;
            break;
        }
        // sum projections for bad pixel corr.
        ///////////////////////////////////////
        cv::Mat mat_float;
        img_mat.convertTo(mat_float, CV_32F);
        projection_sum_tifimg_ = projection_sum_tifimg_ + mat_float;
    }
    progress.setValue(number_of_projection_);
    if (aborted)
    {
        ui.textEdit_logging_output->append("Reading tif files aborted");
    }
    else
    {
        ui.textEdit_logging_output->append("Reading tif files finished");
        ui.pushButton_start_rac->setEnabled(true);
    }
}

// Raw files handling
////////////////////////
void RACGUI::SelectRawFiles()
{
    QStringList file_list = QFileDialog::getOpenFileNames(this, tr("Select all projection files (CTRL a)"),
        QDir::rootPath(),
        tr("Projection File (*.raw *.*)"));
    // clear file list
    raw_file_list_.clear();
    if (file_list.isEmpty())
    {
        ui.textEdit_logging_output->append("No raw files selected.");
        return;
    }
    // store name of files
    raw_file_list_ = file_list;

    // count selected files
    QString msg;
    QTextStream(&msg) << "Select " << file_list.count() << " files.";
    ui.textEdit_logging_output->append(msg);

    // store and show path
    QFileInfo raw_input_directory(file_list[0]);
    raw_input_dir_ = raw_input_directory.absoluteDir().path(); //-ju-24-Feb-2025 hold path without trailing /
    //-ju-24-Feb-2025 hold filename -> create new output path and check if files already exists
    QString filename = raw_input_directory.fileName();
    ui.lineEdit_raw_input_directory->setText(raw_input_dir_);

    // message
    ui.textEdit_logging_output->append(raw_input_dir_);

    // number of projections
    number_of_projection_ = raw_file_list_.size();
    QString number_str;
    QTextStream(&number_str) << number_of_projection_;
    ui.lineEdit_row_show_number_of_files->setText(number_str);
    number_str.clear();

    // disable Run RAC Button to enforce re-loading
    ui.pushButton_start_rac->setEnabled(false);
}

// Selecting raw images and check resources
////////////////////////////////////////////
void RACGUI::SelectRawOutputDir()
{
    QString raw_out_dir =
        QFileDialog::getExistingDirectory(0,
            tr("Select output directory"),
            QDir::rootPath(),
            QFileDialog::ShowDirsOnly);
    if (raw_out_dir.isEmpty())
    {
        return;
    }
    ui.lineEdit_raw_output_directory->setText(raw_out_dir);
    raw_output_dir_ = raw_out_dir;
    QPalette palette = ui.lineEdit_disk_space_avail->palette();
    // save old palette
    disk_space_bg_color_ = palette;
    // check disk space
    ///////////////////
    // get size of image stack in GB
    int type_index = ui.comboBox_raw_spec_type->currentIndex();
    uint32_t data_type_size;
    if (type_index == 0)
    {
        data_type_size = 4;
        raw_type_index_ = 0;
    }
    else
    {
        data_type_size = 2;
        raw_type_index_ = 1;
    }
    raw_img_width_ = ui.spinBox_raw_img_width->value();
    raw_img_height_ = ui.spinBox_raw_img_height->value();

    uint64_t avail_phys_mem;
    GetAvailMemory(avail_phys_mem, GB_);
    QString mem_avail_str;
    QTextStream(&mem_avail_str) << avail_phys_mem << "GB";
    ui.lineEdit_memory_avail->setText(mem_avail_str);
    //disk usage info
    long long stack_space_size = static_cast<long long>(raw_img_width_) 
        * static_cast<long long>(raw_img_height_) 
        * static_cast<long long>(number_of_projection_) 
        * data_type_size / GB_;

    // init error state
    insufficient_ram_ = false;
    insufficient_disk_space_ = false;

    QStorageInfo storage(raw_output_dir_);
    if (storage.isValid() && storage.isReady()) 
    {
        long long disk_space_avail = storage.bytesAvailable() / GB_;
        long long disk_space_remain = disk_space_avail - stack_space_size;
        if (disk_space_remain <= 0)
        {
            QString disk_space;
            QTextStream(&disk_space) << "Current available disk space: " << disk_space_avail << "GB" << "; insufficient disk space: " << disk_space_remain << "GB";
            ui.lineEdit_disk_space_avail->setText(disk_space);
            palette.setColor(QPalette::Base, ErrorColor());
            ui.lineEdit_disk_space_avail->setPalette(palette);
            insufficient_disk_space_ = true;
        }
        else
        {
            QString disk_space;
            QTextStream(&disk_space) << "Current available disk space: " << disk_space_avail << "GB" << "; disk space remain: " << disk_space_remain << "GB";
            ui.lineEdit_disk_space_avail->setText(disk_space);
            palette.setColor(QPalette::Base, Qt::green);
            ui.lineEdit_disk_space_avail->setPalette(palette);
            insufficient_disk_space_ = false;
        }
        // memory handling
        long long memory_needed = static_cast<long long>(raw_img_width_)
            * static_cast<long long>(raw_img_height_)
            * static_cast<long long>(number_of_projection_)
            * data_type_size / GB_;
        long long memory_remain = avail_phys_mem - memory_needed;
        if (memory_remain <= 0)
        {
            QString mem_space;
            QTextStream(&mem_space) << "Memory needed: " << memory_needed << "GB" << "; missing: " << -memory_remain << "GB";
            ui.lineEdit_memory_needed->setText(mem_space);
            palette.setColor(QPalette::Base, ErrorColor());
            ui.lineEdit_memory_needed->setPalette(palette);
            insufficient_ram_ = true;
        }
        else
        {
            QString mem_space;
            QTextStream(&mem_space) << "Memory needed: " << memory_needed << "GB";
            ui.lineEdit_memory_needed->setText(mem_space);
            palette.setColor(QPalette::Base, Qt::green);
            ui.lineEdit_memory_needed->setPalette(palette);
            insufficient_ram_ = false;
        }
    }
}

void RACGUI::ReadRawFiles()
{    // check of resources
    /////////////////////
    if (insufficient_ram_)
    {
        QMessageBox::StandardButton ret =
            QMessageBox::critical(nullptr,
                "Not Enough Memory",
                "Not enough memory available to load images. "\
                "Close application to free memory or abort program. "\
                "Still continue?",
                QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::No)
            return;
    }
    if (insufficient_disk_space_)
    {
        QMessageBox::StandardButton ret =
            QMessageBox::critical(nullptr,
                "Not Enough Disk Space",
                "Not enough disk space available to to store the processed images. "\
                "Select another drive or abort program. "\
                "Still continue?",
                QMessageBox::Yes | QMessageBox::No);
        if (ret == QMessageBox::No)
            return;
    }

    // check if files are selected
    if (number_of_projection_ == 0)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        QIcon dlgicon = QIcon("ico_attention.png");
        msgBox.setWindowIcon(dlgicon);
        msgBox.setText("No files were selected!");
        msgBox.exec();
        return;
    }

    // check if input and output directory is valid
    // /////////////////////////////////////////////
    QString in_dir_str = ui.lineEdit_raw_input_directory->text();
    if (!FileExists(in_dir_str.toStdString()))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setWindowIcon(QIcon("ico_attention.png"));
        msgBox.setText("Please specify input directory!");
        msgBox.exec();
        return;
    }

    QString out_dir_str = ui.lineEdit_raw_output_directory->text();
     if (!FileExists(out_dir_str.toStdString()))
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Warning");
        msgBox.setWindowIcon(QIcon("ico_attention.png"));
        msgBox.setText("Please specify output directory!");
        msgBox.exec();
        return;
    }
    
    // raw type
    int type_index = ui.comboBox_raw_spec_type->currentIndex();

    uint32_t type_size;
    if (type_index == 0)
    {
        type_size = 4;
    }
    else
    {
        type_size = 2;
    }

    // check of valid file size
    ////////////////////////////
    QFileInfo checkFile(raw_file_list_[0]);
    uint32_t img_width = ui.spinBox_raw_img_width->value();
    raw_img_width_ = img_width;
    uint32_t img_height = ui.spinBox_raw_img_height->value();
    raw_img_height_ = img_height;
    uint32_t ceck_size = img_width * img_height * type_size;
    if (checkFile.size() != ceck_size)
    {
        QMessageBox msgBox;
        msgBox.setWindowTitle("Error");
        QIcon dlgicon = QIcon("warningsErrors.png");
        msgBox.setWindowIcon(dlgicon);
        msgBox.setText("Image size is not valid!\nCheck parameters.");
        msgBox.exec();
        return;
    }

    // read raw according data type
    if (type_size == 4)
    {
        float type_float = 0.0f;
        ReadRawImages(type_float);
    }
    else
    {
        uint16_t type_uint16 = 0;
        ReadRawImages(type_uint16);
    }
}


template<typename T>
void RACGUI::ReadRawImages(T type)
{
    image_stack_.clear();

    QProgressDialog progress("Reading Raw Files...", "Cancel", 0, number_of_projection_, this);
    progress.setWindowTitle("Loading RAW Files");
    QIcon dlgicon = QIcon("ico_note.png");
    progress.setWindowIcon(dlgicon);
    progress.setWindowModality(Qt::WindowModal);

    bool aborted = false;
    std::ifstream projections;
    for (uint32_t i = 0; i < number_of_projection_; i++)
    {
        projections.open(raw_file_list_[i].toStdString(), std::ios::binary);
        if (!projections.is_open())
        {
            QString msg;
            QTextStream(&msg) << "Can not open " << raw_file_list_[i];
            image_stack_.clear();
            return;
        }
        cv::Mat img_mat;
        if constexpr (std::is_floating_point<T>::value)
        {
            if (sizeof(T) == 4)
            {
                img_mat = cv::Mat::zeros(raw_img_height_, raw_img_width_, CV_32F);
            }
            else
            {
                ui.textEdit_logging_output->append("Only 4 byte floating point data is supported");
                return;
            }
        }
        if constexpr (std::is_unsigned<T>::value)
        {
            if (sizeof(T) == 2)
            {
                img_mat = cv::Mat::zeros(raw_img_height_, raw_img_width_, CV_16U);
            }
            else
            {
                ui.textEdit_logging_output->append("Only 2 byte unsigned int data is supported");
                return;
            }
        }
        projections.read((char*)img_mat.data, sizeof(T)*raw_img_width_*raw_img_height_);
        image_stack_.push_back(img_mat);
        projections.close();
        progress.setValue(i);
        if (progress.wasCanceled())
        {
            image_stack_.clear();
            aborted = true;
            break;
        }
    }
    progress.setValue(number_of_projection_);
#ifdef _DEBUG
    for (uint32_t i = 0; i < number_of_projection_; i++)
    {
        cv::Mat cloneMat = image_stack_[i];
    }
#endif
    if (aborted)
    {
        ui.textEdit_logging_output->append("Reading raw files aborted.");
    }
    else
    {
        ui.textEdit_logging_output->append("Reading raw files finished.");
        ui.pushButton_start_rac->setEnabled(true);
    }

}

// RAC processing
//////////////////
void RACGUI::CheckFilterlen()
{
    // always odd filter length
    uint32_t fil_len = ui.spinBox_filter_length->value();
    if (fil_len % 2 == 0)
    {
        ui.spinBox_filter_length->setValue(fil_len + 1);
    }
    median_filter_len_ = ui.spinBox_filter_length->value();
}

void RACGUI::CheckNumThreads()
{
    number_of_threads_ = ui.spinBox_number_of_threads->value();
    if (number_of_threads_ > max_number_threads_)
    {
        number_of_threads_ = max_number_threads_;
    }
    ui.spinBox_number_of_threads->setValue(number_of_threads_);
}

void RACGUI::CheckMemory()
{
    uint64_t avail_mem;
    GetAvailMemory(avail_mem, GB_);
    QString mem_info_str;
    QTextStream(&mem_info_str) << "Available physical memory: " << avail_mem << "GB";
    QMessageBox::StandardButton ret =
        QMessageBox::information(nullptr,
            "Memory available", mem_info_str);
}

void RACGUI::SegmentForOutliers()
{
    bad_pixel_mat_ = cv::Mat::zeros(projection_sum_tifimg_.size(), projection_sum_tifimg_.type());
    cv::Mat median_image = cv::Mat::zeros(projection_sum_tifimg_.size(), projection_sum_tifimg_.type());
    const int mask_size = 3;
    // blur projection image by a median filter with mask of height & width of mask_size
    medianBlur(projection_sum_tifimg_, median_image, mask_size);

    // detection of bad pixels 1. step
    absdiff(projection_sum_tifimg_, median_image, bad_pixel_mat_);

    cv::Scalar mean_val;
    cv::Scalar stddev_val;
    cv::meanStdDev(bad_pixel_mat_, mean_val, stddev_val);
    double mean_s = mean_val.val[0];
    double stddev_s = stddev_val.val[0];
    // calc. z score of distribution -> mean = 0, stddev = 1
    // => standard score
    //assume normal Distr.; here only approx. in coarse way
    bad_pixel_mat_ = (bad_pixel_mat_ - mean_s) / stddev_s;
#ifdef _DEBUG
    cv::Scalar meanVal_z;
    cv::Scalar stddevVal_z;
    cv::meanStdDev(bad_pixel_mat_, meanVal_z, stddevVal_z);
    double m = meanVal_z.val[0];
    double s = stddevVal_z.val[0];
#endif
    // threshold bad pixel matrices using a multiple of standardized sigma
    double thres_val = static_cast<double>(ui.spinBox_bad_pixel_theshold->value());
    cv::threshold(bad_pixel_mat_, bad_pixel_mat_, thres_val, 1.0, cv::THRESH_BINARY);
}

// find coordinates of bad pixels and store them
void RACGUI::FindBadPixels(cv::Mat bad_pixel_img_matrix, std::vector<cv::Vec2i>&bad_pixel_list)
{
    int nr_rows = bad_pixel_img_matrix.rows;
    int nr_cols = bad_pixel_img_matrix.cols;
    cv::Vec2i coordinate;

    for (int row = 0; row < nr_rows; row++)
    {
        // start pointer of date in row
        float* data = bad_pixel_img_matrix.ptr<float>(row);
        for (int col = 0; col < nr_cols; col++)
        {
            if (*data > 0.0f)
            {
                coordinate.val[0] = row;
                coordinate.val[1] = col;
                bad_pixel_list.push_back(coordinate);
            }
            *data++;
        }
    }
}

void RACGUI::BadPixelCorrection(std::vector<cv::Mat>& img_stack)
{
    SegmentForOutliers();
    std::vector<cv::Vec2i> bad_pixel_list;
    FindBadPixels(bad_pixel_mat_, bad_pixel_list);

    // loop over all projections and apply corrections on bad pixels
    /////////////////////////////////////////////////////////////////
    omp_set_num_threads(ui.spinBox_number_of_threads->value());
    int i;
#pragma omp parallel for shared(img_stack, bad_pixel_list)
    for (i = 0; i < img_stack.size(); i++)
    {
        for (int k = 0; k < bad_pixel_list.size(); k++)
        {
            BadPixelReplaceByMedian9(img_stack[i], bad_pixel_list[k]);
        }        
    }
}

// replace bad pixels by the median value in a rectangle 3x3 around
void RACGUI::BadPixelReplaceByMedian9(cv::Mat& projection, cv::Vec2i& pixCoord)
{
    cv::Mat filterVec(1, 8, CV_16UC1);
    cv::Vec2i imageDim(projection.rows, projection.cols);
    float val, val0;
    // check out of border values
    if (pixCoord.val[0] > 0 && pixCoord.val[0] < imageDim.val[0] - 2 &&
        pixCoord.val[1] > 0 && pixCoord.val[1] < imageDim.val[1] - 2)
    {
        val0 = projection.at<uint16_t>(pixCoord.val[0], pixCoord.val[1]);
        val = projection.at<uint16_t>(pixCoord.val[0] - 1, pixCoord.val[1] - 1); // (-1,-1) (y,x)
        filterVec.at<uint16_t>(0) = val;
        val = projection.at<uint16_t>(pixCoord.val[0] - 1, pixCoord.val[1]); // (-1, 0)
        filterVec.at<uint16_t>(1) = val;
        val = projection.at<uint16_t>(pixCoord.val[0] - 1, pixCoord.val[1] + 1); // (-1, 1)
        filterVec.at<uint16_t>(2) = val;
        val = projection.at<uint16_t>(pixCoord.val[0], pixCoord.val[1] - 1); // ( 0,-1)
        filterVec.at<uint16_t>(3) = val;
        val = projection.at<uint16_t>(pixCoord.val[0], pixCoord.val[1] + 1); // ( 0, 1)
        filterVec.at<uint16_t>(4) = val;
        val = projection.at<uint16_t>(pixCoord.val[0] + 1, pixCoord.val[1] - 1); // ( 1,-1)
        filterVec.at<uint16_t>(5) = val;
        val = projection.at<uint16_t>(pixCoord.val[0] + 1, pixCoord.val[1]); // ( 1, 0)
        filterVec.at<uint16_t>(6) = val;
        val = projection.at<uint16_t>(pixCoord.val[0] + 1, pixCoord.val[1] + 1); // ( 1, 1)
        filterVec.at<uint16_t>(7) = val;
        cv::sort(filterVec, filterVec, cv::SORT_ASCENDING);
        // take value 4 and 5 to calc. median from mean of both, because of even value list (len=8)
        float medianVal = (filterVec.at<uint16_t>(3) + filterVec.at<uint16_t>(4)) / 2.0f;
        uint16_t median_val = static_cast<uint16_t>(std::round(medianVal));
        // replace central pixel
        projection.at<uint16_t>(pixCoord.val[0], pixCoord.val[1]) = median_val;
    }
}

void RACGUI::RunRAC()
{ 
    // 0 => Tif => only uint 16Bit supported
    if (ui.toolBox_file_import->currentIndex() == 0)
    {
        if (ui.checkBox_apply_bad_pixel_correction->isChecked())
        {
            // perform pixel correction (in parallel)
            ui.textEdit_logging_output->append("Start Bad Pixel Correction");
            std::cout << "Start Bad Pixel Correction\n";
            BadPixelCorrection(image_stack_);
            std::cout << "Bad Pixel Correction finished\n" << std::flush;
            ui.textEdit_logging_output->append("Bad Pixel Correction finished");
        }

        QString proc_msg;
        QTextStream(&proc_msg) << "Run RAC: Data type=Tif 16 Bit unsigned, projections=" << number_of_projection_
            << ", width=" << tif_img_width_ << ", height=" << tif_img_height_
            << ", filter len=" << median_filter_len_ << ", threads=" << number_of_threads_;
        ui.textEdit_logging_output->append(proc_msg);
        ui.textEdit_logging_output->repaint();

        QString msg;
        QTextStream(&msg) << "Please be patient!. Processing will take a while and GUI will freeze meanwhile!";
        ui.textEdit_logging_output->append(msg);
        std::cout << "Please be patient!. Processing will take a while and GUI will freeze meanwhile!\n" << std::flush;
        QPalette palette = ui.textEdit_logging_output->palette();
        text_editor_bg_color_ = palette;
        palette.setColor(QPalette::Text, Qt::red);
        ui.textEdit_logging_output->setPalette(palette);

        // check if image stack > 0
        if (image_stack_.size() == 0)
        {
            ui.textEdit_logging_output->append("Image stack is empty!");
            return;
        }
        const auto start_proc{ std::chrono::steady_clock::now() };
        uint16_t data_type = 0;
        // do RAC processing
        RACProcessing(data_type, image_stack_,
            number_of_projection_,
            tif_img_width_, tif_img_height_,
            median_filter_len_, number_of_threads_
        );
        const auto end_proc{ std::chrono::steady_clock::now() };
        const std::chrono::duration<double> elapsed_seconds_proc{end_proc - start_proc};
        QString msg_proc;
        QTextStream(&msg_proc) << "Time for RAC processing: " << elapsed_seconds_proc.count() << " sec";
        ui.textEdit_logging_output->append(msg_proc);

        // save RAC processed projectionen to defined output directory
        //////////////////////////////////////////////////////////////
        QString msg_save;
        QTextStream(&msg_save) << "Saving projection files to: " << tif_output_dir_;
        ui.textEdit_logging_output->append(msg_save);
        const auto start_write{ std::chrono::steady_clock::now() };
        WriteTifImages();
        const auto end_write{ std::chrono::steady_clock::now() };
        const std::chrono::duration<double> elapsed_seconds_write{end_write - start_write};
        QString msg_write;
        QTextStream(&msg_write) << "Time for writing projections: " << elapsed_seconds_write.count() << " sec";
        ui.textEdit_logging_output->append(msg_write);
    }
    // 1 => Raw
    if (ui.toolBox_file_import->currentIndex() == 1)
    {
        if (raw_type_index_ == FLOAT_TYPE)
        {
            QString proc_msg;
            QTextStream(&proc_msg) << "Run RAC: Data type=float, projections=" << number_of_projection_
                << ", width=" << raw_img_width_ << ", height=" << raw_img_height_
                << ", filter len=" << median_filter_len_ << ", threads=" << number_of_threads_;
            ui.textEdit_logging_output->append(proc_msg);
            ui.textEdit_logging_output->repaint();

            QString msg;
            QTextStream(&msg) << "Please be patient!. Processing will take a while and GUI will freeze meanwhile!";
            ui.textEdit_logging_output->append(msg);
            QPalette palette = ui.textEdit_logging_output->palette();
            text_editor_bg_color_ = palette;
            palette.setColor(QPalette::Text, Qt::red);
            ui.textEdit_logging_output->setPalette(palette);
            ui.textEdit_logging_output->repaint();

            // check if image stack > 0
            if (image_stack_.size() == 0)
            {
                ui.textEdit_logging_output->append("Image stack is empty!");
                return;
            }
            const auto start_proc{ std::chrono::steady_clock::now() };
            float data_type = 0.0f;

            // Start RAC processing
            ////////////////////////
            RACProcessing(data_type, image_stack_,
                number_of_projection_,
                raw_img_width_, raw_img_height_,
                median_filter_len_, number_of_threads_
            );
            const auto end_proc{ std::chrono::steady_clock::now() };
            const std::chrono::duration<double> elapsed_seconds_proc{end_proc - start_proc};
            QString msg_proc;
            QTextStream(&msg_proc) << "Time for RAC processing: " << elapsed_seconds_proc.count() << " sec";
            ui.textEdit_logging_output->append(msg_proc);

            // save RAC processed projectionen to defined output directory
            //////////////////////////////////////////////////////////////
            QString msg_save;
            QTextStream(&msg_save) << "Saving projection files to: " << raw_output_dir_;
            ui.textEdit_logging_output->append(msg_save);
            const auto start_write{ std::chrono::steady_clock::now() };
            WriteRawImages(data_type);
            const auto end_write{ std::chrono::steady_clock::now() };
            const std::chrono::duration<double> elapsed_seconds_write{end_write - start_write};
            QString msg_write;
            QTextStream(&msg_write) << "Time for writing projections: " << elapsed_seconds_write.count() << " sec";
            ui.textEdit_logging_output->append(msg_write);
        }
        if (raw_type_index_ == UINT16_TYPE)
        {
            QString proc_msg;
            QTextStream(&proc_msg) << "Run RAC: Data type=unsigned int 16 Bit, projections=" << number_of_projection_
                << ", width=" << raw_img_width_ << ", height=" << raw_img_height_
                << ", filter len=" << median_filter_len_ << ", threads=" << number_of_threads_;
            ui.textEdit_logging_output->append(proc_msg);
            ui.textEdit_logging_output->repaint();

            QString msg;
            QTextStream(&msg) << "Please be patient!. Processing will take a while and GUI will freeze meanwhile!";
            ui.textEdit_logging_output->append(msg);
            QPalette palette = ui.textEdit_logging_output->palette();
            text_editor_bg_color_ = palette;
            palette.setColor(QPalette::Text, Qt::red);
            ui.textEdit_logging_output->setPalette(palette);
            ui.textEdit_logging_output->repaint();

            // check if image stack > 0
            if (image_stack_.size() == 0)
            {
                ui.textEdit_logging_output->append("Image stack is empty!");
                return;
            }
            const auto start_proc{ std::chrono::steady_clock::now() };
            uint16_t data_type = 0;

            // Start RAC processing
            ////////////////////////
            RACProcessing(data_type, image_stack_,
                number_of_projection_,
                raw_img_width_, raw_img_height_,
                median_filter_len_, number_of_threads_
            );
            const auto end_proc{ std::chrono::steady_clock::now() };
            const std::chrono::duration<double> elapsed_seconds_proc{end_proc - start_proc};
            QString msg_proc;
            QTextStream(&msg_proc) << "Time for RAC processing: " << elapsed_seconds_proc.count() << " sec";
            ui.textEdit_logging_output->append(msg_proc);

            // save RAC processed projectionen to defined output directory
            //////////////////////////////////////////////////////////////
            QString msg_save;
            QTextStream(&msg_save) << "Saving projection files to: " << raw_output_dir_;
            ui.textEdit_logging_output->append(msg_save);
            const auto start_write{ std::chrono::steady_clock::now() };
            WriteRawImages(data_type);
            const auto end_write{ std::chrono::steady_clock::now() };
            const std::chrono::duration<double> elapsed_seconds_write{end_write - start_write};
            QString msg_write;
            QTextStream(&msg_write) << "Time for writing projections: " << elapsed_seconds_write.count() << " sec";
            ui.textEdit_logging_output->append(msg_write);
        }
    }
}

// perform the ring artefact processing
////////////////////////////////////////
template<typename T>
void RACGUI::RACProcessing(T type, 
    std::vector<cv::Mat>& img_stack, 
    const uint& n_projections,
    const uint& im_width,
    const uint& im_height, 
    const uint& filter_len, 
    const uint& num_threads)
{
    omp_set_num_threads(num_threads);
 
    int counter = 0;
    int iy;
    // run the process loop along the sinogram space
    /////////////////////////////////////////////////
#pragma omp parallel for shared(img_stack, n_projections, im_width, im_height, filter_len, counter)
    for (iy = 0; iy < im_height; iy++)
    {
        {
            std::vector<std::vector<T> > reslice_proj;
            std::vector<std::vector<std::pair<T, int> > > reslice_pair_proj;
            for (uint ix = 0; ix < im_width; ix++)
            {
                cv::Mat stack_array;
                if constexpr (std::is_floating_point<T>::value)
                {
                    if (sizeof(T) == 4)
                    {
                        stack_array = cv::Mat::zeros(1, n_projections, CV_32F);
                    }
                    else
                    {
                        std::cerr << "Only 4 byte floating point data is supported --> Exit program\n";
                        terminate();
                    }
                }
                if constexpr (std::is_unsigned<T>::value)
                {
                    if (sizeof(T) == 2)
                    {
                        stack_array = cv::Mat::zeros(1, n_projections, CV_32F);
                    }
                    else
                    {
                        std::cerr << "Only 2 byte unsigned int data is supported --> Exit program\n";
                        terminate();
                    }
                }

                // sort gray values of pixels of a line in sinogram space 
                // and store the original position
                // to be able to re-oder the gray value pixel to the original position
                // after the filtering
                std::vector<std::pair<T, int> > vec_pair;
                std::vector<T> vec;

                for (uint i = 0; i < n_projections; i++)
                {

                    cv::Mat cur_mat = img_stack[i];
                    T cur_val = cur_mat.at<T>(iy, ix);
                    stack_array.at<T>(0, i) = cur_val;
                    vec_pair.push_back(std::make_pair(cur_val, i));
                    vec.push_back(cur_val);
                }
                // sort gray values 
                std::sort(vec.begin(), vec.end());
                // original position (index) is still persistent
                std::sort(vec_pair.begin(), vec_pair.end());
                // x position in first index, grey value choosen from projection
                reslice_proj.push_back(vec);
                reslice_pair_proj.push_back(vec_pair);
            }


            // apply median filter
            std::vector<std::vector<T>> reslice_smooth_proj;
            for (uint y = 0; y < n_projections; y++)
            {
                std::vector<T> row(im_width);
                for (uint ix = 0; ix < im_width; ix++)
                {
                    row[ix] = reslice_proj[ix][y];
                }
                std::vector<T> row_smooth = MedianFilter(row, filter_len);
                reslice_smooth_proj.push_back(row_smooth);
            }
            // reorder sort -> to original order
            ////////////////////////////////////////
            std::vector<T> reordered_line(im_width);
            std::vector<std::vector<T>> array_corr;
            array_corr.resize(n_projections, std::vector<T>(im_width));
            for (uint32_t ix = 0; ix < im_width; ix++)
            {
                for (uint32_t i = 0; i < reslice_smooth_proj.size(); i++)
                {
                    array_corr[reslice_pair_proj[ix][i].second][ix] = reslice_smooth_proj[i][ix];
                }
            }

            std::vector<T> sinogram_line;
            for (uint32_t j = 0; j < n_projections; j++)
            {
                sinogram_line = array_corr[j];
                // pointer to row iy
                T* ptr = img_stack[j].ptr<T>(iy);
                // copy sinogram line to projection
                memcpy(ptr, (uchar*)sinogram_line.data(), sinogram_line.size() * sizeof(T));
            }

        }
        counter++;
        // write to console as long no GUI thread implemented (GUI will freeze)
        if (counter % 50 == 0)
        {
            std::cout << counter << " slices processed\n";
        }
    }
    ui.textEdit_logging_output->setPalette(text_editor_bg_color_);
    ui.textEdit_logging_output->repaint();
    QString prog_msg_finish;
    QTextStream(&prog_msg_finish) << "Finished. " << counter << " sinograms were processed.";
    ui.textEdit_logging_output->append(prog_msg_finish);
}

// writing images
//////////////////

// Tif images
void RACGUI::WriteTifImages()
{
    // allocate memory for a projection
    ////////////////////////////////////

    if (tif_file_list_.size() == 0 || image_stack_.size() == 0)
    {
        ui.textEdit_logging_output->append("File list or image stack is empty.");
        return;
    }

    // check if output directory is empty
    QString file_exist_check(tif_output_dir_);
    file_exist_check += "/";
    QFileInfo tif_ouput_file_path(tif_file_list_[0]);
    file_exist_check += tif_ouput_file_path.fileName();

    if (FileExists(file_exist_check.toStdString()))
    {
        QMessageBox::StandardButton ret = QMessageBox::question(nullptr, "Files are existing", "Overwriting existing files?");
        if (ret == QMessageBox::No)
        {
            return;
        }
    }

    QProgressDialog progress("Writing tif files...", "Cancel", 0, number_of_projection_, this);
    progress.setWindowTitle("Writing Projections");
    QIcon dlgicon = QIcon("ico_note.png");
    progress.setWindowIcon(dlgicon);
    progress.setWindowModality(Qt::WindowModal);

    bool aborted = false;
    for (uint32_t p = 0; p < number_of_projection_; p++)
    {
        QString file_path(tif_output_dir_);
        QFileInfo tif_file(tif_file_list_[p]);
        file_path += "/";
        file_path += tif_file.fileName();

        // write tiff without compression = 1
         cv::imwrite(file_path.toStdString(), image_stack_[p], { cv::IMWRITE_TIFF_COMPRESSION, 1 });

        progress.setValue(p);
        if (progress.wasCanceled())
        {
            aborted = true;
            break;
        }
    }
    progress.setValue(number_of_projection_);
    if (aborted)
    {
        ui.textEdit_logging_output->append("Writing projections aborted");
    }
    else
    {
        ui.textEdit_logging_output->append("Writing projections finished.");
    }
}

// raw images
template<typename T> void RACGUI::WriteRawImages(T type)
{
    // allocate memory for a projection
    ////////////////////////////////////
    uint32_t proj_size = raw_img_width_ * raw_img_height_;
    std::vector<T> proj_data(proj_size);

    if (raw_file_list_.size() == 0 || image_stack_.size() == 0)
    {
        ui.textEdit_logging_output->append("File list or image stack is empty.");
        return;
    }

    // check if output directory is empty
    QString file_exist_check(raw_output_dir_);
    file_exist_check += "/";
    QFileInfo raw_ouput_file_path(raw_file_list_[0]);
    file_exist_check += raw_ouput_file_path.fileName();

    if (FileExists(file_exist_check.toStdString()))
    {
        QMessageBox::StandardButton ret = QMessageBox::question(nullptr, "Files are existing", "Overwriting existing files?");
        if (ret == QMessageBox::No)
        {
            return;
        }
    }

    QProgressDialog progress("Writing raw files...", "Cancel", 0, number_of_projection_, this);
    progress.setWindowTitle("Writing Projections");
    QIcon dlgicon = QIcon("ico_note.png");
    progress.setWindowIcon(dlgicon);
    progress.setWindowModality(Qt::WindowModal);

    bool aborted = false;
    for (uint32_t p = 0; p < number_of_projection_; p++)
    {
        std::ofstream proj_out;
        QString file_path(raw_output_dir_);
        QFileInfo raw_file(raw_file_list_[p]);
        file_path += "/";
        file_path += raw_file.fileName();

        proj_out.open(file_path.toStdString(), std::ios::binary);
        if (!proj_out.is_open())
        {
            QString err_msg;
            QTextStream(&err_msg) << "Can not open file " << file_path << "!";
            ui.textEdit_logging_output->append(err_msg);
            return;
        }
        // point to begin of the current projection
        T* ptr = image_stack_[p].ptr<T>(0);

        // copy data and write
        memcpy(proj_data.data(), ptr, proj_size * sizeof(T));
        proj_out.write((char*)&proj_data[0], proj_size * sizeof(T));

        proj_out.close();

        progress.setValue(p);
        if (progress.wasCanceled())
        {
            aborted = true;
            break;
        }
    }
    progress.setValue(number_of_projection_);
    if (aborted)
    {
        ui.textEdit_logging_output->append("Writing projections aborted");
    }
    else
    {
        ui.textEdit_logging_output->append("Writing projections finished.");
    }
}

RACGUI::~RACGUI()
{}
