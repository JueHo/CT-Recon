/********************************************************************************
** Form generated from reading UI file 'LorentzFilter.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LORENTZFILTER_H
#define UI_LORENTZFILTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QSlider *verticalSlider_profile;
    QSpinBox *spinBox_profile;
    QVBoxLayout *verticalLayout_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_2;
    QLabel *label_OrigImageLeft;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QComboBox *comboBox_ZoomLeftImage;
    QSpacerItem *horizontalSpacer_5;
    QVBoxLayout *verticalLayout;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_2;
    QGridLayout *gridLayout_3;
    QLabel *label_FilteredImageRight;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QComboBox *comboBox_ZoomRightImage;
    QSpacerItem *horizontalSpacer_2;
    QFrame *line_2;
    QVBoxLayout *verticalLayout_4;
    QwtPlot *qwtPlot_CrossSection;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_7;
    QLineEdit *lineEdit_OpenProjectionFile;
    QPushButton *pushButton_OpenProjection;
    QSpacerItem *horizontalSpacer_7;
    QGroupBox *groupBox_alphaComponents;
    QHBoxLayout *horizontalLayout_8;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *pushButton_alphaEstimator;
    QFrame *line;
    QGroupBox *groupBox_2;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label;
    QDoubleSpinBox *doubleSpinBox_alphaProp;
    QLabel *label_2;
    QDoubleSpinBox *doubleSpinBox_alphaStepSize;
    QPushButton *pushButton_processAlphaStepwise;
    QHBoxLayout *horizontalLayout_17;
    QSpacerItem *horizontalSpacer_12;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_7;
    QLabel *label_AlphaReturn;
    QGroupBox *groupBox_WindowsZoomSelection;
    QVBoxLayout *verticalLayout_8;
    QHBoxLayout *horizontalLayout_14;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_5;
    QDoubleSpinBox *doubleSpinBox_Px;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBox_Py;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_Width;
    QHBoxLayout *horizontalLayout_13;
    QLabel *label_4;
    QDoubleSpinBox *doubleSpinBox_Height;
    QHBoxLayout *horizontalLayout_15;
    QSpacerItem *horizontalSpacer_10;
    QPushButton *pushButton_setSelection;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton_Reset;
    QSpacerItem *horizontalSpacer_11;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout;
    QPushButton *cancelButton;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *okButton;
    QSpacerItem *horizontalSpacer_9;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(1400, 1207);
        verticalLayout_5 = new QVBoxLayout(Dialog);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSlider_profile = new QSlider(Dialog);
        verticalSlider_profile->setObjectName(QString::fromUtf8("verticalSlider_profile"));
        verticalSlider_profile->setMaximum(10000);
        verticalSlider_profile->setOrientation(Qt::Vertical);
        verticalSlider_profile->setInvertedAppearance(true);
        verticalSlider_profile->setInvertedControls(false);
        verticalSlider_profile->setTickPosition(QSlider::TicksBelow);
        verticalSlider_profile->setTickInterval(100);

        verticalLayout_3->addWidget(verticalSlider_profile);

        spinBox_profile = new QSpinBox(Dialog);
        spinBox_profile->setObjectName(QString::fromUtf8("spinBox_profile"));
        spinBox_profile->setMaximum(10000);

        verticalLayout_3->addWidget(spinBox_profile);


        horizontalLayout_5->addLayout(verticalLayout_3);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        scrollArea = new QScrollArea(Dialog);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 652, 498));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_OrigImageLeft = new QLabel(scrollAreaWidgetContents);
        label_OrigImageLeft->setObjectName(QString::fromUtf8("label_OrigImageLeft"));
        label_OrigImageLeft->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_OrigImageLeft, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout_2->addWidget(scrollArea);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        comboBox_ZoomLeftImage = new QComboBox(Dialog);
        comboBox_ZoomLeftImage->addItem(QString());
        comboBox_ZoomLeftImage->addItem(QString());
        comboBox_ZoomLeftImage->addItem(QString());
        comboBox_ZoomLeftImage->addItem(QString());
        comboBox_ZoomLeftImage->addItem(QString());
        comboBox_ZoomLeftImage->setObjectName(QString::fromUtf8("comboBox_ZoomLeftImage"));

        horizontalLayout_4->addWidget(comboBox_ZoomLeftImage);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_5);


        verticalLayout_2->addLayout(horizontalLayout_4);


        horizontalLayout_5->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        scrollArea_2 = new QScrollArea(Dialog);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_2 = new QWidget();
        scrollAreaWidgetContents_2->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_2"));
        scrollAreaWidgetContents_2->setGeometry(QRect(0, 0, 651, 498));
        gridLayout_3 = new QGridLayout(scrollAreaWidgetContents_2);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_FilteredImageRight = new QLabel(scrollAreaWidgetContents_2);
        label_FilteredImageRight->setObjectName(QString::fromUtf8("label_FilteredImageRight"));
        label_FilteredImageRight->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_FilteredImageRight, 0, 0, 1, 1);

        scrollArea_2->setWidget(scrollAreaWidgetContents_2);

        verticalLayout->addWidget(scrollArea_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        comboBox_ZoomRightImage = new QComboBox(Dialog);
        comboBox_ZoomRightImage->addItem(QString());
        comboBox_ZoomRightImage->addItem(QString());
        comboBox_ZoomRightImage->addItem(QString());
        comboBox_ZoomRightImage->addItem(QString());
        comboBox_ZoomRightImage->addItem(QString());
        comboBox_ZoomRightImage->setObjectName(QString::fromUtf8("comboBox_ZoomRightImage"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(comboBox_ZoomRightImage->sizePolicy().hasHeightForWidth());
        comboBox_ZoomRightImage->setSizePolicy(sizePolicy);
        comboBox_ZoomRightImage->setMinimumSize(QSize(84, 0));

        horizontalLayout_3->addWidget(comboBox_ZoomRightImage);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);


        verticalLayout->addLayout(horizontalLayout_3);


        horizontalLayout_5->addLayout(verticalLayout);


        verticalLayout_5->addLayout(horizontalLayout_5);

        line_2 = new QFrame(Dialog);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_5->addWidget(line_2);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        qwtPlot_CrossSection = new QwtPlot(Dialog);
        qwtPlot_CrossSection->setObjectName(QString::fromUtf8("qwtPlot_CrossSection"));

        verticalLayout_4->addWidget(qwtPlot_CrossSection);

        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_7 = new QHBoxLayout(groupBox);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        lineEdit_OpenProjectionFile = new QLineEdit(groupBox);
        lineEdit_OpenProjectionFile->setObjectName(QString::fromUtf8("lineEdit_OpenProjectionFile"));
        lineEdit_OpenProjectionFile->setEnabled(true);

        horizontalLayout_7->addWidget(lineEdit_OpenProjectionFile);

        pushButton_OpenProjection = new QPushButton(groupBox);
        pushButton_OpenProjection->setObjectName(QString::fromUtf8("pushButton_OpenProjection"));

        horizontalLayout_7->addWidget(pushButton_OpenProjection);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_7);

        groupBox_alphaComponents = new QGroupBox(groupBox);
        groupBox_alphaComponents->setObjectName(QString::fromUtf8("groupBox_alphaComponents"));
        groupBox_alphaComponents->setEnabled(false);
        horizontalLayout_8 = new QHBoxLayout(groupBox_alphaComponents);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        groupBox_3 = new QGroupBox(groupBox_alphaComponents);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        horizontalLayout_9 = new QHBoxLayout(groupBox_3);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        pushButton_alphaEstimator = new QPushButton(groupBox_3);
        pushButton_alphaEstimator->setObjectName(QString::fromUtf8("pushButton_alphaEstimator"));

        horizontalLayout_9->addWidget(pushButton_alphaEstimator);


        horizontalLayout_8->addWidget(groupBox_3);

        line = new QFrame(groupBox_alphaComponents);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_8->addWidget(line);

        groupBox_2 = new QGroupBox(groupBox_alphaComponents);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        verticalLayout_9 = new QVBoxLayout(groupBox_2);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_6->addWidget(label);

        doubleSpinBox_alphaProp = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox_alphaProp->setObjectName(QString::fromUtf8("doubleSpinBox_alphaProp"));
        doubleSpinBox_alphaProp->setDecimals(3);
        doubleSpinBox_alphaProp->setMinimum(-1.000000000000000);
        doubleSpinBox_alphaProp->setMaximum(1000.000000000000000);
        doubleSpinBox_alphaProp->setSingleStep(0.100000000000000);
        doubleSpinBox_alphaProp->setValue(0.000000000000000);

        horizontalLayout_6->addWidget(doubleSpinBox_alphaProp);

        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_6->addWidget(label_2);

        doubleSpinBox_alphaStepSize = new QDoubleSpinBox(groupBox_2);
        doubleSpinBox_alphaStepSize->setObjectName(QString::fromUtf8("doubleSpinBox_alphaStepSize"));
        doubleSpinBox_alphaStepSize->setDecimals(3);
        doubleSpinBox_alphaStepSize->setSingleStep(0.010000000000000);
        doubleSpinBox_alphaStepSize->setValue(0.100000000000000);

        horizontalLayout_6->addWidget(doubleSpinBox_alphaStepSize);

        pushButton_processAlphaStepwise = new QPushButton(groupBox_2);
        pushButton_processAlphaStepwise->setObjectName(QString::fromUtf8("pushButton_processAlphaStepwise"));

        horizontalLayout_6->addWidget(pushButton_processAlphaStepwise);


        verticalLayout_9->addLayout(horizontalLayout_6);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_12);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_7 = new QLabel(groupBox_2);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_16->addWidget(label_7);

        label_AlphaReturn = new QLabel(groupBox_2);
        label_AlphaReturn->setObjectName(QString::fromUtf8("label_AlphaReturn"));
        label_AlphaReturn->setMinimumSize(QSize(50, 0));
        label_AlphaReturn->setStyleSheet(QString::fromUtf8("background-color: rgb(170, 255, 0);"));
        label_AlphaReturn->setFrameShape(QFrame::Panel);
        label_AlphaReturn->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_16->addWidget(label_AlphaReturn);


        horizontalLayout_17->addLayout(horizontalLayout_16);


        verticalLayout_9->addLayout(horizontalLayout_17);


        horizontalLayout_8->addWidget(groupBox_2);


        horizontalLayout_7->addWidget(groupBox_alphaComponents);

        groupBox_WindowsZoomSelection = new QGroupBox(groupBox);
        groupBox_WindowsZoomSelection->setObjectName(QString::fromUtf8("groupBox_WindowsZoomSelection"));
        groupBox_WindowsZoomSelection->setEnabled(false);
        verticalLayout_8 = new QVBoxLayout(groupBox_WindowsZoomSelection);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        groupBox_5 = new QGroupBox(groupBox_WindowsZoomSelection);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy1);
        groupBox_5->setMinimumSize(QSize(0, 0));
        verticalLayout_7 = new QVBoxLayout(groupBox_5);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_5 = new QLabel(groupBox_5);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy2);

        horizontalLayout_10->addWidget(label_5);

        doubleSpinBox_Px = new QDoubleSpinBox(groupBox_5);
        doubleSpinBox_Px->setObjectName(QString::fromUtf8("doubleSpinBox_Px"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(doubleSpinBox_Px->sizePolicy().hasHeightForWidth());
        doubleSpinBox_Px->setSizePolicy(sizePolicy3);
        doubleSpinBox_Px->setMinimumSize(QSize(60, 0));
        doubleSpinBox_Px->setMaximumSize(QSize(60, 16777215));
        doubleSpinBox_Px->setDecimals(4);
        doubleSpinBox_Px->setMaximum(4000.000000000000000);
        doubleSpinBox_Px->setSingleStep(5.000000000000000);

        horizontalLayout_10->addWidget(doubleSpinBox_Px);


        verticalLayout_7->addLayout(horizontalLayout_10);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_6 = new QLabel(groupBox_5);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_11->addWidget(label_6);

        doubleSpinBox_Py = new QDoubleSpinBox(groupBox_5);
        doubleSpinBox_Py->setObjectName(QString::fromUtf8("doubleSpinBox_Py"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(doubleSpinBox_Py->sizePolicy().hasHeightForWidth());
        doubleSpinBox_Py->setSizePolicy(sizePolicy4);
        doubleSpinBox_Py->setMinimumSize(QSize(60, 0));
        doubleSpinBox_Py->setMaximumSize(QSize(60, 16777215));
        doubleSpinBox_Py->setDecimals(4);
        doubleSpinBox_Py->setMaximum(10000.000000000000000);
        doubleSpinBox_Py->setSingleStep(0.010000000000000);

        horizontalLayout_11->addWidget(doubleSpinBox_Py);


        verticalLayout_7->addLayout(horizontalLayout_11);


        horizontalLayout_14->addWidget(groupBox_5);

        groupBox_6 = new QGroupBox(groupBox_WindowsZoomSelection);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        verticalLayout_6 = new QVBoxLayout(groupBox_6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_3 = new QLabel(groupBox_6);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_12->addWidget(label_3);

        doubleSpinBox_Width = new QDoubleSpinBox(groupBox_6);
        doubleSpinBox_Width->setObjectName(QString::fromUtf8("doubleSpinBox_Width"));
        sizePolicy4.setHeightForWidth(doubleSpinBox_Width->sizePolicy().hasHeightForWidth());
        doubleSpinBox_Width->setSizePolicy(sizePolicy4);
        doubleSpinBox_Width->setMinimumSize(QSize(60, 0));
        doubleSpinBox_Width->setMaximumSize(QSize(60, 16777215));
        doubleSpinBox_Width->setDecimals(4);
        doubleSpinBox_Width->setMaximum(4000.000000000000000);
        doubleSpinBox_Width->setSingleStep(5.000000000000000);

        horizontalLayout_12->addWidget(doubleSpinBox_Width);


        verticalLayout_6->addLayout(horizontalLayout_12);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        label_4 = new QLabel(groupBox_6);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        sizePolicy2.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy2);
        label_4->setMinimumSize(QSize(35, 0));

        horizontalLayout_13->addWidget(label_4);

        doubleSpinBox_Height = new QDoubleSpinBox(groupBox_6);
        doubleSpinBox_Height->setObjectName(QString::fromUtf8("doubleSpinBox_Height"));
        sizePolicy.setHeightForWidth(doubleSpinBox_Height->sizePolicy().hasHeightForWidth());
        doubleSpinBox_Height->setSizePolicy(sizePolicy);
        doubleSpinBox_Height->setMaximumSize(QSize(60, 16777215));
        doubleSpinBox_Height->setDecimals(4);
        doubleSpinBox_Height->setMaximum(10000.000000000000000);
        doubleSpinBox_Height->setSingleStep(0.010000000000000);

        horizontalLayout_13->addWidget(doubleSpinBox_Height);


        verticalLayout_6->addLayout(horizontalLayout_13);


        horizontalLayout_14->addWidget(groupBox_6);


        verticalLayout_8->addLayout(horizontalLayout_14);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_10);

        pushButton_setSelection = new QPushButton(groupBox_WindowsZoomSelection);
        pushButton_setSelection->setObjectName(QString::fromUtf8("pushButton_setSelection"));

        horizontalLayout_15->addWidget(pushButton_setSelection);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_8);

        pushButton_Reset = new QPushButton(groupBox_WindowsZoomSelection);
        pushButton_Reset->setObjectName(QString::fromUtf8("pushButton_Reset"));

        horizontalLayout_15->addWidget(pushButton_Reset);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_11);


        verticalLayout_8->addLayout(horizontalLayout_15);


        horizontalLayout_7->addWidget(groupBox_WindowsZoomSelection);


        verticalLayout_4->addWidget(groupBox);


        verticalLayout_5->addLayout(verticalLayout_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        cancelButton = new QPushButton(Dialog);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        horizontalLayout->addWidget(cancelButton);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        okButton = new QPushButton(Dialog);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        horizontalLayout->addWidget(okButton);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_9);


        horizontalLayout_2->addLayout(horizontalLayout);


        verticalLayout_5->addLayout(horizontalLayout_2);


        retranslateUi(Dialog);
        QObject::connect(okButton, SIGNAL(clicked()), Dialog, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), Dialog, SLOT(reject()));
        QObject::connect(verticalSlider_profile, SIGNAL(valueChanged(int)), spinBox_profile, SLOT(setValue(int)));
        QObject::connect(spinBox_profile, SIGNAL(valueChanged(int)), verticalSlider_profile, SLOT(setValue(int)));

        comboBox_ZoomLeftImage->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Dialog", nullptr));
        label_OrigImageLeft->setText(QCoreApplication::translate("Dialog", "Placeholder Image Original", nullptr));
        comboBox_ZoomLeftImage->setItemText(0, QCoreApplication::translate("Dialog", "Zoom  25 %", nullptr));
        comboBox_ZoomLeftImage->setItemText(1, QCoreApplication::translate("Dialog", "Zoom  50%", nullptr));
        comboBox_ZoomLeftImage->setItemText(2, QCoreApplication::translate("Dialog", "Zoom  75%", nullptr));
        comboBox_ZoomLeftImage->setItemText(3, QCoreApplication::translate("Dialog", "Zoom 100%", nullptr));
        comboBox_ZoomLeftImage->setItemText(4, QCoreApplication::translate("Dialog", "Zoom 200%", nullptr));

        label_FilteredImageRight->setText(QCoreApplication::translate("Dialog", "Placeholder Image Filtered", nullptr));
        comboBox_ZoomRightImage->setItemText(0, QCoreApplication::translate("Dialog", "Zoom  25 %", nullptr));
        comboBox_ZoomRightImage->setItemText(1, QCoreApplication::translate("Dialog", "Zoom  50 %", nullptr));
        comboBox_ZoomRightImage->setItemText(2, QCoreApplication::translate("Dialog", "Zoom  75 %", nullptr));
        comboBox_ZoomRightImage->setItemText(3, QCoreApplication::translate("Dialog", "Zoom  100 %", nullptr));
        comboBox_ZoomRightImage->setItemText(4, QCoreApplication::translate("Dialog", "Zoom  200 %", nullptr));

        groupBox->setTitle(QCoreApplication::translate("Dialog", "Lorentz Filter Parameter Settings", nullptr));
        pushButton_OpenProjection->setText(QCoreApplication::translate("Dialog", "Open Projection ..", nullptr));
        groupBox_alphaComponents->setTitle(QCoreApplication::translate("Dialog", "Lorentz Filter", nullptr));
        groupBox_3->setTitle(QCoreApplication::translate("Dialog", "Try to find Lorentz Filter Alpha Parameter", nullptr));
        pushButton_alphaEstimator->setText(QCoreApplication::translate("Dialog", "Semi Automatic Alpha Estimation ...", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("Dialog", "Manuell Lorentz Filter processing", nullptr));
        label->setText(QCoreApplication::translate("Dialog", " Current Alpha:", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog", "Alpha Step Size:", nullptr));
        pushButton_processAlphaStepwise->setText(QCoreApplication::translate("Dialog", " Iter Alpha Filter Values", nullptr));
        label_7->setText(QCoreApplication::translate("Dialog", "Alpha Return", nullptr));
        label_AlphaReturn->setText(QCoreApplication::translate("Dialog", "0.0", nullptr));
        groupBox_WindowsZoomSelection->setTitle(QCoreApplication::translate("Dialog", "Window Zoom Selection", nullptr));
        groupBox_5->setTitle(QString());
        label_5->setText(QCoreApplication::translate("Dialog", "  Px min:    ", nullptr));
        label_6->setText(QCoreApplication::translate("Dialog", "  Py min:   ", nullptr));
        groupBox_6->setTitle(QString());
        label_3->setText(QCoreApplication::translate("Dialog", "  Width:  ", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog", "  Height:     ", nullptr));
        pushButton_setSelection->setText(QCoreApplication::translate("Dialog", "Set ", nullptr));
        pushButton_Reset->setText(QCoreApplication::translate("Dialog", "Reset", nullptr));
        cancelButton->setText(QCoreApplication::translate("Dialog", "Cancel", nullptr));
        okButton->setText(QCoreApplication::translate("Dialog", "Take Alpha", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LORENTZFILTER_H
