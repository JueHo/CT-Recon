/****************************************************************************
** Meta object code from reading C++ file 'ScaleImageDownThread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../ScaleImageDownThread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ScaleImageDownThread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ThreadScImage_t {
    QByteArrayData data[6];
    char stringdata0[68];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ThreadScImage_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ThreadScImage_t qt_meta_stringdata_ThreadScImage = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ThreadScImage"
QT_MOC_LITERAL(1, 14, 12), // "valueChanged"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 17), // "updateProgressBar"
QT_MOC_LITERAL(4, 46, 11), // "threadStart"
QT_MOC_LITERAL(5, 58, 9) // "threadEnd"

    },
    "ThreadScImage\0valueChanged\0\0"
    "updateProgressBar\0threadStart\0threadEnd"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ThreadScImage[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       3,    1,   37,    2, 0x06 /* Public */,
       4,    0,   40,    2, 0x06 /* Public */,
       5,    0,   41,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ThreadScImage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ThreadScImage *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->updateProgressBar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->threadStart(); break;
        case 3: _t->threadEnd(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ThreadScImage::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadScImage::valueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ThreadScImage::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadScImage::updateProgressBar)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ThreadScImage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadScImage::threadStart)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ThreadScImage::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadScImage::threadEnd)) {
                *result = 3;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ThreadScImage::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_ThreadScImage.data,
    qt_meta_data_ThreadScImage,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ThreadScImage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ThreadScImage::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ThreadScImage.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int ThreadScImage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 4)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 4)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 4;
    }
    return _id;
}

// SIGNAL 0
void ThreadScImage::valueChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ThreadScImage::updateProgressBar(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ThreadScImage::threadStart()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ThreadScImage::threadEnd()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
