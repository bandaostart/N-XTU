/****************************************************************************
** Meta object code from reading C++ file 'consolewindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../N-XTU/consolewindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'consolewindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ConsoleWindow_t {
    QByteArrayData data[8];
    char stringdata0[100];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConsoleWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConsoleWindow_t qt_meta_stringdata_ConsoleWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ConsoleWindow"
QT_MOC_LITERAL(1, 14, 20), // "Signal_Testing_State"
QT_MOC_LITERAL(2, 35, 0), // ""
QT_MOC_LITERAL(3, 36, 5), // "state"
QT_MOC_LITERAL(4, 42, 15), // "Start_RfTesting"
QT_MOC_LITERAL(5, 58, 21), // "Communication_Display"
QT_MOC_LITERAL(6, 80, 3), // "str"
QT_MOC_LITERAL(7, 84, 15) // "Record_MenuText"

    },
    "ConsoleWindow\0Signal_Testing_State\0\0"
    "state\0Start_RfTesting\0Communication_Display\0"
    "str\0Record_MenuText"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConsoleWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       4,    0,   37,    2, 0x0a /* Public */,
       5,    1,   38,    2, 0x0a /* Public */,
       7,    1,   41,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool,    3,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    6,
    QMetaType::Void, QMetaType::QPoint,    2,

       0        // eod
};

void ConsoleWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConsoleWindow *_t = static_cast<ConsoleWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Signal_Testing_State((*reinterpret_cast< const bool(*)>(_a[1]))); break;
        case 1: _t->Start_RfTesting(); break;
        case 2: _t->Communication_Display((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->Record_MenuText((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ConsoleWindow::*_t)(const bool & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConsoleWindow::Signal_Testing_State)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject ConsoleWindow::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_ConsoleWindow.data,
      qt_meta_data_ConsoleWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ConsoleWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ConsoleWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ConsoleWindow.stringdata0))
        return static_cast<void*>(const_cast< ConsoleWindow*>(this));
    return QWidget::qt_metacast(_clname);
}

int ConsoleWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
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
void ConsoleWindow::Signal_Testing_State(const bool & _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
