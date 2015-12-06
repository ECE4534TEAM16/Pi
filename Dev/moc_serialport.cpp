/****************************************************************************
** Meta object code from reading C++ file 'serialport.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "serialport.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialport.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_SerialPort_t {
    QByteArrayData data[12];
    char stringdata0[163];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SerialPort_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SerialPort_t qt_meta_stringdata_SerialPort = {
    {
QT_MOC_LITERAL(0, 0, 10), // "SerialPort"
QT_MOC_LITERAL(1, 11, 11), // "startMapper"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 9), // "startUser"
QT_MOC_LITERAL(4, 34, 18), // "recieveMapperInstr"
QT_MOC_LITERAL(5, 53, 12), // "sendUserPath"
QT_MOC_LITERAL(6, 66, 19), // "user_error_recieved"
QT_MOC_LITERAL(7, 86, 16), // "readMapperSerial"
QT_MOC_LITERAL(8, 103, 15), // "sendMapperStart"
QT_MOC_LITERAL(9, 119, 13), // "sendUserStart"
QT_MOC_LITERAL(10, 133, 14), // "sendUserSerial"
QT_MOC_LITERAL(11, 148, 14) // "readUserSerial"

    },
    "SerialPort\0startMapper\0\0startUser\0"
    "recieveMapperInstr\0sendUserPath\0"
    "user_error_recieved\0readMapperSerial\0"
    "sendMapperStart\0sendUserStart\0"
    "sendUserSerial\0readUserSerial"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SerialPort[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       5,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x06 /* Public */,
       3,    0,   65,    2, 0x06 /* Public */,
       4,    0,   66,    2, 0x06 /* Public */,
       5,    0,   67,    2, 0x06 /* Public */,
       6,    0,   68,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   69,    2, 0x08 /* Private */,
       8,    0,   70,    2, 0x08 /* Private */,
       9,    0,   71,    2, 0x08 /* Private */,
      10,    0,   72,    2, 0x08 /* Private */,
      11,    0,   73,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SerialPort::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SerialPort *_t = static_cast<SerialPort *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->startMapper(); break;
        case 1: _t->startUser(); break;
        case 2: _t->recieveMapperInstr(); break;
        case 3: _t->sendUserPath(); break;
        case 4: _t->user_error_recieved(); break;
        case 5: _t->readMapperSerial(); break;
        case 6: _t->sendMapperStart(); break;
        case 7: _t->sendUserStart(); break;
        case 8: _t->sendUserSerial(); break;
        case 9: _t->readUserSerial(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (SerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SerialPort::startMapper)) {
                *result = 0;
            }
        }
        {
            typedef void (SerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SerialPort::startUser)) {
                *result = 1;
            }
        }
        {
            typedef void (SerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SerialPort::recieveMapperInstr)) {
                *result = 2;
            }
        }
        {
            typedef void (SerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SerialPort::sendUserPath)) {
                *result = 3;
            }
        }
        {
            typedef void (SerialPort::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&SerialPort::user_error_recieved)) {
                *result = 4;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject SerialPort::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_SerialPort.data,
      qt_meta_data_SerialPort,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SerialPort::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SerialPort::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SerialPort.stringdata0))
        return static_cast<void*>(const_cast< SerialPort*>(this));
    return QObject::qt_metacast(_clname);
}

int SerialPort::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}

// SIGNAL 0
void SerialPort::startMapper()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void SerialPort::startUser()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}

// SIGNAL 2
void SerialPort::recieveMapperInstr()
{
    QMetaObject::activate(this, &staticMetaObject, 2, Q_NULLPTR);
}

// SIGNAL 3
void SerialPort::sendUserPath()
{
    QMetaObject::activate(this, &staticMetaObject, 3, Q_NULLPTR);
}

// SIGNAL 4
void SerialPort::user_error_recieved()
{
    QMetaObject::activate(this, &staticMetaObject, 4, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
