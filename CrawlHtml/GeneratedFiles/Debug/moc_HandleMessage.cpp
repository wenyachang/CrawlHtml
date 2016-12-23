/****************************************************************************
** Meta object code from reading C++ file 'HandleMessage.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.3.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../include/HandleMessage.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'HandleMessage.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.3.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HandleMessage_t {
    QByteArrayData data[8];
    char stringdata[82];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HandleMessage_t, stringdata) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HandleMessage_t qt_meta_stringdata_HandleMessage = {
    {
QT_MOC_LITERAL(0, 0, 13),
QT_MOC_LITERAL(1, 14, 10),
QT_MOC_LITERAL(2, 25, 0),
QT_MOC_LITERAL(3, 26, 10),
QT_MOC_LITERAL(4, 37, 7),
QT_MOC_LITERAL(5, 45, 11),
QT_MOC_LITERAL(6, 57, 11),
QT_MOC_LITERAL(7, 69, 12)
    },
    "HandleMessage\0setMessage\0\0exportType\0"
    "message\0isExportTxt\0isOutSqlite\0"
    "isRecordRule"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HandleMessage[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       1,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // methods: name, argc, parameters, tag, flags
       1,    5,   19,    2, 0x02 /* Public */,

 // methods: parameters
    QMetaType::Void, QMetaType::Int, QMetaType::QString, QMetaType::Bool, QMetaType::Bool, QMetaType::Bool,    3,    4,    5,    6,    7,

       0        // eod
};

void HandleMessage::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HandleMessage *_t = static_cast<HandleMessage *>(_o);
        switch (_id) {
        case 0: _t->setMessage((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< QString(*)>(_a[2])),(*reinterpret_cast< bool(*)>(_a[3])),(*reinterpret_cast< bool(*)>(_a[4])),(*reinterpret_cast< bool(*)>(_a[5]))); break;
        default: ;
        }
    }
}

const QMetaObject HandleMessage::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_HandleMessage.data,
      qt_meta_data_HandleMessage,  qt_static_metacall, 0, 0}
};


const QMetaObject *HandleMessage::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HandleMessage::qt_metacast(const char *_clname)
{
    if (!_clname) return 0;
    if (!strcmp(_clname, qt_meta_stringdata_HandleMessage.stringdata))
        return static_cast<void*>(const_cast< HandleMessage*>(this));
    return QObject::qt_metacast(_clname);
}

int HandleMessage::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 1)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 1;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 1)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 1;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
