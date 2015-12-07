/****************************************************************************
** Meta object code from reading C++ file 'celldialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.5.1)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "celldialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'celldialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.5.1. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_CellDialog_t {
    QByteArrayData data[5];
    char stringdata0[52];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_CellDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_CellDialog_t qt_meta_stringdata_CellDialog = {
    {
QT_MOC_LITERAL(0, 0, 10), // "CellDialog"
QT_MOC_LITERAL(1, 11, 15), // "cellStartChange"
QT_MOC_LITERAL(2, 27, 0), // ""
QT_MOC_LITERAL(3, 28, 13), // "cellEndChange"
QT_MOC_LITERAL(4, 42, 9) // "okClicked"

    },
    "CellDialog\0cellStartChange\0\0cellEndChange\0"
    "okClicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_CellDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       3,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   29,    2, 0x06 /* Public */,
       3,    0,   30,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   31,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void CellDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        CellDialog *_t = static_cast<CellDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->cellStartChange(); break;
        case 1: _t->cellEndChange(); break;
        case 2: _t->okClicked(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (CellDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CellDialog::cellStartChange)) {
                *result = 0;
            }
        }
        {
            typedef void (CellDialog::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&CellDialog::cellEndChange)) {
                *result = 1;
            }
        }
    }
    Q_UNUSED(_a);
}

const QMetaObject CellDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_CellDialog.data,
      qt_meta_data_CellDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *CellDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *CellDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_CellDialog.stringdata0))
        return static_cast<void*>(const_cast< CellDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int CellDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 3)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 3;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 3)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 3;
    }
    return _id;
}

// SIGNAL 0
void CellDialog::cellStartChange()
{
    QMetaObject::activate(this, &staticMetaObject, 0, Q_NULLPTR);
}

// SIGNAL 1
void CellDialog::cellEndChange()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
