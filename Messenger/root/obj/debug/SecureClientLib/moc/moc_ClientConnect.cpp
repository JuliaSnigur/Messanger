/****************************************************************************
** Meta object code from reading C++ file 'ClientConnect.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/SecureClientLib/ClientConnect.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QList>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClientConnect.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ClientConnection_t {
    QByteArrayData data[13];
    char stringdata0[174];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientConnection_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientConnection_t qt_meta_stringdata_ClientConnection = {
    {
QT_MOC_LITERAL(0, 0, 16), // "ClientConnection"
QT_MOC_LITERAL(1, 17, 21), // "signalGetListsClients"
QT_MOC_LITERAL(2, 39, 0), // ""
QT_MOC_LITERAL(3, 40, 12), // "QVector<int>"
QT_MOC_LITERAL(4, 53, 11), // "signalGetID"
QT_MOC_LITERAL(5, 65, 17), // "signalSendMessage"
QT_MOC_LITERAL(6, 83, 14), // "signalSendInfo"
QT_MOC_LITERAL(7, 98, 13), // "slotEncrypted"
QT_MOC_LITERAL(8, 112, 13), // "slotReadyRead"
QT_MOC_LITERAL(9, 126, 8), // "sslError"
QT_MOC_LITERAL(10, 135, 16), // "QList<QSslError>"
QT_MOC_LITERAL(11, 152, 6), // "errors"
QT_MOC_LITERAL(12, 159, 14) // "slotDisconnect"

    },
    "ClientConnection\0signalGetListsClients\0"
    "\0QVector<int>\0signalGetID\0signalSendMessage\0"
    "signalSendInfo\0slotEncrypted\0slotReadyRead\0"
    "sslError\0QList<QSslError>\0errors\0"
    "slotDisconnect"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientConnection[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       4,    1,   57,    2, 0x06 /* Public */,
       5,    0,   60,    2, 0x06 /* Public */,
       6,    0,   61,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   62,    2, 0x0a /* Public */,
       8,    0,   63,    2, 0x0a /* Public */,
       9,    1,   64,    2, 0x0a /* Public */,
      12,    0,   67,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 10,   11,
    QMetaType::Void,

       0        // eod
};

void ClientConnection::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClientConnection *_t = static_cast<ClientConnection *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalGetListsClients((*reinterpret_cast< QVector<int>(*)>(_a[1]))); break;
        case 1: _t->signalGetID((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 2: _t->signalSendMessage(); break;
        case 3: _t->signalSendInfo(); break;
        case 4: _t->slotEncrypted(); break;
        case 5: _t->slotReadyRead(); break;
        case 6: _t->sslError((*reinterpret_cast< QList<QSslError>(*)>(_a[1]))); break;
        case 7: _t->slotDisconnect(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 0:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        case 6:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QList<QSslError> >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ClientConnection::*_t)(QVector<int> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientConnection::signalGetListsClients)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ClientConnection::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientConnection::signalGetID)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ClientConnection::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientConnection::signalSendMessage)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ClientConnection::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientConnection::signalSendInfo)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject ClientConnection::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ClientConnection.data,
      qt_meta_data_ClientConnection,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ClientConnection::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientConnection::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ClientConnection.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ClientConnection::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 8)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 8;
    }
    return _id;
}

// SIGNAL 0
void ClientConnection::signalGetListsClients(QVector<int> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ClientConnection::signalGetID(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ClientConnection::signalSendMessage()
{
    QMetaObject::activate(this, &staticMetaObject, 2, nullptr);
}

// SIGNAL 3
void ClientConnection::signalSendInfo()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
