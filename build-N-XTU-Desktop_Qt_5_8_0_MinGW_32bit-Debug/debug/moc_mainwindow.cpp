/****************************************************************************
** Meta object code from reading C++ file 'mainwindow.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../N-XTU/mainwindow.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwindow.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_MainWindow_t {
    QByteArrayData data[20];
    char stringdata0[295];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_MainWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_MainWindow_t qt_meta_stringdata_MainWindow = {
    {
QT_MOC_LITERAL(0, 0, 10), // "MainWindow"
QT_MOC_LITERAL(1, 11, 37), // "Signal_ModuleStateChange_ToCo..."
QT_MOC_LITERAL(2, 49, 0), // ""
QT_MOC_LITERAL(3, 50, 10), // "add_delete"
QT_MOC_LITERAL(4, 61, 8), // "portname"
QT_MOC_LITERAL(5, 70, 8), // "noidtype"
QT_MOC_LITERAL(6, 79, 17), // "Open_SerialDialog"
QT_MOC_LITERAL(7, 97, 18), // "Close_ModuleWindow"
QT_MOC_LITERAL(8, 116, 21), // "Receive_SerialMessage"
QT_MOC_LITERAL(9, 138, 14), // "unsigned char*"
QT_MOC_LITERAL(10, 153, 7), // "rx_data"
QT_MOC_LITERAL(11, 161, 6), // "rx_num"
QT_MOC_LITERAL(12, 168, 18), // "Send_SerialMessage"
QT_MOC_LITERAL(13, 187, 18), // "Close_SearchDialog"
QT_MOC_LITERAL(14, 206, 17), // "Slot_TestRunTimer"
QT_MOC_LITERAL(15, 224, 33), // "Slot_StartStopTest_FromConsol..."
QT_MOC_LITERAL(16, 258, 5), // "state"
QT_MOC_LITERAL(17, 264, 6), // "dmport"
QT_MOC_LITERAL(18, 271, 6), // "dpport"
QT_MOC_LITERAL(19, 278, 16) // "Application_Exit"

    },
    "MainWindow\0Signal_ModuleStateChange_ToConsoleWin\0"
    "\0add_delete\0portname\0noidtype\0"
    "Open_SerialDialog\0Close_ModuleWindow\0"
    "Receive_SerialMessage\0unsigned char*\0"
    "rx_data\0rx_num\0Send_SerialMessage\0"
    "Close_SearchDialog\0Slot_TestRunTimer\0"
    "Slot_StartStopTest_FromConsoleWin\0"
    "state\0dmport\0dpport\0Application_Exit"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_MainWindow[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       9,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    3,   59,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    0,   66,    2, 0x08 /* Private */,
       7,    1,   67,    2, 0x08 /* Private */,
       8,    3,   70,    2, 0x08 /* Private */,
      12,    0,   77,    2, 0x08 /* Private */,
      13,    1,   78,    2, 0x08 /* Private */,
      14,    0,   81,    2, 0x08 /* Private */,
      15,    3,   82,    2, 0x08 /* Private */,
      19,    0,   89,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString,    3,    4,    5,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void, QMetaType::QString, 0x80000000 | 9, QMetaType::UShort,    4,   10,   11,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    4,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString,   16,   17,   18,
    QMetaType::Void,

       0        // eod
};

void MainWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        MainWindow *_t = static_cast<MainWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Signal_ModuleStateChange_ToConsoleWin((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 1: _t->Open_SerialDialog(); break;
        case 2: _t->Close_ModuleWindow((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 3: _t->Receive_SerialMessage((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< unsigned char*(*)>(_a[2])),(*reinterpret_cast< unsigned short(*)>(_a[3]))); break;
        case 4: _t->Send_SerialMessage(); break;
        case 5: _t->Close_SearchDialog((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->Slot_TestRunTimer(); break;
        case 7: _t->Slot_StartStopTest_FromConsoleWin((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 8: _t->Application_Exit(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (MainWindow::*_t)(bool , QString , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&MainWindow::Signal_ModuleStateChange_ToConsoleWin)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject MainWindow::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_MainWindow.data,
      qt_meta_data_MainWindow,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *MainWindow::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *MainWindow::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_MainWindow.stringdata0))
        return static_cast<void*>(const_cast< MainWindow*>(this));
    return QMainWindow::qt_metacast(_clname);
}

int MainWindow::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 9)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 9;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 9)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 9;
    }
    return _id;
}

// SIGNAL 0
void MainWindow::Signal_ModuleStateChange_ToConsoleWin(bool _t1, QString _t2, QString _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
