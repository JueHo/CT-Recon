/********************************************************************************
** Form generated from reading UI file 'NormalizeImageDLG.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_NORMALIZEIMAGEDLG_H
#define UI_NORMALIZEIMAGEDLG_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DialogNormalize
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout;
    QLabel *label_origImage;
    QHBoxLayout *hboxLayout;
    QSpacerItem *horizontalSpacer;
    QLabel *label_3;
    QDoubleSpinBox *doubleSpinBox_meanValue;
    QSpacerItem *spacerItem;
    QPushButton *okButton;
    QPushButton *cancelButton;

    void setupUi(QDialog *DialogNormalize)
    {
        if (DialogNormalize->objectName().isEmpty())
            DialogNormalize->setObjectName(QString::fromUtf8("DialogNormalize"));
        DialogNormalize->resize(931, 936);
        QFont font;
        font.setUnderline(false);
        DialogNormalize->setFont(font);
        verticalLayout = new QVBoxLayout(DialogNormalize);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(DialogNormalize);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Arial"));
        font1.setPointSize(12);
        font1.setBold(true);
        font1.setItalic(true);
        font1.setUnderline(false);
        font1.setWeight(75);
        label_2->setFont(font1);
        label_2->setStyleSheet(QString::fromUtf8("color: rgb(255, 7, 52);\n"
"border-color: rgb(255, 0, 0);"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);


        verticalLayout->addWidget(groupBox);

        scrollArea = new QScrollArea(DialogNormalize);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 911, 833));
        gridLayout = new QGridLayout(scrollAreaWidgetContents);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_origImage = new QLabel(scrollAreaWidgetContents);
        label_origImage->setObjectName(QString::fromUtf8("label_origImage"));
        label_origImage->setFont(font);
        label_origImage->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_origImage, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        verticalLayout->addWidget(scrollArea);

        hboxLayout = new QHBoxLayout();
        hboxLayout->setSpacing(6);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(horizontalSpacer);

        label_3 = new QLabel(DialogNormalize);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        QFont font2;
        font2.setBold(true);
        font2.setUnderline(false);
        font2.setWeight(75);
        label_3->setFont(font2);
        label_3->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);\n"
"background-color: rgb(255, 255, 0);"));

        hboxLayout->addWidget(label_3);

        doubleSpinBox_meanValue = new QDoubleSpinBox(DialogNormalize);
        doubleSpinBox_meanValue->setObjectName(QString::fromUtf8("doubleSpinBox_meanValue"));
        doubleSpinBox_meanValue->setFont(font);
        doubleSpinBox_meanValue->setMaximum(1000000.000000000000000);

        hboxLayout->addWidget(doubleSpinBox_meanValue);

        spacerItem = new QSpacerItem(131, 31, QSizePolicy::Expanding, QSizePolicy::Minimum);

        hboxLayout->addItem(spacerItem);

        okButton = new QPushButton(DialogNormalize);
        okButton->setObjectName(QString::fromUtf8("okButton"));

        hboxLayout->addWidget(okButton);

        cancelButton = new QPushButton(DialogNormalize);
        cancelButton->setObjectName(QString::fromUtf8("cancelButton"));

        hboxLayout->addWidget(cancelButton);


        verticalLayout->addLayout(hboxLayout);


        retranslateUi(DialogNormalize);
        QObject::connect(okButton, SIGNAL(clicked()), DialogNormalize, SLOT(accept()));
        QObject::connect(cancelButton, SIGNAL(clicked()), DialogNormalize, SLOT(reject()));

        QMetaObject::connectSlotsByName(DialogNormalize);
    } // setupUi

    void retranslateUi(QDialog *DialogNormalize)
    {
        DialogNormalize->setWindowTitle(QCoreApplication::translate("DialogNormalize", "Dialog", nullptr));
        groupBox->setTitle(QString());
        label_2->setText(QCoreApplication::translate("DialogNormalize", "Select region for normalization", nullptr));
        label_origImage->setText(QCoreApplication::translate("DialogNormalize", "Image", nullptr));
        label_3->setText(QCoreApplication::translate("DialogNormalize", " Mean Value of Selection: ", nullptr));
        okButton->setText(QCoreApplication::translate("DialogNormalize", "OK", nullptr));
        cancelButton->setText(QCoreApplication::translate("DialogNormalize", "Cancel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DialogNormalize: public Ui_DialogNormalize {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_NORMALIZEIMAGEDLG_H
