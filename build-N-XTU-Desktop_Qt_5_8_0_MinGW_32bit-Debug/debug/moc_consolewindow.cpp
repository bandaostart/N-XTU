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
    QByteArrayData data[15];
    char stringdata0[277];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ConsoleWindow_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ConsoleWindow_t qt_meta_stringdata_ConsoleWindow = {
    {
QT_MOC_LITERAL(0, 0, 13), // "ConsoleWindow"
QT_MOC_LITERAL(1, 14, 30), // "Signal_StartStopTest_ToMainWin"
QT_MOC_LITERAL(2, 45, 0), // ""
QT_MOC_LITERAL(3, 46, 5), // "state"
QT_MOC_LITERAL(4, 52, 6), // "dmport"
QT_MOC_LITERAL(5, 59, 6), // "dpport"
QT_MOC_LITERAL(6, 66, 34), // "Slot_ModuleStateChange_FromMa..."
QT_MOC_LITERAL(7, 101, 10), // "add_delete"
QT_MOC_LITERAL(8, 112, 8), // "portname"
QT_MOC_LITERAL(9, 121, 8), // "noidtype"
QT_MOC_LITERAL(10, 130, 34), // "Slot_StartStopTest_FromStartA..."
QT_MOC_LITERAL(11, 165, 34), // "Slot_RefreshText_FromRefreshA..."
QT_MOC_LITERAL(12, 200, 37), // "Slot_CommunicationDisplay_Fro..."
QT_MOC_LITERAL(13, 238, 3), // "str"
QT_MOC_LITERAL(14, 242, 34) // "Slot_RecordMenuText_FromRecor..."

    },
    "ConsoleWindow\0Signal_StartStopTest_ToMainWin\0"
    "\0state\0dmport\0dpport\0"
    "Slot_ModuleStateChange_FromMainWin\0"
    "add_delete\0portname\0noidtype\0"
    "Slot_StartStopTest_FromStartAction\0"
    "Slot_RefreshText_FromRefreshAction\0"
    "Slot_CommunicationDisplay_FromMainWin\0"
    "str\0Slot_RecordMenuText_FromRecordText"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ConsoleWindow[] = {

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
       6,    3,   51,    2, 0x0a /* Public */,
      10,    0,   58,    2, 0x0a /* Public */,
      11,    0,   59,    2, 0x0a /* Public */,
      12,    2,   60,    2, 0x0a /* Public */,
      14,    1,   65,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString,    3,    4,    5,

 // slots: parameters
    QMetaType::Void, QMetaType::Bool, QMetaType::QString, QMetaType::QString,    7,    8,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString, QMetaType::QString,    8,   13,
    QMetaType::Void, QMetaType::QPoint,    2,

       0        // eod
};

void ConsoleWindow::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ConsoleWindow *_t = static_cast<ConsoleWindow *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->Signal_StartStopTest_ToMainWin((*reinterpret_cast< const bool(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2])),(*reinterpret_cast< const QString(*)>(_a[3]))); break;
        case 1: _t->Slot_ModuleStateChange_FromMainWin((*reinterpret_cast< bool(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< QString(*)>(_a[3]))); break;
        case 2: _t->Slot_StartStopTest_FromStartAction(); break;
        case 3: _t->Slot_RefreshText_FromRefreshAction(); break;
        case 4: _t->Slot_CommunicationDisplay_FromMainWin((*reinterpret_cast< const QString(*)>(_a[1])),(*reinterpret_cast< const QString(*)>(_a[2]))); break;
        case 5: _t->Slot_RecordMenuText_FromRecordText((*reinterpret_cast< QPoint(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ConsoleWindow::*_t)(const bool & , const QString & , const QString & );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ConsoleWindow::Signal_StartStopTest_ToMainWin)) {
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
void ConsoleWindow::Signal_StartStopTest_ToMainWin(const bool & _t1, const QString & _t2, const QString & _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
