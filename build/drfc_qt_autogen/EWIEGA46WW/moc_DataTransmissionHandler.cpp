/****************************************************************************
** Meta object code from reading C++ file 'DataTransmissionHandler.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.15.16)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include <memory>
#include "../../../DataTransmissionHandler.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'DataTransmissionHandler.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.15.16. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_DataTransmissionHandler_t {
    QByteArrayData data[8];
    char stringdata0[119];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_DataTransmissionHandler_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_DataTransmissionHandler_t qt_meta_stringdata_DataTransmissionHandler = {
    {
QT_MOC_LITERAL(0, 0, 23), // "DataTransmissionHandler"
QT_MOC_LITERAL(1, 24, 21), // "ReflectogramDataReady"
QT_MOC_LITERAL(2, 46, 0), // ""
QT_MOC_LITERAL(3, 47, 25), // "QPair<quint16,QByteArray>"
QT_MOC_LITERAL(4, 73, 7), // "newPair"
QT_MOC_LITERAL(5, 81, 14), // "ChartDataReady"
QT_MOC_LITERAL(6, 96, 14), // "QList<quint16>"
QT_MOC_LITERAL(7, 111, 7) // "numbers"

    },
    "DataTransmissionHandler\0ReflectogramDataReady\0"
    "\0QPair<quint16,QByteArray>\0newPair\0"
    "ChartDataReady\0QList<quint16>\0numbers"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_DataTransmissionHandler[] = {

 // content:
       8,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,
       5,    1,   27,    2, 0x06 /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, 0x80000000 | 6,    7,

       0        // eod
};

void DataTransmissionHandler::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        auto *_t = static_cast<DataTransmissionHandler *>(_o);
        (void)_t;
        switch (_id) {
        case 0: _t->ReflectogramDataReady((*reinterpret_cast< const QPair<quint16,QByteArray>(*)>(_a[1]))); break;
        case 1: _t->ChartDataReady((*reinterpret_cast< const QList<quint16>(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<quint16> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (DataTransmissionHandler::*)(const QPair<quint16,QByteArray> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataTransmissionHandler::ReflectogramDataReady)) {
                *result = 0;
                return;
            }
        }
        {
            using _t = void (DataTransmissionHandler::*)(const QList<quint16> & );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&DataTransmissionHandler::ChartDataReady)) {
                *result = 1;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject DataTransmissionHandler::staticMetaObject = { {
    QMetaObject::SuperData::link<QThread::staticMetaObject>(),
    qt_meta_stringdata_DataTransmissionHandler.data,
    qt_meta_data_DataTransmissionHandler,
    qt_static_metacall,
    nullptr,
    nullptr
} };


const QMetaObject *DataTransmissionHandler::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *DataTransmissionHandler::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_DataTransmissionHandler.stringdata0))
        return static_cast<void*>(this);
    return QThread::qt_metacast(_clname);
}

int DataTransmissionHandler::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void DataTransmissionHandler::ReflectogramDataReady(const QPair<quint16,QByteArray> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void DataTransmissionHandler::ChartDataReady(const QList<quint16> & _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(std::addressof(_t1))) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
