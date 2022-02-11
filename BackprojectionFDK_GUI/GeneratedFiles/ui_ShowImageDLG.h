/********************************************************************************
** Form generated from reading UI file 'ShowImageDLG.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWIMAGEDLG_H
#define UI_SHOWIMAGEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_dlg_ShowImage
{
public:
    QGridLayout *gridLayout_2;
    QScrollArea *pw_containerScrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *DLG_ImageArea;
    QHBoxLayout *horizontalLayout;
    QCheckBox *checkBox_keepSelection;
    QSpacerItem *horizontalSpacer_6;
    QLabel *label_5;
    QComboBox *comboBox_imageScale;
    QSpacerItem *horizontalSpacer_5;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout_7;
    QSpacerItem *horizontalSpacer_4;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label;
    QSpinBox *spinBox_x0;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_2;
    QSpinBox *spinBox_y0;
    QSpacerItem *horizontalSpacer_3;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_3;
    QSpinBox *spinBox_width;
    QHBoxLayout *horizontalLayout_6;
    QLabel *label_4;
    QSpinBox *spinBox_height;
    QSpacerItem *horizontalSpacer_2;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontaldummySpacer;
    QPushButton *okButton_ImageDialog;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *dlg_ShowImage)
    {
        if (dlg_ShowImage->objectName().isEmpty())
            dlg_ShowImage->setObjectName(QString::fromUtf8("dlg_ShowImage"));
        dlg_ShowImage->setWindowModality(Qt::NonModal);
        dlg_ShowImage->resize(629, 550);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(dlg_ShowImage->sizePolicy().hasHeightForWidth());
        dlg_ShowImage->setSizePolicy(sizePolicy);
        dlg_ShowImage->setMinimumSize(QSize(600, 500));
        dlg_ShowImage->setMaximumSize(QSize(1400, 1200));
        dlg_ShowImage->setFocusPolicy(Qt::ClickFocus);
        dlg_ShowImage->setContextMenuPolicy(Qt::DefaultContextMenu);
        QIcon icon;
        icon.addFile(QString::fromUtf8("Images/FDK_IMG.png"), QSize(), QIcon::Normal, QIcon::Off);
        dlg_ShowImage->setWindowIcon(icon);
        gridLayout_2 = new QGridLayout(dlg_ShowImage);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        pw_containerScrollArea = new QScrollArea(dlg_ShowImage);
        pw_containerScrollArea->setObjectName(QString::fromUtf8("pw_containerScrollArea"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pw_containerScrollArea->sizePolicy().hasHeightForWidth());
        pw_containerScrollArea->setSizePolicy(sizePolicy1);
        pw_containerScrollArea->setMaximumSize(QSize(3000, 3000));
        pw_containerScrollArea->setMouseTracking(false);
        pw_containerScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        pw_containerScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        pw_containerScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 607, 398));
        sizePolicy.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy);
        scrollAreaWidgetContents->setMaximumSize(QSize(3000, 3000));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        DLG_ImageArea = new QLabel(scrollAreaWidgetContents);
        DLG_ImageArea->setObjectName(QString::fromUtf8("DLG_ImageArea"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(DLG_ImageArea->sizePolicy().hasHeightForWidth());
        DLG_ImageArea->setSizePolicy(sizePolicy2);
        DLG_ImageArea->setMinimumSize(QSize(60, 60));
        DLG_ImageArea->setMaximumSize(QSize(2500, 2500));
        DLG_ImageArea->setMouseTracking(true);
        DLG_ImageArea->setFrameShape(QFrame::Box);
        DLG_ImageArea->setFrameShadow(QFrame::Raised);
        DLG_ImageArea->setScaledContents(false);

        gridLayout->addWidget(DLG_ImageArea, 0, 0, 1, 1);

        pw_containerScrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_2->addWidget(pw_containerScrollArea, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        checkBox_keepSelection = new QCheckBox(dlg_ShowImage);
        checkBox_keepSelection->setObjectName(QString::fromUtf8("checkBox_keepSelection"));
        checkBox_keepSelection->setChecked(false);

        horizontalLayout->addWidget(checkBox_keepSelection);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_6);

        label_5 = new QLabel(dlg_ShowImage);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout->addWidget(label_5);

        comboBox_imageScale = new QComboBox(dlg_ShowImage);
        comboBox_imageScale->addItem(QString());
        comboBox_imageScale->addItem(QString());
        comboBox_imageScale->addItem(QString());
        comboBox_imageScale->addItem(QString());
        comboBox_imageScale->addItem(QString());
        comboBox_imageScale->addItem(QString());
        comboBox_imageScale->setObjectName(QString::fromUtf8("comboBox_imageScale"));

        horizontalLayout->addWidget(comboBox_imageScale);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);


        gridLayout_2->addLayout(horizontalLayout, 1, 0, 1, 1);

        groupBox = new QGroupBox(dlg_ShowImage);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout_7 = new QHBoxLayout(groupBox);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        horizontalSpacer_4 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_4);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_2->addWidget(label);

        spinBox_x0 = new QSpinBox(groupBox);
        spinBox_x0->setObjectName(QString::fromUtf8("spinBox_x0"));
        spinBox_x0->setEnabled(false);
        spinBox_x0->setMaximum(5000);
        spinBox_x0->setSingleStep(6);

        horizontalLayout_2->addWidget(spinBox_x0);


        horizontalLayout_7->addLayout(horizontalLayout_2);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_4->addWidget(label_2);

        spinBox_y0 = new QSpinBox(groupBox);
        spinBox_y0->setObjectName(QString::fromUtf8("spinBox_y0"));
        spinBox_y0->setEnabled(false);
        spinBox_y0->setMaximum(5000);
        spinBox_y0->setSingleStep(6);

        horizontalLayout_4->addWidget(spinBox_y0);


        horizontalLayout_7->addLayout(horizontalLayout_4);

        horizontalSpacer_3 = new QSpacerItem(25, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_3);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_5->addWidget(label_3);

        spinBox_width = new QSpinBox(groupBox);
        spinBox_width->setObjectName(QString::fromUtf8("spinBox_width"));
        spinBox_width->setEnabled(false);
        spinBox_width->setMaximum(5000);
        spinBox_width->setSingleStep(6);

        horizontalLayout_5->addWidget(spinBox_width);


        horizontalLayout_7->addLayout(horizontalLayout_5);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_6->addWidget(label_4);

        spinBox_height = new QSpinBox(groupBox);
        spinBox_height->setObjectName(QString::fromUtf8("spinBox_height"));
        spinBox_height->setEnabled(false);
        spinBox_height->setMaximum(5000);
        spinBox_height->setSingleStep(6);

        horizontalLayout_6->addWidget(spinBox_height);


        horizontalLayout_7->addLayout(horizontalLayout_6);

        horizontalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_2);


        gridLayout_2->addWidget(groupBox, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontaldummySpacer = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontaldummySpacer);

        okButton_ImageDialog = new QPushButton(dlg_ShowImage);
        okButton_ImageDialog->setObjectName(QString::fromUtf8("okButton_ImageDialog"));

        horizontalLayout_3->addWidget(okButton_ImageDialog);

        horizontalSpacer = new QSpacerItem(20, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer);


        gridLayout_2->addLayout(horizontalLayout_3, 3, 0, 1, 1);

        pw_containerScrollArea->raise();
        groupBox->raise();

        retranslateUi(dlg_ShowImage);
        QObject::connect(okButton_ImageDialog, SIGNAL(clicked()), dlg_ShowImage, SLOT(accept()));
        QObject::connect(checkBox_keepSelection, SIGNAL(toggled(bool)), comboBox_imageScale, SLOT(setDisabled(bool)));
        QObject::connect(checkBox_keepSelection, SIGNAL(toggled(bool)), spinBox_x0, SLOT(setEnabled(bool)));
        QObject::connect(checkBox_keepSelection, SIGNAL(toggled(bool)), spinBox_y0, SLOT(setEnabled(bool)));
        QObject::connect(checkBox_keepSelection, SIGNAL(toggled(bool)), spinBox_width, SLOT(setEnabled(bool)));
        QObject::connect(checkBox_keepSelection, SIGNAL(toggled(bool)), spinBox_height, SLOT(setEnabled(bool)));

        QMetaObject::connectSlotsByName(dlg_ShowImage);
    } // setupUi

    void retranslateUi(QDialog *dlg_ShowImage)
    {
        dlg_ShowImage->setWindowTitle(QCoreApplication::translate("dlg_ShowImage", "Dialog", nullptr));
        DLG_ImageArea->setText(QString());
        checkBox_keepSelection->setText(QCoreApplication::translate("dlg_ShowImage", "Keep &&  Modify Selection:", nullptr));
        label_5->setText(QCoreApplication::translate("dlg_ShowImage", "Image Size:", nullptr));
        comboBox_imageScale->setItemText(0, QCoreApplication::translate("dlg_ShowImage", "  50 %", nullptr));
        comboBox_imageScale->setItemText(1, QCoreApplication::translate("dlg_ShowImage", "  10 %", nullptr));
        comboBox_imageScale->setItemText(2, QCoreApplication::translate("dlg_ShowImage", "  20 %", nullptr));
        comboBox_imageScale->setItemText(3, QCoreApplication::translate("dlg_ShowImage", "  25 %", nullptr));
        comboBox_imageScale->setItemText(4, QCoreApplication::translate("dlg_ShowImage", "  33 %", nullptr));
        comboBox_imageScale->setItemText(5, QCoreApplication::translate("dlg_ShowImage", "100 %", nullptr));

        groupBox->setTitle(QCoreApplication::translate("dlg_ShowImage", "Selection Rectangle", nullptr));
        label->setText(QCoreApplication::translate("dlg_ShowImage", "x0=", nullptr));
        label_2->setText(QCoreApplication::translate("dlg_ShowImage", "y0=", nullptr));
        label_3->setText(QCoreApplication::translate("dlg_ShowImage", "Width=", nullptr));
        label_4->setText(QCoreApplication::translate("dlg_ShowImage", "Height=", nullptr));
        okButton_ImageDialog->setText(QCoreApplication::translate("dlg_ShowImage", "OK", nullptr));
    } // retranslateUi

};

namespace Ui {
    class dlg_ShowImage: public Ui_dlg_ShowImage {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWIMAGEDLG_H
