/****************************************************************************
** Meta object code from reading C++ file 'modulewindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../N-XTU/modulewindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'modulewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ModuleWindow_t {
    QByteArrayData data[7];
    char stringdata0[93];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ModuleWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ModuleWindow_t qt_meta_stringdata_ModuleWindow = {
    {
QT_MOC_LITERAL(0, 0, 12), // "ModuleWindow"
QT_MOC_LITERAL(1, 13, 21), // "Signal_ModuleWinClose"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 8), // "portname"
QT_MOC_LITERAL(4, 45, 17), // "Signal_MousePress"
QT_MOC_LITERAL(5, 63, 10), // "moduletype"
QT_MOC_LITERAL(6, 74, 18) // "ModuleWindow_Close"

    },
    "ModuleWindow\0Signal_ModuleWinClose\0\0"
    "portname\0Signal_MousePress\0moduletype\0"
    "ModuleWindow_Close"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ModuleWindow[] = {

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
       1,    1,   29,    2, 0x06 /* Public */,
       4,    2,   32,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   37,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    3,    5,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void ModuleWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ModuleWindow *_t = static_cast<ModuleWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Signal_ModuleWinClose((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 1: _t->Signal_MousePress((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 2: _t->ModuleWindow_Close(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ModuleWindow::*_t)(const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ModuleWindow::Signal_ModuleWinClose)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ModuleWindow::*_t)(const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ModuleWindow::Signal_MousePress)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject ModuleWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ModuleWindow.data,
      qt_meta_data_ModuleWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ModuleWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ModuleWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ModuleWindow.stringdata0))
        return static_cast<void*>(const_cast< ModuleWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int ModuleWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void ModuleWindow::Signal_ModuleWinClose(const QString & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ModuleWindow::Signal_MousePress(const QString & _t1, const QString & _t2)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
