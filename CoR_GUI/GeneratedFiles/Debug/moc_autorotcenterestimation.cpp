/****************************************************************************
** Meta object code from reading C++ file 'autorotcenterestimation.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../autorotcenterestimation.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'autorotcenterestimation.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_AutoRotCenterEstimation_t {
    QByteArrayData data[9];
    char stringdata0[137];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_AutoRotCenterEstimation_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_AutoRotCenterEstimation_t qt_meta_stringdata_AutoRotCenterEstimation = {
    {
QT_MOC_LITERAL(0, 0, 23), // "AutoRotCenterEstimation"
QT_MOC_LITERAL(1, 24, 8), // "CloseWin"
QT_MOC_LITERAL(2, 33, 0), // ""
QT_MOC_LITERAL(3, 34, 12), // "StartAutoRot"
QT_MOC_LITERAL(4, 47, 12), // "LoadPFDKFile"
QT_MOC_LITERAL(5, 60, 15), // "CheckTiltStatus"
QT_MOC_LITERAL(6, 76, 22), // "ChangeMultiRowStepSize"
QT_MOC_LITERAL(7, 99, 15), // "ChangeFromSlice"
QT_MOC_LITERAL(8, 115, 21) // "ChangeCntSupportPoint"

    },
    "AutoRotCenterEstimation\0CloseWin\0\0"
    "StartAutoRot\0LoadPFDKFile\0CheckTiltStatus\0"
    "ChangeMultiRowStepSize\0ChangeFromSlice\0"
    "ChangeCntSupportPoint"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_AutoRotCenterEstimation[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x0a /* Public */,
       3,    0,   50,    2, 0x0a /* Public */,
       4,    0,   51,    2, 0x0a /* Public */,
       5,    0,   52,    2, 0x0a /* Public */,
       6,    0,   53,    2, 0x0a /* Public */,
       7,    0,   54,    2, 0x0a /* Public */,
       8,    0,   55,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void AutoRotCenterEstimation::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<AutoRotCenterEstimation *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->CloseWin(); break;
        case 1: _t->StartAutoRot(); break;
        case 2: _t->LoadPFDKFile(); break;
        case 3: _t->CheckTiltStatus(); break;
        case 4: _t->ChangeMultiRowStepSize(); break;
        case 5: _t->ChangeFromSlice(); break;
        case 6: _t->ChangeCntSupportPoint(); break;
        default: ;
        }
    }
    Q_UNUSED(_a);
}

QT_INIT_METAOBJECT const QMetaObject AutoRotCenterEstimation::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_AutoRotCenterEstimation.data,
    qt_meta_data_AutoRotCenterEstimation,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *AutoRotCenterEstimation::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *AutoRotCenterEstimation::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_AutoRotCenterEstimation.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int AutoRotCenterEstimation::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 7;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
