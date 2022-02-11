/****************************************************************************
** Meta object code from reading C++ file 'LorentzFilterDLG.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../LorentzFilterDLG.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'LorentzFilterDLG.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_LorentzFilterDialog_t {
    QByteArrayData data[14];
    char stringdata0[229];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_LorentzFilterDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_LorentzFilterDialog_t qt_meta_stringdata_LorentzFilterDialog = {
    {
QT_MOC_LITERAL(0, 0, 19), // "LorentzFilterDialog"
QT_MOC_LITERAL(1, 20, 13), // "ZoomLeftImage"
QT_MOC_LITERAL(2, 34, 0), // ""
QT_MOC_LITERAL(3, 35, 14), // "ZoomRightImage"
QT_MOC_LITERAL(4, 50, 18), // "OpenProjectionFile"
QT_MOC_LITERAL(5, 69, 12), // "ValidateFile"
QT_MOC_LITERAL(6, 82, 24), // "OpenAlphaEstimatorDialog"
QT_MOC_LITERAL(7, 107, 20), // "ProcessLorentzFilter"
QT_MOC_LITERAL(8, 128, 24), // "ApplyLorentzFilterByStep"
QT_MOC_LITERAL(9, 153, 18), // "ChangeCrossSection"
QT_MOC_LITERAL(10, 172, 13), // "SetZoomWindow"
QT_MOC_LITERAL(11, 186, 15), // "ResetZoomWindow"
QT_MOC_LITERAL(12, 202, 14), // "DrawZoomWindow"
QT_MOC_LITERAL(13, 217, 11) // "ChangeAlpha"

    },
    "LorentzFilterDialog\0ZoomLeftImage\0\0"
    "ZoomRightImage\0OpenProjectionFile\0"
    "ValidateFile\0OpenAlphaEstimatorDialog\0"
    "ProcessLorentzFilter\0ApplyLorentzFilterByStep\0"
    "ChangeCrossSection\0SetZoomWindow\0"
    "ResetZoomWindow\0DrawZoomWindow\0"
    "ChangeAlpha"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_LorentzFilterDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   74,    2, 0x08 /* Private */,
       3,    0,   75,    2, 0x08 /* Private */,
       4,    0,   76,    2, 0x08 /* Private */,
       5,    0,   77,    2, 0x08 /* Private */,
       6,    0,   78,    2, 0x08 /* Private */,
       7,    0,   79,    2, 0x08 /* Private */,
       8,    0,   80,    2, 0x08 /* Private */,
       9,    0,   81,    2, 0x08 /* Private */,
      10,    0,   82,    2, 0x08 /* Private */,
      11,    0,   83,    2, 0x08 /* Private */,
      12,    0,   84,    2, 0x08 /* Private */,
      13,    0,   85,    2, 0x08 /* Private */,

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

       0        // eod
};

void LorentzFilterDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<LorentzFilterDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ZoomLeftImage(); break;
        case 1: _t->ZoomRightImage(); break;
        case 2: _t->OpenProjectionFile(); break;
        case 3: _t->ValidateFile(); break;
        case 4: _t->OpenAlphaEstimatorDialog(); break;
        case 5: _t->ProcessLorentzFilter(); break;
        case 6: _t->ApplyLorentzFilterByStep(); break;
        case 7: _t->ChangeCrossSection(); break;
        case 8: _t->SetZoomWindow(); break;
        case 9: _t->ResetZoomWindow(); break;
        case 10: _t->DrawZoomWindow(); break;
        case 11: _t->ChangeAlpha(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject LorentzFilterDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_LorentzFilterDialog.data,
    qt_meta_data_LorentzFilterDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *LorentzFilterDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *LorentzFilterDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_LorentzFilterDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int LorentzFilterDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
