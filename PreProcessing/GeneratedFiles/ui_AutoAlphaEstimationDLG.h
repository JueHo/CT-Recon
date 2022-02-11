/********************************************************************************
** Form generated from reading UI file 'AutoAlphaEstimationDLG.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_AUTOALPHAESTIMATIONDLG_H
#define UI_AUTOALPHAESTIMATIONDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "qwt_plot.h"

QT_BEGIN_NAMESPACE

class Ui_Dialog_AutoAlpha
{
public:
    QVBoxLayout *verticalLayout_19;
    QScrollArea *scrollArea_2;
    QWidget *scrollAreaWidgetContents_5;
    QHBoxLayout *horizontalLayout_31;
    QScrollArea *scrollArea_image;
    QWidget *scrollAreaWidgetContents_6;
    QGridLayout *gridLayout_3;
    QLabel *label_imageWinSelection;
    QVBoxLayout *verticalLayout_13;
    QwtPlot *qwtPlot_Skew;
    QGroupBox *groupBox_13;
    QHBoxLayout *horizontalLayout_32;
    QVBoxLayout *verticalLayout_14;
    QGroupBox *groupBox_14;
    QFormLayout *formLayout_3;
    QHBoxLayout *horizontalLayout_33;
    QLabel *label_22;
    QSpinBox *spinBox_PointP1_x;
    QHBoxLayout *horizontalLayout_34;
    QLabel *label_23;
    QSpinBox *spinBox_PointP2_x;
    QHBoxLayout *horizontalLayout_35;
    QLabel *label_24;
    QSpinBox *spinBox_PointP1_y;
    QHBoxLayout *horizontalLayout_36;
    QLabel *label_25;
    QSpinBox *spinBox_PointP2_y;
    QPushButton *pushButton_saveSelection;
    QSpacerItem *verticalSpacer_7;
    QVBoxLayout *verticalLayout_15;
    QGroupBox *groupBox_15;
    QVBoxLayout *verticalLayout_16;
    QHBoxLayout *horizontalLayout_37;
    QSpacerItem *horizontalSpacer_11;
    QLabel *label_26;
    QDoubleSpinBox *doubleSpinBox_AlphaFrom;
    QHBoxLayout *horizontalLayout_38;
    QSpacerItem *horizontalSpacer_12;
    QLabel *label_27;
    QDoubleSpinBox *doubleSpinBox_AlphaTo;
    QHBoxLayout *horizontalLayout_39;
    QSpacerItem *horizontalSpacer_13;
    QLabel *label_28;
    QDoubleSpinBox *doubleSpinBox_AlphaStepSize;
    QHBoxLayout *horizontalLayout_40;
    QLabel *label_29;
    QLCDNumber *lcdNumber_NoSlice;
    QVBoxLayout *verticalLayout_17;
    QGroupBox *groupBox_16;
    QVBoxLayout *verticalLayout_18;
    QHBoxLayout *horizontalLayout_41;
    QSpacerItem *horizontalSpacer_14;
    QPushButton *pushButton_StartAlphaEstimation;
    QHBoxLayout *horizontalLayout_42;
    QLabel *label_30;
    QDoubleSpinBox *doubleSpinBox_AlphaResult;
    QSpacerItem *verticalSpacer_8;
    QSpacerItem *verticalSpacer_9;
    QHBoxLayout *horizontalLayout_43;
    QGroupBox *groupBox_17;
    QHBoxLayout *horizontalLayout_44;
    QComboBox *comboBox_ImageZoom;
    QSpacerItem *horizontalSpacer_15;
    QGroupBox *groupBox_18;
    QHBoxLayout *horizontalLayout_45;
    QPushButton *pushButton_accept;
    QPushButton *pushButton_9;

    void setupUi(QDialog *Dialog_AutoAlpha)
    {
        if (Dialog_AutoAlpha->objectName().isEmpty())
            Dialog_AutoAlpha->setObjectName(QString::fromUtf8("Dialog_AutoAlpha"));
        Dialog_AutoAlpha->resize(1300, 730);
        verticalLayout_19 = new QVBoxLayout(Dialog_AutoAlpha);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        scrollArea_2 = new QScrollArea(Dialog_AutoAlpha);
        scrollArea_2->setObjectName(QString::fromUtf8("scrollArea_2"));
        scrollArea_2->setWidgetResizable(true);
        scrollAreaWidgetContents_5 = new QWidget();
        scrollAreaWidgetContents_5->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_5"));
        scrollAreaWidgetContents_5->setGeometry(QRect(0, 0, 1280, 710));
        horizontalLayout_31 = new QHBoxLayout(scrollAreaWidgetContents_5);
        horizontalLayout_31->setObjectName(QString::fromUtf8("horizontalLayout_31"));
        scrollArea_image = new QScrollArea(scrollAreaWidgetContents_5);
        scrollArea_image->setObjectName(QString::fromUtf8("scrollArea_image"));
        scrollArea_image->setMinimumSize(QSize(0, 0));
        scrollArea_image->setWidgetResizable(true);
        scrollAreaWidgetContents_6 = new QWidget();
        scrollAreaWidgetContents_6->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_6"));
        scrollAreaWidgetContents_6->setGeometry(QRect(0, 0, 626, 690));
        gridLayout_3 = new QGridLayout(scrollAreaWidgetContents_6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_imageWinSelection = new QLabel(scrollAreaWidgetContents_6);
        label_imageWinSelection->setObjectName(QString::fromUtf8("label_imageWinSelection"));
        label_imageWinSelection->setMinimumSize(QSize(0, 0));
        label_imageWinSelection->setScaledContents(false);
        label_imageWinSelection->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_imageWinSelection, 0, 1, 1, 1);

        scrollArea_image->setWidget(scrollAreaWidgetContents_6);

        horizontalLayout_31->addWidget(scrollArea_image);

        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        qwtPlot_Skew = new QwtPlot(scrollAreaWidgetContents_5);
        qwtPlot_Skew->setObjectName(QString::fromUtf8("qwtPlot_Skew"));
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(2);
        sizePolicy.setVerticalStretch(2);
        sizePolicy.setHeightForWidth(qwtPlot_Skew->sizePolicy().hasHeightForWidth());
        qwtPlot_Skew->setSizePolicy(sizePolicy);
        qwtPlot_Skew->setMinimumSize(QSize(0, 450));

        verticalLayout_13->addWidget(qwtPlot_Skew);

        groupBox_13 = new QGroupBox(scrollAreaWidgetContents_5);
        groupBox_13->setObjectName(QString::fromUtf8("groupBox_13"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_13->sizePolicy().hasHeightForWidth());
        groupBox_13->setSizePolicy(sizePolicy1);
        horizontalLayout_32 = new QHBoxLayout(groupBox_13);
        horizontalLayout_32->setObjectName(QString::fromUtf8("horizontalLayout_32"));
        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        groupBox_14 = new QGroupBox(groupBox_13);
        groupBox_14->setObjectName(QString::fromUtf8("groupBox_14"));
        formLayout_3 = new QFormLayout(groupBox_14);
        formLayout_3->setObjectName(QString::fromUtf8("formLayout_3"));
        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setObjectName(QString::fromUtf8("horizontalLayout_33"));
        label_22 = new QLabel(groupBox_14);
        label_22->setObjectName(QString::fromUtf8("label_22"));

        horizontalLayout_33->addWidget(label_22);

        spinBox_PointP1_x = new QSpinBox(groupBox_14);
        spinBox_PointP1_x->setObjectName(QString::fromUtf8("spinBox_PointP1_x"));
        spinBox_PointP1_x->setMaximum(9000);
        spinBox_PointP1_x->setSingleStep(1);

        horizontalLayout_33->addWidget(spinBox_PointP1_x);


        formLayout_3->setLayout(0, QFormLayout::LabelRole, horizontalLayout_33);

        horizontalLayout_34 = new QHBoxLayout();
        horizontalLayout_34->setObjectName(QString::fromUtf8("horizontalLayout_34"));
        label_23 = new QLabel(groupBox_14);
        label_23->setObjectName(QString::fromUtf8("label_23"));

        horizontalLayout_34->addWidget(label_23);

        spinBox_PointP2_x = new QSpinBox(groupBox_14);
        spinBox_PointP2_x->setObjectName(QString::fromUtf8("spinBox_PointP2_x"));
        spinBox_PointP2_x->setMaximum(9000);
        spinBox_PointP2_x->setSingleStep(1);

        horizontalLayout_34->addWidget(spinBox_PointP2_x);


        formLayout_3->setLayout(0, QFormLayout::FieldRole, horizontalLayout_34);

        horizontalLayout_35 = new QHBoxLayout();
        horizontalLayout_35->setObjectName(QString::fromUtf8("horizontalLayout_35"));
        label_24 = new QLabel(groupBox_14);
        label_24->setObjectName(QString::fromUtf8("label_24"));

        horizontalLayout_35->addWidget(label_24);

        spinBox_PointP1_y = new QSpinBox(groupBox_14);
        spinBox_PointP1_y->setObjectName(QString::fromUtf8("spinBox_PointP1_y"));
        spinBox_PointP1_y->setMaximum(9000);
        spinBox_PointP1_y->setSingleStep(1);

        horizontalLayout_35->addWidget(spinBox_PointP1_y);


        formLayout_3->setLayout(1, QFormLayout::LabelRole, horizontalLayout_35);

        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setObjectName(QString::fromUtf8("horizontalLayout_36"));
        label_25 = new QLabel(groupBox_14);
        label_25->setObjectName(QString::fromUtf8("label_25"));

        horizontalLayout_36->addWidget(label_25);

        spinBox_PointP2_y = new QSpinBox(groupBox_14);
        spinBox_PointP2_y->setObjectName(QString::fromUtf8("spinBox_PointP2_y"));
        spinBox_PointP2_y->setMaximum(9000);
        spinBox_PointP2_y->setSingleStep(1);

        horizontalLayout_36->addWidget(spinBox_PointP2_y);


        formLayout_3->setLayout(1, QFormLayout::FieldRole, horizontalLayout_36);


        verticalLayout_14->addWidget(groupBox_14);

        pushButton_saveSelection = new QPushButton(groupBox_13);
        pushButton_saveSelection->setObjectName(QString::fromUtf8("pushButton_saveSelection"));

        verticalLayout_14->addWidget(pushButton_saveSelection);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_14->addItem(verticalSpacer_7);


        horizontalLayout_32->addLayout(verticalLayout_14);

        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        groupBox_15 = new QGroupBox(groupBox_13);
        groupBox_15->setObjectName(QString::fromUtf8("groupBox_15"));
        verticalLayout_16 = new QVBoxLayout(groupBox_15);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        horizontalLayout_37 = new QHBoxLayout();
        horizontalLayout_37->setObjectName(QString::fromUtf8("horizontalLayout_37"));
        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_37->addItem(horizontalSpacer_11);

        label_26 = new QLabel(groupBox_15);
        label_26->setObjectName(QString::fromUtf8("label_26"));

        horizontalLayout_37->addWidget(label_26);

        doubleSpinBox_AlphaFrom = new QDoubleSpinBox(groupBox_15);
        doubleSpinBox_AlphaFrom->setObjectName(QString::fromUtf8("doubleSpinBox_AlphaFrom"));
        doubleSpinBox_AlphaFrom->setMinimum(0.010000000000000);
        doubleSpinBox_AlphaFrom->setSingleStep(0.010000000000000);
        doubleSpinBox_AlphaFrom->setValue(0.100000000000000);

        horizontalLayout_37->addWidget(doubleSpinBox_AlphaFrom);


        verticalLayout_16->addLayout(horizontalLayout_37);

        horizontalLayout_38 = new QHBoxLayout();
        horizontalLayout_38->setObjectName(QString::fromUtf8("horizontalLayout_38"));
        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_38->addItem(horizontalSpacer_12);

        label_27 = new QLabel(groupBox_15);
        label_27->setObjectName(QString::fromUtf8("label_27"));

        horizontalLayout_38->addWidget(label_27);

        doubleSpinBox_AlphaTo = new QDoubleSpinBox(groupBox_15);
        doubleSpinBox_AlphaTo->setObjectName(QString::fromUtf8("doubleSpinBox_AlphaTo"));
        doubleSpinBox_AlphaTo->setMinimum(0.100000000000000);
        doubleSpinBox_AlphaTo->setMaximum(100.000000000000000);
        doubleSpinBox_AlphaTo->setSingleStep(1.000000000000000);
        doubleSpinBox_AlphaTo->setValue(10.000000000000000);

        horizontalLayout_38->addWidget(doubleSpinBox_AlphaTo);


        verticalLayout_16->addLayout(horizontalLayout_38);

        horizontalLayout_39 = new QHBoxLayout();
        horizontalLayout_39->setObjectName(QString::fromUtf8("horizontalLayout_39"));
        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_39->addItem(horizontalSpacer_13);

        label_28 = new QLabel(groupBox_15);
        label_28->setObjectName(QString::fromUtf8("label_28"));

        horizontalLayout_39->addWidget(label_28);

        doubleSpinBox_AlphaStepSize = new QDoubleSpinBox(groupBox_15);
        doubleSpinBox_AlphaStepSize->setObjectName(QString::fromUtf8("doubleSpinBox_AlphaStepSize"));
        doubleSpinBox_AlphaStepSize->setMinimum(0.010000000000000);
        doubleSpinBox_AlphaStepSize->setMaximum(10.000000000000000);
        doubleSpinBox_AlphaStepSize->setSingleStep(0.010000000000000);
        doubleSpinBox_AlphaStepSize->setValue(0.100000000000000);

        horizontalLayout_39->addWidget(doubleSpinBox_AlphaStepSize);


        verticalLayout_16->addLayout(horizontalLayout_39);

        horizontalLayout_40 = new QHBoxLayout();
        horizontalLayout_40->setObjectName(QString::fromUtf8("horizontalLayout_40"));
        label_29 = new QLabel(groupBox_15);
        label_29->setObjectName(QString::fromUtf8("label_29"));

        horizontalLayout_40->addWidget(label_29);

        lcdNumber_NoSlice = new QLCDNumber(groupBox_15);
        lcdNumber_NoSlice->setObjectName(QString::fromUtf8("lcdNumber_NoSlice"));
        lcdNumber_NoSlice->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 0);\n"
"border-color: rgb(0, 0, 127);"));

        horizontalLayout_40->addWidget(lcdNumber_NoSlice);


        verticalLayout_16->addLayout(horizontalLayout_40);


        verticalLayout_15->addWidget(groupBox_15);


        horizontalLayout_32->addLayout(verticalLayout_15);

        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        groupBox_16 = new QGroupBox(groupBox_13);
        groupBox_16->setObjectName(QString::fromUtf8("groupBox_16"));
        verticalLayout_18 = new QVBoxLayout(groupBox_16);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        horizontalLayout_41 = new QHBoxLayout();
        horizontalLayout_41->setObjectName(QString::fromUtf8("horizontalLayout_41"));
        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_41->addItem(horizontalSpacer_14);

        pushButton_StartAlphaEstimation = new QPushButton(groupBox_16);
        pushButton_StartAlphaEstimation->setObjectName(QString::fromUtf8("pushButton_StartAlphaEstimation"));

        horizontalLayout_41->addWidget(pushButton_StartAlphaEstimation);


        verticalLayout_18->addLayout(horizontalLayout_41);

        horizontalLayout_42 = new QHBoxLayout();
        horizontalLayout_42->setObjectName(QString::fromUtf8("horizontalLayout_42"));
        label_30 = new QLabel(groupBox_16);
        label_30->setObjectName(QString::fromUtf8("label_30"));

        horizontalLayout_42->addWidget(label_30);

        doubleSpinBox_AlphaResult = new QDoubleSpinBox(groupBox_16);
        doubleSpinBox_AlphaResult->setObjectName(QString::fromUtf8("doubleSpinBox_AlphaResult"));
        doubleSpinBox_AlphaResult->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 255, 0);"));

        horizontalLayout_42->addWidget(doubleSpinBox_AlphaResult);


        verticalLayout_18->addLayout(horizontalLayout_42);


        verticalLayout_17->addWidget(groupBox_16);

        verticalSpacer_8 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_17->addItem(verticalSpacer_8);


        horizontalLayout_32->addLayout(verticalLayout_17);


        verticalLayout_13->addWidget(groupBox_13);

        verticalSpacer_9 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_13->addItem(verticalSpacer_9);

        horizontalLayout_43 = new QHBoxLayout();
        horizontalLayout_43->setObjectName(QString::fromUtf8("horizontalLayout_43"));
        groupBox_17 = new QGroupBox(scrollAreaWidgetContents_5);
        groupBox_17->setObjectName(QString::fromUtf8("groupBox_17"));
        horizontalLayout_44 = new QHBoxLayout(groupBox_17);
        horizontalLayout_44->setObjectName(QString::fromUtf8("horizontalLayout_44"));
        comboBox_ImageZoom = new QComboBox(groupBox_17);
        comboBox_ImageZoom->addItem(QString());
        comboBox_ImageZoom->addItem(QString());
        comboBox_ImageZoom->addItem(QString());
        comboBox_ImageZoom->addItem(QString());
        comboBox_ImageZoom->addItem(QString());
        comboBox_ImageZoom->setObjectName(QString::fromUtf8("comboBox_ImageZoom"));

        horizontalLayout_44->addWidget(comboBox_ImageZoom);


        horizontalLayout_43->addWidget(groupBox_17);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_43->addItem(horizontalSpacer_15);

        groupBox_18 = new QGroupBox(scrollAreaWidgetContents_5);
        groupBox_18->setObjectName(QString::fromUtf8("groupBox_18"));
        horizontalLayout_45 = new QHBoxLayout(groupBox_18);
        horizontalLayout_45->setObjectName(QString::fromUtf8("horizontalLayout_45"));
        pushButton_accept = new QPushButton(groupBox_18);
        pushButton_accept->setObjectName(QString::fromUtf8("pushButton_accept"));

        horizontalLayout_45->addWidget(pushButton_accept);

        pushButton_9 = new QPushButton(groupBox_18);
        pushButton_9->setObjectName(QString::fromUtf8("pushButton_9"));

        horizontalLayout_45->addWidget(pushButton_9);


        horizontalLayout_43->addWidget(groupBox_18);


        verticalLayout_13->addLayout(horizontalLayout_43);


        horizontalLayout_31->addLayout(verticalLayout_13);

        scrollArea_2->setWidget(scrollAreaWidgetContents_5);

        verticalLayout_19->addWidget(scrollArea_2);


        retranslateUi(Dialog_AutoAlpha);
        QObject::connect(pushButton_accept, SIGNAL(clicked()), Dialog_AutoAlpha, SLOT(accept()));
        QObject::connect(pushButton_9, SIGNAL(clicked()), Dialog_AutoAlpha, SLOT(reject()));

        comboBox_ImageZoom->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(Dialog_AutoAlpha);
    } // setupUi

    void retranslateUi(QDialog *Dialog_AutoAlpha)
    {
        Dialog_AutoAlpha->setWindowTitle(QCoreApplication::translate("Dialog_AutoAlpha", "Alpha Determination", nullptr));
        label_imageWinSelection->setText(QCoreApplication::translate("Dialog_AutoAlpha", "TextLabel", nullptr));
        groupBox_13->setTitle(QString());
        groupBox_14->setTitle(QCoreApplication::translate("Dialog_AutoAlpha", "Windows Selection", nullptr));
        label_22->setText(QCoreApplication::translate("Dialog_AutoAlpha", "P1x: ", nullptr));
        label_23->setText(QCoreApplication::translate("Dialog_AutoAlpha", "P2x: ", nullptr));
        label_24->setText(QCoreApplication::translate("Dialog_AutoAlpha", "P1y: ", nullptr));
        label_25->setText(QCoreApplication::translate("Dialog_AutoAlpha", "P2y: ", nullptr));
        pushButton_saveSelection->setText(QCoreApplication::translate("Dialog_AutoAlpha", "Save Selection (Temp)", nullptr));
        groupBox_15->setTitle(QCoreApplication::translate("Dialog_AutoAlpha", "Alpha Estimation Parameters", nullptr));
        label_26->setText(QCoreApplication::translate("Dialog_AutoAlpha", "From:", nullptr));
        label_27->setText(QCoreApplication::translate("Dialog_AutoAlpha", "To:", nullptr));
        label_28->setText(QCoreApplication::translate("Dialog_AutoAlpha", "Step Size:", nullptr));
        label_29->setText(QCoreApplication::translate("Dialog_AutoAlpha", "Number Slices:", nullptr));
        groupBox_16->setTitle(QCoreApplication::translate("Dialog_AutoAlpha", "Alpha Estimation process", nullptr));
        pushButton_StartAlphaEstimation->setText(QCoreApplication::translate("Dialog_AutoAlpha", "Start", nullptr));
        label_30->setText(QCoreApplication::translate("Dialog_AutoAlpha", "Proposed Alpha:", nullptr));
        groupBox_17->setTitle(QCoreApplication::translate("Dialog_AutoAlpha", "Zoom Image", nullptr));
        comboBox_ImageZoom->setItemText(0, QCoreApplication::translate("Dialog_AutoAlpha", "25%", nullptr));
        comboBox_ImageZoom->setItemText(1, QCoreApplication::translate("Dialog_AutoAlpha", "50%", nullptr));
        comboBox_ImageZoom->setItemText(2, QCoreApplication::translate("Dialog_AutoAlpha", "75%", nullptr));
        comboBox_ImageZoom->setItemText(3, QCoreApplication::translate("Dialog_AutoAlpha", "100%", nullptr));
        comboBox_ImageZoom->setItemText(4, QCoreApplication::translate("Dialog_AutoAlpha", "200 %", nullptr));

        groupBox_18->setTitle(QString());
        pushButton_accept->setText(QCoreApplication::translate("Dialog_AutoAlpha", "Accept Alpha", nullptr));
        pushButton_9->setText(QCoreApplication::translate("Dialog_AutoAlpha", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_AutoAlpha: public Ui_Dialog_AutoAlpha {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_AUTOALPHAESTIMATIONDLG_H
