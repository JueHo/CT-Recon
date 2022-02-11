/****************************************************************************
** Meta object code from reading C++ file 'threadload.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../threadload.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'threadload.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ThreadLoad_t {
    QByteArrayData data[7];
    char stringdata0[79];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ThreadLoad_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ThreadLoad_t qt_meta_stringdata_ThreadLoad = {
    {
QT_MOC_LITERAL(0, 0, 10), // "ThreadLoad"
QT_MOC_LITERAL(1, 11, 12), // "valueChanged"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 17), // "updateProgressBar"
QT_MOC_LITERAL(4, 43, 11), // "threadStart"
QT_MOC_LITERAL(5, 55, 9), // "threadEnd"
QT_MOC_LITERAL(6, 65, 13) // "threadStopped"

    },
    "ThreadLoad\0valueChanged\0\0updateProgressBar\0"
    "threadStart\0threadEnd\0threadStopped"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ThreadLoad[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       5,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   39,    2, 0x06 /* Public */,
       3,    1,   42,    2, 0x06 /* Public */,
       4,    0,   45,    2, 0x06 /* Public */,
       5,    0,   46,    2, 0x06 /* Public */,
       6,    0,   47,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void ThreadLoad::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<ThreadLoad *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->valueChanged((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->updateProgressBar((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->threadStart(); break;
        case 3: _t->threadEnd(); break;
        case 4: _t->threadStopped(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (ThreadLoad::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadLoad::valueChanged)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (ThreadLoad::*)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadLoad::updateProgressBar)) {
                *result = 1;
                return;
            }
        }
        {
            using _t = void (ThreadLoad::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadLoad::threadStart)) {
                *result = 2;
                return;
            }
        }
        {
            using _t = void (ThreadLoad::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadLoad::threadEnd)) {
                *result = 3;
                return;
            }
        }
        {
            using _t = void (ThreadLoad::*)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ThreadLoad::threadStopped)) {
                *result = 4;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject ThreadLoad::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_ThreadLoad.data,
    qt_meta_data_ThreadLoad,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *ThreadLoad::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ThreadLoad::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ThreadLoad.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int ThreadLoad::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 5)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 5;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 5)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 5;
    }
    return _id;
}

// SIGNAL 0
void ThreadLoad::valueChanged(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ThreadLoad::updateProgressBar(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ThreadLoad::threadStart()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ThreadLoad::threadEnd()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}

// SIGNAL 4
void ThreadLoad::threadStopped()
{
    QMetaObject::activate(this, &staticMetaObject, 4, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
