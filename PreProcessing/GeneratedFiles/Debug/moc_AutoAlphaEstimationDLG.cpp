/****************************************************************************
** Meta object code from reading C++ file 'AutoAlphaEstimationDLG.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../AutoAlphaEstimationDLG.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'AutoAlphaEstimationDLG.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AlphaEstimationDialog_t {
    QByteArrayData data[10];
    char stringdata0[152];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AlphaEstimationDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AlphaEstimationDialog_t qt_meta_stringdata_AlphaEstimationDialog = {
    {
QT_MOC_LITERAL(0, 0, 21), // "AlphaEstimationDialog"
QT_MOC_LITERAL(1, 22, 9), // "ImageZoom"
QT_MOC_LITERAL(2, 32, 0), // ""
QT_MOC_LITERAL(3, 33, 16), // "DrawRectangleP1X"
QT_MOC_LITERAL(4, 50, 16), // "DrawRectangleP1Y"
QT_MOC_LITERAL(5, 67, 16), // "DrawRectangleP2X"
QT_MOC_LITERAL(6, 84, 16), // "DrawRectangleP2Y"
QT_MOC_LITERAL(7, 101, 11), // "ChangeAlpha"
QT_MOC_LITERAL(8, 113, 24), // "StartAlphaEstimationProc"
QT_MOC_LITERAL(9, 138, 13) // "SaveSelection"

    },
    "AlphaEstimationDialog\0ImageZoom\0\0"
    "DrawRectangleP1X\0DrawRectangleP1Y\0"
    "DrawRectangleP2X\0DrawRectangleP2Y\0"
    "ChangeAlpha\0StartAlphaEstimationProc\0"
    "SaveSelection"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AlphaEstimationDialog[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    0,   57,    2, 0x08 /* Private */,
       6,    0,   58,    2, 0x08 /* Private */,
       7,    0,   59,    2, 0x08 /* Private */,
       8,    0,   60,    2, 0x08 /* Private */,
       9,    0,   61,    2, 0x08 /* Private */,

 // slots: parameters
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

void AlphaEstimationDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AlphaEstimationDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->ImageZoom(); break;
        case 1: _t->DrawRectangleP1X(); break;
        case 2: _t->DrawRectangleP1Y(); break;
        case 3: _t->DrawRectangleP2X(); break;
        case 4: _t->DrawRectangleP2Y(); break;
        case 5: _t->ChangeAlpha(); break;
        case 6: _t->StartAlphaEstimationProc(); break;
        case 7: _t->SaveSelection(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject AlphaEstimationDialog::staticMetaObject = { {
    QMetaObject::SuperData::link<QDialog::staticMetaObject>(),
    qt_meta_stringdata_AlphaEstimationDialog.data,
    qt_meta_data_AlphaEstimationDialog,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AlphaEstimationDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AlphaEstimationDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AlphaEstimationDialog.stringdata0))
        return static_cast<void*>(this);
    return QDialog::qt_metacast(_clname);
}

int AlphaEstimationDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
