/****************************************************************************
** Meta object code from reading C++ file 'fdk_gui.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../fdk_gui.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'fdk_gui.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_FDK_GUI_t {
    QByteArrayData data[56];
    char stringdata0[938];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_FDK_GUI_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_FDK_GUI_t qt_meta_stringdata_FDK_GUI = {
    {
QT_MOC_LITERAL(0, 0, 7), // "FDK_GUI"
QT_MOC_LITERAL(1, 8, 18), // "SinoFileSelections"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 15), // "EditFilePattern"
QT_MOC_LITERAL(4, 44, 11), // "SinogramDir"
QT_MOC_LITERAL(5, 56, 18), // "SinogramPreProcDir"
QT_MOC_LITERAL(6, 75, 18), // "RemSelSinoFromList"
QT_MOC_LITERAL(7, 94, 12), // "ShowSinogram"
QT_MOC_LITERAL(8, 107, 21), // "LimAnglePreProcDirSel"
QT_MOC_LITERAL(9, 129, 18), // "LimAngleAddSegment"
QT_MOC_LITERAL(10, 148, 21), // "LimAngleRemoveSegment"
QT_MOC_LITERAL(11, 170, 17), // "RunReconstruction"
QT_MOC_LITERAL(12, 188, 20), // "UpdateFromFilterProc"
QT_MOC_LITERAL(13, 209, 17), // "UpdateFromRecProc"
QT_MOC_LITERAL(14, 227, 11), // "ProcStarted"
QT_MOC_LITERAL(15, 239, 12), // "ProcFinished"
QT_MOC_LITERAL(16, 252, 14), // "ProcStartedRec"
QT_MOC_LITERAL(17, 267, 15), // "ProcFinishedRec"
QT_MOC_LITERAL(18, 283, 21), // "DeleteALLItemFromList"
QT_MOC_LITERAL(19, 305, 15), // "SavePathSetting"
QT_MOC_LITERAL(20, 321, 15), // "LoadPathSetting"
QT_MOC_LITERAL(21, 337, 14), // "SetUseFileList"
QT_MOC_LITERAL(22, 352, 12), // "SetupMPIPath"
QT_MOC_LITERAL(23, 365, 16), // "SetupDataTopPath"
QT_MOC_LITERAL(24, 382, 12), // "SetupTomoDir"
QT_MOC_LITERAL(25, 395, 13), // "SetupControls"
QT_MOC_LITERAL(26, 409, 16), // "ChangeGPUThreads"
QT_MOC_LITERAL(27, 426, 14), // "SetVolumeCoord"
QT_MOC_LITERAL(28, 441, 24), // "SetVolumeSelectionButton"
QT_MOC_LITERAL(29, 466, 13), // "StopWFProcess"
QT_MOC_LITERAL(30, 480, 14), // "StopRecProcess"
QT_MOC_LITERAL(31, 495, 18), // "SetBinningSettings"
QT_MOC_LITERAL(32, 514, 18), // "CheckMaxVolRecSize"
QT_MOC_LITERAL(33, 533, 14), // "updateProcTime"
QT_MOC_LITERAL(34, 548, 17), // "AddProjectToBatch"
QT_MOC_LITERAL(35, 566, 22), // "RemoveProjectFromBatch"
QT_MOC_LITERAL(36, 589, 8), // "RunBatch"
QT_MOC_LITERAL(37, 598, 17), // "SaveProcessOutput"
QT_MOC_LITERAL(38, 616, 9), // "StopBatch"
QT_MOC_LITERAL(39, 626, 16), // "CkeckBlockStatus"
QT_MOC_LITERAL(40, 643, 22), // "ResetBlockFileSettings"
QT_MOC_LITERAL(41, 666, 3), // "val"
QT_MOC_LITERAL(42, 670, 20), // "ResetDisplaySettings"
QT_MOC_LITERAL(43, 691, 22), // "ResetDisplaySettingsFS"
QT_MOC_LITERAL(44, 714, 11), // "SetTiltCorr"
QT_MOC_LITERAL(45, 726, 21), // "SlopeTiltValueChanged"
QT_MOC_LITERAL(46, 748, 21), // "ConstTiltValueChanged"
QT_MOC_LITERAL(47, 770, 14), // "SetGuiModified"
QT_MOC_LITERAL(48, 785, 17), // "SetOptionModified"
QT_MOC_LITERAL(49, 803, 17), // "ActionSaveProject"
QT_MOC_LITERAL(50, 821, 19), // "ActionSaveProjectAs"
QT_MOC_LITERAL(51, 841, 16), // "ActionSwitchView"
QT_MOC_LITERAL(52, 858, 17), // "ActionOpenProject"
QT_MOC_LITERAL(53, 876, 21), // "ActionCheckParameters"
QT_MOC_LITERAL(54, 898, 16), // "ActionNewProject"
QT_MOC_LITERAL(55, 915, 22) // "ActionImportDetectData"

    },
    "FDK_GUI\0SinoFileSelections\0\0EditFilePattern\0"
    "SinogramDir\0SinogramPreProcDir\0"
    "RemSelSinoFromList\0ShowSinogram\0"
    "LimAnglePreProcDirSel\0LimAngleAddSegment\0"
    "LimAngleRemoveSegment\0RunReconstruction\0"
    "UpdateFromFilterProc\0UpdateFromRecProc\0"
    "ProcStarted\0ProcFinished\0ProcStartedRec\0"
    "ProcFinishedRec\0DeleteALLItemFromList\0"
    "SavePathSetting\0LoadPathSetting\0"
    "SetUseFileList\0SetupMPIPath\0"
    "SetupDataTopPath\0SetupTomoDir\0"
    "SetupControls\0ChangeGPUThreads\0"
    "SetVolumeCoord\0SetVolumeSelectionButton\0"
    "StopWFProcess\0StopRecProcess\0"
    "SetBinningSettings\0CheckMaxVolRecSize\0"
    "updateProcTime\0AddProjectToBatch\0"
    "RemoveProjectFromBatch\0RunBatch\0"
    "SaveProcessOutput\0StopBatch\0"
    "CkeckBlockStatus\0ResetBlockFileSettings\0"
    "val\0ResetDisplaySettings\0"
    "ResetDisplaySettingsFS\0SetTiltCorr\0"
    "SlopeTiltValueChanged\0ConstTiltValueChanged\0"
    "SetGuiModified\0SetOptionModified\0"
    "ActionSaveProject\0ActionSaveProjectAs\0"
    "ActionSwitchView\0ActionOpenProject\0"
    "ActionCheckParameters\0ActionNewProject\0"
    "ActionImportDetectData"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_FDK_GUI[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      53,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,  279,    2, 0x08 /* Private */,
       3,    0,  280,    2, 0x08 /* Private */,
       4,    0,  281,    2, 0x08 /* Private */,
       5,    0,  282,    2, 0x08 /* Private */,
       6,    0,  283,    2, 0x08 /* Private */,
       7,    0,  284,    2, 0x0a /* Public */,
       8,    0,  285,    2, 0x08 /* Private */,
       9,    0,  286,    2, 0x08 /* Private */,
      10,    0,  287,    2, 0x08 /* Private */,
      11,    0,  288,    2, 0x08 /* Private */,
      12,    0,  289,    2, 0x08 /* Private */,
      13,    0,  290,    2, 0x08 /* Private */,
      14,    0,  291,    2, 0x08 /* Private */,
      15,    0,  292,    2, 0x08 /* Private */,
      16,    0,  293,    2, 0x08 /* Private */,
      17,    0,  294,    2, 0x08 /* Private */,
      18,    0,  295,    2, 0x08 /* Private */,
      19,    0,  296,    2, 0x08 /* Private */,
      20,    0,  297,    2, 0x08 /* Private */,
      21,    0,  298,    2, 0x08 /* Private */,
      22,    0,  299,    2, 0x08 /* Private */,
      23,    0,  300,    2, 0x08 /* Private */,
      24,    0,  301,    2, 0x08 /* Private */,
      25,    0,  302,    2, 0x08 /* Private */,
      26,    0,  303,    2, 0x08 /* Private */,
      27,    0,  304,    2, 0x08 /* Private */,
      28,    0,  305,    2, 0x08 /* Private */,
      29,    0,  306,    2, 0x08 /* Private */,
      30,    0,  307,    2, 0x08 /* Private */,
      31,    0,  308,    2, 0x08 /* Private */,
      32,    0,  309,    2, 0x08 /* Private */,
      33,    0,  310,    2, 0x08 /* Private */,
      34,    0,  311,    2, 0x08 /* Private */,
      35,    0,  312,    2, 0x08 /* Private */,
      36,    0,  313,    2, 0x08 /* Private */,
      37,    0,  314,    2, 0x08 /* Private */,
      38,    0,  315,    2, 0x08 /* Private */,
      39,    0,  316,    2, 0x08 /* Private */,
      40,    1,  317,    2, 0x08 /* Private */,
      42,    1,  320,    2, 0x08 /* Private */,
      43,    1,  323,    2, 0x08 /* Private */,
      44,    0,  326,    2, 0x08 /* Private */,
      45,    0,  327,    2, 0x08 /* Private */,
      46,    0,  328,    2, 0x08 /* Private */,
      47,    0,  329,    2, 0x08 /* Private */,
      48,    0,  330,    2, 0x08 /* Private */,
      49,    0,  331,    2, 0x08 /* Private */,
      50,    0,  332,    2, 0x08 /* Private */,
      51,    0,  333,    2, 0x08 /* Private */,
      52,    0,  334,    2, 0x08 /* Private */,
      53,    0,  335,    2, 0x08 /* Private */,
      54,    0,  336,    2, 0x08 /* Private */,
      55,    0,  337,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   41,
    QMetaType::Void, QMetaType::Bool,   41,
    QMetaType::Void, QMetaType::Int,   41,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void FDK_GUI::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<FDK_GUI *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SinoFileSelections(); break;
        case 1: _t->EditFilePattern(); break;
        case 2: _t->SinogramDir(); break;
        case 3: _t->SinogramPreProcDir(); break;
        case 4: _t->RemSelSinoFromList(); break;
        case 5: _t->ShowSinogram(); break;
        case 6: _t->LimAnglePreProcDirSel(); break;
        case 7: _t->LimAngleAddSegment(); break;
        case 8: _t->LimAngleRemoveSegment(); break;
        case 9: _t->RunReconstruction(); break;
        case 10: _t->UpdateFromFilterProc(); break;
        case 11: _t->UpdateFromRecProc(); break;
        case 12: _t->ProcStarted(); break;
        case 13: _t->ProcFinished(); break;
        case 14: _t->ProcStartedRec(); break;
        case 15: _t->ProcFinishedRec(); break;
        case 16: _t->DeleteALLItemFromList(); break;
        case 17: _t->SavePathSetting(); break;
        case 18: _t->LoadPathSetting(); break;
        case 19: _t->SetUseFileList(); break;
        case 20: _t->SetupMPIPath(); break;
        case 21: _t->SetupDataTopPath(); break;
        case 22: _t->SetupTomoDir(); break;
        case 23: _t->SetupControls(); break;
        case 24: _t->ChangeGPUThreads(); break;
        case 25: _t->SetVolumeCoord(); break;
        case 26: _t->SetVolumeSelectionButton(); break;
        case 27: _t->StopWFProcess(); break;
        case 28: _t->StopRecProcess(); break;
        case 29: _t->SetBinningSettings(); break;
        case 30: _t->CheckMaxVolRecSize(); break;
        case 31: _t->updateProcTime(); break;
        case 32: _t->AddProjectToBatch(); break;
        case 33: _t->RemoveProjectFromBatch(); break;
        case 34: _t->RunBatch(); break;
        case 35: _t->SaveProcessOutput(); break;
        case 36: _t->StopBatch(); break;
        case 37: _t->CkeckBlockStatus(); break;
        case 38: _t->ResetBlockFileSettings((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 39: _t->ResetDisplaySettings((*reinterpret_cast< bool(*)>(_a[1]))); break;
        case 40: _t->ResetDisplaySettingsFS((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 41: _t->SetTiltCorr(); break;
        case 42: _t->SlopeTiltValueChanged(); break;
        case 43: _t->ConstTiltValueChanged(); break;
        case 44: _t->SetGuiModified(); break;
        case 45: _t->SetOptionModified(); break;
        case 46: _t->ActionSaveProject(); break;
        case 47: _t->ActionSaveProjectAs(); break;
        case 48: _t->ActionSwitchView(); break;
        case 49: _t->ActionOpenProject(); break;
        case 50: _t->ActionCheckParameters(); break;
        case 51: _t->ActionNewProject(); break;
        case 52: _t->ActionImportDetectData(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject FDK_GUI::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_FDK_GUI.data,
    qt_meta_data_FDK_GUI,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *FDK_GUI::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *FDK_GUI::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_FDK_GUI.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int FDK_GUI::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 53)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 53;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 53)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 53;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
