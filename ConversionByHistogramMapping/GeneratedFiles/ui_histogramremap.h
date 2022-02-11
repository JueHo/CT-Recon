/********************************************************************************
** Form generated from reading UI file 'histogramremap.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HISTOGRAMREMAP_H
#define UI_HISTOGRAMREMAP_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_HistogramRemapClass
{
public:
    QAction *actionClose;
    QAction *actionDec_2018_Version_0_9;
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_plotHistogram;
    QVBoxLayout *verticalLayout;
    QwtPlot *qwtPlot_histogram;
    QGroupBox *groupBox_histogramOptions;
    QHBoxLayout *horizontalLayout_17;
    QGroupBox *groupBox_scaling;
    QHBoxLayout *horizontalLayout_18;
    QHBoxLayout *horizontalLayout_16;
    QCheckBox *checkBox_yLog10;
    QPushButton *pushButton_rePlot;
    QGroupBox *groupBox_histogramBoundaries;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QLabel *label_leftBound;
    QDoubleSpinBox *doubleSpinBox_leftBound;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_rightBound;
    QDoubleSpinBox *doubleSpinBox_rightBound;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_10;
    QGroupBox *groupBox_colorOptions;
    QHBoxLayout *horizontalLayout_19;
    QPushButton *pushButton_selectColor;
    QLabel *label_histogramColor;
    QSpacerItem *horizontalSpacer_7;
    QPushButton *pushButton_PlotBackgroundColor;
    QLabel *label_plotBackgroundColor;
    QSpacerItem *horizontalSpacer_8;
    QGroupBox *groupBox_imageStack;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_enclose;
    QHBoxLayout *horizontalLayout_13;
    QGroupBox *groupBox_imageSize;
    QHBoxLayout *horizontalLayout_12;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_imgHeight;
    QSpinBox *spinBox_imgHeight;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_imgWidth;
    QSpinBox *spinBox_imgWidth;
    QGroupBox *groupBox_directories;
    QHBoxLayout *horizontalLayout_14;
    QHBoxLayout *horizontalLayout_10;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_selectImageStack;
    QLineEdit *lineEdit_sourceDir;
    QHBoxLayout *horizontalLayout_11;
    QPushButton *pushButton_destinationDir;
    QLineEdit *lineEdit_destinationDir;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_15;
    QCheckBox *checkBox_calcMinMaxStack;
    QVBoxLayout *verticalLayout_7;
    QDoubleSpinBox *doubleSpinBox_minGray;
    QDoubleSpinBox *doubleSpinBox_maxGray;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButton_readFromLogFile;
    QLineEdit *lineEdit_logFile;
    QHBoxLayout *horizontalLayout_readImageStack;
    QPushButton *pushButton_readImageStack;
    QLabel *label_fileSuffix;
    QComboBox *comboBox_fileSuffix;
    QSpacerItem *horizontalSpacer_9;
    QProgressBar *progressBar_readImageStack;
    QGroupBox *groupBox_convertImageStack;
    QVBoxLayout *verticalLayout_2;
    QFrame *line_seperator;
    QHBoxLayout *horizontalLayout_4;
    QPushButton *pushButton_Real32Byte;
    QSpacerItem *horizontalSpacer_3;
    QPushButton *pushButton_Real32Uint16;
    QSpacerItem *horizontalSpacer_5;
    QProgressBar *progressBar_convertImageStack;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuInfo;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *HistogramRemapClass)
    {
        if (HistogramRemapClass->objectName().isEmpty())
            HistogramRemapClass->setObjectName(QString::fromUtf8("HistogramRemapClass"));
        HistogramRemapClass->resize(792, 908);
        HistogramRemapClass->setMaximumSize(QSize(16777215, 16777215));
        QIcon icon;
        icon.addFile(QString::fromUtf8("HistogramRemap.ico"), QSize(), QIcon::Normal, QIcon::Off);
        HistogramRemapClass->setWindowIcon(icon);
        actionClose = new QAction(HistogramRemapClass);
        actionClose->setObjectName(QString::fromUtf8("actionClose"));
        actionDec_2018_Version_0_9 = new QAction(HistogramRemapClass);
        actionDec_2018_Version_0_9->setObjectName(QString::fromUtf8("actionDec_2018_Version_0_9"));
        centralWidget = new QWidget(HistogramRemapClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        centralWidget->setMaximumSize(QSize(16777215, 16777215));
        verticalLayout_3 = new QVBoxLayout(centralWidget);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox_plotHistogram = new QGroupBox(centralWidget);
        groupBox_plotHistogram->setObjectName(QString::fromUtf8("groupBox_plotHistogram"));
        verticalLayout = new QVBoxLayout(groupBox_plotHistogram);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        qwtPlot_histogram = new QwtPlot(groupBox_plotHistogram);
        qwtPlot_histogram->setObjectName(QString::fromUtf8("qwtPlot_histogram"));
        qwtPlot_histogram->setMinimumSize(QSize(600, 300));

        verticalLayout->addWidget(qwtPlot_histogram);

        groupBox_histogramOptions = new QGroupBox(groupBox_plotHistogram);
        groupBox_histogramOptions->setObjectName(QString::fromUtf8("groupBox_histogramOptions"));
        horizontalLayout_17 = new QHBoxLayout(groupBox_histogramOptions);
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        groupBox_scaling = new QGroupBox(groupBox_histogramOptions);
        groupBox_scaling->setObjectName(QString::fromUtf8("groupBox_scaling"));
        QSizePolicy sizePolicy1(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_scaling->sizePolicy().hasHeightForWidth());
        groupBox_scaling->setSizePolicy(sizePolicy1);
        horizontalLayout_18 = new QHBoxLayout(groupBox_scaling);
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        checkBox_yLog10 = new QCheckBox(groupBox_scaling);
        checkBox_yLog10->setObjectName(QString::fromUtf8("checkBox_yLog10"));

        horizontalLayout_16->addWidget(checkBox_yLog10);

        pushButton_rePlot = new QPushButton(groupBox_scaling);
        pushButton_rePlot->setObjectName(QString::fromUtf8("pushButton_rePlot"));

        horizontalLayout_16->addWidget(pushButton_rePlot);


        horizontalLayout_18->addLayout(horizontalLayout_16);


        horizontalLayout_17->addWidget(groupBox_scaling);

        groupBox_histogramBoundaries = new QGroupBox(groupBox_histogramOptions);
        groupBox_histogramBoundaries->setObjectName(QString::fromUtf8("groupBox_histogramBoundaries"));
        horizontalLayout_3 = new QHBoxLayout(groupBox_histogramBoundaries);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_leftBound = new QLabel(groupBox_histogramBoundaries);
        label_leftBound->setObjectName(QString::fromUtf8("label_leftBound"));
        QFont font;
        font.setPointSize(10);
        label_leftBound->setFont(font);
        label_leftBound->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        horizontalLayout_2->addWidget(label_leftBound);

        doubleSpinBox_leftBound = new QDoubleSpinBox(groupBox_histogramBoundaries);
        doubleSpinBox_leftBound->setObjectName(QString::fromUtf8("doubleSpinBox_leftBound"));
        doubleSpinBox_leftBound->setMinimumSize(QSize(80, 0));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush1(QColor(255, 0, 0, 128));
        brush1.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush1);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        QBrush brush2(QColor(255, 0, 0, 128));
        brush2.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        QBrush brush3(QColor(106, 104, 100, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        QBrush brush4(QColor(255, 0, 0, 128));
        brush4.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush4);
#endif
        doubleSpinBox_leftBound->setPalette(palette);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Consolas"));
        doubleSpinBox_leftBound->setFont(font1);
        doubleSpinBox_leftBound->setLayoutDirection(Qt::RightToLeft);
        doubleSpinBox_leftBound->setDecimals(7);
        doubleSpinBox_leftBound->setMinimum(-1000000000.000000000000000);
        doubleSpinBox_leftBound->setMaximum(1000000000.000000000000000);
        doubleSpinBox_leftBound->setSingleStep(1.000000000000000);

        horizontalLayout_2->addWidget(doubleSpinBox_leftBound);

        horizontalSpacer_2 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_rightBound = new QLabel(groupBox_histogramBoundaries);
        label_rightBound->setObjectName(QString::fromUtf8("label_rightBound"));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setWeight(50);
        label_rightBound->setFont(font2);
        label_rightBound->setStyleSheet(QString::fromUtf8("color: rgb(0, 0, 255);"));

        horizontalLayout->addWidget(label_rightBound);

        doubleSpinBox_rightBound = new QDoubleSpinBox(groupBox_histogramBoundaries);
        doubleSpinBox_rightBound->setObjectName(QString::fromUtf8("doubleSpinBox_rightBound"));
        doubleSpinBox_rightBound->setMinimumSize(QSize(80, 0));
        QPalette palette1;
        QBrush brush5(QColor(0, 0, 255, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush5);
        QBrush brush6(QColor(0, 0, 255, 128));
        brush6.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush6);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush5);
        QBrush brush7(QColor(0, 0, 255, 128));
        brush7.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush7);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush3);
        QBrush brush8(QColor(0, 0, 255, 128));
        brush8.setStyle(Qt::NoBrush);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush8);
#endif
        doubleSpinBox_rightBound->setPalette(palette1);
        QFont font3;
        font3.setFamily(QString::fromUtf8("Consolas"));
        font3.setBold(false);
        font3.setWeight(50);
        doubleSpinBox_rightBound->setFont(font3);
        doubleSpinBox_rightBound->setLayoutDirection(Qt::RightToLeft);
        doubleSpinBox_rightBound->setDecimals(7);
        doubleSpinBox_rightBound->setMinimum(-1000000000.000000000000000);
        doubleSpinBox_rightBound->setMaximum(1000000000.000000000000000);
        doubleSpinBox_rightBound->setSingleStep(1.000000000000000);

        horizontalLayout->addWidget(doubleSpinBox_rightBound);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);


        horizontalLayout_2->addLayout(horizontalLayout);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        horizontalLayout_17->addWidget(groupBox_histogramBoundaries);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_10);


        verticalLayout->addWidget(groupBox_histogramOptions);

        groupBox_colorOptions = new QGroupBox(groupBox_plotHistogram);
        groupBox_colorOptions->setObjectName(QString::fromUtf8("groupBox_colorOptions"));
        horizontalLayout_19 = new QHBoxLayout(groupBox_colorOptions);
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        pushButton_selectColor = new QPushButton(groupBox_colorOptions);
        pushButton_selectColor->setObjectName(QString::fromUtf8("pushButton_selectColor"));

        horizontalLayout_19->addWidget(pushButton_selectColor);

        label_histogramColor = new QLabel(groupBox_colorOptions);
        label_histogramColor->setObjectName(QString::fromUtf8("label_histogramColor"));
        label_histogramColor->setFrameShape(QFrame::Panel);

        horizontalLayout_19->addWidget(label_histogramColor);

        horizontalSpacer_7 = new QSpacerItem(20, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_7);

        pushButton_PlotBackgroundColor = new QPushButton(groupBox_colorOptions);
        pushButton_PlotBackgroundColor->setObjectName(QString::fromUtf8("pushButton_PlotBackgroundColor"));

        horizontalLayout_19->addWidget(pushButton_PlotBackgroundColor);

        label_plotBackgroundColor = new QLabel(groupBox_colorOptions);
        label_plotBackgroundColor->setObjectName(QString::fromUtf8("label_plotBackgroundColor"));
        label_plotBackgroundColor->setFrameShape(QFrame::Panel);

        horizontalLayout_19->addWidget(label_plotBackgroundColor);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_8);


        verticalLayout->addWidget(groupBox_colorOptions);


        verticalLayout_3->addWidget(groupBox_plotHistogram);

        groupBox_imageStack = new QGroupBox(centralWidget);
        groupBox_imageStack->setObjectName(QString::fromUtf8("groupBox_imageStack"));
        verticalLayout_6 = new QVBoxLayout(groupBox_imageStack);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        groupBox_enclose = new QGroupBox(groupBox_imageStack);
        groupBox_enclose->setObjectName(QString::fromUtf8("groupBox_enclose"));
        horizontalLayout_13 = new QHBoxLayout(groupBox_enclose);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        groupBox_imageSize = new QGroupBox(groupBox_enclose);
        groupBox_imageSize->setObjectName(QString::fromUtf8("groupBox_imageSize"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(1);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_imageSize->sizePolicy().hasHeightForWidth());
        groupBox_imageSize->setSizePolicy(sizePolicy2);
        horizontalLayout_12 = new QHBoxLayout(groupBox_imageSize);
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_imgHeight = new QLabel(groupBox_imageSize);
        label_imgHeight->setObjectName(QString::fromUtf8("label_imgHeight"));

        horizontalLayout_8->addWidget(label_imgHeight);

        spinBox_imgHeight = new QSpinBox(groupBox_imageSize);
        spinBox_imgHeight->setObjectName(QString::fromUtf8("spinBox_imgHeight"));
        spinBox_imgHeight->setMinimumSize(QSize(100, 0));
        spinBox_imgHeight->setLayoutDirection(Qt::LeftToRight);
        spinBox_imgHeight->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_imgHeight->setMinimum(1);
        spinBox_imgHeight->setMaximum(8196);
        spinBox_imgHeight->setValue(1024);

        horizontalLayout_8->addWidget(spinBox_imgHeight);


        verticalLayout_4->addLayout(horizontalLayout_8);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_imgWidth = new QLabel(groupBox_imageSize);
        label_imgWidth->setObjectName(QString::fromUtf8("label_imgWidth"));

        horizontalLayout_6->addWidget(label_imgWidth);

        spinBox_imgWidth = new QSpinBox(groupBox_imageSize);
        spinBox_imgWidth->setObjectName(QString::fromUtf8("spinBox_imgWidth"));
        spinBox_imgWidth->setMinimumSize(QSize(100, 0));
        spinBox_imgWidth->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_imgWidth->setMinimum(1);
        spinBox_imgWidth->setMaximum(8196);
        spinBox_imgWidth->setValue(1024);

        horizontalLayout_6->addWidget(spinBox_imgWidth);


        verticalLayout_4->addLayout(horizontalLayout_6);


        horizontalLayout_9->addLayout(verticalLayout_4);


        horizontalLayout_12->addLayout(horizontalLayout_9);


        horizontalLayout_13->addWidget(groupBox_imageSize);

        groupBox_directories = new QGroupBox(groupBox_enclose);
        groupBox_directories->setObjectName(QString::fromUtf8("groupBox_directories"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(4);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox_directories->sizePolicy().hasHeightForWidth());
        groupBox_directories->setSizePolicy(sizePolicy3);
        horizontalLayout_14 = new QHBoxLayout(groupBox_directories);
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pushButton_selectImageStack = new QPushButton(groupBox_directories);
        pushButton_selectImageStack->setObjectName(QString::fromUtf8("pushButton_selectImageStack"));
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(pushButton_selectImageStack->sizePolicy().hasHeightForWidth());
        pushButton_selectImageStack->setSizePolicy(sizePolicy4);
        pushButton_selectImageStack->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_5->addWidget(pushButton_selectImageStack);

        lineEdit_sourceDir = new QLineEdit(groupBox_directories);
        lineEdit_sourceDir->setObjectName(QString::fromUtf8("lineEdit_sourceDir"));
        lineEdit_sourceDir->setEnabled(false);

        horizontalLayout_5->addWidget(lineEdit_sourceDir);


        verticalLayout_5->addLayout(horizontalLayout_5);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        pushButton_destinationDir = new QPushButton(groupBox_directories);
        pushButton_destinationDir->setObjectName(QString::fromUtf8("pushButton_destinationDir"));
        sizePolicy4.setHeightForWidth(pushButton_destinationDir->sizePolicy().hasHeightForWidth());
        pushButton_destinationDir->setSizePolicy(sizePolicy4);
        pushButton_destinationDir->setMinimumSize(QSize(120, 0));
        pushButton_destinationDir->setMaximumSize(QSize(200, 16777215));

        horizontalLayout_11->addWidget(pushButton_destinationDir);

        lineEdit_destinationDir = new QLineEdit(groupBox_directories);
        lineEdit_destinationDir->setObjectName(QString::fromUtf8("lineEdit_destinationDir"));
        lineEdit_destinationDir->setEnabled(false);

        horizontalLayout_11->addWidget(lineEdit_destinationDir);


        verticalLayout_5->addLayout(horizontalLayout_11);


        horizontalLayout_10->addLayout(verticalLayout_5);


        horizontalLayout_14->addLayout(horizontalLayout_10);


        horizontalLayout_13->addWidget(groupBox_directories);


        verticalLayout_6->addWidget(groupBox_enclose);

        groupBox = new QGroupBox(groupBox_imageStack);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setEnabled(false);
        verticalLayout_8 = new QVBoxLayout(groupBox);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        checkBox_calcMinMaxStack = new QCheckBox(groupBox);
        checkBox_calcMinMaxStack->setObjectName(QString::fromUtf8("checkBox_calcMinMaxStack"));
        checkBox_calcMinMaxStack->setChecked(true);

        horizontalLayout_15->addWidget(checkBox_calcMinMaxStack);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        doubleSpinBox_minGray = new QDoubleSpinBox(groupBox);
        doubleSpinBox_minGray->setObjectName(QString::fromUtf8("doubleSpinBox_minGray"));
        doubleSpinBox_minGray->setEnabled(false);
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(doubleSpinBox_minGray->sizePolicy().hasHeightForWidth());
        doubleSpinBox_minGray->setSizePolicy(sizePolicy5);
        doubleSpinBox_minGray->setDecimals(10);
        doubleSpinBox_minGray->setMinimum(-1000000000.000000000000000);
        doubleSpinBox_minGray->setMaximum(1000000000.000000000000000);

        verticalLayout_7->addWidget(doubleSpinBox_minGray);

        doubleSpinBox_maxGray = new QDoubleSpinBox(groupBox);
        doubleSpinBox_maxGray->setObjectName(QString::fromUtf8("doubleSpinBox_maxGray"));
        doubleSpinBox_maxGray->setEnabled(false);
        sizePolicy5.setHeightForWidth(doubleSpinBox_maxGray->sizePolicy().hasHeightForWidth());
        doubleSpinBox_maxGray->setSizePolicy(sizePolicy5);
        doubleSpinBox_maxGray->setDecimals(10);
        doubleSpinBox_maxGray->setMinimum(-1000000000.000000000000000);
        doubleSpinBox_maxGray->setMaximum(1000000000.000000000000000);

        verticalLayout_7->addWidget(doubleSpinBox_maxGray);


        horizontalLayout_15->addLayout(verticalLayout_7);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        pushButton_readFromLogFile = new QPushButton(groupBox);
        pushButton_readFromLogFile->setObjectName(QString::fromUtf8("pushButton_readFromLogFile"));
        pushButton_readFromLogFile->setEnabled(false);
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(1);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(pushButton_readFromLogFile->sizePolicy().hasHeightForWidth());
        pushButton_readFromLogFile->setSizePolicy(sizePolicy6);
        pushButton_readFromLogFile->setMinimumSize(QSize(115, 0));

        horizontalLayout_7->addWidget(pushButton_readFromLogFile);

        lineEdit_logFile = new QLineEdit(groupBox);
        lineEdit_logFile->setObjectName(QString::fromUtf8("lineEdit_logFile"));
        lineEdit_logFile->setEnabled(false);
        QSizePolicy sizePolicy7(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy7.setHorizontalStretch(2);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(lineEdit_logFile->sizePolicy().hasHeightForWidth());
        lineEdit_logFile->setSizePolicy(sizePolicy7);

        horizontalLayout_7->addWidget(lineEdit_logFile);


        horizontalLayout_15->addLayout(horizontalLayout_7);


        verticalLayout_8->addLayout(horizontalLayout_15);


        verticalLayout_6->addWidget(groupBox);

        horizontalLayout_readImageStack = new QHBoxLayout();
        horizontalLayout_readImageStack->setSpacing(6);
        horizontalLayout_readImageStack->setObjectName(QString::fromUtf8("horizontalLayout_readImageStack"));
        pushButton_readImageStack = new QPushButton(groupBox_imageStack);
        pushButton_readImageStack->setObjectName(QString::fromUtf8("pushButton_readImageStack"));
        pushButton_readImageStack->setEnabled(true);

        horizontalLayout_readImageStack->addWidget(pushButton_readImageStack);

        label_fileSuffix = new QLabel(groupBox_imageStack);
        label_fileSuffix->setObjectName(QString::fromUtf8("label_fileSuffix"));

        horizontalLayout_readImageStack->addWidget(label_fileSuffix);

        comboBox_fileSuffix = new QComboBox(groupBox_imageStack);
        comboBox_fileSuffix->addItem(QString());
        comboBox_fileSuffix->addItem(QString());
        comboBox_fileSuffix->addItem(QString());
        comboBox_fileSuffix->addItem(QString());
        comboBox_fileSuffix->setObjectName(QString::fromUtf8("comboBox_fileSuffix"));
        comboBox_fileSuffix->setEditable(true);

        horizontalLayout_readImageStack->addWidget(comboBox_fileSuffix);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_readImageStack->addItem(horizontalSpacer_9);

        progressBar_readImageStack = new QProgressBar(groupBox_imageStack);
        progressBar_readImageStack->setObjectName(QString::fromUtf8("progressBar_readImageStack"));
        progressBar_readImageStack->setMaximum(1000);
        progressBar_readImageStack->setValue(0);

        horizontalLayout_readImageStack->addWidget(progressBar_readImageStack);


        verticalLayout_6->addLayout(horizontalLayout_readImageStack);


        verticalLayout_3->addWidget(groupBox_imageStack);

        groupBox_convertImageStack = new QGroupBox(centralWidget);
        groupBox_convertImageStack->setObjectName(QString::fromUtf8("groupBox_convertImageStack"));
        verticalLayout_2 = new QVBoxLayout(groupBox_convertImageStack);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        line_seperator = new QFrame(groupBox_convertImageStack);
        line_seperator->setObjectName(QString::fromUtf8("line_seperator"));
        line_seperator->setFrameShape(QFrame::HLine);
        line_seperator->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_seperator);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        pushButton_Real32Byte = new QPushButton(groupBox_convertImageStack);
        pushButton_Real32Byte->setObjectName(QString::fromUtf8("pushButton_Real32Byte"));
        pushButton_Real32Byte->setEnabled(false);

        horizontalLayout_4->addWidget(pushButton_Real32Byte);

        horizontalSpacer_3 = new QSpacerItem(10, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_3);

        pushButton_Real32Uint16 = new QPushButton(groupBox_convertImageStack);
        pushButton_Real32Uint16->setObjectName(QString::fromUtf8("pushButton_Real32Uint16"));
        pushButton_Real32Uint16->setEnabled(false);

        horizontalLayout_4->addWidget(pushButton_Real32Uint16);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);

        progressBar_convertImageStack = new QProgressBar(groupBox_convertImageStack);
        progressBar_convertImageStack->setObjectName(QString::fromUtf8("progressBar_convertImageStack"));
        progressBar_convertImageStack->setValue(0);

        horizontalLayout_4->addWidget(progressBar_convertImageStack);


        verticalLayout_2->addLayout(horizontalLayout_4);


        verticalLayout_3->addWidget(groupBox_convertImageStack);

        HistogramRemapClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(HistogramRemapClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 792, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuInfo = new QMenu(menuBar);
        menuInfo->setObjectName(QString::fromUtf8("menuInfo"));
        HistogramRemapClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(HistogramRemapClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        HistogramRemapClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuInfo->menuAction());
        menuFile->addAction(actionClose);
        menuInfo->addAction(actionDec_2018_Version_0_9);

        retranslateUi(HistogramRemapClass);
        QObject::connect(actionClose, SIGNAL(triggered()), HistogramRemapClass, SLOT(close()));
        QObject::connect(doubleSpinBox_minGray, SIGNAL(valueChanged(double)), doubleSpinBox_leftBound, SLOT(setValue(double)));
        QObject::connect(doubleSpinBox_maxGray, SIGNAL(valueChanged(double)), doubleSpinBox_rightBound, SLOT(setValue(double)));

        QMetaObject::connectSlotsByName(HistogramRemapClass);
    } // setupUi

    void retranslateUi(QMainWindow *HistogramRemapClass)
    {
        HistogramRemapClass->setWindowTitle(QCoreApplication::translate("HistogramRemapClass", "HistogramRemap", nullptr));
        actionClose->setText(QCoreApplication::translate("HistogramRemapClass", "Close", nullptr));
        actionDec_2018_Version_0_9->setText(QCoreApplication::translate("HistogramRemapClass", "December 2018 Version 0.9 Win10", nullptr));
        groupBox_plotHistogram->setTitle(QCoreApplication::translate("HistogramRemapClass", "Histogram", nullptr));
        groupBox_histogramOptions->setTitle(QCoreApplication::translate("HistogramRemapClass", "Histogram Options", nullptr));
        groupBox_scaling->setTitle(QCoreApplication::translate("HistogramRemapClass", "Scaling", nullptr));
        checkBox_yLog10->setText(QCoreApplication::translate("HistogramRemapClass", "y Log10", nullptr));
        pushButton_rePlot->setText(QCoreApplication::translate("HistogramRemapClass", "Replot", nullptr));
        groupBox_histogramBoundaries->setTitle(QCoreApplication::translate("HistogramRemapClass", "Histogram Boundaries", nullptr));
        label_leftBound->setText(QCoreApplication::translate("HistogramRemapClass", "Left Histogram Limit", nullptr));
        label_rightBound->setText(QCoreApplication::translate("HistogramRemapClass", "Right Histogram Limit", nullptr));
        groupBox_colorOptions->setTitle(QCoreApplication::translate("HistogramRemapClass", "Color Options", nullptr));
        pushButton_selectColor->setText(QCoreApplication::translate("HistogramRemapClass", "Historam Color", nullptr));
        label_histogramColor->setText(QCoreApplication::translate("HistogramRemapClass", "color", nullptr));
        pushButton_PlotBackgroundColor->setText(QCoreApplication::translate("HistogramRemapClass", "Plot Background Color", nullptr));
        label_plotBackgroundColor->setText(QCoreApplication::translate("HistogramRemapClass", "color", nullptr));
        groupBox_imageStack->setTitle(QCoreApplication::translate("HistogramRemapClass", "Image Stack", nullptr));
        groupBox_enclose->setTitle(QString());
        groupBox_imageSize->setTitle(QCoreApplication::translate("HistogramRemapClass", "Image Size", nullptr));
        label_imgHeight->setText(QCoreApplication::translate("HistogramRemapClass", "Height:", nullptr));
        label_imgWidth->setText(QCoreApplication::translate("HistogramRemapClass", "Width:", nullptr));
        groupBox_directories->setTitle(QCoreApplication::translate("HistogramRemapClass", "Directories", nullptr));
        pushButton_selectImageStack->setText(QCoreApplication::translate("HistogramRemapClass", "Image Stack Directory", nullptr));
        pushButton_destinationDir->setText(QCoreApplication::translate("HistogramRemapClass", "Destination Directory", nullptr));
        groupBox->setTitle(QCoreApplication::translate("HistogramRemapClass", "Minimal/Maximal Gray Values", nullptr));
#if QT_CONFIG(tooltip)
        checkBox_calcMinMaxStack->setToolTip(QCoreApplication::translate("HistogramRemapClass", "<html><head/><body><p>to detemine Min/Max Gray Value whole stack have to be read.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        checkBox_calcMinMaxStack->setText(QCoreApplication::translate("HistogramRemapClass", "Automatic calculation of min/max", nullptr));
#if QT_CONFIG(tooltip)
        doubleSpinBox_minGray->setToolTip(QCoreApplication::translate("HistogramRemapClass", "minimum gray value", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(tooltip)
        doubleSpinBox_maxGray->setToolTip(QCoreApplication::translate("HistogramRemapClass", "maximum gray value", nullptr));
#endif // QT_CONFIG(tooltip)
        pushButton_readFromLogFile->setText(QCoreApplication::translate("HistogramRemapClass", "Read from Log File ...", nullptr));
        pushButton_readImageStack->setText(QCoreApplication::translate("HistogramRemapClass", "Read Image Stack", nullptr));
        label_fileSuffix->setText(QCoreApplication::translate("HistogramRemapClass", "File Suffix:", nullptr));
        comboBox_fileSuffix->setItemText(0, QCoreApplication::translate("HistogramRemapClass", "*.raw", nullptr));
        comboBox_fileSuffix->setItemText(1, QCoreApplication::translate("HistogramRemapClass", "*.sin", nullptr));
        comboBox_fileSuffix->setItemText(2, QCoreApplication::translate("HistogramRemapClass", "*.sinF32", nullptr));
        comboBox_fileSuffix->setItemText(3, QCoreApplication::translate("HistogramRemapClass", "*.*", nullptr));

        progressBar_readImageStack->setFormat(QCoreApplication::translate("HistogramRemapClass", "%p%", nullptr));
        groupBox_convertImageStack->setTitle(QCoreApplication::translate("HistogramRemapClass", "Convert Image Stack", nullptr));
        pushButton_Real32Byte->setText(QCoreApplication::translate("HistogramRemapClass", "Real32 -> Byte", nullptr));
        pushButton_Real32Uint16->setText(QCoreApplication::translate("HistogramRemapClass", "Real32 -> Uint16", nullptr));
        menuFile->setTitle(QCoreApplication::translate("HistogramRemapClass", "File", nullptr));
        menuInfo->setTitle(QCoreApplication::translate("HistogramRemapClass", "Info", nullptr));
    } // retranslateUi

};

namespace Ui {
    class HistogramRemapClass: public Ui_HistogramRemapClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HISTOGRAMREMAP_H
