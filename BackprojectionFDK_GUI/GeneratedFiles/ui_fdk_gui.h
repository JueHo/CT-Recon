/********************************************************************************
** Form generated from reading UI file 'fdk_gui.ui'
**
** Created by: Qt User Interface Compiler version 5.15.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FDK_GUI_H
#define UI_FDK_GUI_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDockWidget>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QTreeWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_FDK_GUIClass
{
public:
    QAction *actionExit;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSave_as;
    QAction *actionUse_RDBMS;
    QAction *actionRDBMS_Management;
    QAction *actionImport_Project;
    QAction *actionToolbar;
    QAction *actionImage_View;
    QAction *actionOptions;
    QAction *actionCheck_Parameters;
    QAction *actionImport_convert_DETECT_data;
    QAction *actionVersion_1_1_Build_14082014;
    QAction *actionJuergen_hofmann_empa_ch;
    QAction *actionSubmit_Bug_juergen_hofmann_empa_ch;
    QWidget *centralWidget;
    QGridLayout *gridLayout_4;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QGridLayout *gridLayout_22;
    QVBoxLayout *verticalLayout_3;
    QGridLayout *gridLayout_Parameter_Sinogram_Settings;
    QGroupBox *groupBox;
    QGridLayout *gridLayout_16;
    QTabWidget *tabWidget;
    QWidget *tab_BasicParameters;
    QGridLayout *gridLayout_15;
    QSpacerItem *horizontalSpacer_24;
    QSpacerItem *verticalSpacer_2;
    QGridLayout *gridLayout_10;
    QGroupBox *GrBox_Projections;
    QGridLayout *gridLayout;
    QLabel *label_ImageWidth;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QSpinBox *SBox_ImgWidth;
    QLabel *label_ImageHeight;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer_2;
    QSpinBox *SBox_ImgHeight;
    QLabel *label_NumProjections;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_3;
    QSpinBox *SBox_NumberOfProjections;
    QLabel *label_AngleIncr;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_4;
    QDoubleSpinBox *DSBox_AngleIncr;
    QLabel *label_PixelSize;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer_5;
    QDoubleSpinBox *DSBOX_PixelSize;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *verticalSpacer;
    QGroupBox *GrBox_FilteringSettings;
    QGridLayout *gridLayout_5;
    QLabel *label_InputFormat;
    QHBoxLayout *horizontalLayout_19;
    QSpacerItem *horizontalSpacer_14;
    QComboBox *CBox_InDataFormat;
    QLabel *label_Filtertype;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer_16;
    QComboBox *CBox_FlipSinogramImage;
    QHBoxLayout *horizontalLayout_11;
    QSpacerItem *horizontalSpacer_15;
    QComboBox *CBox_FilterType;
    QHBoxLayout *horizontalLayout_18;
    QSpacerItem *horizontalSpacer_7;
    QSpinBox *SBox_NumStartIndex;
    QLabel *label_FlipSinogram;
    QLabel *label_SinoStartAtAngle;
    QHBoxLayout *horizontalLayout_17;
    QSpacerItem *horizontalSpacer_17;
    QDoubleSpinBox *DSBox_SinoStartAtAngle;
    QLabel *label_StartIndexSinogram;
    QGroupBox *GrBox_GeometrySetup;
    QGridLayout *gridLayout_3;
    QLabel *label_ShiftHorizontal;
    QHBoxLayout *horizontalLayout_10;
    QSpacerItem *horizontalSpacer_10;
    QDoubleSpinBox *DSBox_HorizontalShift;
    QCheckBox *checkBox_applyTiltAxCorr;
    QGroupBox *groupBox_ParamShiftCorrCurve;
    QGridLayout *gridLayout_21;
    QLabel *label_8;
    QDoubleSpinBox *doubleSpinBox_corrSlope_m;
    QLabel *label_9;
    QDoubleSpinBox *doubleSpinBox_corrOffset_c;
    QLabel *label_ShiftVertical;
    QHBoxLayout *horizontalLayout_12;
    QSpacerItem *horizontalSpacer_11;
    QDoubleSpinBox *DSBox_VerticalShift;
    QLabel *label_DSD;
    QHBoxLayout *horizontalLayout_13;
    QSpacerItem *horizontalSpacer_12;
    QDoubleSpinBox *DSBox_DistSrcDetector;
    QLabel *label_DSO;
    QHBoxLayout *horizontalLayout_14;
    QSpacerItem *horizontalSpacer_13;
    QDoubleSpinBox *DSBox_DistSrcRotCentre;
    QSpacerItem *horizontalSpacer_50;
    QWidget *tab_ReconParameter;
    QGridLayout *gridLayout_24;
    QGridLayout *gridLayout_8;
    QGroupBox *GrBox_ReconstructionParamters;
    QGridLayout *gridLayout_7;
    QHBoxLayout *horizontalLayout_24;
    QSpinBox *SBox_BinningFactor;
    QSpacerItem *horizontalSpacer_36;
    QFrame *line_2;
    QLabel *label_VolumeWidth;
    QHBoxLayout *horizontalLayout_39;
    QSpacerItem *horizontalSpacer_38;
    QSpinBox *SBox_VolumeWidth;
    QSpacerItem *horizontalSpacer_37;
    QLabel *label_VolumeHeight;
    QHBoxLayout *horizontalLayout_40;
    QSpacerItem *horizontalSpacer_40;
    QSpinBox *SBox_VolumeHeight;
    QSpacerItem *horizontalSpacer_45;
    QLabel *label_VolumeDepth;
    QHBoxLayout *horizontalLayout_41;
    QSpacerItem *horizontalSpacer_39;
    QSpinBox *SBox_VolumeDepth;
    QSpacerItem *horizontalSpacer_46;
    QFrame *line_3;
    QLabel *label_VolumeOriginX;
    QHBoxLayout *horizontalLayout_42;
    QSpacerItem *horizontalSpacer_43;
    QSpinBox *SBox_VolumeOriginX;
    QSpacerItem *horizontalSpacer_47;
    QLabel *label_VolumeOriginY;
    QHBoxLayout *horizontalLayout_43;
    QSpacerItem *horizontalSpacer_42;
    QSpinBox *SBox_VolumeOriginY;
    QSpacerItem *horizontalSpacer_48;
    QLabel *label_VolumeOriginZ;
    QHBoxLayout *horizontalLayout_44;
    QSpacerItem *horizontalSpacer_41;
    QSpinBox *SBox_VolumeOriginZ;
    QSpacerItem *horizontalSpacer_49;
    QFrame *line;
    QHBoxLayout *horizontalLayout_45;
    QSpacerItem *horizontalSpacer_44;
    QPushButton *Btn_GetVolumeFromSelection;
    QLabel *label_BinningFactor;
    QSpacerItem *horizontalSpacer_52;
    QSpacerItem *horizontalSpacer_53;
    QGroupBox *GrBox_TomoParameters;
    QFormLayout *formLayout;
    QLabel *label_TomoOutDataFormat;
    QHBoxLayout *horizontalLayout_25;
    QComboBox *CBox_TomoOutDataFormat;
    QSpacerItem *horizontalSpacer_51;
    QLabel *label_TomoName;
    QHBoxLayout *horizontalLayout_21;
    QLineEdit *LEd_TomoName;
    QLabel *label_TomoOutDir;
    QHBoxLayout *horizontalLayout_16;
    QLineEdit *LEd_TomoOutDir;
    QPushButton *Btn_SelTomoOutDir;
    QCheckBox *CkBox_WriteBlockFile;
    QLabel *label_WriteToBlockFile;
    QSpacerItem *verticalSpacer_11;
    QSpacerItem *horizontalSpacer_20;
    QSpacerItem *horizontalSpacer_21;
    QSpacerItem *verticalSpacer_3;
    QWidget *tab_AdvancedSettings;
    QGridLayout *gridLayout_6;
    QGridLayout *gridLayout_11;
    QGroupBox *grBox_SystemSettings;
    QVBoxLayout *verticalLayout_21;
    QGroupBox *GrBox_MemoryUsage;
    QVBoxLayout *verticalLayout_7;
    QGridLayout *gridLayout_13;
    QLabel *label_CPUMemUsage;
    QDoubleSpinBox *DSBox_CPUMemUsage;
    QLabel *label_GPUMemUsage;
    QDoubleSpinBox *DSBox_GPUMemUsage;
    QSpacerItem *horizontalSpacer_26;
    QSpacerItem *horizontalSpacer_29;
    QSpacerItem *horizontalSpacer_30;
    QGroupBox *GrBox_GPUPreferences;
    QVBoxLayout *verticalLayout_8;
    QGridLayout *gridLayout_12;
    QSpinBox *SBox_GPUThreadsX;
    QLabel *label_GPUThreadsY;
    QSpinBox *SBox_GPUThreadsY;
    QLabel *label_GPUThreadsX;
    QSpacerItem *horizontalSpacer_23;
    QSpacerItem *horizontalSpacer_31;
    QSpacerItem *horizontalSpacer_32;
    QLabel *label_GPUCompaVers;
    QComboBox *CBox_GPUCompaVers;
    QHBoxLayout *horizontalLayout_23;
    QHBoxLayout *horizontalLayout_22;
    QSpacerItem *horizontalSpacer_35;
    QLabel *label_Use;
    QSpinBox *SBox_UseNumGPUs;
    QLabel *label_GPUs;
    QSpacerItem *horizontalSpacer_22;
    QHBoxLayout *horizontalLayout_48;
    QSpacerItem *horizontalSpacer_64;
    QCheckBox *CkBox_EditSystemSettings;
    QGroupBox *GrBox_CTSystemSelection;
    QVBoxLayout *verticalLayout_18;
    QHBoxLayout *horizontalLayout_28;
    QSpacerItem *horizontalSpacer_61;
    QComboBox *CBox_CT_SystemSelection;
    QGroupBox *groupBox_6;
    QVBoxLayout *verticalLayout_19;
    QHBoxLayout *horizontalLayout_38;
    QRadioButton *radioButton_fullAngleRecon;
    QRadioButton *radioButton_limitedAngleRecon;
    QCheckBox *checkBox_useFileList;
    QSpacerItem *horizontalSpacer_25;
    QSpacerItem *horizontalSpacer_28;
    QSpacerItem *verticalSpacer_10;
    QSpacerItem *horizontalSpacer_65;
    QSpacerItem *horizontalSpacer_66;
    QSpacerItem *horizontalSpacer_67;
    QSpacerItem *horizontalSpacer_68;
    QSpacerItem *horizontalSpacer_69;
    QSpacerItem *horizontalSpacer_70;
    QGroupBox *groupBox_7;
    QVBoxLayout *verticalLayout_10;
    QCheckBox *CkBox_WriteToPreProcBlockFile;
    QCheckBox *CkBox_UsePreProcBlockFile;
    QCheckBox *CkBox_StoreConvTomoBlockFile;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout_20;
    QTabWidget *TabWidget_SinogramSettings;
    QWidget *tab_FullAngle;
    QGridLayout *gridLayout_19;
    QGroupBox *GrBox_FullAngleSinograms;
    QVBoxLayout *verticalLayout_5;
    QGroupBox *groupBox_3;
    QGridLayout *gridLayout_2;
    QLabel *label_SinogramDirectory;
    QHBoxLayout *horizontalLayout_8;
    QLineEdit *LEd_SinogramDirectory;
    QPushButton *Btn_SelectSinogramDirectory;
    QLabel *label_SinoNamePattern;
    QLineEdit *LEd_SinoNamePattern;
    QLabel *label_PreprocSinoDir;
    QHBoxLayout *horizontalLayout_20;
    QLineEdit *LEd_PreprocSinoDirectory;
    QPushButton *Btn_SelectPreprocSinoDir;
    QSpacerItem *verticalSpacer_12;
    QVBoxLayout *verticalLayout_4;
    QHBoxLayout *horizontalLayout_9;
    QPushButton *Btn_SelectSinograms;
    QSpacerItem *horizontalSpacer_6;
    QPushButton *Btn_RemoveSelection;
    QListWidget *ListWidget_SinogramList;
    QWidget *tab_LimAngle;
    QGridLayout *gridLayout_18;
    QGroupBox *GrBox_LimitAngleSinograms;
    QGridLayout *gridLayout_17;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_26;
    QVBoxLayout *verticalLayout;
    QPushButton *Btn_LimAngleAddSeg;
    QPushButton *Btn_LimAngleRemSeg;
    QSpacerItem *verticalSpacer_4;
    QTreeWidget *TreeWidget_LimAngleSeg;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_PreProcSinoDir;
    QSpacerItem *horizontalSpacer_19;
    QLineEdit *LEd_LimAnglePreProcDir;
    QPushButton *Btn_LimAnglePreProcDir;
    QGroupBox *GrBox_ExecuteReconstruction;
    QHBoxLayout *horizontalLayout_34;
    QHBoxLayout *horizontalLayout_32;
    QTabWidget *TabWidget_Reconstruction;
    QWidget *tab_SingleRecon;
    QGridLayout *gridLayout_9;
    QGroupBox *GrBox_SingleRecon;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_30;
    QCheckBox *CkBox_WeightFilter;
    QSpacerItem *horizontalSpacer_54;
    QLabel *label_NumberProcesses;
    QSpinBox *SBox_NumberOfMPIProcesses;
    QHBoxLayout *horizontalLayout_27;
    QCheckBox *CkBox_Backprojection;
    QSpacerItem *horizontalSpacer_9;
    QLabel *label_5;
    QComboBox *CBox_ViewDirection;
    QFrame *line_5;
    QGroupBox *groupBox_InterpolationType;
    QHBoxLayout *horizontalLayout_51;
    QRadioButton *radioButton_fast;
    QRadioButton *radioButton_accurate;
    QSpacerItem *verticalSpacer_8;
    QHBoxLayout *horizontalLayout_31;
    QSpacerItem *horizontalSpacer_60;
    QPushButton *Btn_RunReconstruction;
    QSpacerItem *horizontalSpacer_55;
    QSpacerItem *verticalSpacer_9;
    QGroupBox *GrBox_TerminateReconstruction;
    QHBoxLayout *horizontalLayout_35;
    QPushButton *Btn_StopWeightFilterProc;
    QSpacerItem *horizontalSpacer_57;
    QPushButton *Btn_StopReconstructionProc;
    QHBoxLayout *horizontalLayout_49;
    QSpacerItem *horizontalSpacer_34;
    QLabel *label;
    QLCDNumber *LCD_timing;
    QWidget *tab_BatchRecon;
    QGridLayout *gridLayout_14;
    QHBoxLayout *horizontalLayout_29;
    QVBoxLayout *verticalLayout_12;
    QPushButton *Btn_AddProjectToBatch;
    QPushButton *Btn_RemProjectToBatch;
    QSpacerItem *verticalSpacer_6;
    QPushButton *Btn_RunBatch;
    QSpacerItem *verticalSpacer_7;
    QPushButton *Btn_StopBatch;
    QListWidget *ListWidget_ReconProjectList;
    QGroupBox *groupBox_13;
    QVBoxLayout *verticalLayout_9;
    QTextEdit *Txt_ProcessOutput;
    QHBoxLayout *horizontalLayout_7;
    QPushButton *pushButton_SaveProcessOutput;
    QSpacerItem *horizontalSpacer_8;
    QPushButton *pushButton_ClearOutput;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menu;
    QMenu *menuDatabase;
    QMenu *menuView;
    QMenu *menuVersion;
    QMenu *menuBugs;
    QStatusBar *statusBar;
    QToolBar *toolBar;
    QDockWidget *dockWidget_ImageView;
    QWidget *dockWidgetContents_ImageView;
    QVBoxLayout *verticalLayout_14;
    QScrollArea *pw_containerScrollArea;
    QWidget *scrollAreaWidgetContents_ImageView;
    QGridLayout *gridLayout_23;
    QLabel *Dock_ImageArea;
    QLabel *label_ShowImageName;
    QGroupBox *groupBox_4;
    QGridLayout *gridLayout_25;
    QVBoxLayout *verticalLayout_15;
    QHBoxLayout *horizontalLayout_33;
    QSpinBox *spinBox;
    QSlider *horizontalSlider;
    QHBoxLayout *horizontalLayout_36;
    QPushButton *Btn_LoadImages;
    QSpacerItem *horizontalSpacer_58;
    QLabel *label_2;
    QSpinBox *spinBox_ImageWidth;
    QLabel *label_3;
    QSpinBox *spinBox_ImageHeight;
    QLabel *label_4;
    QComboBox *comboBox_FileType;
    QDockWidget *dockWidget_ProjectOptions;
    QWidget *dockWidgetContents_ProjectOptions;
    QVBoxLayout *verticalLayout_13;
    QGroupBox *groupBox_5;
    QVBoxLayout *verticalLayout_16;
    QHBoxLayout *horizontalLayout_47;
    QLineEdit *lineEdit_MPIPath;
    QPushButton *Btn_MPIPath;
    QHBoxLayout *horizontalLayout_46;
    QLineEdit *lineEdit_DataTopDir;
    QPushButton *Btn_DataTopDir;
    QFrame *line_6;
    QHBoxLayout *horizontalLayout_37;
    QSpacerItem *horizontalSpacer_59;
    QPushButton *Btn_SaveOptions;
    QSpacerItem *horizontalSpacer_63;
    QDockWidget *dockWidget_Database;
    QWidget *dockWidgetContents_Database;
    QVBoxLayout *verticalLayout_17;
    QLabel *label_6;
    QLabel *label_7;
    QButtonGroup *buttonGroup;

    void setupUi(QMainWindow *FDK_GUIClass)
    {
        if (FDK_GUIClass->objectName().isEmpty())
            FDK_GUIClass->setObjectName(QString::fromUtf8("FDK_GUIClass"));
        FDK_GUIClass->setEnabled(true);
        FDK_GUIClass->resize(1617, 1083);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(FDK_GUIClass->sizePolicy().hasHeightForWidth());
        FDK_GUIClass->setSizePolicy(sizePolicy);
        FDK_GUIClass->setMinimumSize(QSize(800, 600));
        FDK_GUIClass->setFocusPolicy(Qt::ClickFocus);
        QIcon icon;
        icon.addFile(QString::fromUtf8("FDK_GUI.ico"), QSize(), QIcon::Normal, QIcon::Off);
        FDK_GUIClass->setWindowIcon(icon);
        actionExit = new QAction(FDK_GUIClass);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionOpen = new QAction(FDK_GUIClass);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("Images/fileopen1.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen->setIcon(icon1);
        actionSave = new QAction(FDK_GUIClass);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("Images/file_save.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave->setIcon(icon2);
        actionSave_as = new QAction(FDK_GUIClass);
        actionSave_as->setObjectName(QString::fromUtf8("actionSave_as"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("Images/filesaveas.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_as->setIcon(icon3);
        actionUse_RDBMS = new QAction(FDK_GUIClass);
        actionUse_RDBMS->setObjectName(QString::fromUtf8("actionUse_RDBMS"));
        actionUse_RDBMS->setCheckable(true);
        actionUse_RDBMS->setChecked(false);
        actionUse_RDBMS->setEnabled(false);
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("Images/database.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon4.addFile(QString::fromUtf8("Images/database_ck.png"), QSize(), QIcon::Normal, QIcon::On);
        actionUse_RDBMS->setIcon(icon4);
        actionRDBMS_Management = new QAction(FDK_GUIClass);
        actionRDBMS_Management->setObjectName(QString::fromUtf8("actionRDBMS_Management"));
        actionRDBMS_Management->setEnabled(false);
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("Images/windowsvista-tableview.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRDBMS_Management->setIcon(icon5);
        actionImport_Project = new QAction(FDK_GUIClass);
        actionImport_Project->setObjectName(QString::fromUtf8("actionImport_Project"));
        actionImport_Project->setCheckable(true);
        actionImport_Project->setEnabled(false);
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("Images/ImportIntoDB.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionImport_Project->setIcon(icon6);
        actionToolbar = new QAction(FDK_GUIClass);
        actionToolbar->setObjectName(QString::fromUtf8("actionToolbar"));
        actionToolbar->setCheckable(true);
        actionToolbar->setChecked(false);
        actionImage_View = new QAction(FDK_GUIClass);
        actionImage_View->setObjectName(QString::fromUtf8("actionImage_View"));
        actionImage_View->setCheckable(true);
        actionImage_View->setEnabled(false);
        actionOptions = new QAction(FDK_GUIClass);
        actionOptions->setObjectName(QString::fromUtf8("actionOptions"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("Images/ProjOptions.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOptions->setIcon(icon7);
        actionCheck_Parameters = new QAction(FDK_GUIClass);
        actionCheck_Parameters->setObjectName(QString::fromUtf8("actionCheck_Parameters"));
        actionCheck_Parameters->setEnabled(false);
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("Images/checkparameters.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCheck_Parameters->setIcon(icon8);
        actionCheck_Parameters->setIconVisibleInMenu(true);
        actionImport_convert_DETECT_data = new QAction(FDK_GUIClass);
        actionImport_convert_DETECT_data->setObjectName(QString::fromUtf8("actionImport_convert_DETECT_data"));
        actionVersion_1_1_Build_14082014 = new QAction(FDK_GUIClass);
        actionVersion_1_1_Build_14082014->setObjectName(QString::fromUtf8("actionVersion_1_1_Build_14082014"));
        actionJuergen_hofmann_empa_ch = new QAction(FDK_GUIClass);
        actionJuergen_hofmann_empa_ch->setObjectName(QString::fromUtf8("actionJuergen_hofmann_empa_ch"));
        actionSubmit_Bug_juergen_hofmann_empa_ch = new QAction(FDK_GUIClass);
        actionSubmit_Bug_juergen_hofmann_empa_ch->setObjectName(QString::fromUtf8("actionSubmit_Bug_juergen_hofmann_empa_ch"));
        centralWidget = new QWidget(FDK_GUIClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(centralWidget->sizePolicy().hasHeightForWidth());
        centralWidget->setSizePolicy(sizePolicy1);
        centralWidget->setMinimumSize(QSize(0, 0));
        gridLayout_4 = new QGridLayout(centralWidget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 1199, 1084));
        sizePolicy1.setHeightForWidth(scrollAreaWidgetContents->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents->setSizePolicy(sizePolicy1);
        gridLayout_22 = new QGridLayout(scrollAreaWidgetContents);
        gridLayout_22->setSpacing(6);
        gridLayout_22->setContentsMargins(11, 11, 11, 11);
        gridLayout_22->setObjectName(QString::fromUtf8("gridLayout_22"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetMinimumSize);
        gridLayout_Parameter_Sinogram_Settings = new QGridLayout();
        gridLayout_Parameter_Sinogram_Settings->setSpacing(6);
        gridLayout_Parameter_Sinogram_Settings->setObjectName(QString::fromUtf8("gridLayout_Parameter_Sinogram_Settings"));
        groupBox = new QGroupBox(scrollAreaWidgetContents);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        gridLayout_16 = new QGridLayout(groupBox);
        gridLayout_16->setSpacing(6);
        gridLayout_16->setContentsMargins(11, 11, 11, 11);
        gridLayout_16->setObjectName(QString::fromUtf8("gridLayout_16"));
        tabWidget = new QTabWidget(groupBox);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(tabWidget->sizePolicy().hasHeightForWidth());
        tabWidget->setSizePolicy(sizePolicy2);
        tabWidget->setMinimumSize(QSize(0, 0));
        tab_BasicParameters = new QWidget();
        tab_BasicParameters->setObjectName(QString::fromUtf8("tab_BasicParameters"));
        gridLayout_15 = new QGridLayout(tab_BasicParameters);
        gridLayout_15->setSpacing(6);
        gridLayout_15->setContentsMargins(11, 11, 11, 11);
        gridLayout_15->setObjectName(QString::fromUtf8("gridLayout_15"));
        horizontalSpacer_24 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_15->addItem(horizontalSpacer_24, 0, 2, 1, 1);

        verticalSpacer_2 = new QSpacerItem(28, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_15->addItem(verticalSpacer_2, 1, 1, 1, 1);

        gridLayout_10 = new QGridLayout();
        gridLayout_10->setSpacing(6);
        gridLayout_10->setObjectName(QString::fromUtf8("gridLayout_10"));
        GrBox_Projections = new QGroupBox(tab_BasicParameters);
        GrBox_Projections->setObjectName(QString::fromUtf8("GrBox_Projections"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(2);
        sizePolicy3.setHeightForWidth(GrBox_Projections->sizePolicy().hasHeightForWidth());
        GrBox_Projections->setSizePolicy(sizePolicy3);
        gridLayout = new QGridLayout(GrBox_Projections);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label_ImageWidth = new QLabel(GrBox_Projections);
        label_ImageWidth->setObjectName(QString::fromUtf8("label_ImageWidth"));
        QSizePolicy sizePolicy4(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_ImageWidth->sizePolicy().hasHeightForWidth());
        label_ImageWidth->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(label_ImageWidth, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(1, 18, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        SBox_ImgWidth = new QSpinBox(GrBox_Projections);
        SBox_ImgWidth->setObjectName(QString::fromUtf8("SBox_ImgWidth"));
        QSizePolicy sizePolicy5(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(SBox_ImgWidth->sizePolicy().hasHeightForWidth());
        SBox_ImgWidth->setSizePolicy(sizePolicy5);
        SBox_ImgWidth->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        SBox_ImgWidth->setMinimum(0);
        SBox_ImgWidth->setMaximum(10000);
        SBox_ImgWidth->setValue(0);

        horizontalLayout->addWidget(SBox_ImgWidth);


        gridLayout->addLayout(horizontalLayout, 0, 1, 1, 1);

        label_ImageHeight = new QLabel(GrBox_Projections);
        label_ImageHeight->setObjectName(QString::fromUtf8("label_ImageHeight"));
        sizePolicy4.setHeightForWidth(label_ImageHeight->sizePolicy().hasHeightForWidth());
        label_ImageHeight->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(label_ImageHeight, 1, 0, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer_2 = new QSpacerItem(1, 18, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer_2);

        SBox_ImgHeight = new QSpinBox(GrBox_Projections);
        SBox_ImgHeight->setObjectName(QString::fromUtf8("SBox_ImgHeight"));
        sizePolicy5.setHeightForWidth(SBox_ImgHeight->sizePolicy().hasHeightForWidth());
        SBox_ImgHeight->setSizePolicy(sizePolicy5);
        SBox_ImgHeight->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        SBox_ImgHeight->setMinimum(0);
        SBox_ImgHeight->setMaximum(10000);
        SBox_ImgHeight->setValue(0);

        horizontalLayout_2->addWidget(SBox_ImgHeight);


        gridLayout->addLayout(horizontalLayout_2, 1, 1, 1, 1);

        label_NumProjections = new QLabel(GrBox_Projections);
        label_NumProjections->setObjectName(QString::fromUtf8("label_NumProjections"));
        sizePolicy4.setHeightForWidth(label_NumProjections->sizePolicy().hasHeightForWidth());
        label_NumProjections->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(label_NumProjections, 2, 0, 1, 1);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_3 = new QSpacerItem(1, 18, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);

        SBox_NumberOfProjections = new QSpinBox(GrBox_Projections);
        SBox_NumberOfProjections->setObjectName(QString::fromUtf8("SBox_NumberOfProjections"));
        sizePolicy5.setHeightForWidth(SBox_NumberOfProjections->sizePolicy().hasHeightForWidth());
        SBox_NumberOfProjections->setSizePolicy(sizePolicy5);
        SBox_NumberOfProjections->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        SBox_NumberOfProjections->setMinimum(0);
        SBox_NumberOfProjections->setMaximum(99999);
        SBox_NumberOfProjections->setValue(0);

        horizontalLayout_3->addWidget(SBox_NumberOfProjections);


        gridLayout->addLayout(horizontalLayout_3, 2, 1, 1, 1);

        label_AngleIncr = new QLabel(GrBox_Projections);
        label_AngleIncr->setObjectName(QString::fromUtf8("label_AngleIncr"));
        label_AngleIncr->setEnabled(false);

        gridLayout->addWidget(label_AngleIncr, 3, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer_4 = new QSpacerItem(1, 18, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_4);

        DSBox_AngleIncr = new QDoubleSpinBox(GrBox_Projections);
        DSBox_AngleIncr->setObjectName(QString::fromUtf8("DSBox_AngleIncr"));
        DSBox_AngleIncr->setEnabled(false);
        sizePolicy5.setHeightForWidth(DSBox_AngleIncr->sizePolicy().hasHeightForWidth());
        DSBox_AngleIncr->setSizePolicy(sizePolicy5);
        DSBox_AngleIncr->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        DSBox_AngleIncr->setDecimals(8);
        DSBox_AngleIncr->setMinimum(-360.000000000000000);
        DSBox_AngleIncr->setMaximum(360.000000000000000);
        DSBox_AngleIncr->setSingleStep(0.100000000000000);
        DSBox_AngleIncr->setValue(0.000000000000000);

        horizontalLayout_4->addWidget(DSBox_AngleIncr);


        gridLayout->addLayout(horizontalLayout_4, 3, 1, 1, 1);

        label_PixelSize = new QLabel(GrBox_Projections);
        label_PixelSize->setObjectName(QString::fromUtf8("label_PixelSize"));
        sizePolicy4.setHeightForWidth(label_PixelSize->sizePolicy().hasHeightForWidth());
        label_PixelSize->setSizePolicy(sizePolicy4);

        gridLayout->addWidget(label_PixelSize, 4, 0, 1, 1);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer_5 = new QSpacerItem(1, 18, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_5);

        DSBOX_PixelSize = new QDoubleSpinBox(GrBox_Projections);
        DSBOX_PixelSize->setObjectName(QString::fromUtf8("DSBOX_PixelSize"));
        sizePolicy5.setHeightForWidth(DSBOX_PixelSize->sizePolicy().hasHeightForWidth());
        DSBOX_PixelSize->setSizePolicy(sizePolicy5);
        DSBOX_PixelSize->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        DSBOX_PixelSize->setDecimals(6);
        DSBOX_PixelSize->setMinimum(0.000100000000000);
        DSBOX_PixelSize->setMaximum(10.000000000000000);
        DSBOX_PixelSize->setSingleStep(0.000100000000000);
        DSBOX_PixelSize->setValue(0.100000000000000);

        horizontalLayout_5->addWidget(DSBOX_PixelSize);


        gridLayout->addLayout(horizontalLayout_5, 4, 1, 1, 1);


        gridLayout_10->addWidget(GrBox_Projections, 0, 0, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_10->addItem(verticalSpacer_5, 1, 0, 1, 1);

        verticalSpacer = new QSpacerItem(13, 13, QSizePolicy::Minimum, QSizePolicy::Fixed);

        gridLayout_10->addItem(verticalSpacer, 3, 0, 1, 1);

        GrBox_FilteringSettings = new QGroupBox(tab_BasicParameters);
        GrBox_FilteringSettings->setObjectName(QString::fromUtf8("GrBox_FilteringSettings"));
        gridLayout_5 = new QGridLayout(GrBox_FilteringSettings);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        label_InputFormat = new QLabel(GrBox_FilteringSettings);
        label_InputFormat->setObjectName(QString::fromUtf8("label_InputFormat"));

        gridLayout_5->addWidget(label_InputFormat, 0, 0, 1, 1);

        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        horizontalSpacer_14 = new QSpacerItem(1, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_19->addItem(horizontalSpacer_14);

        CBox_InDataFormat = new QComboBox(GrBox_FilteringSettings);
        CBox_InDataFormat->addItem(QString());
        CBox_InDataFormat->addItem(QString());
        CBox_InDataFormat->addItem(QString());
        CBox_InDataFormat->addItem(QString());
        CBox_InDataFormat->addItem(QString());
        CBox_InDataFormat->addItem(QString());
        CBox_InDataFormat->setObjectName(QString::fromUtf8("CBox_InDataFormat"));
        CBox_InDataFormat->setMaximumSize(QSize(70, 16777215));

        horizontalLayout_19->addWidget(CBox_InDataFormat);


        gridLayout_5->addLayout(horizontalLayout_19, 0, 1, 1, 2);

        label_Filtertype = new QLabel(GrBox_FilteringSettings);
        label_Filtertype->setObjectName(QString::fromUtf8("label_Filtertype"));

        gridLayout_5->addWidget(label_Filtertype, 3, 0, 1, 1);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setSpacing(6);
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer_16 = new QSpacerItem(1, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer_16);

        CBox_FlipSinogramImage = new QComboBox(GrBox_FilteringSettings);
        CBox_FlipSinogramImage->addItem(QString());
        CBox_FlipSinogramImage->addItem(QString());
        CBox_FlipSinogramImage->addItem(QString());
        CBox_FlipSinogramImage->addItem(QString());
        CBox_FlipSinogramImage->setObjectName(QString::fromUtf8("CBox_FlipSinogramImage"));
        CBox_FlipSinogramImage->setEnabled(false);

        horizontalLayout_6->addWidget(CBox_FlipSinogramImage);


        gridLayout_5->addLayout(horizontalLayout_6, 4, 1, 1, 2);

        horizontalLayout_11 = new QHBoxLayout();
        horizontalLayout_11->setSpacing(6);
        horizontalLayout_11->setObjectName(QString::fromUtf8("horizontalLayout_11"));
        horizontalSpacer_15 = new QSpacerItem(1, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_11->addItem(horizontalSpacer_15);

        CBox_FilterType = new QComboBox(GrBox_FilteringSettings);
        CBox_FilterType->addItem(QString());
        CBox_FilterType->addItem(QString());
        CBox_FilterType->addItem(QString());
        CBox_FilterType->setObjectName(QString::fromUtf8("CBox_FilterType"));
        CBox_FilterType->setMaximumSize(QSize(95, 16777215));

        horizontalLayout_11->addWidget(CBox_FilterType);


        gridLayout_5->addLayout(horizontalLayout_11, 3, 1, 1, 2);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setSpacing(6);
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        horizontalSpacer_7 = new QSpacerItem(1, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_18->addItem(horizontalSpacer_7);

        SBox_NumStartIndex = new QSpinBox(GrBox_FilteringSettings);
        SBox_NumStartIndex->setObjectName(QString::fromUtf8("SBox_NumStartIndex"));
        SBox_NumStartIndex->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        SBox_NumStartIndex->setMaximum(2048);
        SBox_NumStartIndex->setValue(1);

        horizontalLayout_18->addWidget(SBox_NumStartIndex);


        gridLayout_5->addLayout(horizontalLayout_18, 1, 2, 1, 1);

        label_FlipSinogram = new QLabel(GrBox_FilteringSettings);
        label_FlipSinogram->setObjectName(QString::fromUtf8("label_FlipSinogram"));
        label_FlipSinogram->setEnabled(false);

        gridLayout_5->addWidget(label_FlipSinogram, 4, 0, 1, 1);

        label_SinoStartAtAngle = new QLabel(GrBox_FilteringSettings);
        label_SinoStartAtAngle->setObjectName(QString::fromUtf8("label_SinoStartAtAngle"));

        gridLayout_5->addWidget(label_SinoStartAtAngle, 2, 0, 1, 1);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setSpacing(6);
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        horizontalSpacer_17 = new QSpacerItem(1, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_17->addItem(horizontalSpacer_17);

        DSBox_SinoStartAtAngle = new QDoubleSpinBox(GrBox_FilteringSettings);
        DSBox_SinoStartAtAngle->setObjectName(QString::fromUtf8("DSBox_SinoStartAtAngle"));
        DSBox_SinoStartAtAngle->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        DSBox_SinoStartAtAngle->setDecimals(2);
        DSBox_SinoStartAtAngle->setMaximum(360.000000000000000);

        horizontalLayout_17->addWidget(DSBox_SinoStartAtAngle);


        gridLayout_5->addLayout(horizontalLayout_17, 2, 1, 1, 2);

        label_StartIndexSinogram = new QLabel(GrBox_FilteringSettings);
        label_StartIndexSinogram->setObjectName(QString::fromUtf8("label_StartIndexSinogram"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(1);
        sizePolicy6.setHeightForWidth(label_StartIndexSinogram->sizePolicy().hasHeightForWidth());
        label_StartIndexSinogram->setSizePolicy(sizePolicy6);

        gridLayout_5->addWidget(label_StartIndexSinogram, 1, 0, 1, 2);


        gridLayout_10->addWidget(GrBox_FilteringSettings, 4, 0, 1, 1);

        GrBox_GeometrySetup = new QGroupBox(tab_BasicParameters);
        GrBox_GeometrySetup->setObjectName(QString::fromUtf8("GrBox_GeometrySetup"));
        sizePolicy2.setHeightForWidth(GrBox_GeometrySetup->sizePolicy().hasHeightForWidth());
        GrBox_GeometrySetup->setSizePolicy(sizePolicy2);
        gridLayout_3 = new QGridLayout(GrBox_GeometrySetup);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_ShiftHorizontal = new QLabel(GrBox_GeometrySetup);
        label_ShiftHorizontal->setObjectName(QString::fromUtf8("label_ShiftHorizontal"));
        sizePolicy4.setHeightForWidth(label_ShiftHorizontal->sizePolicy().hasHeightForWidth());
        label_ShiftHorizontal->setSizePolicy(sizePolicy4);

        gridLayout_3->addWidget(label_ShiftHorizontal, 0, 0, 1, 1);

        horizontalLayout_10 = new QHBoxLayout();
        horizontalLayout_10->setSpacing(6);
        horizontalLayout_10->setObjectName(QString::fromUtf8("horizontalLayout_10"));
        horizontalSpacer_10 = new QSpacerItem(1, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_10->addItem(horizontalSpacer_10);

        DSBox_HorizontalShift = new QDoubleSpinBox(GrBox_GeometrySetup);
        DSBox_HorizontalShift->setObjectName(QString::fromUtf8("DSBox_HorizontalShift"));
        sizePolicy4.setHeightForWidth(DSBox_HorizontalShift->sizePolicy().hasHeightForWidth());
        DSBox_HorizontalShift->setSizePolicy(sizePolicy4);
        DSBox_HorizontalShift->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        DSBox_HorizontalShift->setMinimum(-2100.000000000000000);
        DSBox_HorizontalShift->setMaximum(2100.000000000000000);
        DSBox_HorizontalShift->setSingleStep(0.100000000000000);

        horizontalLayout_10->addWidget(DSBox_HorizontalShift);


        gridLayout_3->addLayout(horizontalLayout_10, 0, 1, 1, 2);

        checkBox_applyTiltAxCorr = new QCheckBox(GrBox_GeometrySetup);
        checkBox_applyTiltAxCorr->setObjectName(QString::fromUtf8("checkBox_applyTiltAxCorr"));

        gridLayout_3->addWidget(checkBox_applyTiltAxCorr, 1, 0, 1, 1);

        groupBox_ParamShiftCorrCurve = new QGroupBox(GrBox_GeometrySetup);
        groupBox_ParamShiftCorrCurve->setObjectName(QString::fromUtf8("groupBox_ParamShiftCorrCurve"));
        groupBox_ParamShiftCorrCurve->setEnabled(false);
        QSizePolicy sizePolicy7(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy7.setHorizontalStretch(2);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(groupBox_ParamShiftCorrCurve->sizePolicy().hasHeightForWidth());
        groupBox_ParamShiftCorrCurve->setSizePolicy(sizePolicy7);
        gridLayout_21 = new QGridLayout(groupBox_ParamShiftCorrCurve);
        gridLayout_21->setSpacing(6);
        gridLayout_21->setContentsMargins(11, 11, 11, 11);
        gridLayout_21->setObjectName(QString::fromUtf8("gridLayout_21"));
        label_8 = new QLabel(groupBox_ParamShiftCorrCurve);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        gridLayout_21->addWidget(label_8, 0, 0, 1, 1);

        doubleSpinBox_corrSlope_m = new QDoubleSpinBox(groupBox_ParamShiftCorrCurve);
        doubleSpinBox_corrSlope_m->setObjectName(QString::fromUtf8("doubleSpinBox_corrSlope_m"));
        doubleSpinBox_corrSlope_m->setDecimals(8);
        doubleSpinBox_corrSlope_m->setMinimum(-10000.000000000000000);
        doubleSpinBox_corrSlope_m->setMaximum(10000.000000000000000);
        doubleSpinBox_corrSlope_m->setSingleStep(0.100000000000000);

        gridLayout_21->addWidget(doubleSpinBox_corrSlope_m, 0, 1, 1, 1);

        label_9 = new QLabel(groupBox_ParamShiftCorrCurve);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        gridLayout_21->addWidget(label_9, 1, 0, 1, 1);

        doubleSpinBox_corrOffset_c = new QDoubleSpinBox(groupBox_ParamShiftCorrCurve);
        doubleSpinBox_corrOffset_c->setObjectName(QString::fromUtf8("doubleSpinBox_corrOffset_c"));
        doubleSpinBox_corrOffset_c->setDecimals(8);
        doubleSpinBox_corrOffset_c->setMinimum(-10000.000000000000000);
        doubleSpinBox_corrOffset_c->setMaximum(10000.000000000000000);
        doubleSpinBox_corrOffset_c->setSingleStep(0.100000000000000);

        gridLayout_21->addWidget(doubleSpinBox_corrOffset_c, 1, 1, 1, 1);


        gridLayout_3->addWidget(groupBox_ParamShiftCorrCurve, 1, 2, 1, 1);

        label_ShiftVertical = new QLabel(GrBox_GeometrySetup);
        label_ShiftVertical->setObjectName(QString::fromUtf8("label_ShiftVertical"));
        sizePolicy4.setHeightForWidth(label_ShiftVertical->sizePolicy().hasHeightForWidth());
        label_ShiftVertical->setSizePolicy(sizePolicy4);

        gridLayout_3->addWidget(label_ShiftVertical, 2, 0, 1, 1);

        horizontalLayout_12 = new QHBoxLayout();
        horizontalLayout_12->setSpacing(6);
        horizontalLayout_12->setObjectName(QString::fromUtf8("horizontalLayout_12"));
        horizontalSpacer_11 = new QSpacerItem(1, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_12->addItem(horizontalSpacer_11);

        DSBox_VerticalShift = new QDoubleSpinBox(GrBox_GeometrySetup);
        DSBox_VerticalShift->setObjectName(QString::fromUtf8("DSBox_VerticalShift"));
        sizePolicy4.setHeightForWidth(DSBox_VerticalShift->sizePolicy().hasHeightForWidth());
        DSBox_VerticalShift->setSizePolicy(sizePolicy4);
        DSBox_VerticalShift->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        DSBox_VerticalShift->setMinimum(-2100.000000000000000);
        DSBox_VerticalShift->setMaximum(2100.000000000000000);
        DSBox_VerticalShift->setSingleStep(0.100000000000000);
        DSBox_VerticalShift->setValue(0.000000000000000);

        horizontalLayout_12->addWidget(DSBox_VerticalShift);


        gridLayout_3->addLayout(horizontalLayout_12, 2, 1, 1, 2);

        label_DSD = new QLabel(GrBox_GeometrySetup);
        label_DSD->setObjectName(QString::fromUtf8("label_DSD"));
        sizePolicy4.setHeightForWidth(label_DSD->sizePolicy().hasHeightForWidth());
        label_DSD->setSizePolicy(sizePolicy4);

        gridLayout_3->addWidget(label_DSD, 3, 0, 1, 1);

        horizontalLayout_13 = new QHBoxLayout();
        horizontalLayout_13->setSpacing(6);
        horizontalLayout_13->setObjectName(QString::fromUtf8("horizontalLayout_13"));
        horizontalSpacer_12 = new QSpacerItem(1, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_13->addItem(horizontalSpacer_12);

        DSBox_DistSrcDetector = new QDoubleSpinBox(GrBox_GeometrySetup);
        DSBox_DistSrcDetector->setObjectName(QString::fromUtf8("DSBox_DistSrcDetector"));
        sizePolicy4.setHeightForWidth(DSBox_DistSrcDetector->sizePolicy().hasHeightForWidth());
        DSBox_DistSrcDetector->setSizePolicy(sizePolicy4);
        DSBox_DistSrcDetector->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        DSBox_DistSrcDetector->setDecimals(6);
        DSBox_DistSrcDetector->setMinimum(0.000000000000000);
        DSBox_DistSrcDetector->setMaximum(5000.000000000000000);
        DSBox_DistSrcDetector->setSingleStep(10.000000000000000);
        DSBox_DistSrcDetector->setValue(2.000000000000000);

        horizontalLayout_13->addWidget(DSBox_DistSrcDetector);


        gridLayout_3->addLayout(horizontalLayout_13, 3, 1, 1, 2);

        label_DSO = new QLabel(GrBox_GeometrySetup);
        label_DSO->setObjectName(QString::fromUtf8("label_DSO"));
        sizePolicy4.setHeightForWidth(label_DSO->sizePolicy().hasHeightForWidth());
        label_DSO->setSizePolicy(sizePolicy4);

        gridLayout_3->addWidget(label_DSO, 4, 0, 1, 2);

        horizontalLayout_14 = new QHBoxLayout();
        horizontalLayout_14->setSpacing(6);
        horizontalLayout_14->setObjectName(QString::fromUtf8("horizontalLayout_14"));
        horizontalSpacer_13 = new QSpacerItem(1, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_14->addItem(horizontalSpacer_13);

        DSBox_DistSrcRotCentre = new QDoubleSpinBox(GrBox_GeometrySetup);
        DSBox_DistSrcRotCentre->setObjectName(QString::fromUtf8("DSBox_DistSrcRotCentre"));
        sizePolicy4.setHeightForWidth(DSBox_DistSrcRotCentre->sizePolicy().hasHeightForWidth());
        DSBox_DistSrcRotCentre->setSizePolicy(sizePolicy4);
        DSBox_DistSrcRotCentre->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        DSBox_DistSrcRotCentre->setDecimals(6);
        DSBox_DistSrcRotCentre->setMinimum(1.000000000000000);
        DSBox_DistSrcRotCentre->setMaximum(5000.000000000000000);
        DSBox_DistSrcRotCentre->setSingleStep(1.000000000000000);
        DSBox_DistSrcRotCentre->setValue(1.000000000000000);

        horizontalLayout_14->addWidget(DSBox_DistSrcRotCentre);


        gridLayout_3->addLayout(horizontalLayout_14, 4, 2, 1, 1);


        gridLayout_10->addWidget(GrBox_GeometrySetup, 2, 0, 1, 1);


        gridLayout_15->addLayout(gridLayout_10, 0, 1, 1, 1);

        horizontalSpacer_50 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_15->addItem(horizontalSpacer_50, 0, 0, 1, 1);

        tabWidget->addTab(tab_BasicParameters, QString());
        tab_ReconParameter = new QWidget();
        tab_ReconParameter->setObjectName(QString::fromUtf8("tab_ReconParameter"));
        gridLayout_24 = new QGridLayout(tab_ReconParameter);
        gridLayout_24->setSpacing(6);
        gridLayout_24->setContentsMargins(11, 11, 11, 11);
        gridLayout_24->setObjectName(QString::fromUtf8("gridLayout_24"));
        gridLayout_8 = new QGridLayout();
        gridLayout_8->setSpacing(6);
        gridLayout_8->setObjectName(QString::fromUtf8("gridLayout_8"));
        gridLayout_8->setSizeConstraint(QLayout::SetMinimumSize);
        GrBox_ReconstructionParamters = new QGroupBox(tab_ReconParameter);
        GrBox_ReconstructionParamters->setObjectName(QString::fromUtf8("GrBox_ReconstructionParamters"));
        sizePolicy2.setHeightForWidth(GrBox_ReconstructionParamters->sizePolicy().hasHeightForWidth());
        GrBox_ReconstructionParamters->setSizePolicy(sizePolicy2);
        gridLayout_7 = new QGridLayout(GrBox_ReconstructionParamters);
        gridLayout_7->setSpacing(6);
        gridLayout_7->setContentsMargins(11, 11, 11, 11);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        horizontalLayout_24 = new QHBoxLayout();
        horizontalLayout_24->setSpacing(6);
        horizontalLayout_24->setObjectName(QString::fromUtf8("horizontalLayout_24"));
        SBox_BinningFactor = new QSpinBox(GrBox_ReconstructionParamters);
        SBox_BinningFactor->setObjectName(QString::fromUtf8("SBox_BinningFactor"));
        SBox_BinningFactor->setEnabled(false);
        SBox_BinningFactor->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        SBox_BinningFactor->setMinimum(1);
        SBox_BinningFactor->setMaximum(8);

        horizontalLayout_24->addWidget(SBox_BinningFactor);

        horizontalSpacer_36 = new QSpacerItem(106, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_24->addItem(horizontalSpacer_36);


        gridLayout_7->addLayout(horizontalLayout_24, 0, 2, 1, 2);

        line_2 = new QFrame(GrBox_ReconstructionParamters);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        sizePolicy5.setHeightForWidth(line_2->sizePolicy().hasHeightForWidth());
        line_2->setSizePolicy(sizePolicy5);
        line_2->setMinimumSize(QSize(0, 0));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        gridLayout_7->addWidget(line_2, 1, 1, 1, 3);

        label_VolumeWidth = new QLabel(GrBox_ReconstructionParamters);
        label_VolumeWidth->setObjectName(QString::fromUtf8("label_VolumeWidth"));

        gridLayout_7->addWidget(label_VolumeWidth, 2, 1, 1, 2);

        horizontalLayout_39 = new QHBoxLayout();
        horizontalLayout_39->setSpacing(6);
        horizontalLayout_39->setObjectName(QString::fromUtf8("horizontalLayout_39"));
        horizontalSpacer_38 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_39->addItem(horizontalSpacer_38);

        SBox_VolumeWidth = new QSpinBox(GrBox_ReconstructionParamters);
        SBox_VolumeWidth->setObjectName(QString::fromUtf8("SBox_VolumeWidth"));
        SBox_VolumeWidth->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        SBox_VolumeWidth->setMinimum(0);
        SBox_VolumeWidth->setMaximum(10000);
        SBox_VolumeWidth->setSingleStep(1);
        SBox_VolumeWidth->setValue(0);

        horizontalLayout_39->addWidget(SBox_VolumeWidth);

        horizontalSpacer_37 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_39->addItem(horizontalSpacer_37);


        gridLayout_7->addLayout(horizontalLayout_39, 2, 3, 1, 1);

        label_VolumeHeight = new QLabel(GrBox_ReconstructionParamters);
        label_VolumeHeight->setObjectName(QString::fromUtf8("label_VolumeHeight"));

        gridLayout_7->addWidget(label_VolumeHeight, 3, 1, 1, 2);

        horizontalLayout_40 = new QHBoxLayout();
        horizontalLayout_40->setSpacing(6);
        horizontalLayout_40->setObjectName(QString::fromUtf8("horizontalLayout_40"));
        horizontalSpacer_40 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_40->addItem(horizontalSpacer_40);

        SBox_VolumeHeight = new QSpinBox(GrBox_ReconstructionParamters);
        SBox_VolumeHeight->setObjectName(QString::fromUtf8("SBox_VolumeHeight"));
        SBox_VolumeHeight->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        SBox_VolumeHeight->setMaximum(10000);
        SBox_VolumeHeight->setSingleStep(100);
        SBox_VolumeHeight->setValue(0);

        horizontalLayout_40->addWidget(SBox_VolumeHeight);

        horizontalSpacer_45 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_40->addItem(horizontalSpacer_45);


        gridLayout_7->addLayout(horizontalLayout_40, 3, 3, 1, 1);

        label_VolumeDepth = new QLabel(GrBox_ReconstructionParamters);
        label_VolumeDepth->setObjectName(QString::fromUtf8("label_VolumeDepth"));

        gridLayout_7->addWidget(label_VolumeDepth, 4, 1, 1, 2);

        horizontalLayout_41 = new QHBoxLayout();
        horizontalLayout_41->setSpacing(6);
        horizontalLayout_41->setObjectName(QString::fromUtf8("horizontalLayout_41"));
        horizontalSpacer_39 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_41->addItem(horizontalSpacer_39);

        SBox_VolumeDepth = new QSpinBox(GrBox_ReconstructionParamters);
        SBox_VolumeDepth->setObjectName(QString::fromUtf8("SBox_VolumeDepth"));
        SBox_VolumeDepth->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        SBox_VolumeDepth->setMinimum(0);
        SBox_VolumeDepth->setMaximum(10000);
        SBox_VolumeDepth->setSingleStep(1);
        SBox_VolumeDepth->setValue(0);

        horizontalLayout_41->addWidget(SBox_VolumeDepth);

        horizontalSpacer_46 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_41->addItem(horizontalSpacer_46);


        gridLayout_7->addLayout(horizontalLayout_41, 4, 3, 1, 1);

        line_3 = new QFrame(GrBox_ReconstructionParamters);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_7->addWidget(line_3, 5, 1, 1, 3);

        label_VolumeOriginX = new QLabel(GrBox_ReconstructionParamters);
        label_VolumeOriginX->setObjectName(QString::fromUtf8("label_VolumeOriginX"));

        gridLayout_7->addWidget(label_VolumeOriginX, 6, 1, 1, 2);

        horizontalLayout_42 = new QHBoxLayout();
        horizontalLayout_42->setSpacing(6);
        horizontalLayout_42->setObjectName(QString::fromUtf8("horizontalLayout_42"));
        horizontalSpacer_43 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_42->addItem(horizontalSpacer_43);

        SBox_VolumeOriginX = new QSpinBox(GrBox_ReconstructionParamters);
        SBox_VolumeOriginX->setObjectName(QString::fromUtf8("SBox_VolumeOriginX"));
        SBox_VolumeOriginX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        SBox_VolumeOriginX->setMaximum(4048);

        horizontalLayout_42->addWidget(SBox_VolumeOriginX);

        horizontalSpacer_47 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_42->addItem(horizontalSpacer_47);


        gridLayout_7->addLayout(horizontalLayout_42, 6, 3, 1, 1);

        label_VolumeOriginY = new QLabel(GrBox_ReconstructionParamters);
        label_VolumeOriginY->setObjectName(QString::fromUtf8("label_VolumeOriginY"));

        gridLayout_7->addWidget(label_VolumeOriginY, 7, 1, 1, 2);

        horizontalLayout_43 = new QHBoxLayout();
        horizontalLayout_43->setSpacing(6);
        horizontalLayout_43->setObjectName(QString::fromUtf8("horizontalLayout_43"));
        horizontalSpacer_42 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_43->addItem(horizontalSpacer_42);

        SBox_VolumeOriginY = new QSpinBox(GrBox_ReconstructionParamters);
        SBox_VolumeOriginY->setObjectName(QString::fromUtf8("SBox_VolumeOriginY"));
        SBox_VolumeOriginY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        SBox_VolumeOriginY->setMaximum(4048);

        horizontalLayout_43->addWidget(SBox_VolumeOriginY);

        horizontalSpacer_48 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_43->addItem(horizontalSpacer_48);


        gridLayout_7->addLayout(horizontalLayout_43, 7, 3, 1, 1);

        label_VolumeOriginZ = new QLabel(GrBox_ReconstructionParamters);
        label_VolumeOriginZ->setObjectName(QString::fromUtf8("label_VolumeOriginZ"));

        gridLayout_7->addWidget(label_VolumeOriginZ, 8, 1, 1, 2);

        horizontalLayout_44 = new QHBoxLayout();
        horizontalLayout_44->setSpacing(6);
        horizontalLayout_44->setObjectName(QString::fromUtf8("horizontalLayout_44"));
        horizontalSpacer_41 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_44->addItem(horizontalSpacer_41);

        SBox_VolumeOriginZ = new QSpinBox(GrBox_ReconstructionParamters);
        SBox_VolumeOriginZ->setObjectName(QString::fromUtf8("SBox_VolumeOriginZ"));
        SBox_VolumeOriginZ->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        SBox_VolumeOriginZ->setMaximum(4048);

        horizontalLayout_44->addWidget(SBox_VolumeOriginZ);

        horizontalSpacer_49 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_44->addItem(horizontalSpacer_49);


        gridLayout_7->addLayout(horizontalLayout_44, 8, 3, 1, 1);

        line = new QFrame(GrBox_ReconstructionParamters);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        gridLayout_7->addWidget(line, 9, 1, 1, 3);

        horizontalLayout_45 = new QHBoxLayout();
        horizontalLayout_45->setSpacing(6);
        horizontalLayout_45->setObjectName(QString::fromUtf8("horizontalLayout_45"));
        horizontalSpacer_44 = new QSpacerItem(1, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        horizontalLayout_45->addItem(horizontalSpacer_44);

        Btn_GetVolumeFromSelection = new QPushButton(GrBox_ReconstructionParamters);
        Btn_GetVolumeFromSelection->setObjectName(QString::fromUtf8("Btn_GetVolumeFromSelection"));
        Btn_GetVolumeFromSelection->setEnabled(false);
        Btn_GetVolumeFromSelection->setStyleSheet(QString::fromUtf8("background-color: yellow;"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8("Images/Volume.png"), QSize(), QIcon::Normal, QIcon::Off);
        Btn_GetVolumeFromSelection->setIcon(icon9);

        horizontalLayout_45->addWidget(Btn_GetVolumeFromSelection);


        gridLayout_7->addLayout(horizontalLayout_45, 10, 1, 1, 3);

        label_BinningFactor = new QLabel(GrBox_ReconstructionParamters);
        label_BinningFactor->setObjectName(QString::fromUtf8("label_BinningFactor"));
        label_BinningFactor->setMinimumSize(QSize(69, 0));

        gridLayout_7->addWidget(label_BinningFactor, 0, 1, 1, 1);

        horizontalSpacer_52 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_52, 4, 0, 1, 1);

        horizontalSpacer_53 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_7->addItem(horizontalSpacer_53, 6, 4, 1, 1);


        gridLayout_8->addWidget(GrBox_ReconstructionParamters, 0, 0, 1, 1);

        GrBox_TomoParameters = new QGroupBox(tab_ReconParameter);
        GrBox_TomoParameters->setObjectName(QString::fromUtf8("GrBox_TomoParameters"));
        formLayout = new QFormLayout(GrBox_TomoParameters);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        label_TomoOutDataFormat = new QLabel(GrBox_TomoParameters);
        label_TomoOutDataFormat->setObjectName(QString::fromUtf8("label_TomoOutDataFormat"));

        formLayout->setWidget(0, QFormLayout::SpanningRole, label_TomoOutDataFormat);

        horizontalLayout_25 = new QHBoxLayout();
        horizontalLayout_25->setSpacing(6);
        horizontalLayout_25->setObjectName(QString::fromUtf8("horizontalLayout_25"));
        CBox_TomoOutDataFormat = new QComboBox(GrBox_TomoParameters);
        CBox_TomoOutDataFormat->addItem(QString());
        CBox_TomoOutDataFormat->addItem(QString());
        CBox_TomoOutDataFormat->addItem(QString());
        CBox_TomoOutDataFormat->addItem(QString());
        CBox_TomoOutDataFormat->setObjectName(QString::fromUtf8("CBox_TomoOutDataFormat"));
        CBox_TomoOutDataFormat->setMaximumSize(QSize(70, 16777215));
        CBox_TomoOutDataFormat->setLayoutDirection(Qt::LeftToRight);

        horizontalLayout_25->addWidget(CBox_TomoOutDataFormat);

        horizontalSpacer_51 = new QSpacerItem(88, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_25->addItem(horizontalSpacer_51);


        formLayout->setLayout(1, QFormLayout::FieldRole, horizontalLayout_25);

        label_TomoName = new QLabel(GrBox_TomoParameters);
        label_TomoName->setObjectName(QString::fromUtf8("label_TomoName"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_TomoName);

        horizontalLayout_21 = new QHBoxLayout();
        horizontalLayout_21->setSpacing(6);
        horizontalLayout_21->setObjectName(QString::fromUtf8("horizontalLayout_21"));
        LEd_TomoName = new QLineEdit(GrBox_TomoParameters);
        LEd_TomoName->setObjectName(QString::fromUtf8("LEd_TomoName"));
        LEd_TomoName->setMinimumSize(QSize(180, 0));
        LEd_TomoName->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_21->addWidget(LEd_TomoName);


        formLayout->setLayout(2, QFormLayout::FieldRole, horizontalLayout_21);

        label_TomoOutDir = new QLabel(GrBox_TomoParameters);
        label_TomoOutDir->setObjectName(QString::fromUtf8("label_TomoOutDir"));

        formLayout->setWidget(3, QFormLayout::SpanningRole, label_TomoOutDir);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setSpacing(6);
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        LEd_TomoOutDir = new QLineEdit(GrBox_TomoParameters);
        LEd_TomoOutDir->setObjectName(QString::fromUtf8("LEd_TomoOutDir"));
        LEd_TomoOutDir->setMinimumSize(QSize(144, 0));
        LEd_TomoOutDir->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_16->addWidget(LEd_TomoOutDir);

        Btn_SelTomoOutDir = new QPushButton(GrBox_TomoParameters);
        Btn_SelTomoOutDir->setObjectName(QString::fromUtf8("Btn_SelTomoOutDir"));
        Btn_SelTomoOutDir->setStyleSheet(QString::fromUtf8("background: white;"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8("Images/diropen-32.png"), QSize(), QIcon::Normal, QIcon::Off);
        Btn_SelTomoOutDir->setIcon(icon10);

        horizontalLayout_16->addWidget(Btn_SelTomoOutDir);


        formLayout->setLayout(4, QFormLayout::FieldRole, horizontalLayout_16);

        CkBox_WriteBlockFile = new QCheckBox(GrBox_TomoParameters);
        CkBox_WriteBlockFile->setObjectName(QString::fromUtf8("CkBox_WriteBlockFile"));
        CkBox_WriteBlockFile->setEnabled(false);
        CkBox_WriteBlockFile->setChecked(false);

        formLayout->setWidget(5, QFormLayout::FieldRole, CkBox_WriteBlockFile);

        label_WriteToBlockFile = new QLabel(GrBox_TomoParameters);
        label_WriteToBlockFile->setObjectName(QString::fromUtf8("label_WriteToBlockFile"));
        label_WriteToBlockFile->setEnabled(false);

        formLayout->setWidget(5, QFormLayout::LabelRole, label_WriteToBlockFile);


        gridLayout_8->addWidget(GrBox_TomoParameters, 2, 0, 1, 1);

        verticalSpacer_11 = new QSpacerItem(5, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_8->addItem(verticalSpacer_11, 1, 0, 1, 1);


        gridLayout_24->addLayout(gridLayout_8, 0, 1, 1, 1);

        horizontalSpacer_20 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_24->addItem(horizontalSpacer_20, 0, 0, 1, 1);

        horizontalSpacer_21 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_24->addItem(horizontalSpacer_21, 0, 2, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_24->addItem(verticalSpacer_3, 1, 1, 1, 1);

        tabWidget->addTab(tab_ReconParameter, QString());
        tab_AdvancedSettings = new QWidget();
        tab_AdvancedSettings->setObjectName(QString::fromUtf8("tab_AdvancedSettings"));
        gridLayout_6 = new QGridLayout(tab_AdvancedSettings);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        gridLayout_11 = new QGridLayout();
        gridLayout_11->setSpacing(6);
        gridLayout_11->setObjectName(QString::fromUtf8("gridLayout_11"));
        grBox_SystemSettings = new QGroupBox(tab_AdvancedSettings);
        grBox_SystemSettings->setObjectName(QString::fromUtf8("grBox_SystemSettings"));
        grBox_SystemSettings->setEnabled(true);
        verticalLayout_21 = new QVBoxLayout(grBox_SystemSettings);
        verticalLayout_21->setSpacing(6);
        verticalLayout_21->setContentsMargins(11, 11, 11, 11);
        verticalLayout_21->setObjectName(QString::fromUtf8("verticalLayout_21"));
        GrBox_MemoryUsage = new QGroupBox(grBox_SystemSettings);
        GrBox_MemoryUsage->setObjectName(QString::fromUtf8("GrBox_MemoryUsage"));
        GrBox_MemoryUsage->setEnabled(false);
        verticalLayout_7 = new QVBoxLayout(GrBox_MemoryUsage);
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setContentsMargins(11, 11, 11, 11);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        gridLayout_13 = new QGridLayout();
        gridLayout_13->setSpacing(6);
        gridLayout_13->setObjectName(QString::fromUtf8("gridLayout_13"));
        label_CPUMemUsage = new QLabel(GrBox_MemoryUsage);
        label_CPUMemUsage->setObjectName(QString::fromUtf8("label_CPUMemUsage"));

        gridLayout_13->addWidget(label_CPUMemUsage, 0, 1, 1, 1);

        DSBox_CPUMemUsage = new QDoubleSpinBox(GrBox_MemoryUsage);
        DSBox_CPUMemUsage->setObjectName(QString::fromUtf8("DSBox_CPUMemUsage"));
        DSBox_CPUMemUsage->setMinimum(1.000000000000000);
        DSBox_CPUMemUsage->setMaximum(100.000000000000000);
        DSBox_CPUMemUsage->setValue(95.000000000000000);

        gridLayout_13->addWidget(DSBox_CPUMemUsage, 0, 3, 1, 1);

        label_GPUMemUsage = new QLabel(GrBox_MemoryUsage);
        label_GPUMemUsage->setObjectName(QString::fromUtf8("label_GPUMemUsage"));

        gridLayout_13->addWidget(label_GPUMemUsage, 1, 1, 1, 1);

        DSBox_GPUMemUsage = new QDoubleSpinBox(GrBox_MemoryUsage);
        DSBox_GPUMemUsage->setObjectName(QString::fromUtf8("DSBox_GPUMemUsage"));
        DSBox_GPUMemUsage->setMinimum(1.000000000000000);
        DSBox_GPUMemUsage->setMaximum(100.000000000000000);
        DSBox_GPUMemUsage->setValue(90.000000000000000);

        gridLayout_13->addWidget(DSBox_GPUMemUsage, 1, 3, 1, 1);

        horizontalSpacer_26 = new QSpacerItem(5, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_13->addItem(horizontalSpacer_26, 0, 2, 1, 1);

        horizontalSpacer_29 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_13->addItem(horizontalSpacer_29, 0, 0, 1, 1);

        horizontalSpacer_30 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_13->addItem(horizontalSpacer_30, 0, 4, 1, 1);


        verticalLayout_7->addLayout(gridLayout_13);


        verticalLayout_21->addWidget(GrBox_MemoryUsage);

        GrBox_GPUPreferences = new QGroupBox(grBox_SystemSettings);
        GrBox_GPUPreferences->setObjectName(QString::fromUtf8("GrBox_GPUPreferences"));
        GrBox_GPUPreferences->setEnabled(false);
        verticalLayout_8 = new QVBoxLayout(GrBox_GPUPreferences);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        gridLayout_12 = new QGridLayout();
        gridLayout_12->setSpacing(6);
        gridLayout_12->setObjectName(QString::fromUtf8("gridLayout_12"));
        SBox_GPUThreadsX = new QSpinBox(GrBox_GPUPreferences);
        SBox_GPUThreadsX->setObjectName(QString::fromUtf8("SBox_GPUThreadsX"));
        SBox_GPUThreadsX->setMinimum(1);
        SBox_GPUThreadsX->setValue(16);

        gridLayout_12->addWidget(SBox_GPUThreadsX, 0, 3, 1, 1);

        label_GPUThreadsY = new QLabel(GrBox_GPUPreferences);
        label_GPUThreadsY->setObjectName(QString::fromUtf8("label_GPUThreadsY"));

        gridLayout_12->addWidget(label_GPUThreadsY, 1, 1, 1, 1);

        SBox_GPUThreadsY = new QSpinBox(GrBox_GPUPreferences);
        SBox_GPUThreadsY->setObjectName(QString::fromUtf8("SBox_GPUThreadsY"));
        SBox_GPUThreadsY->setMinimum(1);
        SBox_GPUThreadsY->setValue(16);

        gridLayout_12->addWidget(SBox_GPUThreadsY, 1, 3, 1, 1);

        label_GPUThreadsX = new QLabel(GrBox_GPUPreferences);
        label_GPUThreadsX->setObjectName(QString::fromUtf8("label_GPUThreadsX"));

        gridLayout_12->addWidget(label_GPUThreadsX, 0, 1, 1, 1);

        horizontalSpacer_23 = new QSpacerItem(5, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_12->addItem(horizontalSpacer_23, 0, 2, 1, 1);

        horizontalSpacer_31 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_12->addItem(horizontalSpacer_31, 0, 0, 1, 1);

        horizontalSpacer_32 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_12->addItem(horizontalSpacer_32, 0, 4, 1, 1);

        label_GPUCompaVers = new QLabel(GrBox_GPUPreferences);
        label_GPUCompaVers->setObjectName(QString::fromUtf8("label_GPUCompaVers"));

        gridLayout_12->addWidget(label_GPUCompaVers, 2, 1, 1, 1);

        CBox_GPUCompaVers = new QComboBox(GrBox_GPUPreferences);
        CBox_GPUCompaVers->addItem(QString());
        CBox_GPUCompaVers->addItem(QString());
        CBox_GPUCompaVers->setObjectName(QString::fromUtf8("CBox_GPUCompaVers"));

        gridLayout_12->addWidget(CBox_GPUCompaVers, 2, 3, 1, 1);


        verticalLayout_8->addLayout(gridLayout_12);

        horizontalLayout_23 = new QHBoxLayout();
        horizontalLayout_23->setSpacing(6);
        horizontalLayout_23->setObjectName(QString::fromUtf8("horizontalLayout_23"));

        verticalLayout_8->addLayout(horizontalLayout_23);

        horizontalLayout_22 = new QHBoxLayout();
        horizontalLayout_22->setSpacing(6);
        horizontalLayout_22->setObjectName(QString::fromUtf8("horizontalLayout_22"));
        horizontalSpacer_35 = new QSpacerItem(5, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_35);

        label_Use = new QLabel(GrBox_GPUPreferences);
        label_Use->setObjectName(QString::fromUtf8("label_Use"));

        horizontalLayout_22->addWidget(label_Use);

        SBox_UseNumGPUs = new QSpinBox(GrBox_GPUPreferences);
        SBox_UseNumGPUs->setObjectName(QString::fromUtf8("SBox_UseNumGPUs"));
        SBox_UseNumGPUs->setMinimum(1);
        SBox_UseNumGPUs->setMaximum(8);
        SBox_UseNumGPUs->setSingleStep(1);

        horizontalLayout_22->addWidget(SBox_UseNumGPUs);

        label_GPUs = new QLabel(GrBox_GPUPreferences);
        label_GPUs->setObjectName(QString::fromUtf8("label_GPUs"));

        horizontalLayout_22->addWidget(label_GPUs);

        horizontalSpacer_22 = new QSpacerItem(5, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_22->addItem(horizontalSpacer_22);


        verticalLayout_8->addLayout(horizontalLayout_22);


        verticalLayout_21->addWidget(GrBox_GPUPreferences);

        horizontalLayout_48 = new QHBoxLayout();
        horizontalLayout_48->setSpacing(6);
        horizontalLayout_48->setObjectName(QString::fromUtf8("horizontalLayout_48"));
        horizontalSpacer_64 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_48->addItem(horizontalSpacer_64);

        CkBox_EditSystemSettings = new QCheckBox(grBox_SystemSettings);
        CkBox_EditSystemSettings->setObjectName(QString::fromUtf8("CkBox_EditSystemSettings"));
        CkBox_EditSystemSettings->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_48->addWidget(CkBox_EditSystemSettings);


        verticalLayout_21->addLayout(horizontalLayout_48);


        gridLayout_11->addWidget(grBox_SystemSettings, 0, 0, 1, 1);


        gridLayout_6->addLayout(gridLayout_11, 0, 1, 1, 1);

        GrBox_CTSystemSelection = new QGroupBox(tab_AdvancedSettings);
        GrBox_CTSystemSelection->setObjectName(QString::fromUtf8("GrBox_CTSystemSelection"));
        verticalLayout_18 = new QVBoxLayout(GrBox_CTSystemSelection);
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setContentsMargins(11, 11, 11, 11);
        verticalLayout_18->setObjectName(QString::fromUtf8("verticalLayout_18"));
        horizontalLayout_28 = new QHBoxLayout();
        horizontalLayout_28->setSpacing(6);
        horizontalLayout_28->setObjectName(QString::fromUtf8("horizontalLayout_28"));
        horizontalSpacer_61 = new QSpacerItem(5, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_28->addItem(horizontalSpacer_61);

        CBox_CT_SystemSelection = new QComboBox(GrBox_CTSystemSelection);
        CBox_CT_SystemSelection->addItem(QString());
        CBox_CT_SystemSelection->addItem(QString());
        CBox_CT_SystemSelection->setObjectName(QString::fromUtf8("CBox_CT_SystemSelection"));
        CBox_CT_SystemSelection->setEnabled(true);
        CBox_CT_SystemSelection->setMaxVisibleItems(1);

        horizontalLayout_28->addWidget(CBox_CT_SystemSelection);


        verticalLayout_18->addLayout(horizontalLayout_28);


        gridLayout_6->addWidget(GrBox_CTSystemSelection, 3, 1, 1, 1);

        groupBox_6 = new QGroupBox(tab_AdvancedSettings);
        groupBox_6->setObjectName(QString::fromUtf8("groupBox_6"));
        verticalLayout_19 = new QVBoxLayout(groupBox_6);
        verticalLayout_19->setSpacing(6);
        verticalLayout_19->setContentsMargins(11, 11, 11, 11);
        verticalLayout_19->setObjectName(QString::fromUtf8("verticalLayout_19"));
        horizontalLayout_38 = new QHBoxLayout();
        horizontalLayout_38->setSpacing(6);
        horizontalLayout_38->setObjectName(QString::fromUtf8("horizontalLayout_38"));
        radioButton_fullAngleRecon = new QRadioButton(groupBox_6);
        radioButton_fullAngleRecon->setObjectName(QString::fromUtf8("radioButton_fullAngleRecon"));
        radioButton_fullAngleRecon->setLayoutDirection(Qt::RightToLeft);
        radioButton_fullAngleRecon->setChecked(true);

        horizontalLayout_38->addWidget(radioButton_fullAngleRecon);

        radioButton_limitedAngleRecon = new QRadioButton(groupBox_6);
        radioButton_limitedAngleRecon->setObjectName(QString::fromUtf8("radioButton_limitedAngleRecon"));
        radioButton_limitedAngleRecon->setEnabled(false);
        radioButton_limitedAngleRecon->setLayoutDirection(Qt::RightToLeft);

        horizontalLayout_38->addWidget(radioButton_limitedAngleRecon);


        verticalLayout_19->addLayout(horizontalLayout_38);

        checkBox_useFileList = new QCheckBox(groupBox_6);
        checkBox_useFileList->setObjectName(QString::fromUtf8("checkBox_useFileList"));
        checkBox_useFileList->setEnabled(false);
        checkBox_useFileList->setLayoutDirection(Qt::RightToLeft);

        verticalLayout_19->addWidget(checkBox_useFileList);


        gridLayout_6->addWidget(groupBox_6, 2, 1, 1, 1);

        horizontalSpacer_25 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_25, 0, 0, 1, 1);

        horizontalSpacer_28 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_28, 0, 2, 1, 1);

        verticalSpacer_10 = new QSpacerItem(10, 1, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_10, 5, 1, 1, 1);

        horizontalSpacer_65 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_65, 3, 0, 1, 1);

        horizontalSpacer_66 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_66, 3, 2, 1, 1);

        horizontalSpacer_67 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_67, 2, 0, 1, 1);

        horizontalSpacer_68 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_68, 2, 2, 1, 1);

        horizontalSpacer_69 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_69, 4, 0, 1, 1);

        horizontalSpacer_70 = new QSpacerItem(1, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_70, 4, 2, 1, 1);

        groupBox_7 = new QGroupBox(tab_AdvancedSettings);
        groupBox_7->setObjectName(QString::fromUtf8("groupBox_7"));
        groupBox_7->setEnabled(false);
        groupBox_7->setCursor(QCursor(Qt::PointingHandCursor));
        verticalLayout_10 = new QVBoxLayout(groupBox_7);
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setContentsMargins(11, 11, 11, 11);
        verticalLayout_10->setObjectName(QString::fromUtf8("verticalLayout_10"));
        CkBox_WriteToPreProcBlockFile = new QCheckBox(groupBox_7);
        CkBox_WriteToPreProcBlockFile->setObjectName(QString::fromUtf8("CkBox_WriteToPreProcBlockFile"));
        CkBox_WriteToPreProcBlockFile->setEnabled(false);
        CkBox_WriteToPreProcBlockFile->setCursor(QCursor(Qt::PointingHandCursor));
        CkBox_WriteToPreProcBlockFile->setChecked(false);

        verticalLayout_10->addWidget(CkBox_WriteToPreProcBlockFile);

        CkBox_UsePreProcBlockFile = new QCheckBox(groupBox_7);
        CkBox_UsePreProcBlockFile->setObjectName(QString::fromUtf8("CkBox_UsePreProcBlockFile"));
        CkBox_UsePreProcBlockFile->setEnabled(false);
        CkBox_UsePreProcBlockFile->setCursor(QCursor(Qt::PointingHandCursor));
        CkBox_UsePreProcBlockFile->setChecked(false);

        verticalLayout_10->addWidget(CkBox_UsePreProcBlockFile);

        CkBox_StoreConvTomoBlockFile = new QCheckBox(groupBox_7);
        CkBox_StoreConvTomoBlockFile->setObjectName(QString::fromUtf8("CkBox_StoreConvTomoBlockFile"));
        CkBox_StoreConvTomoBlockFile->setEnabled(false);
        CkBox_StoreConvTomoBlockFile->setCursor(QCursor(Qt::PointingHandCursor));

        verticalLayout_10->addWidget(CkBox_StoreConvTomoBlockFile);


        gridLayout_6->addWidget(groupBox_7, 4, 1, 1, 1);

        tabWidget->addTab(tab_AdvancedSettings, QString());

        gridLayout_16->addWidget(tabWidget, 0, 0, 1, 1);


        gridLayout_Parameter_Sinogram_Settings->addWidget(groupBox, 0, 0, 1, 1);

        groupBox_2 = new QGroupBox(scrollAreaWidgetContents);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        sizePolicy2.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy2);
        gridLayout_20 = new QGridLayout(groupBox_2);
        gridLayout_20->setSpacing(6);
        gridLayout_20->setContentsMargins(11, 11, 11, 11);
        gridLayout_20->setObjectName(QString::fromUtf8("gridLayout_20"));
        TabWidget_SinogramSettings = new QTabWidget(groupBox_2);
        TabWidget_SinogramSettings->setObjectName(QString::fromUtf8("TabWidget_SinogramSettings"));
        TabWidget_SinogramSettings->setEnabled(true);
        sizePolicy2.setHeightForWidth(TabWidget_SinogramSettings->sizePolicy().hasHeightForWidth());
        TabWidget_SinogramSettings->setSizePolicy(sizePolicy2);
        tab_FullAngle = new QWidget();
        tab_FullAngle->setObjectName(QString::fromUtf8("tab_FullAngle"));
        gridLayout_19 = new QGridLayout(tab_FullAngle);
        gridLayout_19->setSpacing(6);
        gridLayout_19->setContentsMargins(11, 11, 11, 11);
        gridLayout_19->setObjectName(QString::fromUtf8("gridLayout_19"));
        GrBox_FullAngleSinograms = new QGroupBox(tab_FullAngle);
        GrBox_FullAngleSinograms->setObjectName(QString::fromUtf8("GrBox_FullAngleSinograms"));
        sizePolicy2.setHeightForWidth(GrBox_FullAngleSinograms->sizePolicy().hasHeightForWidth());
        GrBox_FullAngleSinograms->setSizePolicy(sizePolicy2);
        verticalLayout_5 = new QVBoxLayout(GrBox_FullAngleSinograms);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        groupBox_3 = new QGroupBox(GrBox_FullAngleSinograms);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        gridLayout_2 = new QGridLayout(groupBox_3);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_SinogramDirectory = new QLabel(groupBox_3);
        label_SinogramDirectory->setObjectName(QString::fromUtf8("label_SinogramDirectory"));
        sizePolicy2.setHeightForWidth(label_SinogramDirectory->sizePolicy().hasHeightForWidth());
        label_SinogramDirectory->setSizePolicy(sizePolicy2);

        gridLayout_2->addWidget(label_SinogramDirectory, 0, 0, 1, 1);

        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setSpacing(6);
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        horizontalLayout_8->setSizeConstraint(QLayout::SetDefaultConstraint);
        LEd_SinogramDirectory = new QLineEdit(groupBox_3);
        LEd_SinogramDirectory->setObjectName(QString::fromUtf8("LEd_SinogramDirectory"));
        LEd_SinogramDirectory->setEnabled(false);
        QSizePolicy sizePolicy8(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy8.setHorizontalStretch(1);
        sizePolicy8.setVerticalStretch(0);
        sizePolicy8.setHeightForWidth(LEd_SinogramDirectory->sizePolicy().hasHeightForWidth());
        LEd_SinogramDirectory->setSizePolicy(sizePolicy8);
        LEd_SinogramDirectory->setMinimumSize(QSize(260, 0));
        LEd_SinogramDirectory->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_8->addWidget(LEd_SinogramDirectory);

        Btn_SelectSinogramDirectory = new QPushButton(groupBox_3);
        Btn_SelectSinogramDirectory->setObjectName(QString::fromUtf8("Btn_SelectSinogramDirectory"));
        Btn_SelectSinogramDirectory->setStyleSheet(QString::fromUtf8("background: white;"));
        Btn_SelectSinogramDirectory->setIcon(icon10);

        horizontalLayout_8->addWidget(Btn_SelectSinogramDirectory);


        gridLayout_2->addLayout(horizontalLayout_8, 0, 1, 1, 1);

        label_SinoNamePattern = new QLabel(groupBox_3);
        label_SinoNamePattern->setObjectName(QString::fromUtf8("label_SinoNamePattern"));
        sizePolicy2.setHeightForWidth(label_SinoNamePattern->sizePolicy().hasHeightForWidth());
        label_SinoNamePattern->setSizePolicy(sizePolicy2);
        label_SinoNamePattern->setMinimumSize(QSize(110, 0));
        label_SinoNamePattern->setMaximumSize(QSize(100, 16777215));

        gridLayout_2->addWidget(label_SinoNamePattern, 1, 0, 1, 1);

        LEd_SinoNamePattern = new QLineEdit(groupBox_3);
        LEd_SinoNamePattern->setObjectName(QString::fromUtf8("LEd_SinoNamePattern"));
        LEd_SinoNamePattern->setEnabled(true);
        QSizePolicy sizePolicy9(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy9.setHorizontalStretch(0);
        sizePolicy9.setVerticalStretch(0);
        sizePolicy9.setHeightForWidth(LEd_SinoNamePattern->sizePolicy().hasHeightForWidth());
        LEd_SinoNamePattern->setSizePolicy(sizePolicy9);
        LEd_SinoNamePattern->setMinimumSize(QSize(280, 0));
        LEd_SinoNamePattern->setStyleSheet(QString::fromUtf8(""));
        LEd_SinoNamePattern->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        gridLayout_2->addWidget(LEd_SinoNamePattern, 1, 1, 1, 1);

        label_PreprocSinoDir = new QLabel(groupBox_3);
        label_PreprocSinoDir->setObjectName(QString::fromUtf8("label_PreprocSinoDir"));

        gridLayout_2->addWidget(label_PreprocSinoDir, 2, 0, 1, 1);

        horizontalLayout_20 = new QHBoxLayout();
        horizontalLayout_20->setSpacing(6);
        horizontalLayout_20->setObjectName(QString::fromUtf8("horizontalLayout_20"));
        LEd_PreprocSinoDirectory = new QLineEdit(groupBox_3);
        LEd_PreprocSinoDirectory->setObjectName(QString::fromUtf8("LEd_PreprocSinoDirectory"));
        sizePolicy9.setHeightForWidth(LEd_PreprocSinoDirectory->sizePolicy().hasHeightForWidth());
        LEd_PreprocSinoDirectory->setSizePolicy(sizePolicy9);
        LEd_PreprocSinoDirectory->setMinimumSize(QSize(320, 0));
        LEd_PreprocSinoDirectory->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_20->addWidget(LEd_PreprocSinoDirectory);

        Btn_SelectPreprocSinoDir = new QPushButton(groupBox_3);
        Btn_SelectPreprocSinoDir->setObjectName(QString::fromUtf8("Btn_SelectPreprocSinoDir"));
        Btn_SelectPreprocSinoDir->setStyleSheet(QString::fromUtf8("background: white;"));
        Btn_SelectPreprocSinoDir->setIcon(icon10);

        horizontalLayout_20->addWidget(Btn_SelectPreprocSinoDir);


        gridLayout_2->addLayout(horizontalLayout_20, 2, 1, 1, 1);


        verticalLayout_5->addWidget(groupBox_3);

        verticalSpacer_12 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_12);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setSpacing(6);
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        Btn_SelectSinograms = new QPushButton(GrBox_FullAngleSinograms);
        Btn_SelectSinograms->setObjectName(QString::fromUtf8("Btn_SelectSinograms"));
        Btn_SelectSinograms->setEnabled(false);
        Btn_SelectSinograms->setStyleSheet(QString::fromUtf8("background: white"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8("Images/fileopen2.png"), QSize(), QIcon::Normal, QIcon::Off);
        Btn_SelectSinograms->setIcon(icon11);
        Btn_SelectSinograms->setIconSize(QSize(32, 32));
        Btn_SelectSinograms->setAutoRepeat(false);

        horizontalLayout_9->addWidget(Btn_SelectSinograms);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_9->addItem(horizontalSpacer_6);

        Btn_RemoveSelection = new QPushButton(GrBox_FullAngleSinograms);
        Btn_RemoveSelection->setObjectName(QString::fromUtf8("Btn_RemoveSelection"));
        Btn_RemoveSelection->setEnabled(false);
        Btn_RemoveSelection->setStyleSheet(QString::fromUtf8("background: white"));
        QIcon icon12;
        icon12.addFile(QString::fromUtf8("Images/modelview-begin-remove-rows.png"), QSize(), QIcon::Normal, QIcon::Off);
        Btn_RemoveSelection->setIcon(icon12);
        Btn_RemoveSelection->setIconSize(QSize(32, 32));

        horizontalLayout_9->addWidget(Btn_RemoveSelection);


        verticalLayout_4->addLayout(horizontalLayout_9);

        ListWidget_SinogramList = new QListWidget(GrBox_FullAngleSinograms);
        ListWidget_SinogramList->setObjectName(QString::fromUtf8("ListWidget_SinogramList"));
        ListWidget_SinogramList->setEnabled(false);
        sizePolicy2.setHeightForWidth(ListWidget_SinogramList->sizePolicy().hasHeightForWidth());
        ListWidget_SinogramList->setSizePolicy(sizePolicy2);
        ListWidget_SinogramList->setMinimumSize(QSize(400, 300));
        ListWidget_SinogramList->setAcceptDrops(true);
        ListWidget_SinogramList->setLayoutDirection(Qt::LeftToRight);
        ListWidget_SinogramList->setEditTriggers(QAbstractItemView::NoEditTriggers);
        ListWidget_SinogramList->setDragDropMode(QAbstractItemView::DropOnly);
        ListWidget_SinogramList->setAlternatingRowColors(true);
        ListWidget_SinogramList->setSelectionMode(QAbstractItemView::ExtendedSelection);
        ListWidget_SinogramList->setTextElideMode(Qt::ElideLeft);
        ListWidget_SinogramList->setSelectionRectVisible(true);
        ListWidget_SinogramList->setSortingEnabled(true);

        verticalLayout_4->addWidget(ListWidget_SinogramList);


        verticalLayout_5->addLayout(verticalLayout_4);


        gridLayout_19->addWidget(GrBox_FullAngleSinograms, 0, 0, 1, 1);

        QIcon icon13;
        icon13.addFile(QString::fromUtf8("Images/FullAngleR.png"), QSize(), QIcon::Normal, QIcon::Off);
        TabWidget_SinogramSettings->addTab(tab_FullAngle, icon13, QString());
        tab_LimAngle = new QWidget();
        tab_LimAngle->setObjectName(QString::fromUtf8("tab_LimAngle"));
        tab_LimAngle->setEnabled(false);
        gridLayout_18 = new QGridLayout(tab_LimAngle);
        gridLayout_18->setSpacing(6);
        gridLayout_18->setContentsMargins(11, 11, 11, 11);
        gridLayout_18->setObjectName(QString::fromUtf8("gridLayout_18"));
        GrBox_LimitAngleSinograms = new QGroupBox(tab_LimAngle);
        GrBox_LimitAngleSinograms->setObjectName(QString::fromUtf8("GrBox_LimitAngleSinograms"));
        sizePolicy2.setHeightForWidth(GrBox_LimitAngleSinograms->sizePolicy().hasHeightForWidth());
        GrBox_LimitAngleSinograms->setSizePolicy(sizePolicy2);
        gridLayout_17 = new QGridLayout(GrBox_LimitAngleSinograms);
        gridLayout_17->setSpacing(6);
        gridLayout_17->setContentsMargins(11, 11, 11, 11);
        gridLayout_17->setObjectName(QString::fromUtf8("gridLayout_17"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_26 = new QHBoxLayout();
        horizontalLayout_26->setSpacing(6);
        horizontalLayout_26->setObjectName(QString::fromUtf8("horizontalLayout_26"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        Btn_LimAngleAddSeg = new QPushButton(GrBox_LimitAngleSinograms);
        Btn_LimAngleAddSeg->setObjectName(QString::fromUtf8("Btn_LimAngleAddSeg"));
        Btn_LimAngleAddSeg->setStyleSheet(QString::fromUtf8("background: white\n"
""));
        QIcon icon14;
        icon14.addFile(QString::fromUtf8("Images/LimAddSegment.png"), QSize(), QIcon::Normal, QIcon::Off);
        Btn_LimAngleAddSeg->setIcon(icon14);
        Btn_LimAngleAddSeg->setIconSize(QSize(42, 42));

        verticalLayout->addWidget(Btn_LimAngleAddSeg);

        Btn_LimAngleRemSeg = new QPushButton(GrBox_LimitAngleSinograms);
        Btn_LimAngleRemSeg->setObjectName(QString::fromUtf8("Btn_LimAngleRemSeg"));
        Btn_LimAngleRemSeg->setStyleSheet(QString::fromUtf8("background: white"));
        QIcon icon15;
        icon15.addFile(QString::fromUtf8("Images/LimRemSegment.png"), QSize(), QIcon::Normal, QIcon::Off);
        Btn_LimAngleRemSeg->setIcon(icon15);
        Btn_LimAngleRemSeg->setIconSize(QSize(42, 42));

        verticalLayout->addWidget(Btn_LimAngleRemSeg);

        verticalSpacer_4 = new QSpacerItem(20, 270, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_4);


        horizontalLayout_26->addLayout(verticalLayout);

        TreeWidget_LimAngleSeg = new QTreeWidget(GrBox_LimitAngleSinograms);
        TreeWidget_LimAngleSeg->setObjectName(QString::fromUtf8("TreeWidget_LimAngleSeg"));
        TreeWidget_LimAngleSeg->setMinimumSize(QSize(400, 450));
        TreeWidget_LimAngleSeg->setSelectionMode(QAbstractItemView::SingleSelection);
        TreeWidget_LimAngleSeg->header()->setMinimumSectionSize(50);
        TreeWidget_LimAngleSeg->header()->setDefaultSectionSize(80);

        horizontalLayout_26->addWidget(TreeWidget_LimAngleSeg);


        verticalLayout_2->addLayout(horizontalLayout_26);

        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setSpacing(6);
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_PreProcSinoDir = new QLabel(GrBox_LimitAngleSinograms);
        label_PreProcSinoDir->setObjectName(QString::fromUtf8("label_PreProcSinoDir"));

        horizontalLayout_15->addWidget(label_PreProcSinoDir);

        horizontalSpacer_19 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_15->addItem(horizontalSpacer_19);

        LEd_LimAnglePreProcDir = new QLineEdit(GrBox_LimitAngleSinograms);
        LEd_LimAnglePreProcDir->setObjectName(QString::fromUtf8("LEd_LimAnglePreProcDir"));
        LEd_LimAnglePreProcDir->setMinimumSize(QSize(320, 0));

        horizontalLayout_15->addWidget(LEd_LimAnglePreProcDir);

        Btn_LimAnglePreProcDir = new QPushButton(GrBox_LimitAngleSinograms);
        Btn_LimAnglePreProcDir->setObjectName(QString::fromUtf8("Btn_LimAnglePreProcDir"));
        Btn_LimAnglePreProcDir->setStyleSheet(QString::fromUtf8("background: white;"));
        Btn_LimAnglePreProcDir->setIcon(icon10);

        horizontalLayout_15->addWidget(Btn_LimAnglePreProcDir);


        verticalLayout_2->addLayout(horizontalLayout_15);


        gridLayout_17->addLayout(verticalLayout_2, 0, 0, 1, 1);


        gridLayout_18->addWidget(GrBox_LimitAngleSinograms, 0, 0, 1, 1);

        TabWidget_SinogramSettings->addTab(tab_LimAngle, QString());

        gridLayout_20->addWidget(TabWidget_SinogramSettings, 0, 0, 1, 1);


        gridLayout_Parameter_Sinogram_Settings->addWidget(groupBox_2, 0, 1, 1, 1);


        verticalLayout_3->addLayout(gridLayout_Parameter_Sinogram_Settings);

        GrBox_ExecuteReconstruction = new QGroupBox(scrollAreaWidgetContents);
        GrBox_ExecuteReconstruction->setObjectName(QString::fromUtf8("GrBox_ExecuteReconstruction"));
        QSizePolicy sizePolicy10(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy10.setHorizontalStretch(0);
        sizePolicy10.setVerticalStretch(0);
        sizePolicy10.setHeightForWidth(GrBox_ExecuteReconstruction->sizePolicy().hasHeightForWidth());
        GrBox_ExecuteReconstruction->setSizePolicy(sizePolicy10);
        GrBox_ExecuteReconstruction->setMinimumSize(QSize(800, 150));
        horizontalLayout_34 = new QHBoxLayout(GrBox_ExecuteReconstruction);
        horizontalLayout_34->setSpacing(6);
        horizontalLayout_34->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_34->setObjectName(QString::fromUtf8("horizontalLayout_34"));
        horizontalLayout_32 = new QHBoxLayout();
        horizontalLayout_32->setSpacing(6);
        horizontalLayout_32->setObjectName(QString::fromUtf8("horizontalLayout_32"));
        TabWidget_Reconstruction = new QTabWidget(GrBox_ExecuteReconstruction);
        TabWidget_Reconstruction->setObjectName(QString::fromUtf8("TabWidget_Reconstruction"));
        TabWidget_Reconstruction->setEnabled(true);
        sizePolicy2.setHeightForWidth(TabWidget_Reconstruction->sizePolicy().hasHeightForWidth());
        TabWidget_Reconstruction->setSizePolicy(sizePolicy2);
        tab_SingleRecon = new QWidget();
        tab_SingleRecon->setObjectName(QString::fromUtf8("tab_SingleRecon"));
        tab_SingleRecon->setEnabled(true);
        gridLayout_9 = new QGridLayout(tab_SingleRecon);
        gridLayout_9->setSpacing(6);
        gridLayout_9->setContentsMargins(11, 11, 11, 11);
        gridLayout_9->setObjectName(QString::fromUtf8("gridLayout_9"));
        GrBox_SingleRecon = new QGroupBox(tab_SingleRecon);
        GrBox_SingleRecon->setObjectName(QString::fromUtf8("GrBox_SingleRecon"));
        GrBox_SingleRecon->setEnabled(true);
        verticalLayout_6 = new QVBoxLayout(GrBox_SingleRecon);
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setContentsMargins(11, 11, 11, 11);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_30 = new QHBoxLayout();
        horizontalLayout_30->setSpacing(6);
        horizontalLayout_30->setObjectName(QString::fromUtf8("horizontalLayout_30"));
        CkBox_WeightFilter = new QCheckBox(GrBox_SingleRecon);
        CkBox_WeightFilter->setObjectName(QString::fromUtf8("CkBox_WeightFilter"));
        CkBox_WeightFilter->setEnabled(true);
        CkBox_WeightFilter->setChecked(true);

        horizontalLayout_30->addWidget(CkBox_WeightFilter);

        horizontalSpacer_54 = new QSpacerItem(80, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_30->addItem(horizontalSpacer_54);

        label_NumberProcesses = new QLabel(GrBox_SingleRecon);
        label_NumberProcesses->setObjectName(QString::fromUtf8("label_NumberProcesses"));

        horizontalLayout_30->addWidget(label_NumberProcesses);

        SBox_NumberOfMPIProcesses = new QSpinBox(GrBox_SingleRecon);
        SBox_NumberOfMPIProcesses->setObjectName(QString::fromUtf8("SBox_NumberOfMPIProcesses"));
        SBox_NumberOfMPIProcesses->setMinimum(1);
        SBox_NumberOfMPIProcesses->setMaximum(64);
        SBox_NumberOfMPIProcesses->setValue(8);

        horizontalLayout_30->addWidget(SBox_NumberOfMPIProcesses);


        verticalLayout_6->addLayout(horizontalLayout_30);

        horizontalLayout_27 = new QHBoxLayout();
        horizontalLayout_27->setSpacing(6);
        horizontalLayout_27->setObjectName(QString::fromUtf8("horizontalLayout_27"));
        CkBox_Backprojection = new QCheckBox(GrBox_SingleRecon);
        CkBox_Backprojection->setObjectName(QString::fromUtf8("CkBox_Backprojection"));
        CkBox_Backprojection->setChecked(true);

        horizontalLayout_27->addWidget(CkBox_Backprojection);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_27->addItem(horizontalSpacer_9);

        label_5 = new QLabel(GrBox_SingleRecon);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        horizontalLayout_27->addWidget(label_5);

        CBox_ViewDirection = new QComboBox(GrBox_SingleRecon);
        CBox_ViewDirection->addItem(QString());
        CBox_ViewDirection->addItem(QString());
        CBox_ViewDirection->setObjectName(QString::fromUtf8("CBox_ViewDirection"));
        CBox_ViewDirection->setMinimumSize(QSize(145, 0));

        horizontalLayout_27->addWidget(CBox_ViewDirection);


        verticalLayout_6->addLayout(horizontalLayout_27);

        line_5 = new QFrame(GrBox_SingleRecon);
        line_5->setObjectName(QString::fromUtf8("line_5"));
        line_5->setFrameShape(QFrame::HLine);
        line_5->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_5);

        groupBox_InterpolationType = new QGroupBox(GrBox_SingleRecon);
        groupBox_InterpolationType->setObjectName(QString::fromUtf8("groupBox_InterpolationType"));
        groupBox_InterpolationType->setMinimumSize(QSize(20, 26));
        horizontalLayout_51 = new QHBoxLayout(groupBox_InterpolationType);
        horizontalLayout_51->setSpacing(6);
        horizontalLayout_51->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_51->setObjectName(QString::fromUtf8("horizontalLayout_51"));
        radioButton_fast = new QRadioButton(groupBox_InterpolationType);
        buttonGroup = new QButtonGroup(FDK_GUIClass);
        buttonGroup->setObjectName(QString::fromUtf8("buttonGroup"));
        buttonGroup->addButton(radioButton_fast);
        radioButton_fast->setObjectName(QString::fromUtf8("radioButton_fast"));
        radioButton_fast->setChecked(true);

        horizontalLayout_51->addWidget(radioButton_fast);

        radioButton_accurate = new QRadioButton(groupBox_InterpolationType);
        buttonGroup->addButton(radioButton_accurate);
        radioButton_accurate->setObjectName(QString::fromUtf8("radioButton_accurate"));

        horizontalLayout_51->addWidget(radioButton_accurate);


        verticalLayout_6->addWidget(groupBox_InterpolationType);

        verticalSpacer_8 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_8);

        horizontalLayout_31 = new QHBoxLayout();
        horizontalLayout_31->setSpacing(6);
        horizontalLayout_31->setObjectName(QString::fromUtf8("horizontalLayout_31"));
        horizontalSpacer_60 = new QSpacerItem(10, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_31->addItem(horizontalSpacer_60);

        Btn_RunReconstruction = new QPushButton(GrBox_SingleRecon);
        Btn_RunReconstruction->setObjectName(QString::fromUtf8("Btn_RunReconstruction"));
        Btn_RunReconstruction->setEnabled(false);

        horizontalLayout_31->addWidget(Btn_RunReconstruction);

        horizontalSpacer_55 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_31->addItem(horizontalSpacer_55);


        verticalLayout_6->addLayout(horizontalLayout_31);

        verticalSpacer_9 = new QSpacerItem(20, 5, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_9);

        GrBox_TerminateReconstruction = new QGroupBox(GrBox_SingleRecon);
        GrBox_TerminateReconstruction->setObjectName(QString::fromUtf8("GrBox_TerminateReconstruction"));
        GrBox_TerminateReconstruction->setMinimumSize(QSize(0, 30));
        GrBox_TerminateReconstruction->setStyleSheet(QString::fromUtf8(""));
        horizontalLayout_35 = new QHBoxLayout(GrBox_TerminateReconstruction);
        horizontalLayout_35->setSpacing(6);
        horizontalLayout_35->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_35->setObjectName(QString::fromUtf8("horizontalLayout_35"));
        Btn_StopWeightFilterProc = new QPushButton(GrBox_TerminateReconstruction);
        Btn_StopWeightFilterProc->setObjectName(QString::fromUtf8("Btn_StopWeightFilterProc"));
        Btn_StopWeightFilterProc->setEnabled(false);
        QFont font;
        font.setFamily(QString::fromUtf8("Lucida Sans Typewriter"));
        font.setPointSize(8);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        Btn_StopWeightFilterProc->setFont(font);
        Btn_StopWeightFilterProc->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: red;\n"
"	font: 75 8pt \"Lucida Sans Typewriter\";\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: rgb(255, 136, 106);\n"
"	color: rgb(144, 144, 144);\n"
"}\n"
""));

        horizontalLayout_35->addWidget(Btn_StopWeightFilterProc);

        horizontalSpacer_57 = new QSpacerItem(46, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_35->addItem(horizontalSpacer_57);

        Btn_StopReconstructionProc = new QPushButton(GrBox_TerminateReconstruction);
        Btn_StopReconstructionProc->setObjectName(QString::fromUtf8("Btn_StopReconstructionProc"));
        Btn_StopReconstructionProc->setEnabled(false);
        Btn_StopReconstructionProc->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: red;\n"
"	font: 75 8pt \"Lucida Sans Typewriter\";\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: rgb(255, 136, 106);\n"
"	color: rgb(144, 144, 144);\n"
"}\n"
""));

        horizontalLayout_35->addWidget(Btn_StopReconstructionProc);


        verticalLayout_6->addWidget(GrBox_TerminateReconstruction);

        horizontalLayout_49 = new QHBoxLayout();
        horizontalLayout_49->setSpacing(6);
        horizontalLayout_49->setObjectName(QString::fromUtf8("horizontalLayout_49"));
        horizontalSpacer_34 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_49->addItem(horizontalSpacer_34);

        label = new QLabel(GrBox_SingleRecon);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_49->addWidget(label);

        LCD_timing = new QLCDNumber(GrBox_SingleRecon);
        LCD_timing->setObjectName(QString::fromUtf8("LCD_timing"));
        LCD_timing->setStyleSheet(QString::fromUtf8("color: blue; background: gold;"));
        LCD_timing->setFrameShadow(QFrame::Raised);
        LCD_timing->setSmallDecimalPoint(false);
        LCD_timing->setDigitCount(7);
        LCD_timing->setSegmentStyle(QLCDNumber::Flat);

        horizontalLayout_49->addWidget(LCD_timing);


        verticalLayout_6->addLayout(horizontalLayout_49);


        gridLayout_9->addWidget(GrBox_SingleRecon, 0, 0, 1, 1);

        TabWidget_Reconstruction->addTab(tab_SingleRecon, QString());
        tab_BatchRecon = new QWidget();
        tab_BatchRecon->setObjectName(QString::fromUtf8("tab_BatchRecon"));
        tab_BatchRecon->setEnabled(true);
        gridLayout_14 = new QGridLayout(tab_BatchRecon);
        gridLayout_14->setSpacing(6);
        gridLayout_14->setContentsMargins(11, 11, 11, 11);
        gridLayout_14->setObjectName(QString::fromUtf8("gridLayout_14"));
        horizontalLayout_29 = new QHBoxLayout();
        horizontalLayout_29->setSpacing(6);
        horizontalLayout_29->setObjectName(QString::fromUtf8("horizontalLayout_29"));
        verticalLayout_12 = new QVBoxLayout();
        verticalLayout_12->setSpacing(6);
        verticalLayout_12->setObjectName(QString::fromUtf8("verticalLayout_12"));
        Btn_AddProjectToBatch = new QPushButton(tab_BatchRecon);
        Btn_AddProjectToBatch->setObjectName(QString::fromUtf8("Btn_AddProjectToBatch"));
        Btn_AddProjectToBatch->setEnabled(true);

        verticalLayout_12->addWidget(Btn_AddProjectToBatch);

        Btn_RemProjectToBatch = new QPushButton(tab_BatchRecon);
        Btn_RemProjectToBatch->setObjectName(QString::fromUtf8("Btn_RemProjectToBatch"));
        Btn_RemProjectToBatch->setEnabled(true);

        verticalLayout_12->addWidget(Btn_RemProjectToBatch);

        verticalSpacer_6 = new QSpacerItem(20, 70, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_12->addItem(verticalSpacer_6);

        Btn_RunBatch = new QPushButton(tab_BatchRecon);
        Btn_RunBatch->setObjectName(QString::fromUtf8("Btn_RunBatch"));
        Btn_RunBatch->setEnabled(true);

        verticalLayout_12->addWidget(Btn_RunBatch);

        verticalSpacer_7 = new QSpacerItem(20, 13, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_12->addItem(verticalSpacer_7);

        Btn_StopBatch = new QPushButton(tab_BatchRecon);
        Btn_StopBatch->setObjectName(QString::fromUtf8("Btn_StopBatch"));
        Btn_StopBatch->setEnabled(false);
        Btn_StopBatch->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"	background-color: red;\n"
"    color: yellow; \n"
"	font: 75 10pt \"Consolas\";\n"
"}\n"
"\n"
"QPushButton:disabled {\n"
"    background-color: rgb(255, 242, 219);\n"
"	color: grey;\n"
"	font: italic 10pt \"Consolas\";\n"
"}\n"
""));
        Btn_StopBatch->setCheckable(false);

        verticalLayout_12->addWidget(Btn_StopBatch);


        horizontalLayout_29->addLayout(verticalLayout_12);

        ListWidget_ReconProjectList = new QListWidget(tab_BatchRecon);
        ListWidget_ReconProjectList->setObjectName(QString::fromUtf8("ListWidget_ReconProjectList"));
        ListWidget_ReconProjectList->setEnabled(true);
        sizePolicy10.setHeightForWidth(ListWidget_ReconProjectList->sizePolicy().hasHeightForWidth());
        ListWidget_ReconProjectList->setSizePolicy(sizePolicy10);

        horizontalLayout_29->addWidget(ListWidget_ReconProjectList);


        gridLayout_14->addLayout(horizontalLayout_29, 0, 0, 1, 1);

        TabWidget_Reconstruction->addTab(tab_BatchRecon, QString());

        horizontalLayout_32->addWidget(TabWidget_Reconstruction);

        groupBox_13 = new QGroupBox(GrBox_ExecuteReconstruction);
        groupBox_13->setObjectName(QString::fromUtf8("groupBox_13"));
        sizePolicy3.setHeightForWidth(groupBox_13->sizePolicy().hasHeightForWidth());
        groupBox_13->setSizePolicy(sizePolicy3);
        verticalLayout_9 = new QVBoxLayout(groupBox_13);
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setContentsMargins(11, 11, 11, 11);
        verticalLayout_9->setObjectName(QString::fromUtf8("verticalLayout_9"));
        Txt_ProcessOutput = new QTextEdit(groupBox_13);
        Txt_ProcessOutput->setObjectName(QString::fromUtf8("Txt_ProcessOutput"));
        Txt_ProcessOutput->setEnabled(true);
        sizePolicy.setHeightForWidth(Txt_ProcessOutput->sizePolicy().hasHeightForWidth());
        Txt_ProcessOutput->setSizePolicy(sizePolicy);
        Txt_ProcessOutput->setStyleSheet(QString::fromUtf8("background: khaki"));
        Txt_ProcessOutput->setLineWrapMode(QTextEdit::NoWrap);
        Txt_ProcessOutput->setReadOnly(true);

        verticalLayout_9->addWidget(Txt_ProcessOutput);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setSpacing(6);
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        pushButton_SaveProcessOutput = new QPushButton(groupBox_13);
        pushButton_SaveProcessOutput->setObjectName(QString::fromUtf8("pushButton_SaveProcessOutput"));

        horizontalLayout_7->addWidget(pushButton_SaveProcessOutput);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_7->addItem(horizontalSpacer_8);

        pushButton_ClearOutput = new QPushButton(groupBox_13);
        pushButton_ClearOutput->setObjectName(QString::fromUtf8("pushButton_ClearOutput"));

        horizontalLayout_7->addWidget(pushButton_ClearOutput);


        verticalLayout_9->addLayout(horizontalLayout_7);


        horizontalLayout_32->addWidget(groupBox_13);


        horizontalLayout_34->addLayout(horizontalLayout_32);


        verticalLayout_3->addWidget(GrBox_ExecuteReconstruction);


        gridLayout_22->addLayout(verticalLayout_3, 0, 0, 1, 1);

        scrollArea->setWidget(scrollAreaWidgetContents);

        gridLayout_4->addWidget(scrollArea, 0, 0, 1, 1);

        FDK_GUIClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(FDK_GUIClass);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1617, 21));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menu = new QMenu(menuBar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menuDatabase = new QMenu(menuBar);
        menuDatabase->setObjectName(QString::fromUtf8("menuDatabase"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuVersion = new QMenu(menuBar);
        menuVersion->setObjectName(QString::fromUtf8("menuVersion"));
        menuBugs = new QMenu(menuBar);
        menuBugs->setObjectName(QString::fromUtf8("menuBugs"));
        FDK_GUIClass->setMenuBar(menuBar);
        statusBar = new QStatusBar(FDK_GUIClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        FDK_GUIClass->setStatusBar(statusBar);
        toolBar = new QToolBar(FDK_GUIClass);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        FDK_GUIClass->addToolBar(Qt::TopToolBarArea, toolBar);
        dockWidget_ImageView = new QDockWidget(FDK_GUIClass);
        dockWidget_ImageView->setObjectName(QString::fromUtf8("dockWidget_ImageView"));
        dockWidget_ImageView->setMinimumSize(QSize(500, 500));
        dockWidget_ImageView->setFloating(true);
        dockWidgetContents_ImageView = new QWidget();
        dockWidgetContents_ImageView->setObjectName(QString::fromUtf8("dockWidgetContents_ImageView"));
        verticalLayout_14 = new QVBoxLayout(dockWidgetContents_ImageView);
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setContentsMargins(11, 11, 11, 11);
        verticalLayout_14->setObjectName(QString::fromUtf8("verticalLayout_14"));
        pw_containerScrollArea = new QScrollArea(dockWidgetContents_ImageView);
        pw_containerScrollArea->setObjectName(QString::fromUtf8("pw_containerScrollArea"));
        QSizePolicy sizePolicy11(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy11.setHorizontalStretch(0);
        sizePolicy11.setVerticalStretch(0);
        sizePolicy11.setHeightForWidth(pw_containerScrollArea->sizePolicy().hasHeightForWidth());
        pw_containerScrollArea->setSizePolicy(sizePolicy11);
        pw_containerScrollArea->setMaximumSize(QSize(3000, 3000));
        pw_containerScrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        pw_containerScrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        pw_containerScrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents_ImageView = new QWidget();
        scrollAreaWidgetContents_ImageView->setObjectName(QString::fromUtf8("scrollAreaWidgetContents_ImageView"));
        scrollAreaWidgetContents_ImageView->setGeometry(QRect(0, 0, 480, 575));
        sizePolicy1.setHeightForWidth(scrollAreaWidgetContents_ImageView->sizePolicy().hasHeightForWidth());
        scrollAreaWidgetContents_ImageView->setSizePolicy(sizePolicy1);
        scrollAreaWidgetContents_ImageView->setMaximumSize(QSize(3000, 3000));
        gridLayout_23 = new QGridLayout(scrollAreaWidgetContents_ImageView);
        gridLayout_23->setSpacing(6);
        gridLayout_23->setContentsMargins(11, 11, 11, 11);
        gridLayout_23->setObjectName(QString::fromUtf8("gridLayout_23"));
        Dock_ImageArea = new QLabel(scrollAreaWidgetContents_ImageView);
        Dock_ImageArea->setObjectName(QString::fromUtf8("Dock_ImageArea"));
        QSizePolicy sizePolicy12(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy12.setHorizontalStretch(0);
        sizePolicy12.setVerticalStretch(1);
        sizePolicy12.setHeightForWidth(Dock_ImageArea->sizePolicy().hasHeightForWidth());
        Dock_ImageArea->setSizePolicy(sizePolicy12);
        Dock_ImageArea->setMinimumSize(QSize(60, 60));
        Dock_ImageArea->setMaximumSize(QSize(2500, 2500));
        Dock_ImageArea->setFrameShape(QFrame::Box);
        Dock_ImageArea->setFrameShadow(QFrame::Raised);

        gridLayout_23->addWidget(Dock_ImageArea, 1, 1, 1, 1);

        label_ShowImageName = new QLabel(scrollAreaWidgetContents_ImageView);
        label_ShowImageName->setObjectName(QString::fromUtf8("label_ShowImageName"));
        label_ShowImageName->setMinimumSize(QSize(0, 24));
        label_ShowImageName->setFrameShape(QFrame::Box);
        label_ShowImageName->setFrameShadow(QFrame::Plain);
        label_ShowImageName->setLineWidth(1);

        gridLayout_23->addWidget(label_ShowImageName, 0, 1, 1, 1);

        groupBox_4 = new QGroupBox(scrollAreaWidgetContents_ImageView);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        gridLayout_25 = new QGridLayout(groupBox_4);
        gridLayout_25->setSpacing(6);
        gridLayout_25->setContentsMargins(11, 11, 11, 11);
        gridLayout_25->setObjectName(QString::fromUtf8("gridLayout_25"));
        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setObjectName(QString::fromUtf8("verticalLayout_15"));
        horizontalLayout_33 = new QHBoxLayout();
        horizontalLayout_33->setSpacing(6);
        horizontalLayout_33->setObjectName(QString::fromUtf8("horizontalLayout_33"));
        spinBox = new QSpinBox(groupBox_4);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));

        horizontalLayout_33->addWidget(spinBox);

        horizontalSlider = new QSlider(groupBox_4);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setMinimum(1);
        horizontalSlider->setMaximum(100);
        horizontalSlider->setOrientation(Qt::Horizontal);
        horizontalSlider->setInvertedAppearance(true);
        horizontalSlider->setInvertedControls(true);
        horizontalSlider->setTickPosition(QSlider::TicksBelow);
        horizontalSlider->setTickInterval(10);

        horizontalLayout_33->addWidget(horizontalSlider);


        verticalLayout_15->addLayout(horizontalLayout_33);

        horizontalLayout_36 = new QHBoxLayout();
        horizontalLayout_36->setSpacing(6);
        horizontalLayout_36->setObjectName(QString::fromUtf8("horizontalLayout_36"));
        Btn_LoadImages = new QPushButton(groupBox_4);
        Btn_LoadImages->setObjectName(QString::fromUtf8("Btn_LoadImages"));

        horizontalLayout_36->addWidget(Btn_LoadImages);

        horizontalSpacer_58 = new QSpacerItem(13, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_36->addItem(horizontalSpacer_58);

        label_2 = new QLabel(groupBox_4);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_36->addWidget(label_2);

        spinBox_ImageWidth = new QSpinBox(groupBox_4);
        spinBox_ImageWidth->setObjectName(QString::fromUtf8("spinBox_ImageWidth"));

        horizontalLayout_36->addWidget(spinBox_ImageWidth);

        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_36->addWidget(label_3);

        spinBox_ImageHeight = new QSpinBox(groupBox_4);
        spinBox_ImageHeight->setObjectName(QString::fromUtf8("spinBox_ImageHeight"));

        horizontalLayout_36->addWidget(spinBox_ImageHeight);

        label_4 = new QLabel(groupBox_4);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        horizontalLayout_36->addWidget(label_4);

        comboBox_FileType = new QComboBox(groupBox_4);
        comboBox_FileType->setObjectName(QString::fromUtf8("comboBox_FileType"));
        comboBox_FileType->setMinimumSize(QSize(120, 0));

        horizontalLayout_36->addWidget(comboBox_FileType);


        verticalLayout_15->addLayout(horizontalLayout_36);


        gridLayout_25->addLayout(verticalLayout_15, 0, 0, 1, 1);


        gridLayout_23->addWidget(groupBox_4, 2, 1, 1, 1);

        pw_containerScrollArea->setWidget(scrollAreaWidgetContents_ImageView);

        verticalLayout_14->addWidget(pw_containerScrollArea);

        dockWidget_ImageView->setWidget(dockWidgetContents_ImageView);
        FDK_GUIClass->addDockWidget(Qt::LeftDockWidgetArea, dockWidget_ImageView);
        dockWidget_ProjectOptions = new QDockWidget(FDK_GUIClass);
        dockWidget_ProjectOptions->setObjectName(QString::fromUtf8("dockWidget_ProjectOptions"));
        sizePolicy5.setHeightForWidth(dockWidget_ProjectOptions->sizePolicy().hasHeightForWidth());
        dockWidget_ProjectOptions->setSizePolicy(sizePolicy5);
        dockWidget_ProjectOptions->setMinimumSize(QSize(268, 156));
        dockWidget_ProjectOptions->setFloating(true);
        dockWidget_ProjectOptions->setAllowedAreas(Qt::AllDockWidgetAreas);
        dockWidgetContents_ProjectOptions = new QWidget();
        dockWidgetContents_ProjectOptions->setObjectName(QString::fromUtf8("dockWidgetContents_ProjectOptions"));
        sizePolicy2.setHeightForWidth(dockWidgetContents_ProjectOptions->sizePolicy().hasHeightForWidth());
        dockWidgetContents_ProjectOptions->setSizePolicy(sizePolicy2);
        verticalLayout_13 = new QVBoxLayout(dockWidgetContents_ProjectOptions);
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setContentsMargins(11, 11, 11, 11);
        verticalLayout_13->setObjectName(QString::fromUtf8("verticalLayout_13"));
        groupBox_5 = new QGroupBox(dockWidgetContents_ProjectOptions);
        groupBox_5->setObjectName(QString::fromUtf8("groupBox_5"));
        sizePolicy2.setHeightForWidth(groupBox_5->sizePolicy().hasHeightForWidth());
        groupBox_5->setSizePolicy(sizePolicy2);
        verticalLayout_16 = new QVBoxLayout(groupBox_5);
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QString::fromUtf8("verticalLayout_16"));
        horizontalLayout_47 = new QHBoxLayout();
        horizontalLayout_47->setSpacing(6);
        horizontalLayout_47->setObjectName(QString::fromUtf8("horizontalLayout_47"));
        lineEdit_MPIPath = new QLineEdit(groupBox_5);
        lineEdit_MPIPath->setObjectName(QString::fromUtf8("lineEdit_MPIPath"));
        lineEdit_MPIPath->setEnabled(false);
        sizePolicy8.setHeightForWidth(lineEdit_MPIPath->sizePolicy().hasHeightForWidth());
        lineEdit_MPIPath->setSizePolicy(sizePolicy8);
        lineEdit_MPIPath->setMinimumSize(QSize(130, 0));

        horizontalLayout_47->addWidget(lineEdit_MPIPath);

        Btn_MPIPath = new QPushButton(groupBox_5);
        Btn_MPIPath->setObjectName(QString::fromUtf8("Btn_MPIPath"));
        Btn_MPIPath->setEnabled(false);
        sizePolicy9.setHeightForWidth(Btn_MPIPath->sizePolicy().hasHeightForWidth());
        Btn_MPIPath->setSizePolicy(sizePolicy9);
        Btn_MPIPath->setMinimumSize(QSize(84, 0));

        horizontalLayout_47->addWidget(Btn_MPIPath);


        verticalLayout_16->addLayout(horizontalLayout_47);

        horizontalLayout_46 = new QHBoxLayout();
        horizontalLayout_46->setSpacing(6);
        horizontalLayout_46->setObjectName(QString::fromUtf8("horizontalLayout_46"));
        lineEdit_DataTopDir = new QLineEdit(groupBox_5);
        lineEdit_DataTopDir->setObjectName(QString::fromUtf8("lineEdit_DataTopDir"));
        sizePolicy8.setHeightForWidth(lineEdit_DataTopDir->sizePolicy().hasHeightForWidth());
        lineEdit_DataTopDir->setSizePolicy(sizePolicy8);
        lineEdit_DataTopDir->setMinimumSize(QSize(130, 0));

        horizontalLayout_46->addWidget(lineEdit_DataTopDir);

        Btn_DataTopDir = new QPushButton(groupBox_5);
        Btn_DataTopDir->setObjectName(QString::fromUtf8("Btn_DataTopDir"));
        sizePolicy9.setHeightForWidth(Btn_DataTopDir->sizePolicy().hasHeightForWidth());
        Btn_DataTopDir->setSizePolicy(sizePolicy9);

        horizontalLayout_46->addWidget(Btn_DataTopDir);


        verticalLayout_16->addLayout(horizontalLayout_46);

        line_6 = new QFrame(groupBox_5);
        line_6->setObjectName(QString::fromUtf8("line_6"));
        sizePolicy9.setHeightForWidth(line_6->sizePolicy().hasHeightForWidth());
        line_6->setSizePolicy(sizePolicy9);
        line_6->setFrameShape(QFrame::HLine);
        line_6->setFrameShadow(QFrame::Sunken);

        verticalLayout_16->addWidget(line_6);


        verticalLayout_13->addWidget(groupBox_5);

        horizontalLayout_37 = new QHBoxLayout();
        horizontalLayout_37->setSpacing(6);
        horizontalLayout_37->setObjectName(QString::fromUtf8("horizontalLayout_37"));
        horizontalSpacer_59 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_37->addItem(horizontalSpacer_59);

        Btn_SaveOptions = new QPushButton(dockWidgetContents_ProjectOptions);
        Btn_SaveOptions->setObjectName(QString::fromUtf8("Btn_SaveOptions"));
        sizePolicy5.setHeightForWidth(Btn_SaveOptions->sizePolicy().hasHeightForWidth());
        Btn_SaveOptions->setSizePolicy(sizePolicy5);

        horizontalLayout_37->addWidget(Btn_SaveOptions);

        horizontalSpacer_63 = new QSpacerItem(10, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        horizontalLayout_37->addItem(horizontalSpacer_63);


        verticalLayout_13->addLayout(horizontalLayout_37);

        dockWidget_ProjectOptions->setWidget(dockWidgetContents_ProjectOptions);
        FDK_GUIClass->addDockWidget(Qt::RightDockWidgetArea, dockWidget_ProjectOptions);
        dockWidget_Database = new QDockWidget(FDK_GUIClass);
        dockWidget_Database->setObjectName(QString::fromUtf8("dockWidget_Database"));
        dockWidget_Database->setEnabled(true);
        dockWidget_Database->setMinimumSize(QSize(265, 300));
        dockWidget_Database->setFloating(true);
        dockWidgetContents_Database = new QWidget();
        dockWidgetContents_Database->setObjectName(QString::fromUtf8("dockWidgetContents_Database"));
        verticalLayout_17 = new QVBoxLayout(dockWidgetContents_Database);
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setContentsMargins(11, 11, 11, 11);
        verticalLayout_17->setObjectName(QString::fromUtf8("verticalLayout_17"));
        label_6 = new QLabel(dockWidgetContents_Database);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_17->addWidget(label_6);

        label_7 = new QLabel(dockWidgetContents_Database);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_17->addWidget(label_7);

        dockWidget_Database->setWidget(dockWidgetContents_Database);
        FDK_GUIClass->addDockWidget(Qt::LeftDockWidgetArea, dockWidget_Database);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menu->menuAction());
        menuBar->addAction(menuDatabase->menuAction());
        menuBar->addAction(menuVersion->menuAction());
        menuBar->addAction(menuBugs->menuAction());
        menuFile->addSeparator();
        menuFile->addAction(actionExit);
        menu->addAction(actionOpen);
        menu->addAction(actionSave);
        menu->addAction(actionSave_as);
        menu->addSeparator();
        menu->addAction(actionCheck_Parameters);
        menu->addSeparator();
        menu->addAction(actionOptions);
        menuDatabase->addAction(actionUse_RDBMS);
        menuDatabase->addAction(actionImport_Project);
        menuView->addAction(actionToolbar);
        menuView->addAction(actionImage_View);
        menuVersion->addAction(actionVersion_1_1_Build_14082014);
        menuBugs->addAction(actionSubmit_Bug_juergen_hofmann_empa_ch);
        toolBar->addAction(actionSave);
        toolBar->addAction(actionSave_as);
        toolBar->addAction(actionOpen);
        toolBar->addAction(actionCheck_Parameters);
        toolBar->addAction(actionOptions);
        toolBar->addSeparator();
        toolBar->addAction(actionUse_RDBMS);
        toolBar->addAction(actionImport_Project);

        retranslateUi(FDK_GUIClass);
        QObject::connect(actionExit, SIGNAL(triggered(bool)), FDK_GUIClass, SLOT(close()));
        QObject::connect(CkBox_WeightFilter, SIGNAL(toggled(bool)), SBox_NumberOfMPIProcesses, SLOT(setEnabled(bool)));
        QObject::connect(actionToolbar, SIGNAL(toggled(bool)), toolBar, SLOT(setVisible(bool)));
        QObject::connect(actionImage_View, SIGNAL(toggled(bool)), dockWidget_ImageView, SLOT(setVisible(bool)));
        QObject::connect(CkBox_EditSystemSettings, SIGNAL(toggled(bool)), GrBox_GPUPreferences, SLOT(setEnabled(bool)));
        QObject::connect(CkBox_EditSystemSettings, SIGNAL(toggled(bool)), GrBox_MemoryUsage, SLOT(setEnabled(bool)));
        QObject::connect(radioButton_limitedAngleRecon, SIGNAL(toggled(bool)), checkBox_useFileList, SLOT(setDisabled(bool)));
        QObject::connect(pushButton_ClearOutput, SIGNAL(clicked(bool)), Txt_ProcessOutput, SLOT(clear()));
        QObject::connect(checkBox_useFileList, SIGNAL(toggled(bool)), ListWidget_SinogramList, SLOT(setEnabled(bool)));
        QObject::connect(Btn_SelectSinograms, SIGNAL(clicked()), LEd_SinoNamePattern, SLOT(clear()));
        QObject::connect(checkBox_useFileList, SIGNAL(toggled(bool)), Btn_SelectSinograms, SLOT(setEnabled(bool)));
        QObject::connect(checkBox_useFileList, SIGNAL(toggled(bool)), Btn_RemoveSelection, SLOT(setEnabled(bool)));
        QObject::connect(radioButton_limitedAngleRecon, SIGNAL(toggled(bool)), GrBox_LimitAngleSinograms, SLOT(setEnabled(bool)));
        QObject::connect(radioButton_fullAngleRecon, SIGNAL(toggled(bool)), GrBox_FullAngleSinograms, SLOT(setEnabled(bool)));

        tabWidget->setCurrentIndex(0);
        TabWidget_SinogramSettings->setCurrentIndex(0);
        TabWidget_Reconstruction->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(FDK_GUIClass);
    } // setupUi

    void retranslateUi(QMainWindow *FDK_GUIClass)
    {
        FDK_GUIClass->setWindowTitle(QCoreApplication::translate("FDK_GUIClass", "FDK Reconstruction R2.0 - no Project", nullptr));
        actionExit->setText(QCoreApplication::translate("FDK_GUIClass", "Exit", nullptr));
#if QT_CONFIG(shortcut)
        actionExit->setShortcut(QCoreApplication::translate("FDK_GUIClass", "Ctrl+Q", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpen->setText(QCoreApplication::translate("FDK_GUIClass", "Open ...", nullptr));
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("FDK_GUIClass", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave->setText(QCoreApplication::translate("FDK_GUIClass", "Save", nullptr));
#if QT_CONFIG(shortcut)
        actionSave->setShortcut(QCoreApplication::translate("FDK_GUIClass", "Ctrl+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionSave_as->setText(QCoreApplication::translate("FDK_GUIClass", "Save as ...", nullptr));
#if QT_CONFIG(shortcut)
        actionSave_as->setShortcut(QCoreApplication::translate("FDK_GUIClass", "Ctrl+Shift+S", nullptr));
#endif // QT_CONFIG(shortcut)
        actionUse_RDBMS->setText(QCoreApplication::translate("FDK_GUIClass", "RDBMS", nullptr));
        actionRDBMS_Management->setText(QCoreApplication::translate("FDK_GUIClass", "RDBMS Management ...", nullptr));
        actionImport_Project->setText(QCoreApplication::translate("FDK_GUIClass", "Import Project ...", nullptr));
        actionToolbar->setText(QCoreApplication::translate("FDK_GUIClass", "Toolbar", nullptr));
        actionImage_View->setText(QCoreApplication::translate("FDK_GUIClass", "Image View", nullptr));
        actionOptions->setText(QCoreApplication::translate("FDK_GUIClass", "Path Settings", nullptr));
#if QT_CONFIG(shortcut)
        actionOptions->setShortcut(QCoreApplication::translate("FDK_GUIClass", "Ctrl+T", nullptr));
#endif // QT_CONFIG(shortcut)
        actionCheck_Parameters->setText(QCoreApplication::translate("FDK_GUIClass", "Check Parameters", nullptr));
        actionImport_convert_DETECT_data->setText(QCoreApplication::translate("FDK_GUIClass", "Import && convert DETECT data ...", nullptr));
        actionVersion_1_1_Build_14082014->setText(QCoreApplication::translate("FDK_GUIClass", "Version 2.0.1    Oct-2021 Win10 /  Empa X-ray Center 499 / Juergen Hofmann", nullptr));
#if QT_CONFIG(tooltip)
        actionVersion_1_1_Build_14082014->setToolTip(QCoreApplication::translate("FDK_GUIClass", "<html><head/><body><p>Version 2.0 Win10 13.Dec 2018 / Empa Lab 499</p><p>Author: J\303\274rgen Hofmann</p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        actionVersion_1_1_Build_14082014->setStatusTip(QCoreApplication::translate("FDK_GUIClass", "Version 2.0    Dec-2018 /  Empa X-ray Center 499 / Juergen Hofmann", nullptr));
#endif // QT_CONFIG(statustip)
        actionJuergen_hofmann_empa_ch->setText(QCoreApplication::translate("FDK_GUIClass", "juergen.hofmann@empa.ch", nullptr));
        actionSubmit_Bug_juergen_hofmann_empa_ch->setText(QCoreApplication::translate("FDK_GUIClass", "Send Bug Report to J\303\274rgen Hofmann Empa Center for X-ray Analytics", nullptr));
        groupBox->setTitle(QCoreApplication::translate("FDK_GUIClass", "Parameter Settings", nullptr));
        GrBox_Projections->setTitle(QCoreApplication::translate("FDK_GUIClass", "Projections", nullptr));
        label_ImageWidth->setText(QCoreApplication::translate("FDK_GUIClass", "Image Width [pixel]:", nullptr));
        label_ImageHeight->setText(QCoreApplication::translate("FDK_GUIClass", "Image Height [pixel]:", nullptr));
        label_NumProjections->setText(QCoreApplication::translate("FDK_GUIClass", "Number of Projections:", nullptr));
        label_AngleIncr->setText(QCoreApplication::translate("FDK_GUIClass", "Angle Increment (\302\260):", nullptr));
        label_PixelSize->setText(QCoreApplication::translate("FDK_GUIClass", "Pixel size [mm]:", nullptr));
        GrBox_FilteringSettings->setTitle(QCoreApplication::translate("FDK_GUIClass", "Filtering && Sinogram Settings", nullptr));
        label_InputFormat->setText(QCoreApplication::translate("FDK_GUIClass", "Sinogram Input Data Format:", nullptr));
        CBox_InDataFormat->setItemText(0, QCoreApplication::translate("FDK_GUIClass", "real32", nullptr));
        CBox_InDataFormat->setItemText(1, QCoreApplication::translate("FDK_GUIClass", "ushort16", nullptr));
        CBox_InDataFormat->setItemText(2, QCoreApplication::translate("FDK_GUIClass", "byte", nullptr));
        CBox_InDataFormat->setItemText(3, QCoreApplication::translate("FDK_GUIClass", "short16", nullptr));
        CBox_InDataFormat->setItemText(4, QCoreApplication::translate("FDK_GUIClass", "int32", nullptr));
        CBox_InDataFormat->setItemText(5, QCoreApplication::translate("FDK_GUIClass", "undef", nullptr));

        label_Filtertype->setText(QCoreApplication::translate("FDK_GUIClass", "Filter Type:", nullptr));
        CBox_FlipSinogramImage->setItemText(0, QCoreApplication::translate("FDK_GUIClass", "none", nullptr));
        CBox_FlipSinogramImage->setItemText(1, QCoreApplication::translate("FDK_GUIClass", "x-axis", nullptr));
        CBox_FlipSinogramImage->setItemText(2, QCoreApplication::translate("FDK_GUIClass", "y-axis", nullptr));
        CBox_FlipSinogramImage->setItemText(3, QCoreApplication::translate("FDK_GUIClass", "x/y-axis", nullptr));

        CBox_FilterType->setItemText(0, QCoreApplication::translate("FDK_GUIClass", "Ramp", nullptr));
        CBox_FilterType->setItemText(1, QCoreApplication::translate("FDK_GUIClass", "SheppLogan", nullptr));
        CBox_FilterType->setItemText(2, QCoreApplication::translate("FDK_GUIClass", "PhaseContrast", nullptr));

        CBox_FilterType->setCurrentText(QCoreApplication::translate("FDK_GUIClass", "Ramp", nullptr));
        label_FlipSinogram->setText(QCoreApplication::translate("FDK_GUIClass", "Flip Sinogram Image along:", nullptr));
        label_SinoStartAtAngle->setText(QCoreApplication::translate("FDK_GUIClass", "Sinograms start at Angle [\302\260]:", nullptr));
        label_StartIndexSinogram->setText(QCoreApplication::translate("FDK_GUIClass", "Sinogram Numbering starts with Index:", nullptr));
        GrBox_GeometrySetup->setTitle(QCoreApplication::translate("FDK_GUIClass", "Geometry Setup", nullptr));
        label_ShiftHorizontal->setText(QCoreApplication::translate("FDK_GUIClass", "Horizontal Shift [pixel]:", nullptr));
        checkBox_applyTiltAxCorr->setText(QCoreApplication::translate("FDK_GUIClass", "Apply Tilted Axis Correction", nullptr));
        groupBox_ParamShiftCorrCurve->setTitle(QCoreApplication::translate("FDK_GUIClass", "Parameters for Shift Correction Curve [ y = m\342\210\231x + c ]", nullptr));
        label_8->setText(QCoreApplication::translate("FDK_GUIClass", "Slope m:", nullptr));
        label_9->setText(QCoreApplication::translate("FDK_GUIClass", "Offset c:", nullptr));
        label_ShiftVertical->setText(QCoreApplication::translate("FDK_GUIClass", "Vertical Shift [pixel]:", nullptr));
        label_DSD->setText(QCoreApplication::translate("FDK_GUIClass", "Distance Source -  Detector [mm]:", nullptr));
        label_DSO->setText(QCoreApplication::translate("FDK_GUIClass", "Distance Source - Rotation Centre [mm]:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_BasicParameters), QCoreApplication::translate("FDK_GUIClass", "Basic Parameters", nullptr));
        GrBox_ReconstructionParamters->setTitle(QCoreApplication::translate("FDK_GUIClass", "Reconstruction Volume Parameters", nullptr));
        label_VolumeWidth->setText(QCoreApplication::translate("FDK_GUIClass", "Volume Width [Voxel:]", nullptr));
        label_VolumeHeight->setText(QCoreApplication::translate("FDK_GUIClass", "Volume Height [Voxel]:", nullptr));
        label_VolumeDepth->setText(QCoreApplication::translate("FDK_GUIClass", "Volume Depth [Voxel]:", nullptr));
        label_VolumeOriginX->setText(QCoreApplication::translate("FDK_GUIClass", "Volume Origin x [Voxel]:", nullptr));
        label_VolumeOriginY->setText(QCoreApplication::translate("FDK_GUIClass", "Volume Origin y [Voxel]:", nullptr));
        label_VolumeOriginZ->setText(QCoreApplication::translate("FDK_GUIClass", "Volume Origin z [Voxel]:", nullptr));
        Btn_GetVolumeFromSelection->setText(QCoreApplication::translate("FDK_GUIClass", "Get Volume Selection ...", nullptr));
        label_BinningFactor->setText(QCoreApplication::translate("FDK_GUIClass", "Binning Factor:", nullptr));
        GrBox_TomoParameters->setTitle(QCoreApplication::translate("FDK_GUIClass", "Tomogram Parameters", nullptr));
        label_TomoOutDataFormat->setText(QCoreApplication::translate("FDK_GUIClass", "Tomogram Output Data Format:", nullptr));
        CBox_TomoOutDataFormat->setItemText(0, QCoreApplication::translate("FDK_GUIClass", "real32", nullptr));
        CBox_TomoOutDataFormat->setItemText(1, QCoreApplication::translate("FDK_GUIClass", "byte", nullptr));
        CBox_TomoOutDataFormat->setItemText(2, QCoreApplication::translate("FDK_GUIClass", "ushort16", nullptr));
        CBox_TomoOutDataFormat->setItemText(3, QCoreApplication::translate("FDK_GUIClass", "short16", nullptr));

        label_TomoName->setText(QCoreApplication::translate("FDK_GUIClass", "Tomogram Name:", nullptr));
        LEd_TomoName->setText(QCoreApplication::translate("FDK_GUIClass", "tomo_", nullptr));
        label_TomoOutDir->setText(QCoreApplication::translate("FDK_GUIClass", "Tomogram Output Directory:", nullptr));
#if QT_CONFIG(whatsthis)
        LEd_TomoOutDir->setWhatsThis(QCoreApplication::translate("FDK_GUIClass", "<empty>", nullptr));
#endif // QT_CONFIG(whatsthis)
        Btn_SelTomoOutDir->setText(QString());
        CkBox_WriteBlockFile->setText(QString());
        label_WriteToBlockFile->setText(QCoreApplication::translate("FDK_GUIClass", "Write to Block File:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_ReconParameter), QCoreApplication::translate("FDK_GUIClass", "Reconstruct. Parameters", nullptr));
        grBox_SystemSettings->setTitle(QCoreApplication::translate("FDK_GUIClass", "System && GPU Settings", nullptr));
        GrBox_MemoryUsage->setTitle(QCoreApplication::translate("FDK_GUIClass", "Memory usage", nullptr));
        label_CPUMemUsage->setText(QCoreApplication::translate("FDK_GUIClass", "CPU Memory usage [%]:", nullptr));
        label_GPUMemUsage->setText(QCoreApplication::translate("FDK_GUIClass", "GPU Memory usage [%]:", nullptr));
        GrBox_GPUPreferences->setTitle(QCoreApplication::translate("FDK_GUIClass", "GPU Preferences", nullptr));
        label_GPUThreadsY->setText(QCoreApplication::translate("FDK_GUIClass", "GPU Threads Y:", nullptr));
        label_GPUThreadsX->setText(QCoreApplication::translate("FDK_GUIClass", "GPU Threads X:", nullptr));
        label_GPUCompaVers->setText(QCoreApplication::translate("FDK_GUIClass", "GPU Compatibility Version:", nullptr));
        CBox_GPUCompaVers->setItemText(0, QCoreApplication::translate("FDK_GUIClass", "1.x", nullptr));
        CBox_GPUCompaVers->setItemText(1, QCoreApplication::translate("FDK_GUIClass", "2.x", nullptr));

        label_Use->setText(QCoreApplication::translate("FDK_GUIClass", "Use ", nullptr));
        label_GPUs->setText(QCoreApplication::translate("FDK_GUIClass", "GPUs", nullptr));
        CkBox_EditSystemSettings->setText(QCoreApplication::translate("FDK_GUIClass", "Enable Editing System Settings", nullptr));
        GrBox_CTSystemSelection->setTitle(QCoreApplication::translate("FDK_GUIClass", "CT System Selection", nullptr));
        CBox_CT_SystemSelection->setItemText(0, QCoreApplication::translate("FDK_GUIClass", "Micro_CT", nullptr));
        CBox_CT_SystemSelection->setItemText(1, QCoreApplication::translate("FDK_GUIClass", "Detect_CT", nullptr));

        groupBox_6->setTitle(QCoreApplication::translate("FDK_GUIClass", "Sinograms && File List", nullptr));
        radioButton_fullAngleRecon->setText(QCoreApplication::translate("FDK_GUIClass", "Full Angle Reconstruction", nullptr));
        radioButton_limitedAngleRecon->setText(QCoreApplication::translate("FDK_GUIClass", "Limited Angle Reconstruction", nullptr));
        checkBox_useFileList->setText(QCoreApplication::translate("FDK_GUIClass", "Use File List (Full Angle)", nullptr));
#if QT_CONFIG(tooltip)
        groupBox_7->setToolTip(QCoreApplication::translate("FDK_GUIClass", "<html><head/><body><p><span style=\" font-size:11pt; font-weight:600; color:#ff0000;\">Use Features only for migration proposes!</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        groupBox_7->setTitle(QCoreApplication::translate("FDK_GUIClass", "Block Files", nullptr));
#if QT_CONFIG(tooltip)
        CkBox_WriteToPreProcBlockFile->setToolTip(QCoreApplication::translate("FDK_GUIClass", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600; color:#ff0000;\"> Should not be used.</span></p><p><span style=\" font-size:10pt; font-weight:600; color:#ff0000;\">Feature is not stable!</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        CkBox_WriteToPreProcBlockFile->setText(QCoreApplication::translate("FDK_GUIClass", "Write to pre-processed Block File", nullptr));
#if QT_CONFIG(tooltip)
        CkBox_UsePreProcBlockFile->setToolTip(QCoreApplication::translate("FDK_GUIClass", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600; color:#ff0000;\"> Should not be used.</span></p><p><span style=\" font-size:10pt; font-weight:600; color:#ff0000;\">Feature is not stable!</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        CkBox_UsePreProcBlockFile->setText(QCoreApplication::translate("FDK_GUIClass", "Use pre-processed Block File", nullptr));
#if QT_CONFIG(tooltip)
        CkBox_StoreConvTomoBlockFile->setToolTip(QCoreApplication::translate("FDK_GUIClass", "<html><head/><body><p><span style=\" font-size:10pt; font-weight:600; color:#ff0000;\"> Should not be used.</span></p><p><span style=\" font-size:10pt; font-weight:600; color:#ff0000;\">Feature is not stable!</span></p></body></html>", nullptr));
#endif // QT_CONFIG(tooltip)
        CkBox_StoreConvTomoBlockFile->setText(QCoreApplication::translate("FDK_GUIClass", "Store converted Tomograms in Tomo Block File (overwrite)", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_AdvancedSettings), QCoreApplication::translate("FDK_GUIClass", "Advanced Settings", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("FDK_GUIClass", "Settings Sinogram Files", nullptr));
        GrBox_FullAngleSinograms->setTitle(QCoreApplication::translate("FDK_GUIClass", "Sinogram Properties", nullptr));
        label_SinogramDirectory->setText(QCoreApplication::translate("FDK_GUIClass", "Sinogram Directory:", nullptr));
        LEd_SinogramDirectory->setPlaceholderText(QString());
        Btn_SelectSinogramDirectory->setText(QString());
        label_SinoNamePattern->setText(QCoreApplication::translate("FDK_GUIClass", "Sinogram File Pattern:", nullptr));
        label_PreprocSinoDir->setText(QCoreApplication::translate("FDK_GUIClass", "Preprocessed Sinogram Directory:", nullptr));
        Btn_SelectPreprocSinoDir->setText(QString());
        Btn_SelectSinograms->setText(QCoreApplication::translate("FDK_GUIClass", "Select Sinograms ...", nullptr));
        Btn_RemoveSelection->setText(QCoreApplication::translate("FDK_GUIClass", "Remove Selection", nullptr));
        TabWidget_SinogramSettings->setTabText(TabWidget_SinogramSettings->indexOf(tab_FullAngle), QCoreApplication::translate("FDK_GUIClass", "Properties", nullptr));
        GrBox_LimitAngleSinograms->setTitle(QCoreApplication::translate("FDK_GUIClass", "Limited Angle", nullptr));
        Btn_LimAngleAddSeg->setText(QCoreApplication::translate("FDK_GUIClass", "Add Segments ...", nullptr));
        Btn_LimAngleRemSeg->setText(QCoreApplication::translate("FDK_GUIClass", "Rem Segments ...", nullptr));
        QTreeWidgetItem *___qtreewidgetitem = TreeWidget_LimAngleSeg->headerItem();
        ___qtreewidgetitem->setText(1, QCoreApplication::translate("FDK_GUIClass", "Angle", nullptr));
        ___qtreewidgetitem->setText(0, QCoreApplication::translate("FDK_GUIClass", "Sinogram Files", nullptr));
        label_PreProcSinoDir->setText(QCoreApplication::translate("FDK_GUIClass", "Preprocessed Sinogram Directory:", nullptr));
        Btn_LimAnglePreProcDir->setText(QString());
        TabWidget_SinogramSettings->setTabText(TabWidget_SinogramSettings->indexOf(tab_LimAngle), QString());
        GrBox_ExecuteReconstruction->setTitle(QCoreApplication::translate("FDK_GUIClass", "Execute Reconstruction", nullptr));
        GrBox_SingleRecon->setTitle(QString());
        CkBox_WeightFilter->setText(QCoreApplication::translate("FDK_GUIClass", "Weight && Filter", nullptr));
        label_NumberProcesses->setText(QCoreApplication::translate("FDK_GUIClass", "Number of Threads:", nullptr));
        CkBox_Backprojection->setText(QCoreApplication::translate("FDK_GUIClass", "Backprojection", nullptr));
        label_5->setText(QCoreApplication::translate("FDK_GUIClass", "View direction:", nullptr));
        CBox_ViewDirection->setItemText(0, QCoreApplication::translate("FDK_GUIClass", "X-ray Source -> Detector", nullptr));
        CBox_ViewDirection->setItemText(1, QCoreApplication::translate("FDK_GUIClass", "Detector -> X-ray Source", nullptr));

        groupBox_InterpolationType->setTitle(QCoreApplication::translate("FDK_GUIClass", "Interpolation Type", nullptr));
        radioButton_fast->setText(QCoreApplication::translate("FDK_GUIClass", "Fast", nullptr));
        radioButton_accurate->setText(QCoreApplication::translate("FDK_GUIClass", "More Accurate", nullptr));
        Btn_RunReconstruction->setText(QCoreApplication::translate("FDK_GUIClass", "Run Reconstruction", nullptr));
        GrBox_TerminateReconstruction->setTitle(QCoreApplication::translate("FDK_GUIClass", "Terminate Process", nullptr));
        Btn_StopWeightFilterProc->setText(QCoreApplication::translate("FDK_GUIClass", "Stop Weight && Filter", nullptr));
        Btn_StopReconstructionProc->setText(QCoreApplication::translate("FDK_GUIClass", "Stop Reconstruction", nullptr));
        label->setText(QCoreApplication::translate("FDK_GUIClass", "Total execution time [s]:", nullptr));
        TabWidget_Reconstruction->setTabText(TabWidget_Reconstruction->indexOf(tab_SingleRecon), QCoreApplication::translate("FDK_GUIClass", "Single Reconstruction", nullptr));
        Btn_AddProjectToBatch->setText(QCoreApplication::translate("FDK_GUIClass", "Add Project", nullptr));
        Btn_RemProjectToBatch->setText(QCoreApplication::translate("FDK_GUIClass", "Remove Project", nullptr));
        Btn_RunBatch->setText(QCoreApplication::translate("FDK_GUIClass", "Run Batch", nullptr));
        Btn_StopBatch->setText(QCoreApplication::translate("FDK_GUIClass", "Stop Batch", nullptr));
        TabWidget_Reconstruction->setTabText(TabWidget_Reconstruction->indexOf(tab_BatchRecon), QCoreApplication::translate("FDK_GUIClass", "Batch Reconstruction", nullptr));
        groupBox_13->setTitle(QCoreApplication::translate("FDK_GUIClass", "Process Output", nullptr));
        pushButton_SaveProcessOutput->setText(QCoreApplication::translate("FDK_GUIClass", "Save Process Output ...", nullptr));
        pushButton_ClearOutput->setText(QCoreApplication::translate("FDK_GUIClass", "Clear Output", nullptr));
        menuFile->setTitle(QCoreApplication::translate("FDK_GUIClass", "File", nullptr));
        menu->setTitle(QCoreApplication::translate("FDK_GUIClass", "Project", nullptr));
        menuDatabase->setTitle(QCoreApplication::translate("FDK_GUIClass", "Database", nullptr));
        menuView->setTitle(QCoreApplication::translate("FDK_GUIClass", "View", nullptr));
        menuVersion->setTitle(QCoreApplication::translate("FDK_GUIClass", "Version", nullptr));
        menuBugs->setTitle(QCoreApplication::translate("FDK_GUIClass", "Bugs", nullptr));
        toolBar->setWindowTitle(QCoreApplication::translate("FDK_GUIClass", "toolBar", nullptr));
        dockWidget_ImageView->setWindowTitle(QCoreApplication::translate("FDK_GUIClass", "ImageViewer", nullptr));
        Dock_ImageArea->setText(QString());
        label_ShowImageName->setText(QCoreApplication::translate("FDK_GUIClass", "Image: ", nullptr));
        groupBox_4->setTitle(QCoreApplication::translate("FDK_GUIClass", "Control", nullptr));
        Btn_LoadImages->setText(QCoreApplication::translate("FDK_GUIClass", "Load Images ...", nullptr));
        label_2->setText(QCoreApplication::translate("FDK_GUIClass", "Width:", nullptr));
        label_3->setText(QCoreApplication::translate("FDK_GUIClass", "Height:", nullptr));
        label_4->setText(QCoreApplication::translate("FDK_GUIClass", "Type:", nullptr));
        dockWidget_ProjectOptions->setWindowTitle(QCoreApplication::translate("FDK_GUIClass", "Path Settings", nullptr));
        groupBox_5->setTitle(QString());
        Btn_MPIPath->setText(QCoreApplication::translate("FDK_GUIClass", "MPI BIN-Dir ...", nullptr));
        Btn_DataTopDir->setText(QCoreApplication::translate("FDK_GUIClass", "Data Top Dir ...", nullptr));
        Btn_SaveOptions->setText(QCoreApplication::translate("FDK_GUIClass", "Save Settings", nullptr));
        dockWidget_Database->setWindowTitle(QCoreApplication::translate("FDK_GUIClass", "Database Options", nullptr));
        label_6->setText(QString());
        label_7->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class FDK_GUIClass: public Ui_FDK_GUIClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FDK_GUI_H
