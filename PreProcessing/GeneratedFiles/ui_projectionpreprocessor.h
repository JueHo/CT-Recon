/********************************************************************************
** Form generated from reading UI file 'projectionpreprocessor.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECTIONPREPROCESSOR_H
#define UI_PROJECTIONPREPROCESSOR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolBox>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ProjectionPreProcessorClass
{
public:
    QAction *actionOpen_Project;
    QAction *actionSave_Project_as;
    QAction *actionSave;
    QAction *actionExport_PFDK;
    QAction *actionAbout;
    QAction *actionNew;
    QAction *actionExit;
    QAction *actionLorentz_Filter;
    QWidget *centralWidget;
    QHBoxLayout *horizontalLayout_24;
    QScrollArea *scrollArea_PreProcessorLayoutLeftSide;
    QWidget *scrollAreaWidgetContents_PreProcessorLeftSide;
    QVBoxLayout *verticalLayout_4;
    QTabWidget *tabWidget_ParameterSettings;
    QWidget *tab_BasicParamSettings;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_ProjectSettings;
    QHBoxLayout *horizontalLayout;
    QLabel *label_Project;
    QLineEdit *lineEdit_projectName;
    QSpacerItem *horizontalSpacer_4;
    QLabel *label_CreatorOwner;
    QLineEdit *lineEdit_CreatorOwner;
    QSpacerItem *horizontalSpacer_5;
    QLabel *label_Date;
    QLineEdit *lineEdit_date;
    QTabWidget *tabWidget_IOSettings;
    QWidget *tab_IOInput;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_IOInput;
    QVBoxLayout *verticalLayout_6;
    QGroupBox *groupBox_FileSelection;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label_InputDir;
    QLineEdit *lineEdit_InputDir;
    QPushButton *pushButton_SelInputDir;
    QLabel *label_InputFilePattern;
    QLineEdit *lineEdit_InputFilePattern;
    QSpacerItem *horizontalSpacer;
    QLabel *label_FileType;
    QComboBox *comboBox_SelFileType;
    QFrame *line_inputIO;
    QGroupBox *groupBox_projectionParam;
    QGridLayout *gridLayout;
    QLabel *label_InputType;
    QSpinBox *spinBox_ProjectionHeight;
    QSpinBox *spinBox_ProjectionWidth;
    QLabel *label_ProjectionHeight;
    QLabel *label_ProjectionWidth;
    QLabel *label_NumberProjections;
    QSpinBox *spinBox_NumberProjections;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_13;
    QLabel *label_CVDataType;
    QGroupBox *groupBox_LoadInputData;
    QVBoxLayout *verticalLayout_26;
    QHBoxLayout *horizontalLayout_20;
    QCheckBox *checkBox_TileMemory;
    QLabel *label_3;
    QFrame *line;
    QLabel *label_2;
    QLabel *label_4;
    QSlider *horizontalSlider_MemSavMinMax;
    QLabel *label_5;
    QSpinBox *spinBox_MemMultFac;
    QSpacerItem *horizontalSpacer_28;
    QHBoxLayout *horizontalLayout_22;
    QPushButton *pushButton_LoadInputData;
    QProgressBar *progressBar_LoadData;
    QPushButton *pushButton_LoadDataInterrupt;
    QSpacerItem *horizontalSpacer_32;
    QLabel *label_RotationDirection;
    QComboBox *comboBox_ClockWise;
    QWidget *tab_IOOutput;
    QVBoxLayout *verticalLayout_13;
    QGroupBox *groupBox_IOOutput;
    QVBoxLayout *verticalLayout_12;
    QGroupBox *groupBox_FileDirSelection;
    QGridLayout *gridLayout_4;
    QLabel *label_22;
    QLineEdit *lineEdit_OutPutDir;
    QPushButton *pushButton_SelectOutputDir;
    QLabel *label_RawOutPattern;
    QLineEdit *lineEdit_OutRawPattern;
    QLabel *label_OutputFileType;
    QComboBox *comboBox_OutputFileType;
    QGroupBox *groupBox_SaveData;
    QHBoxLayout *horizontalLayout_13;
    QPushButton *pushButton_SaveDataStart;
    QProgressBar *progressBar_Savedata;
    QGroupBox *groupBox_MethodSelection;
    QHBoxLayout *horizontalLayout_3;
    QCheckBox *checkBox_Normalize;
    QCheckBox *checkBox_OutlierSuppression;
    QCheckBox *checkBox_BHC;
    QCheckBox *checkBox_StripeReduction;
    QToolBox *toolBox_ProcessingMethods;
    QWidget *page_MethodNormalization;
    QVBoxLayout *verticalLayout_19;
    QGroupBox *groupBox_NormalizationOption;
    QVBoxLayout *verticalLayout_29;
    QHBoxLayout *horizontalLayout_6;
    QRadioButton *radioButton_UseFlatFieldNormalization;
    QRadioButton *radioButton_UseFlatWindowNormalization;
    QSpacerItem *horizontalSpacer_30;
    QSpacerItem *horizontalSpacer_29;
    QCheckBox *checkBox_NoLogarithm;
    QFrame *line_3;
    QCheckBox *checkBox_useDarkFlatCorrected;
    QFrame *line_2;
    QGroupBox *groupBox_Normalization;
    QVBoxLayout *verticalLayout_10;
    QGridLayout *gridLayout_DarkFlatFiled;
    QLabel *label_FlatFieldImage;
    QLineEdit *lineEdit_FlatFieldImage;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton_SelectFlat;
    QLabel *label_DarkFieldImage;
    QLineEdit *lineEdit_DarkFieldImage;
    QSpacerItem *horizontalSpacer_9;
    QPushButton *pushButton_SelectDark;
    QHBoxLayout *horizontalLayout_NormWin;
    QGroupBox *groupBox_NormWin;
    QHBoxLayout *horizontalLayout_9;
    QFormLayout *formLayout_WinPos;
    QLabel *label_NormWinXPos;
    QSpinBox *spinBox_NormWinXPos;
    QSpinBox *spinBox_NormWinYPos;
    QLabel *label_NormWinYPos;
    QSpacerItem *horizontalSpacer_7;
    QFormLayout *formLayout_NormWinSize;
    QSpinBox *spinBox_NormWinWidth;
    QLabel *label_NormWinHeight;
    QSpinBox *spinBox_NormWinHeight;
    QLabel *label_NormWinWidth;
    QSpacerItem *horizontalSpacer_10;
    QWidget *page_MethodOutlier;
    QVBoxLayout *verticalLayout_11;
    QGroupBox *groupBox_6;
    QHBoxLayout *horizontalLayout_17;
    QCheckBox *checkBox_UseRAC;
    QCheckBox *checkBox_UseOutlierSuppression;
    QGroupBox *groupBox_OutlierSettings;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout_CoorrectionAlgo;
    QLabel *label_CorrectionAlgo;
    QComboBox *comboBox_MethodSelection;
    QSpacerItem *horizontalSpacer_14;
    QStackedWidget *stackedWidget_MethodsParameter;
    QWidget *page_MethodMedian9;
    QHBoxLayout *horizontalLayout_11;
    QLabel *label_SigmaMedian9;
    QDoubleSpinBox *doubleSpinBox_SigmaMedian9;
    QSpacerItem *horizontalSpacer_12;
    QWidget *page_MethodMean9;
    QHBoxLayout *horizontalLayout_4;
    QLabel *label_SigmaMean9;
    QDoubleSpinBox *doubleSpinBox_SigmaMean9;
    QSpacerItem *horizontalSpacer_11;
    QWidget *page_MethodBHC;
    QVBoxLayout *verticalLayout_18;
    QGroupBox *groupBox_BHCSettings;
    QVBoxLayout *verticalLayout_15;
    QHBoxLayout *horizontalLayout_Formular;
    QLabel *label_Formular;
    QSpacerItem *horizontalSpacer_18;
    QHBoxLayout *horizontalLayout_CorrectionLinearConstant;
    QLabel *label_BHC_CorrectionLinearConstantC;
    QDoubleSpinBox *doubleSpinBox_BHCCorrectionLinearConstA;
    QSpacerItem *horizontalSpacer_27;
    QHBoxLayout *horizontalLayout_CorrectionLinearConstant_2;
    QLabel *label_BHC_CorrectionLinearConstantB;
    QDoubleSpinBox *doubleSpinBox_BHCCorrectionLinearConstB;
    QSpacerItem *horizontalSpacer_31;
    QHBoxLayout *horizontalLayout_CorrectionExponent;
    QLabel *label_BHC_CorrectionExpo;
    QDoubleSpinBox *doubleSpinBox_BHCCorrectionExpo;
    QSpacerItem *horizontalSpacer_16;
    QWidget *page_StripeReduction;
    QVBoxLayout *verticalLayout_17;
    QGroupBox *groupBox_StripeSettings;
    QVBoxLayout *verticalLayout_16;
    QHBoxLayout *horizontalLayout_PadMultFFt;
    QLabel *label_PadMultFFT;
    QComboBox *comboBox_PadMultFFT;
    QSpacerItem *horizontalSpacer_17;
    QCheckBox *checkBox_FFTRunMultiThread;
    QWidget *page_EdgeEnhancement;
    QVBoxLayout *verticalLayout_27;
    QGroupBox *groupBox_EnhanceParams;
    QHBoxLayout *horizontalLayout_23;
    QCheckBox *checkBox_applyLorentzFilter;
    QGroupBox *groupBox_8;
    QVBoxLayout *verticalLayout_28;
    QHBoxLayout *horizontalLayout_25;
    QLabel *label_9;
    QDoubleSpinBox *doubleSpinBox_filterStrengthAlpha;
    QWidget *tab_AdvancedParamSettings;
    QVBoxLayout *verticalLayout_20;
    QGroupBox *groupBox_19;
    QHBoxLayout *horizontalLayout_19;
    QLabel *label_26;
    QGroupBox *groupBox_Running;
    QHBoxLayout *horizontalLayout_5;
    QTabWidget *tabWidget_Running;
    QWidget *tab_Start;
    QVBoxLayout *verticalLayout_9;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_21;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_Run;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *pushButton_SaveSettingsForRun;
    QSpacerItem *horizontalSpacer_15;
    QPushButton *pushButton_SaveMessageOutput;
    QPushButton *pushButton_CancelRun;
    QWidget *tab_batch;
    QVBoxLayout *verticalLayout_14;
    QGroupBox *groupBox_runBatch;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_Dummy;
    QGroupBox *groupBox_MessageOutput;
    QVBoxLayout *verticalLayout_8;
    QTextEdit *textEdit_MessagesOutput;
    QScrollArea *scrollArea_PreProcessorLayoutRightSide;
    QWidget *scrollAreaWidgetContents_ImageProcessing;
    QVBoxLayout *verticalLayout_5;
    QTabWidget *tabWidget_Projections;
    QWidget *tab_ProjectionViewer;
    QVBoxLayout *verticalLayout_7;
    QScrollArea *scrollArea_ImageViewer;
    QWidget *scrollAreaWidgetContents_ImageViewer;
    QGridLayout *gridLayout_2;
    QLabel *label_ImageView;
    QHBoxLayout *horizontalLayout_ProjectionSlice;
    QLabel *label_SliceNr;
    QSpinBox *spinBox_SliceNumber;
    QSlider *horizontalSlider_imageView;
    QGroupBox *groupBox_ImageOperations;
    QVBoxLayout *verticalLayout_25;
    QGroupBox *groupBox_2;
    QHBoxLayout *horizontalLayout_16;
    QVBoxLayout *verticalLayout_24;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label;
    QPushButton *pushButton_applyEqualize;
    QSpacerItem *horizontalSpacer_19;
    QGroupBox *groupBox_3;
    QHBoxLayout *horizontalLayout_21;
    QHBoxLayout *horizontalLayout_8;
    QLabel *label_ContrastSlope;
    QDoubleSpinBox *doubleSpinBox_ContrastSlope;
    QLabel *label_contrastOffset;
    QDoubleSpinBox *doubleSpinBox_ContrastOffset;
    QSpacerItem *horizontalSpacer_20;
    QLabel *label_ContrastApply;
    QPushButton *pushButton_ContrastApply;
    QSpacerItem *horizontalSpacer_21;
    QHBoxLayout *horizontalLayout_15;
    QPushButton *pushButton_UndoImageProcessing;
    QSpacerItem *horizontalSpacer_22;
    QProgressBar *progressBar_ImageProcessing;
    QGroupBox *groupBox_4;
    QVBoxLayout *verticalLayout_23;
    QHBoxLayout *horizontalLayout_14;
    QCheckBox *checkBox_EnableWindowSelection;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_22;
    QHBoxLayout *horizontalLayout_10;
    QLabel *label_xPosition;
    QSpinBox *spinBox_xWinPos;
    QSpacerItem *horizontalSpacer_23;
    QLabel *label_7;
    QSpinBox *spinBox_WinWidth;
    QSpacerItem *horizontalSpacer_25;
    QHBoxLayout *horizontalLayout_12;
    QLabel *label_6;
    QSpinBox *spinBox_yWinPos;
    QSpacerItem *horizontalSpacer_24;
    QLabel *label_8;
    QSpinBox *spinBox_WinHeight;
    QSpacerItem *horizontalSpacer_26;
    QWidget *tab_NOP;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuTools;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *ProjectionPreProcessorClass)
    {
        if (ProjectionPreProcessorClass->objectName().isEmpty())
            ProjectionPreProcessorClass->setObjectName(QString::fromUtf8("ProjectionPreProcessorClass"));
        ProjectionPreProcessorClass->resize(1504, 1291);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/ProjectionPreProcessor/Pre-Proc.png"), QSize(), QIcon::Normal, QIcon::Off);
        ProjectionPreProcessorClass->setWindowIcon(icon);
        actionOpen_Project = new QAction(ProjectionPreProcessorClass);
        actionOpen_Project->setObjectName(QString::fromUtf8("actionOpen_Project"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/ProjectionPreProcessor/Images/open-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_Project->setIcon(icon1);
        actionSave_Project_as = new QAction(ProjectionPreProcessorClass);
        actionSave_Project_as->setObjectName(QString::fromUtf8("actionSave_Project_as"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/ProjectionPreProcessor/Images/saveas.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_Project_as->setIcon(icon2);
        actionSave = new QAction(ProjectionPreProcessorClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/ProjectionPreProcessor/Images/save-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon3);
        actionExport_PFDK = new QAction(ProjectionPreProcessorClass);
        actionExport_PFDK->setObjectName(QString::fromUtf8("actionExport_PFDK"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/ProjectionPreProcessor/Images/exportpfdk.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExport_PFDK->setIcon(icon4);
        actionAbout = new QAction(ProjectionPreProcessorClass);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/ProjectionPreProcessor/Images/about.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon5);
        actionNew = new QAction(ProjectionPreProcessorClass);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/ProjectionPreProcessor/Images/new-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon6);
        actionExit = new QAction(ProjectionPreProcessorClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/ProjectionPreProcessor/Images/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionExit->setIcon(icon7);
        actionLorentz_Filter = new QAction(ProjectionPreProcessorClass);
        actionLorentz_Filter->setObjectName(QString::fromUtf8("actionLorentz_Filter"));
        actionLorentz_Filter->setEnabled(true);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/ProjectionPreProcessor/Images/Lorentz.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionLorentz_Filter->setIcon(icon8);
        centralWidget = new QWidget(ProjectionPreProcessorClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        centralWidget->setEnabled(true);
        horizontalLayout_24 = new QHBoxLayout(centralWidget);
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        scrollArea_PreProcessorLayoutLeftSide = new QScrollArea(centralWidget);
        scrollArea_PreProcessorLayoutLeftSide->setObjectName(QString::fromUtf8("scrollArea_PreProcessorLayoutLeftSide"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(scrollArea_PreProcessorLayoutLeftSide->sizePolicy().hasHeightForWidth());
        scrollArea_PreProcessorLayoutLeftSide->setSizePolicy(sizePolicy);
        scrollArea_PreProcessorLayoutLeftSide->setMinimumSize(QSize(500, 600));
        scrollArea_PreProcessorLayoutLeftSide->setWidgetResizable(true);
        scrollAreaWidgetContents_PreProcessorLeftSide = new QWidget();
        scrollAreaWidgetContents_PreProcessorLeftSide->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_PreProcessorLeftSide"));
        scrollAreaWidgetContents_PreProcessorLeftSide->setGeometry(QRect(0, 0, 738, 1179));
        verticalLayout_4 = new QVBoxLayout(scrollAreaWidgetContents_PreProcessorLeftSide);
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setContentsMargins(11, 11, 11, 11);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        tabWidget_ParameterSettings = new QTabWidget(scrollAreaWidgetContents_PreProcessorLeftSide);
        tabWidget_ParameterSettings->setObjectName(QString::fromUtf8("tabWidget_ParameterSettings"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(1);
        sizePolicy1.setHeightForWidth(tabWidget_ParameterSettings->sizePolicy().hasHeightForWidth());
        tabWidget_ParameterSettings->setSizePolicy(sizePolicy1);
        tabWidget_ParameterSettings->setMinimumSize(QSize(625, 720));
        tabWidget_ParameterSettings->setTabPosition(QTabWidget::South);
        tab_BasicParamSettings = new QWidget();
        tab_BasicParamSettings->setObjectName(QString::fromUtf8("tab_BasicParamSettings"));
        verticalLayout_3 = new QVBoxLayout(tab_BasicParamSettings);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox_ProjectSettings = new QGroupBox(tab_BasicParamSettings);
        groupBox_ProjectSettings->setObjectName(QString::fromUtf8("groupBox_ProjectSettings"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_ProjectSettings->sizePolicy().hasHeightForWidth());
        groupBox_ProjectSettings->setSizePolicy(sizePolicy2);
        groupBox_ProjectSettings->setMinimumSize(QSize(0, 0));
        horizontalLayout = new QHBoxLayout(groupBox_ProjectSettings);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label_Project = new QLabel(groupBox_ProjectSettings);
        label_Project->setObjectName(QString::fromUtf8("label_Project"));
        QSizePolicy sizePolicy3(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(label_Project->sizePolicy().hasHeightForWidth());
        label_Project->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(label_Project);

        lineEdit_projectName = new QLineEdit(groupBox_ProjectSettings);
        lineEdit_projectName->setObjectName(QString::fromUtf8("lineEdit_projectName"));
        sizePolicy3.setHeightForWidth(lineEdit_projectName->sizePolicy().hasHeightForWidth());
        lineEdit_projectName->setSizePolicy(sizePolicy3);
        lineEdit_projectName->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(lineEdit_projectName);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        label_CreatorOwner = new QLabel(groupBox_ProjectSettings);
        label_CreatorOwner->setObjectName(QString::fromUtf8("label_CreatorOwner"));
        sizePolicy3.setHeightForWidth(label_CreatorOwner->sizePolicy().hasHeightForWidth());
        label_CreatorOwner->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(label_CreatorOwner);

        lineEdit_CreatorOwner = new QLineEdit(groupBox_ProjectSettings);
        lineEdit_CreatorOwner->setObjectName(QString::fromUtf8("lineEdit_CreatorOwner"));
        sizePolicy3.setHeightForWidth(lineEdit_CreatorOwner->sizePolicy().hasHeightForWidth());
        lineEdit_CreatorOwner->setSizePolicy(sizePolicy3);
        lineEdit_CreatorOwner->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(lineEdit_CreatorOwner);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_5);

        label_Date = new QLabel(groupBox_ProjectSettings);
        label_Date->setObjectName(QString::fromUtf8("label_Date"));
        sizePolicy3.setHeightForWidth(label_Date->sizePolicy().hasHeightForWidth());
        label_Date->setSizePolicy(sizePolicy3);

        horizontalLayout->addWidget(label_Date);

        lineEdit_date = new QLineEdit(groupBox_ProjectSettings);
        lineEdit_date->setObjectName(QString::fromUtf8("lineEdit_date"));
        sizePolicy3.setHeightForWidth(lineEdit_date->sizePolicy().hasHeightForWidth());
        lineEdit_date->setSizePolicy(sizePolicy3);
        lineEdit_date->setMaximumSize(QSize(120, 16777215));

        horizontalLayout->addWidget(lineEdit_date);


        verticalLayout_3->addWidget(groupBox_ProjectSettings);

        tabWidget_IOSettings = new QTabWidget(tab_BasicParamSettings);
        tabWidget_IOSettings->setObjectName(QString::fromUtf8("tabWidget_IOSettings"));
        QSizePolicy sizePolicy4(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(tabWidget_IOSettings->sizePolicy().hasHeightForWidth());
        tabWidget_IOSettings->setSizePolicy(sizePolicy4);
        tabWidget_IOSettings->setMinimumSize(QSize(550, 280));
        tab_IOInput = new QWidget();
        tab_IOInput->setObjectName(QString::fromUtf8("tab_IOInput"));
        verticalLayout_2 = new QVBoxLayout(tab_IOInput);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_IOInput = new QGroupBox(tab_IOInput);
        groupBox_IOInput->setObjectName(QString::fromUtf8("groupBox_IOInput"));
        sizePolicy3.setHeightForWidth(groupBox_IOInput->sizePolicy().hasHeightForWidth());
        groupBox_IOInput->setSizePolicy(sizePolicy3);
        groupBox_IOInput->setMinimumSize(QSize(0, 193));
        verticalLayout_6 = new QVBoxLayout(groupBox_IOInput);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        groupBox_FileSelection = new QGroupBox(groupBox_IOInput);
        groupBox_FileSelection->setObjectName(QString::fromUtf8("groupBox_FileSelection"));
        sizePolicy4.setHeightForWidth(groupBox_FileSelection->sizePolicy().hasHeightForWidth());
        groupBox_FileSelection->setSizePolicy(sizePolicy4);
        groupBox_FileSelection->setMinimumSize(QSize(0, 0));
        horizontalLayout_2 = new QHBoxLayout(groupBox_FileSelection);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label_InputDir = new QLabel(groupBox_FileSelection);
        label_InputDir->setObjectName(QString::fromUtf8("label_InputDir"));
        sizePolicy3.setHeightForWidth(label_InputDir->sizePolicy().hasHeightForWidth());
        label_InputDir->setSizePolicy(sizePolicy3);

        horizontalLayout_2->addWidget(label_InputDir);

        lineEdit_InputDir = new QLineEdit(groupBox_FileSelection);
        lineEdit_InputDir->setObjectName(QString::fromUtf8("lineEdit_InputDir"));
        lineEdit_InputDir->setEnabled(false);
        sizePolicy3.setHeightForWidth(lineEdit_InputDir->sizePolicy().hasHeightForWidth());
        lineEdit_InputDir->setSizePolicy(sizePolicy3);
        lineEdit_InputDir->setMinimumSize(QSize(0, 21));

        horizontalLayout_2->addWidget(lineEdit_InputDir);

        pushButton_SelInputDir = new QPushButton(groupBox_FileSelection);
        pushButton_SelInputDir->setObjectName(QString::fromUtf8("pushButton_SelInputDir"));
        sizePolicy3.setHeightForWidth(pushButton_SelInputDir->sizePolicy().hasHeightForWidth());
        pushButton_SelInputDir->setSizePolicy(sizePolicy3);
        pushButton_SelInputDir->setMinimumSize(QSize(0, 21));

        horizontalLayout_2->addWidget(pushButton_SelInputDir);

        label_InputFilePattern = new QLabel(groupBox_FileSelection);
        label_InputFilePattern->setObjectName(QString::fromUtf8("label_InputFilePattern"));

        horizontalLayout_2->addWidget(label_InputFilePattern);

        lineEdit_InputFilePattern = new QLineEdit(groupBox_FileSelection);
        lineEdit_InputFilePattern->setObjectName(QString::fromUtf8("lineEdit_InputFilePattern"));
        lineEdit_InputFilePattern->setEnabled(false);
        lineEdit_InputFilePattern->setMinimumSize(QSize(0, 21));

        horizontalLayout_2->addWidget(lineEdit_InputFilePattern);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        label_FileType = new QLabel(groupBox_FileSelection);
        label_FileType->setObjectName(QString::fromUtf8("label_FileType"));
        sizePolicy3.setHeightForWidth(label_FileType->sizePolicy().hasHeightForWidth());
        label_FileType->setSizePolicy(sizePolicy3);
        label_FileType->setMinimumSize(QSize(0, 21));

        horizontalLayout_2->addWidget(label_FileType);

        comboBox_SelFileType = new QComboBox(groupBox_FileSelection);
        comboBox_SelFileType->addItem(QString());
        comboBox_SelFileType->setObjectName(QString::fromUtf8("comboBox_SelFileType"));
        sizePolicy3.setHeightForWidth(comboBox_SelFileType->sizePolicy().hasHeightForWidth());
        comboBox_SelFileType->setSizePolicy(sizePolicy3);
        comboBox_SelFileType->setMinimumSize(QSize(0, 21));
        comboBox_SelFileType->setMaxVisibleItems(7);

        horizontalLayout_2->addWidget(comboBox_SelFileType);


        verticalLayout_6->addWidget(groupBox_FileSelection);

        line_inputIO = new QFrame(groupBox_IOInput);
        line_inputIO->setObjectName(QString::fromUtf8("line_inputIO"));
        sizePolicy4.setHeightForWidth(line_inputIO->sizePolicy().hasHeightForWidth());
        line_inputIO->setSizePolicy(sizePolicy4);
        line_inputIO->setMinimumSize(QSize(0, 2));
        line_inputIO->setFrameShape(QFrame::HLine);
        line_inputIO->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_inputIO);

        groupBox_projectionParam = new QGroupBox(groupBox_IOInput);
        groupBox_projectionParam->setObjectName(QString::fromUtf8("groupBox_projectionParam"));
        QSizePolicy sizePolicy5(QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(groupBox_projectionParam->sizePolicy().hasHeightForWidth());
        groupBox_projectionParam->setSizePolicy(sizePolicy5);
        groupBox_projectionParam->setMinimumSize(QSize(0, 57));
        gridLayout = new QGridLayout(groupBox_projectionParam);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_InputType = new QLabel(groupBox_projectionParam);
        label_InputType->setObjectName(QString::fromUtf8("label_InputType"));

        gridLayout->addWidget(label_InputType, 0, 9, 1, 1);

        spinBox_ProjectionHeight = new QSpinBox(groupBox_projectionParam);
        spinBox_ProjectionHeight->setObjectName(QString::fromUtf8("spinBox_ProjectionHeight"));
        spinBox_ProjectionHeight->setEnabled(false);
        sizePolicy4.setHeightForWidth(spinBox_ProjectionHeight->sizePolicy().hasHeightForWidth());
        spinBox_ProjectionHeight->setSizePolicy(sizePolicy4);
        spinBox_ProjectionHeight->setMinimumSize(QSize(0, 21));
        spinBox_ProjectionHeight->setMaximum(10000);

        gridLayout->addWidget(spinBox_ProjectionHeight, 0, 4, 1, 1);

        spinBox_ProjectionWidth = new QSpinBox(groupBox_projectionParam);
        spinBox_ProjectionWidth->setObjectName(QString::fromUtf8("spinBox_ProjectionWidth"));
        spinBox_ProjectionWidth->setEnabled(false);
        sizePolicy4.setHeightForWidth(spinBox_ProjectionWidth->sizePolicy().hasHeightForWidth());
        spinBox_ProjectionWidth->setSizePolicy(sizePolicy4);
        spinBox_ProjectionWidth->setMinimumSize(QSize(0, 21));
        spinBox_ProjectionWidth->setMaximum(10000);

        gridLayout->addWidget(spinBox_ProjectionWidth, 0, 1, 1, 1);

        label_ProjectionHeight = new QLabel(groupBox_projectionParam);
        label_ProjectionHeight->setObjectName(QString::fromUtf8("label_ProjectionHeight"));
        QSizePolicy sizePolicy6(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(label_ProjectionHeight->sizePolicy().hasHeightForWidth());
        label_ProjectionHeight->setSizePolicy(sizePolicy6);
        label_ProjectionHeight->setMinimumSize(QSize(0, 21));

        gridLayout->addWidget(label_ProjectionHeight, 0, 3, 1, 1);

        label_ProjectionWidth = new QLabel(groupBox_projectionParam);
        label_ProjectionWidth->setObjectName(QString::fromUtf8("label_ProjectionWidth"));
        sizePolicy6.setHeightForWidth(label_ProjectionWidth->sizePolicy().hasHeightForWidth());
        label_ProjectionWidth->setSizePolicy(sizePolicy6);
        label_ProjectionWidth->setMinimumSize(QSize(0, 21));

        gridLayout->addWidget(label_ProjectionWidth, 0, 0, 1, 1);

        label_NumberProjections = new QLabel(groupBox_projectionParam);
        label_NumberProjections->setObjectName(QString::fromUtf8("label_NumberProjections"));
        sizePolicy6.setHeightForWidth(label_NumberProjections->sizePolicy().hasHeightForWidth());
        label_NumberProjections->setSizePolicy(sizePolicy6);
        label_NumberProjections->setMinimumSize(QSize(0, 21));

        gridLayout->addWidget(label_NumberProjections, 0, 6, 1, 1);

        spinBox_NumberProjections = new QSpinBox(groupBox_projectionParam);
        spinBox_NumberProjections->setObjectName(QString::fromUtf8("spinBox_NumberProjections"));
        spinBox_NumberProjections->setEnabled(true);
        sizePolicy4.setHeightForWidth(spinBox_NumberProjections->sizePolicy().hasHeightForWidth());
        spinBox_NumberProjections->setSizePolicy(sizePolicy4);
        spinBox_NumberProjections->setMinimumSize(QSize(0, 21));
        spinBox_NumberProjections->setMaximum(10000);

        gridLayout->addWidget(spinBox_NumberProjections, 0, 7, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 2, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 5, 1, 1);

        horizontalSpacer_13 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_13, 0, 8, 1, 1);

        label_CVDataType = new QLabel(groupBox_projectionParam);
        label_CVDataType->setObjectName(QString::fromUtf8("label_CVDataType"));
        label_CVDataType->setEnabled(false);
        label_CVDataType->setMinimumSize(QSize(40, 0));
        label_CVDataType->setFrameShape(QFrame::StyledPanel);

        gridLayout->addWidget(label_CVDataType, 0, 10, 1, 1);


        verticalLayout_6->addWidget(groupBox_projectionParam);

        groupBox_LoadInputData = new QGroupBox(groupBox_IOInput);
        groupBox_LoadInputData->setObjectName(QString::fromUtf8("groupBox_LoadInputData"));
        QSizePolicy sizePolicy7(QSizePolicy::MinimumExpanding, QSizePolicy::Preferred);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(groupBox_LoadInputData->sizePolicy().hasHeightForWidth());
        groupBox_LoadInputData->setSizePolicy(sizePolicy7);
        groupBox_LoadInputData->setMinimumSize(QSize(0, 80));
        verticalLayout_26 = new QVBoxLayout(groupBox_LoadInputData);
        verticalLayout_26->setSpacing(6);
        verticalLayout_26->setContentsMargins(11, 11, 11, 11);
        verticalLayout_26->setObjectName(QString::fromUtf8("verticalLayout_26"));
        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        checkBox_TileMemory = new QCheckBox(groupBox_LoadInputData);
        checkBox_TileMemory->setObjectName(QString::fromUtf8("checkBox_TileMemory"));
        checkBox_TileMemory->setMinimumSize(QSize(0, 23));
        checkBox_TileMemory->setLayoutDirection(Qt::RightToLeft);
        checkBox_TileMemory->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 170, 0);"));

        horizontalLayout_20->addWidget(checkBox_TileMemory);

        label_3 = new QLabel(groupBox_LoadInputData);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_20->addWidget(label_3);

        line = new QFrame(groupBox_LoadInputData);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);

        horizontalLayout_20->addWidget(line);

        label_2 = new QLabel(groupBox_LoadInputData);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_20->addWidget(label_2);

        label_4 = new QLabel(groupBox_LoadInputData);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        label_4->setFont(font);
        label_4->setStyleSheet(QString::fromUtf8("color: rgb(0, 170, 0);"));

        horizontalLayout_20->addWidget(label_4);

        horizontalSlider_MemSavMinMax = new QSlider(groupBox_LoadInputData);
        horizontalSlider_MemSavMinMax->setObjectName(QString::fromUtf8("horizontalSlider_MemSavMinMax"));
        horizontalSlider_MemSavMinMax->setEnabled(false);
        horizontalSlider_MemSavMinMax->setMinimum(1);
        horizontalSlider_MemSavMinMax->setMaximum(10);
        horizontalSlider_MemSavMinMax->setValue(2);
        horizontalSlider_MemSavMinMax->setOrientation(Qt::Horizontal);
        horizontalSlider_MemSavMinMax->setInvertedAppearance(false);
        horizontalSlider_MemSavMinMax->setInvertedControls(true);
        horizontalSlider_MemSavMinMax->setTickPosition(QSlider::TicksBelow);
        horizontalSlider_MemSavMinMax->setTickInterval(1);

        horizontalLayout_20->addWidget(horizontalSlider_MemSavMinMax);

        label_5 = new QLabel(groupBox_LoadInputData);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setFont(font);
        label_5->setStyleSheet(QString::fromUtf8("color: rgb(255, 0, 0);"));

        horizontalLayout_20->addWidget(label_5);

        spinBox_MemMultFac = new QSpinBox(groupBox_LoadInputData);
        spinBox_MemMultFac->setObjectName(QString::fromUtf8("spinBox_MemMultFac"));
        spinBox_MemMultFac->setEnabled(false);
        spinBox_MemMultFac->setMinimum(1);
        spinBox_MemMultFac->setMaximum(10);
        spinBox_MemMultFac->setValue(2);

        horizontalLayout_20->addWidget(spinBox_MemMultFac);

        horizontalSpacer_28 = new QSpacerItem(80, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_20->addItem(horizontalSpacer_28);


        verticalLayout_26->addLayout(horizontalLayout_20);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        pushButton_LoadInputData = new QPushButton(groupBox_LoadInputData);
        pushButton_LoadInputData->setObjectName(QString::fromUtf8("pushButton_LoadInputData"));
        sizePolicy4.setHeightForWidth(pushButton_LoadInputData->sizePolicy().hasHeightForWidth());
        pushButton_LoadInputData->setSizePolicy(sizePolicy4);
        pushButton_LoadInputData->setMinimumSize(QSize(0, 23));

        horizontalLayout_22->addWidget(pushButton_LoadInputData);

        progressBar_LoadData = new QProgressBar(groupBox_LoadInputData);
        progressBar_LoadData->setObjectName(QString::fromUtf8("progressBar_LoadData"));
        QSizePolicy sizePolicy8(QSizePolicy::MinimumExpanding, QSizePolicy::Fixed);
        sizePolicy8.setHorizontalStretch(2);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(progressBar_LoadData->sizePolicy().hasHeightForWidth());
        progressBar_LoadData->setSizePolicy(sizePolicy8);
        progressBar_LoadData->setMaximum(10000);
        progressBar_LoadData->setValue(0);

        horizontalLayout_22->addWidget(progressBar_LoadData);

        pushButton_LoadDataInterrupt = new QPushButton(groupBox_LoadInputData);
        pushButton_LoadDataInterrupt->setObjectName(QString::fromUtf8("pushButton_LoadDataInterrupt"));

        horizontalLayout_22->addWidget(pushButton_LoadDataInterrupt);

        horizontalSpacer_32 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_32);

        label_RotationDirection = new QLabel(groupBox_LoadInputData);
        label_RotationDirection->setObjectName(QString::fromUtf8("label_RotationDirection"));

        horizontalLayout_22->addWidget(label_RotationDirection);

        comboBox_ClockWise = new QComboBox(groupBox_LoadInputData);
        comboBox_ClockWise->addItem(QString());
        comboBox_ClockWise->addItem(QString());
        comboBox_ClockWise->setObjectName(QString::fromUtf8("comboBox_ClockWise"));

        horizontalLayout_22->addWidget(comboBox_ClockWise);


        verticalLayout_26->addLayout(horizontalLayout_22);


        verticalLayout_6->addWidget(groupBox_LoadInputData);


        verticalLayout_2->addWidget(groupBox_IOInput);

        tabWidget_IOSettings->addTab(tab_IOInput, QString());
        tab_IOOutput = new QWidget();
        tab_IOOutput->setObjectName(QString::fromUtf8("tab_IOOutput"));
        verticalLayout_13 = new QVBoxLayout(tab_IOOutput);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        groupBox_IOOutput = new QGroupBox(tab_IOOutput);
        groupBox_IOOutput->setObjectName(QString::fromUtf8("groupBox_IOOutput"));
        sizePolicy3.setHeightForWidth(groupBox_IOOutput->sizePolicy().hasHeightForWidth());
        groupBox_IOOutput->setSizePolicy(sizePolicy3);
        groupBox_IOOutput->setMinimumSize(QSize(0, 0));
        verticalLayout_12 = new QVBoxLayout(groupBox_IOOutput);
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        groupBox_FileDirSelection = new QGroupBox(groupBox_IOOutput);
        groupBox_FileDirSelection->setObjectName(QString::fromUtf8("groupBox_FileDirSelection"));
        sizePolicy4.setHeightForWidth(groupBox_FileDirSelection->sizePolicy().hasHeightForWidth());
        groupBox_FileDirSelection->setSizePolicy(sizePolicy4);
        groupBox_FileDirSelection->setMinimumSize(QSize(0, 0));
        gridLayout_4 = new QGridLayout(groupBox_FileDirSelection);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        label_22 = new QLabel(groupBox_FileDirSelection);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        sizePolicy3.setHeightForWidth(label_22->sizePolicy().hasHeightForWidth());
        label_22->setSizePolicy(sizePolicy3);

        gridLayout_4->addWidget(label_22, 0, 0, 1, 1);

        lineEdit_OutPutDir = new QLineEdit(groupBox_FileDirSelection);
        lineEdit_OutPutDir->setObjectName(QString::fromUtf8("lineEdit_OutPutDir"));
        lineEdit_OutPutDir->setEnabled(false);
        QSizePolicy sizePolicy9(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy9.setHorizontalStretch(20);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(lineEdit_OutPutDir->sizePolicy().hasHeightForWidth());
        lineEdit_OutPutDir->setSizePolicy(sizePolicy9);

        gridLayout_4->addWidget(lineEdit_OutPutDir, 0, 1, 1, 1);

        pushButton_SelectOutputDir = new QPushButton(groupBox_FileDirSelection);
        pushButton_SelectOutputDir->setObjectName(QString::fromUtf8("pushButton_SelectOutputDir"));
        sizePolicy3.setHeightForWidth(pushButton_SelectOutputDir->sizePolicy().hasHeightForWidth());
        pushButton_SelectOutputDir->setSizePolicy(sizePolicy3);
        pushButton_SelectOutputDir->setMinimumSize(QSize(80, 0));
        pushButton_SelectOutputDir->setMaximumSize(QSize(80, 16777215));

        gridLayout_4->addWidget(pushButton_SelectOutputDir, 0, 2, 1, 2);

        label_RawOutPattern = new QLabel(groupBox_FileDirSelection);
        label_RawOutPattern->setObjectName(QString::fromUtf8("label_RawOutPattern"));

        gridLayout_4->addWidget(label_RawOutPattern, 1, 0, 1, 1);

        lineEdit_OutRawPattern = new QLineEdit(groupBox_FileDirSelection);
        lineEdit_OutRawPattern->setObjectName(QString::fromUtf8("lineEdit_OutRawPattern"));
        lineEdit_OutRawPattern->setEnabled(false);
        QSizePolicy sizePolicy10(QSizePolicy::Maximum, QSizePolicy::Fixed);
        sizePolicy10.setHorizontalStretch(2);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(lineEdit_OutRawPattern->sizePolicy().hasHeightForWidth());
        lineEdit_OutRawPattern->setSizePolicy(sizePolicy10);
        lineEdit_OutRawPattern->setMinimumSize(QSize(350, 0));

        gridLayout_4->addWidget(lineEdit_OutRawPattern, 1, 1, 1, 2);

        label_OutputFileType = new QLabel(groupBox_FileDirSelection);
        label_OutputFileType->setObjectName(QString::fromUtf8("label_OutputFileType"));
        sizePolicy3.setHeightForWidth(label_OutputFileType->sizePolicy().hasHeightForWidth());
        label_OutputFileType->setSizePolicy(sizePolicy3);

        gridLayout_4->addWidget(label_OutputFileType, 2, 0, 1, 1);

        comboBox_OutputFileType = new QComboBox(groupBox_FileDirSelection);
        comboBox_OutputFileType->addItem(QString());
        comboBox_OutputFileType->addItem(QString());
        comboBox_OutputFileType->setObjectName(QString::fromUtf8("comboBox_OutputFileType"));
        comboBox_OutputFileType->setEnabled(false);
        QSizePolicy sizePolicy11(QSizePolicy::Maximum, QSizePolicy::MinimumExpanding);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(comboBox_OutputFileType->sizePolicy().hasHeightForWidth());
        comboBox_OutputFileType->setSizePolicy(sizePolicy11);
        comboBox_OutputFileType->setMinimumSize(QSize(170, 0));
        comboBox_OutputFileType->setMaximumSize(QSize(170, 16777215));
        comboBox_OutputFileType->setMaxVisibleItems(7);

        gridLayout_4->addWidget(comboBox_OutputFileType, 2, 1, 1, 1);


        verticalLayout_12->addWidget(groupBox_FileDirSelection);

        groupBox_SaveData = new QGroupBox(groupBox_IOOutput);
        groupBox_SaveData->setObjectName(QString::fromUtf8("groupBox_SaveData"));
        sizePolicy4.setHeightForWidth(groupBox_SaveData->sizePolicy().hasHeightForWidth());
        groupBox_SaveData->setSizePolicy(sizePolicy4);
        groupBox_SaveData->setMinimumSize(QSize(0, 0));
        horizontalLayout_13 = new QHBoxLayout(groupBox_SaveData);
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        pushButton_SaveDataStart = new QPushButton(groupBox_SaveData);
        pushButton_SaveDataStart->setObjectName(QString::fromUtf8("pushButton_SaveDataStart"));
        pushButton_SaveDataStart->setEnabled(false);
        sizePolicy4.setHeightForWidth(pushButton_SaveDataStart->sizePolicy().hasHeightForWidth());
        pushButton_SaveDataStart->setSizePolicy(sizePolicy4);
        pushButton_SaveDataStart->setMinimumSize(QSize(0, 0));

        horizontalLayout_13->addWidget(pushButton_SaveDataStart);

        progressBar_Savedata = new QProgressBar(groupBox_SaveData);
        progressBar_Savedata->setObjectName(QString::fromUtf8("progressBar_Savedata"));
        sizePolicy8.setHeightForWidth(progressBar_Savedata->sizePolicy().hasHeightForWidth());
        progressBar_Savedata->setSizePolicy(sizePolicy8);
        progressBar_Savedata->setMaximum(10000);
        progressBar_Savedata->setValue(0);

        horizontalLayout_13->addWidget(progressBar_Savedata);


        verticalLayout_12->addWidget(groupBox_SaveData);


        verticalLayout_13->addWidget(groupBox_IOOutput);

        tabWidget_IOSettings->addTab(tab_IOOutput, QString());

        verticalLayout_3->addWidget(tabWidget_IOSettings);

        groupBox_MethodSelection = new QGroupBox(tab_BasicParamSettings);
        groupBox_MethodSelection->setObjectName(QString::fromUtf8("groupBox_MethodSelection"));
        sizePolicy4.setHeightForWidth(groupBox_MethodSelection->sizePolicy().hasHeightForWidth());
        groupBox_MethodSelection->setSizePolicy(sizePolicy4);
        groupBox_MethodSelection->setMinimumSize(QSize(0, 50));
        horizontalLayout_3 = new QHBoxLayout(groupBox_MethodSelection);
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        checkBox_Normalize = new QCheckBox(groupBox_MethodSelection);
        checkBox_Normalize->setObjectName(QString::fromUtf8("checkBox_Normalize"));
        checkBox_Normalize->setEnabled(false);
        sizePolicy3.setHeightForWidth(checkBox_Normalize->sizePolicy().hasHeightForWidth());
        checkBox_Normalize->setSizePolicy(sizePolicy3);
        checkBox_Normalize->setChecked(true);

        horizontalLayout_3->addWidget(checkBox_Normalize);

        checkBox_OutlierSuppression = new QCheckBox(groupBox_MethodSelection);
        checkBox_OutlierSuppression->setObjectName(QString::fromUtf8("checkBox_OutlierSuppression"));
        checkBox_OutlierSuppression->setEnabled(false);
        sizePolicy3.setHeightForWidth(checkBox_OutlierSuppression->sizePolicy().hasHeightForWidth());
        checkBox_OutlierSuppression->setSizePolicy(sizePolicy3);
        checkBox_OutlierSuppression->setChecked(true);

        horizontalLayout_3->addWidget(checkBox_OutlierSuppression);

        checkBox_BHC = new QCheckBox(groupBox_MethodSelection);
        checkBox_BHC->setObjectName(QString::fromUtf8("checkBox_BHC"));
        sizePolicy3.setHeightForWidth(checkBox_BHC->sizePolicy().hasHeightForWidth());
        checkBox_BHC->setSizePolicy(sizePolicy3);

        horizontalLayout_3->addWidget(checkBox_BHC);

        checkBox_StripeReduction = new QCheckBox(groupBox_MethodSelection);
        checkBox_StripeReduction->setObjectName(QString::fromUtf8("checkBox_StripeReduction"));
        checkBox_StripeReduction->setEnabled(false);
        sizePolicy3.setHeightForWidth(checkBox_StripeReduction->sizePolicy().hasHeightForWidth());
        checkBox_StripeReduction->setSizePolicy(sizePolicy3);

        horizontalLayout_3->addWidget(checkBox_StripeReduction);


        verticalLayout_3->addWidget(groupBox_MethodSelection);

        toolBox_ProcessingMethods = new QToolBox(tab_BasicParamSettings);
        toolBox_ProcessingMethods->setObjectName(QString::fromUtf8("toolBox_ProcessingMethods"));
        toolBox_ProcessingMethods->setEnabled(true);
        sizePolicy3.setHeightForWidth(toolBox_ProcessingMethods->sizePolicy().hasHeightForWidth());
        toolBox_ProcessingMethods->setSizePolicy(sizePolicy3);
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        toolBox_ProcessingMethods->setFont(font1);
        toolBox_ProcessingMethods->setFrameShape(QFrame::StyledPanel);
        toolBox_ProcessingMethods->setFrameShadow(QFrame::Sunken);
        page_MethodNormalization = new QWidget();
        page_MethodNormalization->setObjectName(QString::fromUtf8("page_MethodNormalization"));
        page_MethodNormalization->setGeometry(QRect(0, 0, 677, 317));
        QFont font2;
        font2.setBold(false);
        font2.setWeight(50);
        page_MethodNormalization->setFont(font2);
        verticalLayout_19 = new QVBoxLayout(page_MethodNormalization);
        verticalLayout_19->setSpacing(6);
        verticalLayout_19->setContentsMargins(11, 11, 11, 11);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        groupBox_NormalizationOption = new QGroupBox(page_MethodNormalization);
        groupBox_NormalizationOption->setObjectName(QString::fromUtf8("groupBox_NormalizationOption"));
        verticalLayout_29 = new QVBoxLayout(groupBox_NormalizationOption);
        verticalLayout_29->setSpacing(6);
        verticalLayout_29->setContentsMargins(11, 11, 11, 11);
        verticalLayout_29->setObjectName(QString::fromUtf8("verticalLayout_29"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        radioButton_UseFlatFieldNormalization = new QRadioButton(groupBox_NormalizationOption);
        radioButton_UseFlatFieldNormalization->setObjectName(QString::fromUtf8("radioButton_UseFlatFieldNormalization"));
        radioButton_UseFlatFieldNormalization->setChecked(true);

        horizontalLayout_6->addWidget(radioButton_UseFlatFieldNormalization);

        radioButton_UseFlatWindowNormalization = new QRadioButton(groupBox_NormalizationOption);
        radioButton_UseFlatWindowNormalization->setObjectName(QString::fromUtf8("radioButton_UseFlatWindowNormalization"));

        horizontalLayout_6->addWidget(radioButton_UseFlatWindowNormalization);

        horizontalSpacer_30 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_30);

        horizontalSpacer_29 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_29);

        checkBox_NoLogarithm = new QCheckBox(groupBox_NormalizationOption);
        checkBox_NoLogarithm->setObjectName(QString::fromUtf8("checkBox_NoLogarithm"));

        horizontalLayout_6->addWidget(checkBox_NoLogarithm);


        verticalLayout_29->addLayout(horizontalLayout_6);

        line_3 = new QFrame(groupBox_NormalizationOption);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_29->addWidget(line_3);

        checkBox_useDarkFlatCorrected = new QCheckBox(groupBox_NormalizationOption);
        checkBox_useDarkFlatCorrected->setObjectName(QString::fromUtf8("checkBox_useDarkFlatCorrected"));

        verticalLayout_29->addWidget(checkBox_useDarkFlatCorrected);

        line_2 = new QFrame(groupBox_NormalizationOption);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        QSizePolicy sizePolicy12(QSizePolicy::Fixed, QSizePolicy::Minimum);
        sizePolicy12.setHorizontalStretch(0);
        sizePolicy12.setVerticalStretch(0);
        sizePolicy12.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy12);
        line_2->setFrameShape(QFrame::VLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_29->addWidget(line_2);


        verticalLayout_19->addWidget(groupBox_NormalizationOption);

        groupBox_Normalization = new QGroupBox(page_MethodNormalization);
        groupBox_Normalization->setObjectName(QString::fromUtf8("groupBox_Normalization"));
        sizePolicy3.setHeightForWidth(groupBox_Normalization->sizePolicy().hasHeightForWidth());
        groupBox_Normalization->setSizePolicy(sizePolicy3);
        groupBox_Normalization->setMinimumSize(QSize(400, 200));
        verticalLayout_10 = new QVBoxLayout(groupBox_Normalization);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        gridLayout_DarkFlatFiled = new QGridLayout();
        gridLayout_DarkFlatFiled->setSpacing(6);
        gridLayout_DarkFlatFiled->setObjectName(QString::fromUtf8("gridLayout_DarkFlatFiled"));
        label_FlatFieldImage = new QLabel(groupBox_Normalization);
        label_FlatFieldImage->setObjectName(QString::fromUtf8("label_FlatFieldImage"));
        sizePolicy6.setHeightForWidth(label_FlatFieldImage->sizePolicy().hasHeightForWidth());
        label_FlatFieldImage->setSizePolicy(sizePolicy6);

        gridLayout_DarkFlatFiled->addWidget(label_FlatFieldImage, 0, 0, 1, 1);

        lineEdit_FlatFieldImage = new QLineEdit(groupBox_Normalization);
        lineEdit_FlatFieldImage->setObjectName(QString::fromUtf8("lineEdit_FlatFieldImage"));
        QSizePolicy sizePolicy13(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy13.setHorizontalStretch(1);
        sizePolicy13.setVerticalStretch(0);
        sizePolicy13.setHeightForWidth(lineEdit_FlatFieldImage->sizePolicy().hasHeightForWidth());
        lineEdit_FlatFieldImage->setSizePolicy(sizePolicy13);
        lineEdit_FlatFieldImage->setMinimumSize(QSize(0, 0));

        gridLayout_DarkFlatFiled->addWidget(lineEdit_FlatFieldImage, 0, 1, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_DarkFlatFiled->addItem(horizontalSpacer_8, 0, 2, 1, 1);

        pushButton_SelectFlat = new QPushButton(groupBox_Normalization);
        pushButton_SelectFlat->setObjectName(QString::fromUtf8("pushButton_SelectFlat"));
        sizePolicy6.setHeightForWidth(pushButton_SelectFlat->sizePolicy().hasHeightForWidth());
        pushButton_SelectFlat->setSizePolicy(sizePolicy6);
        QFont font3;
        font3.setBold(false);
        font3.setItalic(false);
        font3.setWeight(50);
        pushButton_SelectFlat->setFont(font3);

        gridLayout_DarkFlatFiled->addWidget(pushButton_SelectFlat, 0, 3, 1, 1);

        label_DarkFieldImage = new QLabel(groupBox_Normalization);
        label_DarkFieldImage->setObjectName(QString::fromUtf8("label_DarkFieldImage"));
        sizePolicy6.setHeightForWidth(label_DarkFieldImage->sizePolicy().hasHeightForWidth());
        label_DarkFieldImage->setSizePolicy(sizePolicy6);

        gridLayout_DarkFlatFiled->addWidget(label_DarkFieldImage, 1, 0, 1, 1);

        lineEdit_DarkFieldImage = new QLineEdit(groupBox_Normalization);
        lineEdit_DarkFieldImage->setObjectName(QString::fromUtf8("lineEdit_DarkFieldImage"));
        sizePolicy13.setHeightForWidth(lineEdit_DarkFieldImage->sizePolicy().hasHeightForWidth());
        lineEdit_DarkFieldImage->setSizePolicy(sizePolicy13);
        lineEdit_DarkFieldImage->setMinimumSize(QSize(0, 0));

        gridLayout_DarkFlatFiled->addWidget(lineEdit_DarkFieldImage, 1, 1, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(18, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_DarkFlatFiled->addItem(horizontalSpacer_9, 1, 2, 1, 1);

        pushButton_SelectDark = new QPushButton(groupBox_Normalization);
        pushButton_SelectDark->setObjectName(QString::fromUtf8("pushButton_SelectDark"));
        sizePolicy6.setHeightForWidth(pushButton_SelectDark->sizePolicy().hasHeightForWidth());
        pushButton_SelectDark->setSizePolicy(sizePolicy6);
        pushButton_SelectDark->setFont(font3);

        gridLayout_DarkFlatFiled->addWidget(pushButton_SelectDark, 1, 3, 1, 1);


        verticalLayout_10->addLayout(gridLayout_DarkFlatFiled);

        horizontalLayout_NormWin = new QHBoxLayout();
        horizontalLayout_NormWin->setSpacing(6);
        horizontalLayout_NormWin->setObjectName(QString::fromUtf8("horizontalLayout_NormWin"));
        groupBox_NormWin = new QGroupBox(groupBox_Normalization);
        groupBox_NormWin->setObjectName(QString::fromUtf8("groupBox_NormWin"));
        sizePolicy5.setHeightForWidth(groupBox_NormWin->sizePolicy().hasHeightForWidth());
        groupBox_NormWin->setSizePolicy(sizePolicy5);
        groupBox_NormWin->setMinimumSize(QSize(0, 0));
        horizontalLayout_9 = new QHBoxLayout(groupBox_NormWin);
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        formLayout_WinPos = new QFormLayout();
        formLayout_WinPos->setSpacing(6);
        formLayout_WinPos->setObjectName(QString::fromUtf8("formLayout_WinPos"));
        formLayout_WinPos->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        label_NormWinXPos = new QLabel(groupBox_NormWin);
        label_NormWinXPos->setObjectName(QString::fromUtf8("label_NormWinXPos"));

        formLayout_WinPos->setWidget(0, QFormLayout::LabelRole, label_NormWinXPos);

        spinBox_NormWinXPos = new QSpinBox(groupBox_NormWin);
        spinBox_NormWinXPos->setObjectName(QString::fromUtf8("spinBox_NormWinXPos"));
        spinBox_NormWinXPos->setMaximum(9000);

        formLayout_WinPos->setWidget(0, QFormLayout::FieldRole, spinBox_NormWinXPos);

        spinBox_NormWinYPos = new QSpinBox(groupBox_NormWin);
        spinBox_NormWinYPos->setObjectName(QString::fromUtf8("spinBox_NormWinYPos"));
        spinBox_NormWinYPos->setMaximum(9000);

        formLayout_WinPos->setWidget(1, QFormLayout::FieldRole, spinBox_NormWinYPos);

        label_NormWinYPos = new QLabel(groupBox_NormWin);
        label_NormWinYPos->setObjectName(QString::fromUtf8("label_NormWinYPos"));

        formLayout_WinPos->setWidget(1, QFormLayout::LabelRole, label_NormWinYPos);


        horizontalLayout_9->addLayout(formLayout_WinPos);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_7);

        formLayout_NormWinSize = new QFormLayout();
        formLayout_NormWinSize->setSpacing(6);
        formLayout_NormWinSize->setObjectName(QString::fromUtf8("formLayout_NormWinSize"));
        formLayout_NormWinSize->setFormAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBox_NormWinWidth = new QSpinBox(groupBox_NormWin);
        spinBox_NormWinWidth->setObjectName(QString::fromUtf8("spinBox_NormWinWidth"));
        spinBox_NormWinWidth->setMaximum(9000);

        formLayout_NormWinSize->setWidget(0, QFormLayout::FieldRole, spinBox_NormWinWidth);

        label_NormWinHeight = new QLabel(groupBox_NormWin);
        label_NormWinHeight->setObjectName(QString::fromUtf8("label_NormWinHeight"));

        formLayout_NormWinSize->setWidget(1, QFormLayout::LabelRole, label_NormWinHeight);

        spinBox_NormWinHeight = new QSpinBox(groupBox_NormWin);
        spinBox_NormWinHeight->setObjectName(QString::fromUtf8("spinBox_NormWinHeight"));
        spinBox_NormWinHeight->setMaximum(9000);

        formLayout_NormWinSize->setWidget(1, QFormLayout::FieldRole, spinBox_NormWinHeight);

        label_NormWinWidth = new QLabel(groupBox_NormWin);
        label_NormWinWidth->setObjectName(QString::fromUtf8("label_NormWinWidth"));

        formLayout_NormWinSize->setWidget(0, QFormLayout::LabelRole, label_NormWinWidth);


        horizontalLayout_9->addLayout(formLayout_NormWinSize);


        horizontalLayout_NormWin->addWidget(groupBox_NormWin);

        horizontalSpacer_10 = new QSpacerItem(400, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_NormWin->addItem(horizontalSpacer_10);


        verticalLayout_10->addLayout(horizontalLayout_NormWin);


        verticalLayout_19->addWidget(groupBox_Normalization);

        toolBox_ProcessingMethods->addItem(page_MethodNormalization, QString::fromUtf8("Normalization"));
        page_MethodOutlier = new QWidget();
        page_MethodOutlier->setObjectName(QString::fromUtf8("page_MethodOutlier"));
        page_MethodOutlier->setGeometry(QRect(0, 0, 694, 316));
        verticalLayout_11 = new QVBoxLayout(page_MethodOutlier);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QString::fromUtf8("verticalLayout_11"));
        groupBox_6 = new QGroupBox(page_MethodOutlier);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        horizontalLayout_17 = new QHBoxLayout(groupBox_6);
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        checkBox_UseRAC = new QCheckBox(groupBox_6);
        checkBox_UseRAC->setObjectName(QString::fromUtf8("checkBox_UseRAC"));

        horizontalLayout_17->addWidget(checkBox_UseRAC);

        checkBox_UseOutlierSuppression = new QCheckBox(groupBox_6);
        checkBox_UseOutlierSuppression->setObjectName(QString::fromUtf8("checkBox_UseOutlierSuppression"));
        checkBox_UseOutlierSuppression->setChecked(true);

        horizontalLayout_17->addWidget(checkBox_UseOutlierSuppression);


        verticalLayout_11->addWidget(groupBox_6);

        groupBox_OutlierSettings = new QGroupBox(page_MethodOutlier);
        groupBox_OutlierSettings->setObjectName(QString::fromUtf8("groupBox_OutlierSettings"));
        QSizePolicy sizePolicy14(QSizePolicy::Fixed, QSizePolicy::Preferred);
        sizePolicy14.setHorizontalStretch(0);
        sizePolicy14.setVerticalStretch(0);
        sizePolicy14.setHeightForWidth(groupBox_OutlierSettings->sizePolicy().hasHeightForWidth());
        groupBox_OutlierSettings->setSizePolicy(sizePolicy14);
        verticalLayout = new QVBoxLayout(groupBox_OutlierSettings);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout_CoorrectionAlgo = new QHBoxLayout();
        horizontalLayout_CoorrectionAlgo->setSpacing(6);
        horizontalLayout_CoorrectionAlgo->setObjectName(QString::fromUtf8("horizontalLayout_CoorrectionAlgo"));
        label_CorrectionAlgo = new QLabel(groupBox_OutlierSettings);
        label_CorrectionAlgo->setObjectName(QString::fromUtf8("label_CorrectionAlgo"));

        horizontalLayout_CoorrectionAlgo->addWidget(label_CorrectionAlgo);

        comboBox_MethodSelection = new QComboBox(groupBox_OutlierSettings);
        comboBox_MethodSelection->addItem(QString());
        comboBox_MethodSelection->addItem(QString());
        comboBox_MethodSelection->setObjectName(QString::fromUtf8("comboBox_MethodSelection"));

        horizontalLayout_CoorrectionAlgo->addWidget(comboBox_MethodSelection);

        horizontalSpacer_14 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_CoorrectionAlgo->addItem(horizontalSpacer_14);


        verticalLayout->addLayout(horizontalLayout_CoorrectionAlgo);

        stackedWidget_MethodsParameter = new QStackedWidget(groupBox_OutlierSettings);
        stackedWidget_MethodsParameter->setObjectName(QString::fromUtf8("stackedWidget_MethodsParameter"));
        sizePolicy14.setHeightForWidth(stackedWidget_MethodsParameter->sizePolicy().hasHeightForWidth());
        stackedWidget_MethodsParameter->setSizePolicy(sizePolicy14);
        stackedWidget_MethodsParameter->setMinimumSize(QSize(500, 0));
        stackedWidget_MethodsParameter->setFrameShape(QFrame::Panel);
        stackedWidget_MethodsParameter->setFrameShadow(QFrame::Raised);
        page_MethodMedian9 = new QWidget();
        page_MethodMedian9->setObjectName(QString::fromUtf8("page_MethodMedian9"));
        page_MethodMedian9->setStyleSheet(QString::fromUtf8(" background-color: rgb(197, 230, 255)"));
        horizontalLayout_11 = new QHBoxLayout(page_MethodMedian9);
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        label_SigmaMedian9 = new QLabel(page_MethodMedian9);
        label_SigmaMedian9->setObjectName(QString::fromUtf8("label_SigmaMedian9"));

        horizontalLayout_11->addWidget(label_SigmaMedian9);

        doubleSpinBox_SigmaMedian9 = new QDoubleSpinBox(page_MethodMedian9);
        doubleSpinBox_SigmaMedian9->setObjectName(QString::fromUtf8("doubleSpinBox_SigmaMedian9"));
        doubleSpinBox_SigmaMedian9->setMinimum(3.000000000000000);
        doubleSpinBox_SigmaMedian9->setMaximum(12.000000000000000);
        doubleSpinBox_SigmaMedian9->setSingleStep(0.500000000000000);
        doubleSpinBox_SigmaMedian9->setValue(6.000000000000000);

        horizontalLayout_11->addWidget(doubleSpinBox_SigmaMedian9);

        horizontalSpacer_12 = new QSpacerItem(274, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_12);

        stackedWidget_MethodsParameter->addWidget(page_MethodMedian9);
        page_MethodMean9 = new QWidget();
        page_MethodMean9->setObjectName(QString::fromUtf8("page_MethodMean9"));
        page_MethodMean9->setStyleSheet(QString::fromUtf8(" background-color: rgb(235, 235, 176)"));
        horizontalLayout_4 = new QHBoxLayout(page_MethodMean9);
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        label_SigmaMean9 = new QLabel(page_MethodMean9);
        label_SigmaMean9->setObjectName(QString::fromUtf8("label_SigmaMean9"));

        horizontalLayout_4->addWidget(label_SigmaMean9);

        doubleSpinBox_SigmaMean9 = new QDoubleSpinBox(page_MethodMean9);
        doubleSpinBox_SigmaMean9->setObjectName(QString::fromUtf8("doubleSpinBox_SigmaMean9"));
        doubleSpinBox_SigmaMean9->setMinimum(3.000000000000000);
        doubleSpinBox_SigmaMean9->setMaximum(12.000000000000000);
        doubleSpinBox_SigmaMean9->setSingleStep(0.500000000000000);
        doubleSpinBox_SigmaMean9->setValue(6.000000000000000);

        horizontalLayout_4->addWidget(doubleSpinBox_SigmaMean9);

        horizontalSpacer_11 = new QSpacerItem(282, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_11);

        stackedWidget_MethodsParameter->addWidget(page_MethodMean9);

        verticalLayout->addWidget(stackedWidget_MethodsParameter);


        verticalLayout_11->addWidget(groupBox_OutlierSettings);

        toolBox_ProcessingMethods->addItem(page_MethodOutlier, QString::fromUtf8("Outlier / Ring Artefact"));
        page_MethodBHC = new QWidget();
        page_MethodBHC->setObjectName(QString::fromUtf8("page_MethodBHC"));
        page_MethodBHC->setGeometry(QRect(0, 0, 694, 316));
        verticalLayout_18 = new QVBoxLayout(page_MethodBHC);
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setContentsMargins(11, 11, 11, 11);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        groupBox_BHCSettings = new QGroupBox(page_MethodBHC);
        groupBox_BHCSettings->setObjectName(QString::fromUtf8("groupBox_BHCSettings"));
        sizePolicy2.setHeightForWidth(groupBox_BHCSettings->sizePolicy().hasHeightForWidth());
        groupBox_BHCSettings->setSizePolicy(sizePolicy2);
        verticalLayout_15 = new QVBoxLayout(groupBox_BHCSettings);
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setContentsMargins(11, 11, 11, 11);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        horizontalLayout_Formular = new QHBoxLayout();
        horizontalLayout_Formular->setSpacing(6);
        horizontalLayout_Formular->setObjectName(QString::fromUtf8("horizontalLayout_Formular"));
        label_Formular = new QLabel(groupBox_BHCSettings);
        label_Formular->setObjectName(QString::fromUtf8("label_Formular"));
        QSizePolicy sizePolicy15(QSizePolicy::Preferred, QSizePolicy::Minimum);
        sizePolicy15.setHorizontalStretch(0);
        sizePolicy15.setVerticalStretch(0);
        sizePolicy15.setHeightForWidth(label_Formular->sizePolicy().hasHeightForWidth());
        label_Formular->setSizePolicy(sizePolicy15);
        QFont font4;
        font4.setPointSize(11);
        font4.setBold(true);
        font4.setWeight(75);
        label_Formular->setFont(font4);

        horizontalLayout_Formular->addWidget(label_Formular);

        horizontalSpacer_18 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_Formular->addItem(horizontalSpacer_18);


        verticalLayout_15->addLayout(horizontalLayout_Formular);

        horizontalLayout_CorrectionLinearConstant = new QHBoxLayout();
        horizontalLayout_CorrectionLinearConstant->setSpacing(6);
        horizontalLayout_CorrectionLinearConstant->setObjectName(QString::fromUtf8("horizontalLayout_CorrectionLinearConstant"));
        label_BHC_CorrectionLinearConstantC = new QLabel(groupBox_BHCSettings);
        label_BHC_CorrectionLinearConstantC->setObjectName(QString::fromUtf8("label_BHC_CorrectionLinearConstantC"));
        sizePolicy15.setHeightForWidth(label_BHC_CorrectionLinearConstantC->sizePolicy().hasHeightForWidth());
        label_BHC_CorrectionLinearConstantC->setSizePolicy(sizePolicy15);

        horizontalLayout_CorrectionLinearConstant->addWidget(label_BHC_CorrectionLinearConstantC);

        doubleSpinBox_BHCCorrectionLinearConstA = new QDoubleSpinBox(groupBox_BHCSettings);
        doubleSpinBox_BHCCorrectionLinearConstA->setObjectName(QString::fromUtf8("doubleSpinBox_BHCCorrectionLinearConstA"));
        doubleSpinBox_BHCCorrectionLinearConstA->setDecimals(3);
        doubleSpinBox_BHCCorrectionLinearConstA->setMinimum(0.001000000000000);
        doubleSpinBox_BHCCorrectionLinearConstA->setMaximum(1000.000000000000000);
        doubleSpinBox_BHCCorrectionLinearConstA->setSingleStep(0.100000000000000);
        doubleSpinBox_BHCCorrectionLinearConstA->setValue(1.000000000000000);

        horizontalLayout_CorrectionLinearConstant->addWidget(doubleSpinBox_BHCCorrectionLinearConstA);

        horizontalSpacer_27 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_CorrectionLinearConstant->addItem(horizontalSpacer_27);


        verticalLayout_15->addLayout(horizontalLayout_CorrectionLinearConstant);

        horizontalLayout_CorrectionLinearConstant_2 = new QHBoxLayout();
        horizontalLayout_CorrectionLinearConstant_2->setSpacing(6);
        horizontalLayout_CorrectionLinearConstant_2->setObjectName(QString::fromUtf8("horizontalLayout_CorrectionLinearConstant_2"));
        label_BHC_CorrectionLinearConstantB = new QLabel(groupBox_BHCSettings);
        label_BHC_CorrectionLinearConstantB->setObjectName(QString::fromUtf8("label_BHC_CorrectionLinearConstantB"));
        sizePolicy15.setHeightForWidth(label_BHC_CorrectionLinearConstantB->sizePolicy().hasHeightForWidth());
        label_BHC_CorrectionLinearConstantB->setSizePolicy(sizePolicy15);

        horizontalLayout_CorrectionLinearConstant_2->addWidget(label_BHC_CorrectionLinearConstantB);

        doubleSpinBox_BHCCorrectionLinearConstB = new QDoubleSpinBox(groupBox_BHCSettings);
        doubleSpinBox_BHCCorrectionLinearConstB->setObjectName(QString::fromUtf8("doubleSpinBox_BHCCorrectionLinearConstB"));
        doubleSpinBox_BHCCorrectionLinearConstB->setDecimals(3);
        doubleSpinBox_BHCCorrectionLinearConstB->setMinimum(0.001000000000000);
        doubleSpinBox_BHCCorrectionLinearConstB->setMaximum(1000.000000000000000);
        doubleSpinBox_BHCCorrectionLinearConstB->setSingleStep(0.100000000000000);
        doubleSpinBox_BHCCorrectionLinearConstB->setValue(1.000000000000000);

        horizontalLayout_CorrectionLinearConstant_2->addWidget(doubleSpinBox_BHCCorrectionLinearConstB);

        horizontalSpacer_31 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_CorrectionLinearConstant_2->addItem(horizontalSpacer_31);


        verticalLayout_15->addLayout(horizontalLayout_CorrectionLinearConstant_2);

        horizontalLayout_CorrectionExponent = new QHBoxLayout();
        horizontalLayout_CorrectionExponent->setSpacing(6);
        horizontalLayout_CorrectionExponent->setObjectName(QString::fromUtf8("horizontalLayout_CorrectionExponent"));
        label_BHC_CorrectionExpo = new QLabel(groupBox_BHCSettings);
        label_BHC_CorrectionExpo->setObjectName(QString::fromUtf8("label_BHC_CorrectionExpo"));
        sizePolicy15.setHeightForWidth(label_BHC_CorrectionExpo->sizePolicy().hasHeightForWidth());
        label_BHC_CorrectionExpo->setSizePolicy(sizePolicy15);

        horizontalLayout_CorrectionExponent->addWidget(label_BHC_CorrectionExpo);

        doubleSpinBox_BHCCorrectionExpo = new QDoubleSpinBox(groupBox_BHCSettings);
        doubleSpinBox_BHCCorrectionExpo->setObjectName(QString::fromUtf8("doubleSpinBox_BHCCorrectionExpo"));
        doubleSpinBox_BHCCorrectionExpo->setDecimals(3);
        doubleSpinBox_BHCCorrectionExpo->setMinimum(0.001000000000000);
        doubleSpinBox_BHCCorrectionExpo->setMaximum(1000.000000000000000);
        doubleSpinBox_BHCCorrectionExpo->setSingleStep(0.100000000000000);
        doubleSpinBox_BHCCorrectionExpo->setValue(2.000000000000000);

        horizontalLayout_CorrectionExponent->addWidget(doubleSpinBox_BHCCorrectionExpo);

        horizontalSpacer_16 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_CorrectionExponent->addItem(horizontalSpacer_16);


        verticalLayout_15->addLayout(horizontalLayout_CorrectionExponent);


        verticalLayout_18->addWidget(groupBox_BHCSettings);

        toolBox_ProcessingMethods->addItem(page_MethodBHC, QString::fromUtf8("BHC"));
        page_StripeReduction = new QWidget();
        page_StripeReduction->setObjectName(QString::fromUtf8("page_StripeReduction"));
        page_StripeReduction->setGeometry(QRect(0, 0, 694, 316));
        verticalLayout_17 = new QVBoxLayout(page_StripeReduction);
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setContentsMargins(11, 11, 11, 11);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        groupBox_StripeSettings = new QGroupBox(page_StripeReduction);
        groupBox_StripeSettings->setObjectName(QString::fromUtf8("groupBox_StripeSettings"));
        sizePolicy2.setHeightForWidth(groupBox_StripeSettings->sizePolicy().hasHeightForWidth());
        groupBox_StripeSettings->setSizePolicy(sizePolicy2);
        verticalLayout_16 = new QVBoxLayout(groupBox_StripeSettings);
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        horizontalLayout_PadMultFFt = new QHBoxLayout();
        horizontalLayout_PadMultFFt->setSpacing(6);
        horizontalLayout_PadMultFFt->setObjectName(QString::fromUtf8("horizontalLayout_PadMultFFt"));
        label_PadMultFFT = new QLabel(groupBox_StripeSettings);
        label_PadMultFFT->setObjectName(QString::fromUtf8("label_PadMultFFT"));

        horizontalLayout_PadMultFFt->addWidget(label_PadMultFFT);

        comboBox_PadMultFFT = new QComboBox(groupBox_StripeSettings);
        comboBox_PadMultFFT->addItem(QString());
        comboBox_PadMultFFT->addItem(QString());
        comboBox_PadMultFFT->addItem(QString());
        comboBox_PadMultFFT->addItem(QString());
        comboBox_PadMultFFT->setObjectName(QString::fromUtf8("comboBox_PadMultFFT"));

        horizontalLayout_PadMultFFt->addWidget(comboBox_PadMultFFT);

        horizontalSpacer_17 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_PadMultFFt->addItem(horizontalSpacer_17);


        verticalLayout_16->addLayout(horizontalLayout_PadMultFFt);

        checkBox_FFTRunMultiThread = new QCheckBox(groupBox_StripeSettings);
        checkBox_FFTRunMultiThread->setObjectName(QString::fromUtf8("checkBox_FFTRunMultiThread"));
        checkBox_FFTRunMultiThread->setChecked(false);

        verticalLayout_16->addWidget(checkBox_FFTRunMultiThread);


        verticalLayout_17->addWidget(groupBox_StripeSettings);

        toolBox_ProcessingMethods->addItem(page_StripeReduction, QString::fromUtf8("Sinogram / Stripe Reduction  "));
        page_EdgeEnhancement = new QWidget();
        page_EdgeEnhancement->setObjectName(QString::fromUtf8("page_EdgeEnhancement"));
        page_EdgeEnhancement->setGeometry(QRect(0, 0, 694, 316));
        verticalLayout_27 = new QVBoxLayout(page_EdgeEnhancement);
        verticalLayout_27->setSpacing(6);
        verticalLayout_27->setContentsMargins(11, 11, 11, 11);
        verticalLayout_27->setObjectName(QString::fromUtf8("verticalLayout_27"));
        groupBox_EnhanceParams = new QGroupBox(page_EdgeEnhancement);
        groupBox_EnhanceParams->setObjectName(QString::fromUtf8("groupBox_EnhanceParams"));
        groupBox_EnhanceParams->setEnabled(true);
        sizePolicy2.setHeightForWidth(groupBox_EnhanceParams->sizePolicy().hasHeightForWidth());
        groupBox_EnhanceParams->setSizePolicy(sizePolicy2);
        horizontalLayout_23 = new QHBoxLayout(groupBox_EnhanceParams);
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));
        checkBox_applyLorentzFilter = new QCheckBox(groupBox_EnhanceParams);
        checkBox_applyLorentzFilter->setObjectName(QString::fromUtf8("checkBox_applyLorentzFilter"));

        horizontalLayout_23->addWidget(checkBox_applyLorentzFilter);

        groupBox_8 = new QGroupBox(groupBox_EnhanceParams);
        groupBox_8->setObjectName(QString::fromUtf8("groupBox_8"));
        verticalLayout_28 = new QVBoxLayout(groupBox_8);
        verticalLayout_28->setSpacing(6);
        verticalLayout_28->setContentsMargins(11, 11, 11, 11);
        verticalLayout_28->setObjectName(QString::fromUtf8("verticalLayout_28"));
        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        label_9 = new QLabel(groupBox_8);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        horizontalLayout_25->addWidget(label_9);

        doubleSpinBox_filterStrengthAlpha = new QDoubleSpinBox(groupBox_8);
        doubleSpinBox_filterStrengthAlpha->setObjectName(QString::fromUtf8("doubleSpinBox_filterStrengthAlpha"));
        doubleSpinBox_filterStrengthAlpha->setMaximum(1000000.000000000000000);
        doubleSpinBox_filterStrengthAlpha->setValue(2.000000000000000);

        horizontalLayout_25->addWidget(doubleSpinBox_filterStrengthAlpha);


        verticalLayout_28->addLayout(horizontalLayout_25);


        horizontalLayout_23->addWidget(groupBox_8);


        verticalLayout_27->addWidget(groupBox_EnhanceParams);

        toolBox_ProcessingMethods->addItem(page_EdgeEnhancement, QString::fromUtf8("Edge Enhancement (Lorentz Filter)"));

        verticalLayout_3->addWidget(toolBox_ProcessingMethods);

        tabWidget_ParameterSettings->addTab(tab_BasicParamSettings, QString());
        tab_AdvancedParamSettings = new QWidget();
        tab_AdvancedParamSettings->setObjectName(QString::fromUtf8("tab_AdvancedParamSettings"));
        tab_AdvancedParamSettings->setEnabled(false);
        verticalLayout_20 = new QVBoxLayout(tab_AdvancedParamSettings);
        verticalLayout_20->setSpacing(6);
        verticalLayout_20->setContentsMargins(11, 11, 11, 11);
        verticalLayout_20->setObjectName(QString::fromUtf8("verticalLayout_20"));
        groupBox_19 = new QGroupBox(tab_AdvancedParamSettings);
        groupBox_19->setObjectName(QString::fromUtf8("groupBox_19"));
        horizontalLayout_19 = new QHBoxLayout(groupBox_19);
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        label_26 = new QLabel(groupBox_19);
        label_26->setObjectName(QString::fromUtf8("label_26"));
        QFont font5;
        font5.setPointSize(11);
        font5.setBold(true);
        font5.setItalic(true);
        font5.setWeight(75);
        label_26->setFont(font5);
        label_26->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0)"));
        label_26->setAlignment(Qt::AlignCenter);

        horizontalLayout_19->addWidget(label_26);


        verticalLayout_20->addWidget(groupBox_19);

        tabWidget_ParameterSettings->addTab(tab_AdvancedParamSettings, QString());

        verticalLayout_4->addWidget(tabWidget_ParameterSettings);

        groupBox_Running = new QGroupBox(scrollAreaWidgetContents_PreProcessorLeftSide);
        groupBox_Running->setObjectName(QString::fromUtf8("groupBox_Running"));
        sizePolicy3.setHeightForWidth(groupBox_Running->sizePolicy().hasHeightForWidth());
        groupBox_Running->setSizePolicy(sizePolicy3);
        groupBox_Running->setMinimumSize(QSize(0, 200));
        horizontalLayout_5 = new QHBoxLayout(groupBox_Running);
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        tabWidget_Running = new QTabWidget(groupBox_Running);
        tabWidget_Running->setObjectName(QString::fromUtf8("tabWidget_Running"));
        sizePolicy3.setHeightForWidth(tabWidget_Running->sizePolicy().hasHeightForWidth());
        tabWidget_Running->setSizePolicy(sizePolicy3);
        tab_Start = new QWidget();
        tab_Start->setObjectName(QString::fromUtf8("tab_Start"));
        verticalLayout_9 = new QVBoxLayout(tab_Start);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        groupBox = new QGroupBox(tab_Start);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_21 = new QVBoxLayout(groupBox);
        verticalLayout_21->setSpacing(6);
        verticalLayout_21->setContentsMargins(11, 11, 11, 11);
        verticalLayout_21->setObjectName(QString::fromUtf8("verticalLayout_21"));
        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        pushButton_Run = new QPushButton(groupBox);
        pushButton_Run->setObjectName(QString::fromUtf8("pushButton_Run"));
        pushButton_Run->setEnabled(false);

        gridLayout_3->addWidget(pushButton_Run, 0, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_6, 0, 1, 1, 1);

        pushButton_SaveSettingsForRun = new QPushButton(groupBox);
        pushButton_SaveSettingsForRun->setObjectName(QString::fromUtf8("pushButton_SaveSettingsForRun"));
        pushButton_SaveSettingsForRun->setMinimumSize(QSize(130, 0));
        pushButton_SaveSettingsForRun->setStyleSheet(QString::fromUtf8(""));

        gridLayout_3->addWidget(pushButton_SaveSettingsForRun, 0, 2, 1, 1);

        horizontalSpacer_15 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_15, 1, 1, 1, 1);

        pushButton_SaveMessageOutput = new QPushButton(groupBox);
        pushButton_SaveMessageOutput->setObjectName(QString::fromUtf8("pushButton_SaveMessageOutput"));
        pushButton_SaveMessageOutput->setMinimumSize(QSize(130, 0));

        gridLayout_3->addWidget(pushButton_SaveMessageOutput, 1, 2, 1, 1);

        pushButton_CancelRun = new QPushButton(groupBox);
        pushButton_CancelRun->setObjectName(QString::fromUtf8("pushButton_CancelRun"));
        pushButton_CancelRun->setEnabled(false);

        gridLayout_3->addWidget(pushButton_CancelRun, 1, 0, 1, 1);


        verticalLayout_21->addLayout(gridLayout_3);


        verticalLayout_9->addWidget(groupBox);

        tabWidget_Running->addTab(tab_Start, QString());
        tab_batch = new QWidget();
        tab_batch->setObjectName(QString::fromUtf8("tab_batch"));
        verticalLayout_14 = new QVBoxLayout(tab_batch);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        groupBox_runBatch = new QGroupBox(tab_batch);
        groupBox_runBatch->setObjectName(QString::fromUtf8("groupBox_runBatch"));
        horizontalLayout_18 = new QHBoxLayout(groupBox_runBatch);
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label_Dummy = new QLabel(groupBox_runBatch);
        label_Dummy->setObjectName(QString::fromUtf8("label_Dummy"));
        label_Dummy->setFont(font5);
        label_Dummy->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 0, 0)"));
        label_Dummy->setAlignment(Qt::AlignCenter);

        horizontalLayout_18->addWidget(label_Dummy);


        verticalLayout_14->addWidget(groupBox_runBatch);

        tabWidget_Running->addTab(tab_batch, QString());

        horizontalLayout_5->addWidget(tabWidget_Running);

        groupBox_MessageOutput = new QGroupBox(groupBox_Running);
        groupBox_MessageOutput->setObjectName(QString::fromUtf8("groupBox_MessageOutput"));
        QSizePolicy sizePolicy16(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy16.setHorizontalStretch(0);
        sizePolicy16.setVerticalStretch(0);
        sizePolicy16.setHeightForWidth(groupBox_MessageOutput->sizePolicy().hasHeightForWidth());
        groupBox_MessageOutput->setSizePolicy(sizePolicy16);
        groupBox_MessageOutput->setMinimumSize(QSize(8, 0));
        verticalLayout_8 = new QVBoxLayout(groupBox_MessageOutput);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        textEdit_MessagesOutput = new QTextEdit(groupBox_MessageOutput);
        textEdit_MessagesOutput->setObjectName(QString::fromUtf8("textEdit_MessagesOutput"));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Consolas"));
        font6.setBold(false);
        font6.setWeight(50);
        textEdit_MessagesOutput->setFont(font6);
        textEdit_MessagesOutput->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        textEdit_MessagesOutput->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        textEdit_MessagesOutput->setLineWrapMode(QTextEdit::NoWrap);

        verticalLayout_8->addWidget(textEdit_MessagesOutput);


        horizontalLayout_5->addWidget(groupBox_MessageOutput);


        verticalLayout_4->addWidget(groupBox_Running);

        scrollArea_PreProcessorLayoutLeftSide->setWidget(scrollAreaWidgetContents_PreProcessorLeftSide);

        horizontalLayout_24->addWidget(scrollArea_PreProcessorLayoutLeftSide);

        scrollArea_PreProcessorLayoutRightSide = new QScrollArea(centralWidget);
        scrollArea_PreProcessorLayoutRightSide->setObjectName(QString::fromUtf8("scrollArea_PreProcessorLayoutRightSide"));
        QSizePolicy sizePolicy17(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy17.setHorizontalStretch(0);
        sizePolicy17.setVerticalStretch(0);
        sizePolicy17.setHeightForWidth(scrollArea_PreProcessorLayoutRightSide->sizePolicy().hasHeightForWidth());
        scrollArea_PreProcessorLayoutRightSide->setSizePolicy(sizePolicy17);
        scrollArea_PreProcessorLayoutRightSide->setMinimumSize(QSize(500, 600));
        scrollArea_PreProcessorLayoutRightSide->setWidgetResizable(true);
        scrollAreaWidgetContents_ImageProcessing = new QWidget();
        scrollAreaWidgetContents_ImageProcessing->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_ImageProcessing"));
        scrollAreaWidgetContents_ImageProcessing->setGeometry(QRect(0, 0, 738, 1179));
        verticalLayout_5 = new QVBoxLayout(scrollAreaWidgetContents_ImageProcessing);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        tabWidget_Projections = new QTabWidget(scrollAreaWidgetContents_ImageProcessing);
        tabWidget_Projections->setObjectName(QString::fromUtf8("tabWidget_Projections"));
        QSizePolicy sizePolicy18(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy18.setHorizontalStretch(0);
        sizePolicy18.setVerticalStretch(0);
        sizePolicy18.setHeightForWidth(tabWidget_Projections->sizePolicy().hasHeightForWidth());
        tabWidget_Projections->setSizePolicy(sizePolicy18);
        tabWidget_Projections->setMinimumSize(QSize(605, 932));
        tab_ProjectionViewer = new QWidget();
        tab_ProjectionViewer->setObjectName(QString::fromUtf8("tab_ProjectionViewer"));
        verticalLayout_7 = new QVBoxLayout(tab_ProjectionViewer);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        scrollArea_ImageViewer = new QScrollArea(tab_ProjectionViewer);
        scrollArea_ImageViewer->setObjectName(QString::fromUtf8("scrollArea_ImageViewer"));
        sizePolicy.setHeightForWidth(scrollArea_ImageViewer->sizePolicy().hasHeightForWidth());
        scrollArea_ImageViewer->setSizePolicy(sizePolicy);
        scrollArea_ImageViewer->setMinimumSize(QSize(540, 540));
        scrollArea_ImageViewer->setWidgetResizable(true);
        scrollArea_ImageViewer->setAlignment(Qt::AlignCenter);
        scrollAreaWidgetContents_ImageViewer = new QWidget();
        scrollAreaWidgetContents_ImageViewer->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_ImageViewer"));
        scrollAreaWidgetContents_ImageViewer->setGeometry(QRect(0, 0, 694, 538));
        sizePolicy18.setHeightForWidth(scrollAreaWidgetContents_ImageViewer->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents_ImageViewer->setSizePolicy(sizePolicy18);
        scrollAreaWidgetContents_ImageViewer->setMinimumSize(QSize(512, 512));
        gridLayout_2 = new QGridLayout(scrollAreaWidgetContents_ImageViewer);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_ImageView = new QLabel(scrollAreaWidgetContents_ImageViewer);
        label_ImageView->setObjectName(QString::fromUtf8("label_ImageView"));
        sizePolicy6.setHeightForWidth(label_ImageView->sizePolicy().hasHeightForWidth());
        label_ImageView->setSizePolicy(sizePolicy6);
        label_ImageView->setMinimumSize(QSize(512, 512));
        label_ImageView->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label_ImageView, 0, 0, 1, 1);

        scrollArea_ImageViewer->setWidget(scrollAreaWidgetContents_ImageViewer);

        verticalLayout_7->addWidget(scrollArea_ImageViewer);

        horizontalLayout_ProjectionSlice = new QHBoxLayout();
        horizontalLayout_ProjectionSlice->setSpacing(6);
        horizontalLayout_ProjectionSlice->setObjectName(QString::fromUtf8("horizontalLayout_ProjectionSlice"));
        label_SliceNr = new QLabel(tab_ProjectionViewer);
        label_SliceNr->setObjectName(QString::fromUtf8("label_SliceNr"));

        horizontalLayout_ProjectionSlice->addWidget(label_SliceNr);

        spinBox_SliceNumber = new QSpinBox(tab_ProjectionViewer);
        spinBox_SliceNumber->setObjectName(QString::fromUtf8("spinBox_SliceNumber"));
        spinBox_SliceNumber->setMinimum(1);
        spinBox_SliceNumber->setMaximum(10000);

        horizontalLayout_ProjectionSlice->addWidget(spinBox_SliceNumber);

        horizontalSlider_imageView = new QSlider(tab_ProjectionViewer);
        horizontalSlider_imageView->setObjectName(QString::fromUtf8("horizontalSlider_imageView"));
        horizontalSlider_imageView->setMinimum(1);
        horizontalSlider_imageView->setMaximum(10000);
        horizontalSlider_imageView->setOrientation(Qt::Horizontal);

        horizontalLayout_ProjectionSlice->addWidget(horizontalSlider_imageView);


        verticalLayout_7->addLayout(horizontalLayout_ProjectionSlice);

        groupBox_ImageOperations = new QGroupBox(tab_ProjectionViewer);
        groupBox_ImageOperations->setObjectName(QString::fromUtf8("groupBox_ImageOperations"));
        QSizePolicy sizePolicy19(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy19.setHorizontalStretch(2);
        sizePolicy19.setVerticalStretch(0);
        sizePolicy19.setHeightForWidth(groupBox_ImageOperations->sizePolicy().hasHeightForWidth());
        groupBox_ImageOperations->setSizePolicy(sizePolicy19);
        groupBox_ImageOperations->setMinimumSize(QSize(586, 314));
        verticalLayout_25 = new QVBoxLayout(groupBox_ImageOperations);
        verticalLayout_25->setSpacing(6);
        verticalLayout_25->setContentsMargins(11, 11, 11, 11);
        verticalLayout_25->setObjectName(QString::fromUtf8("verticalLayout_25"));
        groupBox_2 = new QGroupBox(groupBox_ImageOperations);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        QSizePolicy sizePolicy20(QSizePolicy::Expanding, QSizePolicy::Minimum);
        sizePolicy20.setHorizontalStretch(0);
        sizePolicy20.setVerticalStretch(0);
        sizePolicy20.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy20);
        groupBox_2->setMinimumSize(QSize(0, 184));
        horizontalLayout_16 = new QHBoxLayout(groupBox_2);
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        verticalLayout_24 = new QVBoxLayout();
        verticalLayout_24->setSpacing(6);
        verticalLayout_24->setObjectName(QString::fromUtf8("verticalLayout_24"));
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_7->addWidget(label);

        pushButton_applyEqualize = new QPushButton(groupBox_2);
        pushButton_applyEqualize->setObjectName(QString::fromUtf8("pushButton_applyEqualize"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/ProjectionPreProcessor/Images/forward.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_applyEqualize->setIcon(icon9);

        horizontalLayout_7->addWidget(pushButton_applyEqualize);

        horizontalSpacer_19 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_19);


        verticalLayout_24->addLayout(horizontalLayout_7);

        groupBox_3 = new QGroupBox(groupBox_2);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        sizePolicy20.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy20);
        groupBox_3->setMinimumSize(QSize(0, 55));
        horizontalLayout_21 = new QHBoxLayout(groupBox_3);
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        label_ContrastSlope = new QLabel(groupBox_3);
        label_ContrastSlope->setObjectName(QString::fromUtf8("label_ContrastSlope"));

        horizontalLayout_8->addWidget(label_ContrastSlope);

        doubleSpinBox_ContrastSlope = new QDoubleSpinBox(groupBox_3);
        doubleSpinBox_ContrastSlope->setObjectName(QString::fromUtf8("doubleSpinBox_ContrastSlope"));
        sizePolicy2.setHeightForWidth(doubleSpinBox_ContrastSlope->sizePolicy().hasHeightForWidth());
        doubleSpinBox_ContrastSlope->setSizePolicy(sizePolicy2);
        doubleSpinBox_ContrastSlope->setMinimumSize(QSize(0, 21));
        doubleSpinBox_ContrastSlope->setDecimals(3);
        doubleSpinBox_ContrastSlope->setMinimum(0.100000000000000);
        doubleSpinBox_ContrastSlope->setMaximum(10.000000000000000);
        doubleSpinBox_ContrastSlope->setSingleStep(0.100000000000000);
        doubleSpinBox_ContrastSlope->setValue(1.000000000000000);

        horizontalLayout_8->addWidget(doubleSpinBox_ContrastSlope);

        label_contrastOffset = new QLabel(groupBox_3);
        label_contrastOffset->setObjectName(QString::fromUtf8("label_contrastOffset"));

        horizontalLayout_8->addWidget(label_contrastOffset);

        doubleSpinBox_ContrastOffset = new QDoubleSpinBox(groupBox_3);
        doubleSpinBox_ContrastOffset->setObjectName(QString::fromUtf8("doubleSpinBox_ContrastOffset"));
        doubleSpinBox_ContrastOffset->setDecimals(3);
        doubleSpinBox_ContrastOffset->setMinimum(-255.000000000000000);
        doubleSpinBox_ContrastOffset->setMaximum(255.000000000000000);
        doubleSpinBox_ContrastOffset->setValue(0.000000000000000);

        horizontalLayout_8->addWidget(doubleSpinBox_ContrastOffset);

        horizontalSpacer_20 = new QSpacerItem(105, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_20);

        label_ContrastApply = new QLabel(groupBox_3);
        label_ContrastApply->setObjectName(QString::fromUtf8("label_ContrastApply"));

        horizontalLayout_8->addWidget(label_ContrastApply);

        pushButton_ContrastApply = new QPushButton(groupBox_3);
        pushButton_ContrastApply->setObjectName(QString::fromUtf8("pushButton_ContrastApply"));
        pushButton_ContrastApply->setIcon(icon9);

        horizontalLayout_8->addWidget(pushButton_ContrastApply);

        horizontalSpacer_21 = new QSpacerItem(105, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_8->addItem(horizontalSpacer_21);


        horizontalLayout_21->addLayout(horizontalLayout_8);


        verticalLayout_24->addWidget(groupBox_3);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        pushButton_UndoImageProcessing = new QPushButton(groupBox_2);
        pushButton_UndoImageProcessing->setObjectName(QString::fromUtf8("pushButton_UndoImageProcessing"));

        horizontalLayout_15->addWidget(pushButton_UndoImageProcessing);

        horizontalSpacer_22 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_22);


        verticalLayout_24->addLayout(horizontalLayout_15);

        progressBar_ImageProcessing = new QProgressBar(groupBox_2);
        progressBar_ImageProcessing->setObjectName(QString::fromUtf8("progressBar_ImageProcessing"));
        progressBar_ImageProcessing->setMinimum(0);
        progressBar_ImageProcessing->setMaximum(10000);
        progressBar_ImageProcessing->setValue(0);
        progressBar_ImageProcessing->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        verticalLayout_24->addWidget(progressBar_ImageProcessing);


        horizontalLayout_16->addLayout(verticalLayout_24);


        verticalLayout_25->addWidget(groupBox_2);

        groupBox_4 = new QGroupBox(groupBox_ImageOperations);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        sizePolicy15.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy15);
        groupBox_4->setMinimumSize(QSize(0, 105));
        verticalLayout_23 = new QVBoxLayout(groupBox_4);
        verticalLayout_23->setSpacing(6);
        verticalLayout_23->setContentsMargins(11, 11, 11, 11);
        verticalLayout_23->setObjectName(QString::fromUtf8("verticalLayout_23"));
        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        checkBox_EnableWindowSelection = new QCheckBox(groupBox_4);
        checkBox_EnableWindowSelection->setObjectName(QString::fromUtf8("checkBox_EnableWindowSelection"));

        horizontalLayout_14->addWidget(checkBox_EnableWindowSelection);

        groupBox_5 = new QGroupBox(groupBox_4);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        verticalLayout_22 = new QVBoxLayout(groupBox_5);
        verticalLayout_22->setSpacing(6);
        verticalLayout_22->setContentsMargins(11, 11, 11, 11);
        verticalLayout_22->setObjectName(QString::fromUtf8("verticalLayout_22"));
        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        label_xPosition = new QLabel(groupBox_5);
        label_xPosition->setObjectName(QString::fromUtf8("label_xPosition"));

        horizontalLayout_10->addWidget(label_xPosition);

        spinBox_xWinPos = new QSpinBox(groupBox_5);
        spinBox_xWinPos->setObjectName(QString::fromUtf8("spinBox_xWinPos"));
        spinBox_xWinPos->setEnabled(false);
        spinBox_xWinPos->setMaximum(9000);

        horizontalLayout_10->addWidget(spinBox_xWinPos);

        horizontalSpacer_23 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_23);

        label_7 = new QLabel(groupBox_5);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        horizontalLayout_10->addWidget(label_7);

        spinBox_WinWidth = new QSpinBox(groupBox_5);
        spinBox_WinWidth->setObjectName(QString::fromUtf8("spinBox_WinWidth"));
        spinBox_WinWidth->setEnabled(false);
        spinBox_WinWidth->setMaximum(9000);

        horizontalLayout_10->addWidget(spinBox_WinWidth);

        horizontalSpacer_25 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_25);


        verticalLayout_22->addLayout(horizontalLayout_10);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        label_6 = new QLabel(groupBox_5);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        horizontalLayout_12->addWidget(label_6);

        spinBox_yWinPos = new QSpinBox(groupBox_5);
        spinBox_yWinPos->setObjectName(QString::fromUtf8("spinBox_yWinPos"));
        spinBox_yWinPos->setEnabled(false);
        spinBox_yWinPos->setMaximum(9000);

        horizontalLayout_12->addWidget(spinBox_yWinPos);

        horizontalSpacer_24 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_24);

        label_8 = new QLabel(groupBox_5);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        horizontalLayout_12->addWidget(label_8);

        spinBox_WinHeight = new QSpinBox(groupBox_5);
        spinBox_WinHeight->setObjectName(QString::fromUtf8("spinBox_WinHeight"));
        spinBox_WinHeight->setEnabled(false);
        spinBox_WinHeight->setMaximum(9000);

        horizontalLayout_12->addWidget(spinBox_WinHeight);

        horizontalSpacer_26 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_26);


        verticalLayout_22->addLayout(horizontalLayout_12);


        horizontalLayout_14->addWidget(groupBox_5);


        verticalLayout_23->addLayout(horizontalLayout_14);


        verticalLayout_25->addWidget(groupBox_4);


        verticalLayout_7->addWidget(groupBox_ImageOperations);

        tabWidget_Projections->addTab(tab_ProjectionViewer, QString());
        tab_NOP = new QWidget();
        tab_NOP->setObjectName(QString::fromUtf8("tab_NOP"));
        tabWidget_Projections->addTab(tab_NOP, QString());

        verticalLayout_5->addWidget(tabWidget_Projections);

        scrollArea_PreProcessorLayoutRightSide->setWidget(scrollAreaWidgetContents_ImageProcessing);

        horizontalLayout_24->addWidget(scrollArea_PreProcessorLayoutRightSide);

        ProjectionPreProcessorClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(ProjectionPreProcessorClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1504, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuTools = new QMenu(menuBar);
        menuTools->setObjectName(QString::fromUtf8("menuTools"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        ProjectionPreProcessorClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(ProjectionPreProcessorClass);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        mainToolBar->setEnabled(true);
        mainToolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        ProjectionPreProcessorClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(ProjectionPreProcessorClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        ProjectionPreProcessorClass->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuTools->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionOpen_Project);
        menuFile->addAction(actionSave_Project_as);
        menuFile->addAction(actionSave);
        menuFile->addSeparator();
        menuFile->addAction(actionNew);
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menuFile->addAction(actionLorentz_Filter);
        menuTools->addAction(actionExport_PFDK);
        menuHelp->addAction(actionAbout);
        mainToolBar->addAction(actionExit);
        mainToolBar->addAction(actionNew);
        mainToolBar->addAction(actionLorentz_Filter);
        mainToolBar->addAction(actionOpen_Project);
        mainToolBar->addAction(actionSave);
        mainToolBar->addAction(actionSave_Project_as);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionExport_PFDK);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionAbout);
        mainToolBar->addSeparator();

        retranslateUi(ProjectionPreProcessorClass);
        QObject::connect(comboBox_MethodSelection, SIGNAL(currentIndexChanged(int)), stackedWidget_MethodsParameter, SLOT(setCurrentIndex(int)));
        QObject::connect(actionExit, SIGNAL(triggered(bool)), ProjectionPreProcessorClass, SLOT(close()));
        QObject::connect(horizontalSlider_imageView, SIGNAL(sliderMoved(int)), spinBox_SliceNumber, SLOT(setValue(int)));
        QObject::connect(spinBox_NormWinWidth, SIGNAL(valueChanged(int)), spinBox_WinWidth, SLOT(setValue(int)));
        QObject::connect(spinBox_NormWinHeight, SIGNAL(valueChanged(int)), spinBox_WinHeight, SLOT(setValue(int)));
        QObject::connect(spinBox_NormWinXPos, SIGNAL(valueChanged(int)), spinBox_xWinPos, SLOT(setValue(int)));
        QObject::connect(spinBox_NormWinYPos, SIGNAL(valueChanged(int)), spinBox_yWinPos, SLOT(setValue(int)));
        QObject::connect(horizontalSlider_MemSavMinMax, SIGNAL(valueChanged(int)), spinBox_MemMultFac, SLOT(setValue(int)));
        QObject::connect(spinBox_MemMultFac, SIGNAL(valueChanged(int)), horizontalSlider_MemSavMinMax, SLOT(setValue(int)));
        QObject::connect(checkBox_TileMemory, SIGNAL(toggled(bool)), horizontalSlider_MemSavMinMax, SLOT(setEnabled(bool)));
        QObject::connect(checkBox_TileMemory, SIGNAL(toggled(bool)), spinBox_MemMultFac, SLOT(setEnabled(bool)));

        tabWidget_ParameterSettings->setCurrentIndex(0);
        tabWidget_IOSettings->setCurrentIndex(0);
        toolBox_ProcessingMethods->setCurrentIndex(0);
        stackedWidget_MethodsParameter->setCurrentIndex(0);
        comboBox_PadMultFFT->setCurrentIndex(1);
        tabWidget_Running->setCurrentIndex(0);
        tabWidget_Projections->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(ProjectionPreProcessorClass);
    } // setupUi

    void retranslateUi(QMainWindow *ProjectionPreProcessorClass)
    {
        ProjectionPreProcessorClass->setWindowTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "Projection pre processor Project: #", nullptr));
        actionOpen_Project->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Open Project ...", nullptr));
        actionSave_Project_as->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Save Project as ...", nullptr));
        actionSave->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Save Project", nullptr));
        actionExport_PFDK->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Export to PFDK File ...", nullptr));
        actionAbout->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "About", nullptr));
        actionNew->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "New Project", nullptr));
#if QT_CONFIG(tooltip)
        actionNew->setToolTip(QCoreApplication::translate("ProjectionPreProcessorClass", "New Project", nullptr));
#endif // QT_CONFIG(tooltip)
        actionExit->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Exit", nullptr));
        actionLorentz_Filter->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Lorentz Filter", nullptr));
#if QT_CONFIG(tooltip)
        actionLorentz_Filter->setToolTip(QCoreApplication::translate("ProjectionPreProcessorClass", "<html><head/><body><p>Lorentz Filter: Alpha determination</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_ProjectSettings->setTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "Project Settings", nullptr));
        label_Project->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Project:", nullptr));
        label_CreatorOwner->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Creator/Owner:", nullptr));
        label_Date->setText(QCoreApplication::translate("ProjectionPreProcessorClass", " Date:", nullptr));
        groupBox_IOInput->setTitle(QString());
        groupBox_FileSelection->setTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "File Selection", nullptr));
        label_InputDir->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Directory:", nullptr));
        pushButton_SelInputDir->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Select Files...", nullptr));
        label_InputFilePattern->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Pattern:", nullptr));
        label_FileType->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "File Type:", nullptr));
        comboBox_SelFileType->setItemText(0, QCoreApplication::translate("ProjectionPreProcessorClass", "tif / tiff", nullptr));

        groupBox_projectionParam->setTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "Projection Parameters", nullptr));
        label_InputType->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Data Type:", nullptr));
        label_ProjectionHeight->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Height:", nullptr));
        label_ProjectionWidth->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Width:", nullptr));
        label_NumberProjections->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Number of Projections:", nullptr));
        label_CVDataType->setText(QString());
        groupBox_LoadInputData->setTitle(QString());
        checkBox_TileMemory->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Apply File Tiling", nullptr));
        label_3->setText(QString());
        label_2->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Memory save settings", nullptr));
        label_4->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "   Min", nullptr));
        label_5->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Max  ", nullptr));
        pushButton_LoadInputData->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Load Data", nullptr));
        progressBar_LoadData->setFormat(QCoreApplication::translate("ProjectionPreProcessorClass", "%v Files loaded", nullptr));
        pushButton_LoadDataInterrupt->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Interrupt", nullptr));
        label_RotationDirection->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Rotation Direction:", nullptr));
        comboBox_ClockWise->setItemText(0, QCoreApplication::translate("ProjectionPreProcessorClass", "Clockwise", nullptr));
        comboBox_ClockWise->setItemText(1, QCoreApplication::translate("ProjectionPreProcessorClass", "Anti Clockwise", nullptr));

        tabWidget_IOSettings->setTabText(tabWidget_IOSettings->indexOf(tab_IOInput), QCoreApplication::translate("ProjectionPreProcessorClass", "Input", nullptr));
        groupBox_IOOutput->setTitle(QString());
        groupBox_FileDirSelection->setTitle(QString());
        label_22->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Directory:", nullptr));
        pushButton_SelectOutputDir->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Select ...", nullptr));
        label_RawOutPattern->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Pattern: ", nullptr));
        label_OutputFileType->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "File Type:", nullptr));
        comboBox_OutputFileType->setItemText(0, QCoreApplication::translate("ProjectionPreProcessorClass", "RAW 32 Bit Real", nullptr));
        comboBox_OutputFileType->setItemText(1, QCoreApplication::translate("ProjectionPreProcessorClass", "RAW 16 Bit Unsigned Integer", nullptr));

        groupBox_SaveData->setTitle(QString());
        pushButton_SaveDataStart->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Save Data", nullptr));
        progressBar_Savedata->setFormat(QCoreApplication::translate("ProjectionPreProcessorClass", "%v Files saved", nullptr));
        tabWidget_IOSettings->setTabText(tabWidget_IOSettings->indexOf(tab_IOOutput), QCoreApplication::translate("ProjectionPreProcessorClass", "Save Data", nullptr));
        groupBox_MethodSelection->setTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "Method Selection", nullptr));
        checkBox_Normalize->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Normalize", nullptr));
        checkBox_OutlierSuppression->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Outlier/ Ring Artefact - Suppression", nullptr));
        checkBox_BHC->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "BHC", nullptr));
        checkBox_StripeReduction->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Strip Reduction", nullptr));
        groupBox_NormalizationOption->setTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "Normalization Options", nullptr));
        radioButton_UseFlatFieldNormalization->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Use Flat Field Image for Normalization", nullptr));
        radioButton_UseFlatWindowNormalization->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Use Selection Window", nullptr));
        checkBox_NoLogarithm->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Take no Logarithm", nullptr));
        checkBox_useDarkFlatCorrected->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Use Dark/Flat corrected Projection Image Stack (apply no Normalization)", nullptr));
        groupBox_Normalization->setTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "Settings", nullptr));
        label_FlatFieldImage->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Flat field image:", nullptr));
        pushButton_SelectFlat->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Select ...", nullptr));
        label_DarkFieldImage->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Dark field image:", nullptr));
        pushButton_SelectDark->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Select ...", nullptr));
        groupBox_NormWin->setTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "Normalization Window", nullptr));
        label_NormWinXPos->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "x pos:", nullptr));
        label_NormWinYPos->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "y pos:", nullptr));
        label_NormWinHeight->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "height:", nullptr));
        label_NormWinWidth->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "width:", nullptr));
        toolBox_ProcessingMethods->setItemText(toolBox_ProcessingMethods->indexOf(page_MethodNormalization), QCoreApplication::translate("ProjectionPreProcessorClass", "Normalization", nullptr));
        groupBox_6->setTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "Use", nullptr));
        checkBox_UseRAC->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Ring Artefact Suppression", nullptr));
        checkBox_UseOutlierSuppression->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Outlier Suppression", nullptr));
        groupBox_OutlierSettings->setTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "Settings Outliers", nullptr));
        label_CorrectionAlgo->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Correction Algorithm:", nullptr));
        comboBox_MethodSelection->setItemText(0, QCoreApplication::translate("ProjectionPreProcessorClass", "Sinogram Median 9", nullptr));
        comboBox_MethodSelection->setItemText(1, QCoreApplication::translate("ProjectionPreProcessorClass", "Sinogram Median/Mean 9", nullptr));

        label_SigmaMedian9->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Correct Outliers Sigma (median) >", nullptr));
        label_SigmaMean9->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Correct Outliers Sigma (mean) >", nullptr));
        toolBox_ProcessingMethods->setItemText(toolBox_ProcessingMethods->indexOf(page_MethodOutlier), QCoreApplication::translate("ProjectionPreProcessorClass", "Outlier / Ring Artefact", nullptr));
        groupBox_BHCSettings->setTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "Settings", nullptr));
        label_Formular->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Corrected grey value = A* Value + B*Value^R ", nullptr));
        label_BHC_CorrectionLinearConstantC->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Correction Linear Constant A = ", nullptr));
        label_BHC_CorrectionLinearConstantB->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Correction Linear Constant B = ", nullptr));
        label_BHC_CorrectionExpo->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Correction Exponent             R = ", nullptr));
        toolBox_ProcessingMethods->setItemText(toolBox_ProcessingMethods->indexOf(page_MethodBHC), QCoreApplication::translate("ProjectionPreProcessorClass", "BHC", nullptr));
        groupBox_StripeSettings->setTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "Settings", nullptr));
        label_PadMultFFT->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Padding Multiplier for FFT: ", nullptr));
        comboBox_PadMultFFT->setItemText(0, QCoreApplication::translate("ProjectionPreProcessorClass", "1", nullptr));
        comboBox_PadMultFFT->setItemText(1, QCoreApplication::translate("ProjectionPreProcessorClass", "2", nullptr));
        comboBox_PadMultFFT->setItemText(2, QCoreApplication::translate("ProjectionPreProcessorClass", "4", nullptr));
        comboBox_PadMultFFT->setItemText(3, QCoreApplication::translate("ProjectionPreProcessorClass", "8", nullptr));

        checkBox_FFTRunMultiThread->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Run Multithreaded", nullptr));
        toolBox_ProcessingMethods->setItemText(toolBox_ProcessingMethods->indexOf(page_StripeReduction), QCoreApplication::translate("ProjectionPreProcessorClass", "Sinogram / Stripe Reduction  ", nullptr));
        groupBox_EnhanceParams->setTitle(QString());
        checkBox_applyLorentzFilter->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Apply Lorentz Filter", nullptr));
        groupBox_8->setTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "Filter strenght ", nullptr));
        label_9->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Alpha:", nullptr));
        toolBox_ProcessingMethods->setItemText(toolBox_ProcessingMethods->indexOf(page_EdgeEnhancement), QCoreApplication::translate("ProjectionPreProcessorClass", "Edge Enhancement (Lorentz Filter)", nullptr));
        tabWidget_ParameterSettings->setTabText(tabWidget_ParameterSettings->indexOf(tab_BasicParamSettings), QCoreApplication::translate("ProjectionPreProcessorClass", "Basic", nullptr));
        groupBox_19->setTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "Advanced", nullptr));
        label_26->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Not implemented yet!", nullptr));
        tabWidget_ParameterSettings->setTabText(tabWidget_ParameterSettings->indexOf(tab_AdvancedParamSettings), QCoreApplication::translate("ProjectionPreProcessorClass", "Advanced", nullptr));
        groupBox_Running->setTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "Running", nullptr));
        groupBox->setTitle(QString());
        pushButton_Run->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Run", nullptr));
        pushButton_SaveSettingsForRun->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Check for Run", nullptr));
        pushButton_SaveMessageOutput->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Save Message Output ...", nullptr));
#if QT_CONFIG(tooltip)
        pushButton_CancelRun->setToolTip(QCoreApplication::translate("ProjectionPreProcessorClass", "Sorry not implemented yet!", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        pushButton_CancelRun->setStatusTip(QCoreApplication::translate("ProjectionPreProcessorClass", "Sorry not implemented yet!", nullptr));
#endif // QT_CONFIG(statustip)
        pushButton_CancelRun->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Cancel Run", nullptr));
        tabWidget_Running->setTabText(tabWidget_Running->indexOf(tab_Start), QCoreApplication::translate("ProjectionPreProcessorClass", "Start", nullptr));
        groupBox_runBatch->setTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "Batch", nullptr));
        label_Dummy->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Not implemented yet!", nullptr));
        tabWidget_Running->setTabText(tabWidget_Running->indexOf(tab_batch), QCoreApplication::translate("ProjectionPreProcessorClass", "Batch", nullptr));
        groupBox_MessageOutput->setTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "Output Messages", nullptr));
        label_ImageView->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Image", nullptr));
        label_SliceNr->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Slice Number:", nullptr));
        groupBox_ImageOperations->setTitle(QString());
        groupBox_2->setTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "Image processing", nullptr));
        label->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Equalize all Images:", nullptr));
        pushButton_applyEqualize->setText(QString());
        groupBox_3->setTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "Contrast", nullptr));
        label_ContrastSlope->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Slope", nullptr));
        label_contrastOffset->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Offset", nullptr));
        label_ContrastApply->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Apply to all Images:", nullptr));
        pushButton_ContrastApply->setText(QString());
        pushButton_UndoImageProcessing->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Undo", nullptr));
        progressBar_ImageProcessing->setFormat(QString());
        groupBox_4->setTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "Window Selection", nullptr));
        checkBox_EnableWindowSelection->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Enable normalize windows selection", nullptr));
        groupBox_5->setTitle(QString());
        label_xPosition->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "x Position:", nullptr));
        label_7->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Window width:", nullptr));
        label_6->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "y Position:", nullptr));
        label_8->setText(QCoreApplication::translate("ProjectionPreProcessorClass", "Window height:", nullptr));
        tabWidget_Projections->setTabText(tabWidget_Projections->indexOf(tab_ProjectionViewer), QCoreApplication::translate("ProjectionPreProcessorClass", "Projection Viewer", nullptr));
        tabWidget_Projections->setTabText(tabWidget_Projections->indexOf(tab_NOP), QCoreApplication::translate("ProjectionPreProcessorClass", "NOP", nullptr));
        menuFile->setTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "File", nullptr));
        menuTools->setTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "Tools", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("ProjectionPreProcessorClass", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ProjectionPreProcessorClass: public Ui_ProjectionPreProcessorClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECTIONPREPROCESSOR_H
