/********************************************************************************
** Form generated from reading UI file 'autorotcenterestimation.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOROTCENTERESTIMATION_H
#define UI_AUTOROTCENTERESTIMATION_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AutoRotCenterEstimationClass
{
public:
    QWidget *centralWidget;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_Parameters;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_Parameters_Sub;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_ParameterFile;
    QLineEdit *lineEdit_PFDK_File;
    QPushButton *pushButton_LoadPFDK;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_3;
    QLabel *label_SliceNumber;
    QSpinBox *spinBox_SliceNumber;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_StepWidth;
    QDoubleSpinBox *doubleSpinBox_StepWidth;
    QGroupBox *groupBox_PixelShift_IntervalLimits;
    QHBoxLayout *horizontalLayout_3;
    QHBoxLayout *horizontalLayout_2;
    QHBoxLayout *horizontalLayout;
    QLabel *label_LBound;
    QDoubleSpinBox *doubleSpinBox_LBound;
    QSpacerItem *horizontalSpacer;
    QLabel *label_RBound;
    QDoubleSpinBox *doubleSpinBox_RBound;
    QGroupBox *groupBox;
    QGridLayout *gridLayout;
    QSpinBox *spinBox_supportPointSize;
    QCheckBox *checkBox_tilted;
    QLabel *label_5;
    QLabel *label_4;
    QSpinBox *spinBox_multiRowStepSize;
    QLabel *label_endSlice;
    QSpinBox *spinBox_startSlice;
    QLabel *label_2;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_3;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_8;
    QLabel *label_6;
    QLabel *label_7;
    QGroupBox *groupBox_Start_Close;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *pushButton_Start;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *pushButton_Close;
    QHBoxLayout *horizontalLayout_8;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label;
    QMenuBar *menuBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *AutoRotCenterEstimationClass)
    {
        if (AutoRotCenterEstimationClass->objectName().isEmpty())
            AutoRotCenterEstimationClass->setObjectName(QString::fromUtf8("AutoRotCenterEstimationClass"));
        AutoRotCenterEstimationClass->resize(573, 489);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(AutoRotCenterEstimationClass->sizePolicy().hasHeightForWidth());
        AutoRotCenterEstimationClass->setSizePolicy(sizePolicy);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/AutoRotCenterEstimation/Icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        AutoRotCenterEstimationClass->setWindowIcon(icon);
        centralWidget = new QWidget(AutoRotCenterEstimationClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        sizePolicy.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(centralWidget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_Parameters = new QGroupBox(centralWidget);
        groupBox_Parameters->setObjectName(QString::fromUtf8("groupBox_Parameters"));
        verticalLayout_2 = new QVBoxLayout(groupBox_Parameters);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_Parameters_Sub = new QGroupBox(groupBox_Parameters);
        groupBox_Parameters_Sub->setObjectName(QString::fromUtf8("groupBox_Parameters_Sub"));
        sizePolicy.setHeightForWidth(groupBox_Parameters_Sub->sizePolicy().hasHeightForWidth());
        groupBox_Parameters_Sub->setSizePolicy(sizePolicy);
        verticalLayout_3 = new QVBoxLayout(groupBox_Parameters_Sub);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_ParameterFile = new QLabel(groupBox_Parameters_Sub);
        label_ParameterFile->setObjectName(QString::fromUtf8("label_ParameterFile"));

        horizontalLayout_4->addWidget(label_ParameterFile);

        lineEdit_PFDK_File = new QLineEdit(groupBox_Parameters_Sub);
        lineEdit_PFDK_File->setObjectName(QString::fromUtf8("lineEdit_PFDK_File"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(2);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(lineEdit_PFDK_File->sizePolicy().hasHeightForWidth());
        lineEdit_PFDK_File->setSizePolicy(sizePolicy1);

        horizontalLayout_4->addWidget(lineEdit_PFDK_File);

        pushButton_LoadPFDK = new QPushButton(groupBox_Parameters_Sub);
        pushButton_LoadPFDK->setObjectName(QString::fromUtf8("pushButton_LoadPFDK"));

        horizontalLayout_4->addWidget(pushButton_LoadPFDK);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_3);

        label_SliceNumber = new QLabel(groupBox_Parameters_Sub);
        label_SliceNumber->setObjectName(QString::fromUtf8("label_SliceNumber"));

        horizontalLayout_6->addWidget(label_SliceNumber);

        spinBox_SliceNumber = new QSpinBox(groupBox_Parameters_Sub);
        spinBox_SliceNumber->setObjectName(QString::fromUtf8("spinBox_SliceNumber"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(spinBox_SliceNumber->sizePolicy().hasHeightForWidth());
        spinBox_SliceNumber->setSizePolicy(sizePolicy2);
        spinBox_SliceNumber->setMinimumSize(QSize(70, 0));
        spinBox_SliceNumber->setMaximum(10000);
        spinBox_SliceNumber->setValue(512);

        horizontalLayout_6->addWidget(spinBox_SliceNumber);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_5);

        label_StepWidth = new QLabel(groupBox_Parameters_Sub);
        label_StepWidth->setObjectName(QString::fromUtf8("label_StepWidth"));

        horizontalLayout_7->addWidget(label_StepWidth);

        doubleSpinBox_StepWidth = new QDoubleSpinBox(groupBox_Parameters_Sub);
        doubleSpinBox_StepWidth->setObjectName(QString::fromUtf8("doubleSpinBox_StepWidth"));
        sizePolicy2.setHeightForWidth(doubleSpinBox_StepWidth->sizePolicy().hasHeightForWidth());
        doubleSpinBox_StepWidth->setSizePolicy(sizePolicy2);
        doubleSpinBox_StepWidth->setMinimumSize(QSize(70, 0));
        doubleSpinBox_StepWidth->setDecimals(3);
        doubleSpinBox_StepWidth->setMinimum(0.001000000000000);
        doubleSpinBox_StepWidth->setMaximum(10.000000000000000);
        doubleSpinBox_StepWidth->setSingleStep(0.100000000000000);
        doubleSpinBox_StepWidth->setValue(0.100000000000000);

        horizontalLayout_7->addWidget(doubleSpinBox_StepWidth);


        verticalLayout_3->addLayout(horizontalLayout_7);


        verticalLayout_2->addWidget(groupBox_Parameters_Sub);

        groupBox_PixelShift_IntervalLimits = new QGroupBox(groupBox_Parameters);
        groupBox_PixelShift_IntervalLimits->setObjectName(QString::fromUtf8("groupBox_PixelShift_IntervalLimits"));
        sizePolicy.setHeightForWidth(groupBox_PixelShift_IntervalLimits->sizePolicy().hasHeightForWidth());
        groupBox_PixelShift_IntervalLimits->setSizePolicy(sizePolicy);
        horizontalLayout_3 = new QHBoxLayout(groupBox_PixelShift_IntervalLimits);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_LBound = new QLabel(groupBox_PixelShift_IntervalLimits);
        label_LBound->setObjectName(QString::fromUtf8("label_LBound"));

        horizontalLayout->addWidget(label_LBound);

        doubleSpinBox_LBound = new QDoubleSpinBox(groupBox_PixelShift_IntervalLimits);
        doubleSpinBox_LBound->setObjectName(QString::fromUtf8("doubleSpinBox_LBound"));
        doubleSpinBox_LBound->setDecimals(3);
        doubleSpinBox_LBound->setMinimum(-200.000000000000000);
        doubleSpinBox_LBound->setMaximum(200.000000000000000);
        doubleSpinBox_LBound->setValue(-10.000000000000000);

        horizontalLayout->addWidget(doubleSpinBox_LBound);


        horizontalLayout_2->addLayout(horizontalLayout);

        horizontalSpacer = new QSpacerItem(52, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_RBound = new QLabel(groupBox_PixelShift_IntervalLimits);
        label_RBound->setObjectName(QString::fromUtf8("label_RBound"));

        horizontalLayout_2->addWidget(label_RBound);

        doubleSpinBox_RBound = new QDoubleSpinBox(groupBox_PixelShift_IntervalLimits);
        doubleSpinBox_RBound->setObjectName(QString::fromUtf8("doubleSpinBox_RBound"));
        doubleSpinBox_RBound->setMinimum(-200.000000000000000);
        doubleSpinBox_RBound->setMaximum(200.000000000000000);
        doubleSpinBox_RBound->setValue(10.000000000000000);

        horizontalLayout_2->addWidget(doubleSpinBox_RBound);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_2->addWidget(groupBox_PixelShift_IntervalLimits);


        verticalLayout->addWidget(groupBox_Parameters);

        groupBox = new QGroupBox(centralWidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout = new QGridLayout(groupBox);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        spinBox_supportPointSize = new QSpinBox(groupBox);
        spinBox_supportPointSize->setObjectName(QString::fromUtf8("spinBox_supportPointSize"));
        spinBox_supportPointSize->setEnabled(false);
        spinBox_supportPointSize->setMinimum(3);
        spinBox_supportPointSize->setMaximum(1000);

        gridLayout->addWidget(spinBox_supportPointSize, 3, 1, 1, 1);

        checkBox_tilted = new QCheckBox(groupBox);
        checkBox_tilted->setObjectName(QString::fromUtf8("checkBox_tilted"));

        gridLayout->addWidget(checkBox_tilted, 0, 0, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 4, 0, 1, 1);

        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 3, 0, 1, 1);

        spinBox_multiRowStepSize = new QSpinBox(groupBox);
        spinBox_multiRowStepSize->setObjectName(QString::fromUtf8("spinBox_multiRowStepSize"));
        spinBox_multiRowStepSize->setEnabled(false);
        spinBox_multiRowStepSize->setMaximum(10000);
        spinBox_multiRowStepSize->setSingleStep(10);
        spinBox_multiRowStepSize->setValue(100);

        gridLayout->addWidget(spinBox_multiRowStepSize, 1, 1, 1, 1);

        label_endSlice = new QLabel(groupBox);
        label_endSlice->setObjectName(QString::fromUtf8("label_endSlice"));
        label_endSlice->setFrameShape(QFrame::Box);

        gridLayout->addWidget(label_endSlice, 4, 1, 1, 1);

        spinBox_startSlice = new QSpinBox(groupBox);
        spinBox_startSlice->setObjectName(QString::fromUtf8("spinBox_startSlice"));
        spinBox_startSlice->setEnabled(false);
        spinBox_startSlice->setMaximum(10000);

        gridLayout->addWidget(spinBox_startSlice, 2, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout->addWidget(label_2, 1, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_6, 0, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout->addWidget(label_3, 2, 0, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_7, 1, 3, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_8, 1, 2, 1, 1);

        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout->addWidget(label_6, 2, 2, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout->addWidget(label_7, 4, 2, 1, 1);


        verticalLayout->addWidget(groupBox);

        groupBox_Start_Close = new QGroupBox(centralWidget);
        groupBox_Start_Close->setObjectName(QString::fromUtf8("groupBox_Start_Close"));
        sizePolicy.setHeightForWidth(groupBox_Start_Close->sizePolicy().hasHeightForWidth());
        groupBox_Start_Close->setSizePolicy(sizePolicy);
        horizontalLayout_5 = new QHBoxLayout(groupBox_Start_Close);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        pushButton_Start = new QPushButton(groupBox_Start_Close);
        pushButton_Start->setObjectName(QString::fromUtf8("pushButton_Start"));

        horizontalLayout_5->addWidget(pushButton_Start);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_2);

        pushButton_Close = new QPushButton(groupBox_Start_Close);
        pushButton_Close->setObjectName(QString::fromUtf8("pushButton_Close"));

        horizontalLayout_5->addWidget(pushButton_Close);


        verticalLayout->addWidget(groupBox_Start_Close);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_4);

        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy3);

        horizontalLayout_8->addWidget(label);


        verticalLayout->addLayout(horizontalLayout_8);

        AutoRotCenterEstimationClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(AutoRotCenterEstimationClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 573, 21));
        AutoRotCenterEstimationClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(AutoRotCenterEstimationClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        AutoRotCenterEstimationClass->setStatusBar(statusBar);

        retranslateUi(AutoRotCenterEstimationClass);

        QMetaObject::connectSlotsByName(AutoRotCenterEstimationClass);
    } // setupUi

    void retranslateUi(QMainWindow *AutoRotCenterEstimationClass)
    {
        AutoRotCenterEstimationClass->setWindowTitle(QCoreApplication::translate("AutoRotCenterEstimationClass", "AutoRotCenterEstimation", nullptr));
        groupBox_Parameters->setTitle(QCoreApplication::translate("AutoRotCenterEstimationClass", "Parameters", nullptr));
        groupBox_Parameters_Sub->setTitle(QString());
        label_ParameterFile->setText(QCoreApplication::translate("AutoRotCenterEstimationClass", "Specify Reconstruction Parameter File (*pfdk):", nullptr));
        pushButton_LoadPFDK->setText(QCoreApplication::translate("AutoRotCenterEstimationClass", "Load File ...", nullptr));
        label_SliceNumber->setText(QCoreApplication::translate("AutoRotCenterEstimationClass", "Slice number used for Reconstruction [count from top of projection image] :", nullptr));
#if QT_CONFIG(tooltip)
        spinBox_SliceNumber->setToolTip(QCoreApplication::translate("AutoRotCenterEstimationClass", "<html><head/><body><p>As standard take the midth slice of the projection image.</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        label_StepWidth->setText(QCoreApplication::translate("AutoRotCenterEstimationClass", "Iterate with Step Width [pixel(fraction)]:", nullptr));
        groupBox_PixelShift_IntervalLimits->setTitle(QCoreApplication::translate("AutoRotCenterEstimationClass", "Pixel Shift -  Interval Limits", nullptr));
        label_LBound->setText(QCoreApplication::translate("AutoRotCenterEstimationClass", "Left Interval Border:", nullptr));
        label_RBound->setText(QCoreApplication::translate("AutoRotCenterEstimationClass", "Right Interval Border:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("AutoRotCenterEstimationClass", "Tilted Axis Estimation", nullptr));
        checkBox_tilted->setText(QCoreApplication::translate("AutoRotCenterEstimationClass", "Calculate regression curve", nullptr));
        label_5->setText(QCoreApplication::translate("AutoRotCenterEstimationClass", "To Slice:", nullptr));
        label_4->setText(QCoreApplication::translate("AutoRotCenterEstimationClass", "Number of Supporting Points:", nullptr));
        label_endSlice->setText(QString());
        label_2->setText(QCoreApplication::translate("AutoRotCenterEstimationClass", "\316\224 Step :", nullptr));
        label_3->setText(QCoreApplication::translate("AutoRotCenterEstimationClass", "From Slice:", nullptr));
        label_6->setText(QCoreApplication::translate("AutoRotCenterEstimationClass", "(Check for valid value)", nullptr));
        label_7->setText(QCoreApplication::translate("AutoRotCenterEstimationClass", "(Check for valid value)", nullptr));
        groupBox_Start_Close->setTitle(QString());
        pushButton_Start->setText(QCoreApplication::translate("AutoRotCenterEstimationClass", " Start Rotation Determination", nullptr));
        pushButton_Close->setText(QCoreApplication::translate("AutoRotCenterEstimationClass", "Close Window", nullptr));
        label->setText(QCoreApplication::translate("AutoRotCenterEstimationClass", "<html><head/><body><p><span style=\" font-style:italic;\">June 2021 Version 2.1 Win10</span></p></body></html>", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AutoRotCenterEstimationClass: public Ui_AutoRotCenterEstimationClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOROTCENTERESTIMATION_H
