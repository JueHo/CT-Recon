/****************************************************************************
** Meta object code from reading C++ file 'histogramremap.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../histogramremap.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'histogramremap.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_HistogramRemap_t {
    QByteArrayData data[16];
    char stringdata0[254];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HistogramRemap_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HistogramRemap_t qt_meta_stringdata_HistogramRemap = {
    {
QT_MOC_LITERAL(0, 0, 14), // "HistogramRemap"
QT_MOC_LITERAL(1, 15, 13), // "SetRightBound"
QT_MOC_LITERAL(2, 29, 0), // ""
QT_MOC_LITERAL(3, 30, 8), // "QPointF&"
QT_MOC_LITERAL(4, 39, 4), // "fPos"
QT_MOC_LITERAL(5, 44, 12), // "SetLeftBound"
QT_MOC_LITERAL(6, 57, 22), // "GetImageStackDirectory"
QT_MOC_LITERAL(7, 80, 28), // "GetImageDestinationDirectory"
QT_MOC_LITERAL(8, 109, 14), // "ReadImageStack"
QT_MOC_LITERAL(9, 124, 22), // "SetMinMaxLogGroupState"
QT_MOC_LITERAL(10, 147, 20), // "GetMinMaxFromLogFile"
QT_MOC_LITERAL(11, 168, 17), // "PopulateHistogram"
QT_MOC_LITERAL(12, 186, 20), // "SelectHistogramColor"
QT_MOC_LITERAL(13, 207, 15), // "SelectPlotColor"
QT_MOC_LITERAL(14, 223, 14), // "ConvertToUChar"
QT_MOC_LITERAL(15, 238, 15) // "ConvertToUShort"

    },
    "HistogramRemap\0SetRightBound\0\0QPointF&\0"
    "fPos\0SetLeftBound\0GetImageStackDirectory\0"
    "GetImageDestinationDirectory\0"
    "ReadImageStack\0SetMinMaxLogGroupState\0"
    "GetMinMaxFromLogFile\0PopulateHistogram\0"
    "SelectHistogramColor\0SelectPlotColor\0"
    "ConvertToUChar\0ConvertToUShort"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HistogramRemap[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   84,    2, 0x08 /* Private */,
       1,    1,   85,    2, 0x08 /* Private */,
       5,    0,   88,    2, 0x08 /* Private */,
       5,    1,   89,    2, 0x08 /* Private */,
       6,    0,   92,    2, 0x08 /* Private */,
       7,    0,   93,    2, 0x08 /* Private */,
       8,    0,   94,    2, 0x08 /* Private */,
       9,    0,   95,    2, 0x08 /* Private */,
      10,    0,   96,    2, 0x08 /* Private */,
      11,    0,   97,    2, 0x08 /* Private */,
      12,    0,   98,    2, 0x08 /* Private */,
      13,    0,   99,    2, 0x08 /* Private */,
      14,    0,  100,    2, 0x08 /* Private */,
      15,    0,  101,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Bool,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void HistogramRemap::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<HistogramRemap *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SetRightBound(); break;
        case 1: _t->SetRightBound((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 2: _t->SetLeftBound(); break;
        case 3: _t->SetLeftBound((*reinterpret_cast< QPointF(*)>(_a[1]))); break;
        case 4: _t->GetImageStackDirectory(); break;
        case 5: _t->GetImageDestinationDirectory(); break;
        case 6: _t->ReadImageStack(); break;
        case 7: _t->SetMinMaxLogGroupState(); break;
        case 8: _t->GetMinMaxFromLogFile(); break;
        case 9: { bool _r = _t->PopulateHistogram();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 10: _t->SelectHistogramColor(); break;
        case 11: _t->SelectPlotColor(); break;
        case 12: _t->ConvertToUChar(); break;
        case 13: _t->ConvertToUShort(); break;
        default: ;
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject HistogramRemap::staticMetaObject = { {
    QMetaObject::SuperData::link<QMainWindow::staticMetaObject>(),
    qt_meta_stringdata_HistogramRemap.data,
    qt_meta_data_HistogramRemap,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *HistogramRemap::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HistogramRemap::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_HistogramRemap.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int HistogramRemap::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
