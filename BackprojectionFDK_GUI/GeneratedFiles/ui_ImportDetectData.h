/********************************************************************************
** Form generated from reading UI file 'ImportDetectData.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_IMPORTDETECTDATA_H
#define UI_IMPORTDETECTDATA_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QGridLayout *gridLayout;
    QLabel *label_4;
    QSpinBox *spinBox_imgWidth;
    QLabel *label_5;
    QSpinBox *spinBox_ImgHeight;
    QSpacerItem *horizontalSpacer_4;
    QGridLayout *gridLayout_2;
    QLabel *label_6;
    QDoubleSpinBox *doubleSpinBox_BHC;
    QLabel *label_7;
    QDoubleSpinBox *doubleSpinBox_FlatCorrFac;
    QSpacerItem *verticalSpacer_2;
    QFrame *line;
    QGridLayout *gridLayout_3;
    QLabel *label;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit_VolumeFile;
    QPushButton *btn_ImportFileSelect;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEdit_SinoOutDir;
    QPushButton *btn_SinoOutputDir;
    QLabel *label_3;
    QLineEdit *lineEdit__SinoBaseName;
    QFrame *line_2;
    QSpacerItem *verticalSpacer_3;
    QHBoxLayout *horizontalLayout_8;
    QPushButton *btn_ImportConvert;
    QProgressBar *progressBar;
    QSpacerItem *verticalSpacer_4;
    QFrame *line_3;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *hboxLayout;
    QSpacerItem *spacerItem;
    QPushButton *closeButton;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QString::fromUtf8("Dialog"));
        Dialog->resize(368, 338);
        verticalLayout = new QVBoxLayout(Dialog);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(Dialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        gridLayout->addWidget(label_4, 0, 0, 1, 1);

        spinBox_imgWidth = new QSpinBox(groupBox);
        spinBox_imgWidth->setObjectName(QString::fromUtf8("spinBox_imgWidth"));
        spinBox_imgWidth->setMinimum(1);
        spinBox_imgWidth->setMaximum(2184);
        spinBox_imgWidth->setValue(512);

        gridLayout->addWidget(spinBox_imgWidth, 0, 1, 1, 1);

        label_5 = new QLabel(groupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        gridLayout->addWidget(label_5, 1, 0, 1, 1);

        spinBox_ImgHeight = new QSpinBox(groupBox);
        spinBox_ImgHeight->setObjectName(QString::fromUtf8("spinBox_ImgHeight"));
        spinBox_ImgHeight->setMinimum(1);
        spinBox_ImgHeight->setMaximum(1472);
        spinBox_ImgHeight->setValue(512);

        gridLayout->addWidget(spinBox_ImgHeight, 1, 1, 1, 1);


        horizontalLayout_4->addLayout(gridLayout);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_6 = new QLabel(groupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        gridLayout_2->addWidget(label_6, 0, 0, 1, 1);

        doubleSpinBox_BHC = new QDoubleSpinBox(groupBox);
        doubleSpinBox_BHC->setObjectName(QString::fromUtf8("doubleSpinBox_BHC"));
        doubleSpinBox_BHC->setMinimum(1.000000000000000);
        doubleSpinBox_BHC->setMaximum(20.000000000000000);
        doubleSpinBox_BHC->setValue(1.000000000000000);

        gridLayout_2->addWidget(doubleSpinBox_BHC, 0, 1, 1, 1);

        label_7 = new QLabel(groupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        gridLayout_2->addWidget(label_7, 1, 0, 1, 1);

        doubleSpinBox_FlatCorrFac = new QDoubleSpinBox(groupBox);
        doubleSpinBox_FlatCorrFac->setObjectName(QString::fromUtf8("doubleSpinBox_FlatCorrFac"));
        doubleSpinBox_FlatCorrFac->setDecimals(5);
        doubleSpinBox_FlatCorrFac->setMinimum(0.500000000000000);
        doubleSpinBox_FlatCorrFac->setMaximum(2.000000000000000);
        doubleSpinBox_FlatCorrFac->setSingleStep(0.000100000000000);
        doubleSpinBox_FlatCorrFac->setValue(1.097400000000000);

        gridLayout_2->addWidget(doubleSpinBox_FlatCorrFac, 1, 1, 1, 1);


        horizontalLayout_4->addLayout(gridLayout_2);


        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalSpacer_2 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_2->addItem(verticalSpacer_2);

        line = new QFrame(groupBox);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout_3->addWidget(label, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        lineEdit_VolumeFile = new QLineEdit(groupBox);
        lineEdit_VolumeFile->setObjectName(QString::fromUtf8("lineEdit_VolumeFile"));

        horizontalLayout->addWidget(lineEdit_VolumeFile);

        btn_ImportFileSelect = new QPushButton(groupBox);
        btn_ImportFileSelect->setObjectName(QString::fromUtf8("btn_ImportFileSelect"));
        btn_ImportFileSelect->setStyleSheet(QString::fromUtf8("background: white;"));
        QIcon icon;
        icon.addFile(QString::fromUtf8("Images/fileopen1.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_ImportFileSelect->setIcon(icon);

        horizontalLayout->addWidget(btn_ImportFileSelect);


        gridLayout_3->addLayout(horizontalLayout, 0, 1, 1, 1);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_3->addWidget(label_2, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lineEdit_SinoOutDir = new QLineEdit(groupBox);
        lineEdit_SinoOutDir->setObjectName(QString::fromUtf8("lineEdit_SinoOutDir"));

        horizontalLayout_2->addWidget(lineEdit_SinoOutDir);

        btn_SinoOutputDir = new QPushButton(groupBox);
        btn_SinoOutputDir->setObjectName(QString::fromUtf8("btn_SinoOutputDir"));
        btn_SinoOutputDir->setStyleSheet(QString::fromUtf8("background: white;"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("Images/diropen-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        btn_SinoOutputDir->setIcon(icon1);

        horizontalLayout_2->addWidget(btn_SinoOutputDir);


        gridLayout_3->addLayout(horizontalLayout_2, 1, 1, 1, 1);

        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 2, 0, 1, 1);

        lineEdit__SinoBaseName = new QLineEdit(groupBox);
        lineEdit__SinoBaseName->setObjectName(QString::fromUtf8("lineEdit__SinoBaseName"));

        gridLayout_3->addWidget(lineEdit__SinoBaseName, 2, 1, 1, 1);


        verticalLayout_2->addLayout(gridLayout_3);

        line_2 = new QFrame(groupBox);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_2);

        verticalSpacer_3 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_2->addItem(verticalSpacer_3);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        btn_ImportConvert = new QPushButton(groupBox);
        btn_ImportConvert->setObjectName(QString::fromUtf8("btn_ImportConvert"));
        btn_ImportConvert->setEnabled(true);
        btn_ImportConvert->setStyleSheet(QString::fromUtf8("background: yellowgreen;"));

        horizontalLayout_8->addWidget(btn_ImportConvert);

        progressBar = new QProgressBar(groupBox);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMinimum(1);
        progressBar->setValue(1);

        horizontalLayout_8->addWidget(progressBar);


        verticalLayout_2->addLayout(horizontalLayout_8);

        verticalSpacer_4 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_2->addItem(verticalSpacer_4);

        line_3 = new QFrame(groupBox);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_2->addWidget(line_3);

        verticalSpacer = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_2->addItem(verticalSpacer);

        hboxLayout = new QHBoxLayout();
#ifndef Q_OS_MAC
        hboxLayout->setSpacing(6);
#endif
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        closeButton = new QPushButton(groupBox);
        closeButton->setObjectName(QString::fromUtf8("closeButton"));

        hboxLayout->addWidget(closeButton);


        verticalLayout_2->addLayout(hboxLayout);


        verticalLayout->addWidget(groupBox);


        retranslateUi(Dialog);

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QCoreApplication::translate("Dialog", "Import & Convert DETECT Data", nullptr));
        groupBox->setTitle(QCoreApplication::translate("Dialog", "Import Settings", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog", "Image width: ", nullptr));
        label_5->setText(QCoreApplication::translate("Dialog", "Image height:", nullptr));
        label_6->setText(QCoreApplication::translate("Dialog", "BHC Polynom Coefficient:", nullptr));
        label_7->setText(QCoreApplication::translate("Dialog", "Flat Correction Factor:", nullptr));
        label->setText(QCoreApplication::translate("Dialog", "Volume file [*.pru]:", nullptr));
        btn_ImportFileSelect->setText(QString());
        label_2->setText(QCoreApplication::translate("Dialog", "Sinogram Output Directory:", nullptr));
        btn_SinoOutputDir->setText(QString());
        label_3->setText(QCoreApplication::translate("Dialog", "Sinogram Base Name:", nullptr));
        lineEdit__SinoBaseName->setText(QCoreApplication::translate("Dialog", "Sino_", nullptr));
        btn_ImportConvert->setText(QCoreApplication::translate("Dialog", "Import && Convert", nullptr));
        closeButton->setText(QCoreApplication::translate("Dialog", "Close", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_IMPORTDETECTDATA_H
