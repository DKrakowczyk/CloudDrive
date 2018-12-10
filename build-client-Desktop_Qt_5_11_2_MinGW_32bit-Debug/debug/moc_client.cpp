/****************************************************************************
** Meta object code from reading C++ file 'client.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.11.2)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../client.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'client.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.11.2. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_client_t {
    QByteArrayData data[14];
    char stringdata0[213];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_client_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_client_t qt_meta_stringdata_client = {
    {
QT_MOC_LITERAL(0, 0, 6), // "client"
QT_MOC_LITERAL(1, 7, 9), // "loginData"
QT_MOC_LITERAL(2, 17, 0), // ""
QT_MOC_LITERAL(3, 18, 11), // "readFortune"
QT_MOC_LITERAL(4, 30, 19), // "on_Register_clicked"
QT_MOC_LITERAL(5, 50, 15), // "getRegisterData"
QT_MOC_LITERAL(6, 66, 15), // "connectToServer"
QT_MOC_LITERAL(7, 82, 13), // "sendLoginData"
QT_MOC_LITERAL(8, 96, 16), // "on_logIn_clicked"
QT_MOC_LITERAL(9, 113, 16), // "sendFileToServer"
QT_MOC_LITERAL(10, 130, 18), // "downloadFromServer"
QT_MOC_LITERAL(11, 149, 27), // "on_disconnectClient_clicked"
QT_MOC_LITERAL(12, 177, 20), // "on_connectTo_clicked"
QT_MOC_LITERAL(13, 198, 14) // "showMainWindow"

    },
    "client\0loginData\0\0readFortune\0"
    "on_Register_clicked\0getRegisterData\0"
    "connectToServer\0sendLoginData\0"
    "on_logIn_clicked\0sendFileToServer\0"
    "downloadFromServer\0on_disconnectClient_clicked\0"
    "on_connectTo_clicked\0showMainWindow"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_client[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    0,   77,    2, 0x08 /* Private */,
       4,    0,   78,    2, 0x08 /* Private */,
       5,    1,   79,    2, 0x08 /* Private */,
       6,    0,   82,    2, 0x08 /* Private */,
       7,    1,   83,    2, 0x08 /* Private */,
       8,    0,   86,    2, 0x08 /* Private */,
       9,    1,   87,    2, 0x08 /* Private */,
      10,    1,   90,    2, 0x08 /* Private */,
      11,    0,   93,    2, 0x08 /* Private */,
      12,    0,   94,    2, 0x08 /* Private */,
      13,    0,   95,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Bool,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void client::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        client *_t = static_cast<client *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loginData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->readFortune(); break;
        case 2: _t->on_Register_clicked(); break;
        case 3: _t->getRegisterData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: { bool _r = _t->connectToServer();
            if (_a[0]) *reinterpret_cast< bool*>(_a[0]) = std::move(_r); }  break;
        case 5: _t->sendLoginData((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->on_logIn_clicked(); break;
        case 7: _t->sendFileToServer((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 8: _t->downloadFromServer((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 9: _t->on_disconnectClient_clicked(); break;
        case 10: _t->on_connectTo_clicked(); break;
        case 11: _t->showMainWindow(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            using _t = void (client::*)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&client::loginData)) {
                *result = 0;
                return;
            }
        }
    }
}

QT_INIT_METAOBJECT const QMetaObject client::staticMetaObject = {
    { &QMainWindow::staticMetaObject, qt_meta_stringdata_client.data,
      qt_meta_data_client,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *client::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *client::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_client.stringdata0))
        return static_cast<void*>(this);
    return QMainWindow::qt_metacast(_clname);
}

int client::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QMainWindow::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 12)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 12;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 12)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 12;
    }
    return _id;
}

// SIGNAL 0
void client::loginData(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
