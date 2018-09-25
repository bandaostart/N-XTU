/****************************************************************************
** Meta object code from reading C++ file 'serialdialog.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.8.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../N-XTU/serialdialog.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'serialdialog.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.8.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_SerialDialog_t {
    QByteArrayData data[13];
    char stringdata0[265];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_SerialDialog_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_SerialDialog_t qt_meta_stringdata_SerialDialog = {
    {
QT_MOC_LITERAL(0, 0, 12), // "SerialDialog"
QT_MOC_LITERAL(1, 13, 27), // "on_SelectPort_Radio_clicked"
QT_MOC_LITERAL(2, 41, 0), // ""
QT_MOC_LITERAL(3, 42, 28), // "on_ProvidePort_Radio_clicked"
QT_MOC_LITERAL(4, 71, 29), // "on_RefreshPort_Button_clicked"
QT_MOC_LITERAL(5, 101, 28), // "on_Port_ListView_itemClicked"
QT_MOC_LITERAL(6, 130, 16), // "QListWidgetItem*"
QT_MOC_LITERAL(7, 147, 4), // "item"
QT_MOC_LITERAL(8, 152, 28), // "on_Port_LineEdit_textChanged"
QT_MOC_LITERAL(9, 181, 4), // "arg1"
QT_MOC_LITERAL(10, 186, 24), // "on_Finish_Button_clicked"
QT_MOC_LITERAL(11, 211, 28), // "on_SetDefault_Button_clicked"
QT_MOC_LITERAL(12, 240, 24) // "on_Cancel_Button_clicked"

    },
    "SerialDialog\0on_SelectPort_Radio_clicked\0"
    "\0on_ProvidePort_Radio_clicked\0"
    "on_RefreshPort_Button_clicked\0"
    "on_Port_ListView_itemClicked\0"
    "QListWidgetItem*\0item\0"
    "on_Port_LineEdit_textChanged\0arg1\0"
    "on_Finish_Button_clicked\0"
    "on_SetDefault_Button_clicked\0"
    "on_Cancel_Button_clicked"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_SerialDialog[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   54,    2, 0x08 /* Private */,
       3,    0,   55,    2, 0x08 /* Private */,
       4,    0,   56,    2, 0x08 /* Private */,
       5,    1,   57,    2, 0x08 /* Private */,
       8,    1,   60,    2, 0x08 /* Private */,
      10,    0,   63,    2, 0x08 /* Private */,
      11,    0,   64,    2, 0x08 /* Private */,
      12,    0,   65,    2, 0x08 /* Private */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 6,    7,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void SerialDialog::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        SerialDialog *_t = static_cast<SerialDialog *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->on_SelectPort_Radio_clicked(); break;
        case 1: _t->on_ProvidePort_Radio_clicked(); break;
        case 2: _t->on_RefreshPort_Button_clicked(); break;
        case 3: _t->on_Port_ListView_itemClicked((*reinterpret_cast< QListWidgetItem*(*)>(_a[1]))); break;
        case 4: _t->on_Port_LineEdit_textChanged((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->on_Finish_Button_clicked(); break;
        case 6: _t->on_SetDefault_Button_clicked(); break;
        case 7: _t->on_Cancel_Button_clicked(); break;
        default: ;
        }
    }
}

const QMetaObject SerialDialog::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_SerialDialog.data,
      qt_meta_data_SerialDialog,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *SerialDialog::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *SerialDialog::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_SerialDialog.stringdata0))
        return static_cast<void*>(const_cast< SerialDialog*>(this));
    return QDialog::qt_metacast(_clname);
}

int SerialDialog::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
    return _id;
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
