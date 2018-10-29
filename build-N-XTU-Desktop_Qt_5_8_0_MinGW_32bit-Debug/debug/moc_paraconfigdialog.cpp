/****************************************************************************
** Meta object code from reading C++ file 'paraconfigdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../N-XTU/paraconfigdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'paraconfigdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ParaConfigDialog_t {
    QByteArrayData data[13];
    char stringdata0[146];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ParaConfigDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ParaConfigDialog_t qt_meta_stringdata_ParaConfigDialog = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ParaConfigDialog"
QT_MOC_LITERAL(1, 17, 20), // "Signal_Para_ToManWin"
QT_MOC_LITERAL(2, 38, 0), // ""
QT_MOC_LITERAL(3, 39, 12), // "const float*"
QT_MOC_LITERAL(4, 52, 11), // "paradatamin"
QT_MOC_LITERAL(5, 64, 11), // "paradatamax"
QT_MOC_LITERAL(6, 76, 3), // "num"
QT_MOC_LITERAL(7, 80, 10), // "Apply_Deal"
QT_MOC_LITERAL(8, 91, 11), // "Cancle_Deal"
QT_MOC_LITERAL(9, 103, 12), // "Default_Deal"
QT_MOC_LITERAL(10, 116, 10), // "Timer_Deal"
QT_MOC_LITERAL(11, 127, 12), // "ParaCfg_Deal"
QT_MOC_LITERAL(12, 140, 5) // "index"

    },
    "ParaConfigDialog\0Signal_Para_ToManWin\0"
    "\0const float*\0paradatamin\0paradatamax\0"
    "num\0Apply_Deal\0Cancle_Deal\0Default_Deal\0"
    "Timer_Deal\0ParaCfg_Deal\0index"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ParaConfigDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       6,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   44,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   51,    2, 0x08 /* Private */,
       8,    0,   52,    2, 0x08 /* Private */,
       9,    0,   53,    2, 0x08 /* Private */,
      10,    0,   54,    2, 0x08 /* Private */,
      11,    1,   55,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3, 0x80000000 | 3, QMetaType::Int,    4,    5,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   12,

       0        // eod
};

void ParaConfigDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ParaConfigDialog *_t = static_cast<ParaConfigDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Signal_Para_ToManWin((*reinterpret_cast< const float*(*)>(_a[1])),(*reinterpret_cast< const float*(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 1: _t->Apply_Deal(); break;
        case 2: _t->Cancle_Deal(); break;
        case 3: _t->Default_Deal(); break;
        case 4: _t->Timer_Deal(); break;
        case 5: _t->ParaCfg_Deal((*reinterpret_cast< int(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ParaConfigDialog::*_t)(const float * , const float * , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParaConfigDialog::Signal_Para_ToManWin)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ParaConfigDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_ParaConfigDialog.data,
      qt_meta_data_ParaConfigDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ParaConfigDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ParaConfigDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ParaConfigDialog.stringdata0))
        return static_cast<void*>(const_cast< ParaConfigDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int ParaConfigDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 6)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 6;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 6)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 6;
    }
    return _id;
}

// SIGNAL 0
void ParaConfigDialog::Signal_Para_ToManWin(const float * _t1, const float * _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
