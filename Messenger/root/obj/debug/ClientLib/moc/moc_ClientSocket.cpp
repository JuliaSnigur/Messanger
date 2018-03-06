/****************************************************************************
** Meta object code from reading C++ file 'ClientSocket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/ClientLib/ClientSocket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#include <QtCore/QVector>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'ClientSocket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_ClientNamespace__ClientSocket_t {
    QByteArrayData data[11];
    char stringdata0[194];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ClientNamespace__ClientSocket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ClientNamespace__ClientSocket_t qt_meta_stringdata_ClientNamespace__ClientSocket = {
    {
QT_MOC_LITERAL(0, 0, 29), // "ClientNamespace::ClientSocket"
QT_MOC_LITERAL(1, 30, 30), // "signalInsertUserIntoTabSession"
QT_MOC_LITERAL(2, 61, 0), // ""
QT_MOC_LITERAL(3, 62, 21), // "signalGetListsClients"
QT_MOC_LITERAL(4, 84, 12), // "QVector<int>"
QT_MOC_LITERAL(5, 97, 11), // "signalGetID"
QT_MOC_LITERAL(6, 109, 17), // "signalSendMessage"
QT_MOC_LITERAL(7, 127, 13), // "slotReadyRead"
QT_MOC_LITERAL(8, 141, 9), // "slotError"
QT_MOC_LITERAL(9, 151, 28), // "QAbstractSocket::SocketError"
QT_MOC_LITERAL(10, 180, 13) // "slotConnected"

    },
    "ClientNamespace::ClientSocket\0"
    "signalInsertUserIntoTabSession\0\0"
    "signalGetListsClients\0QVector<int>\0"
    "signalGetID\0signalSendMessage\0"
    "slotReadyRead\0slotError\0"
    "QAbstractSocket::SocketError\0slotConnected"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ClientNamespace__ClientSocket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       7,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    0,   49,    2, 0x06 /* Public */,
       3,    1,   50,    2, 0x06 /* Public */,
       5,    1,   53,    2, 0x06 /* Public */,
       6,    0,   56,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   57,    2, 0x08 /* Private */,
       8,    1,   58,    2, 0x08 /* Private */,
      10,    0,   61,    2, 0x08 /* Private */,

 // signals: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 4,    2,
    QMetaType::Void, QMetaType::Int,    2,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, 0x80000000 | 9,    2,
    QMetaType::Void,

       0        // eod
};

void ClientNamespace::ClientSocket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ClientSocket *_t = static_cast<ClientSocket *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalInsertUserIntoTabSession(); break;
        case 1: _t->signalGetListsClients((*reinterpret_cast< QVector<int>(*)>(_a[1]))); break;
        case 2: _t->signalGetID((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 3: _t->signalSendMessage(); break;
        case 4: _t->slotReadyRead(); break;
        case 5: _t->slotError((*reinterpret_cast< QAbstractSocket::SocketError(*)>(_a[1]))); break;
        case 6: _t->slotConnected(); break;
        default: ;
        }
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        switch (_id) {
        default: *reinterpret_cast<int*>(_a[0]) = -1; break;
        case 1:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QVector<int> >(); break;
            }
            break;
        case 5:
            switch (*reinterpret_cast<int*>(_a[1])) {
            default: *reinterpret_cast<int*>(_a[0]) = -1; break;
            case 0:
                *reinterpret_cast<int*>(_a[0]) = qRegisterMetaType< QAbstractSocket::SocketError >(); break;
            }
            break;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (ClientSocket::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientSocket::signalInsertUserIntoTabSession)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ClientSocket::*_t)(QVector<int> );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientSocket::signalGetListsClients)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ClientSocket::*_t)(int );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientSocket::signalGetID)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ClientSocket::*_t)();
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&ClientSocket::signalSendMessage)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject ClientNamespace::ClientSocket::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ClientNamespace__ClientSocket.data,
      qt_meta_data_ClientNamespace__ClientSocket,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *ClientNamespace::ClientSocket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ClientNamespace::ClientSocket::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_ClientNamespace__ClientSocket.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int ClientNamespace::ClientSocket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 7)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 7;
    }
    return _id;
}

// SIGNAL 0
void ClientNamespace::ClientSocket::signalInsertUserIntoTabSession()
{
    QMetaObject::activate(this, &staticMetaObject, 0, nullptr);
}

// SIGNAL 1
void ClientNamespace::ClientSocket::signalGetListsClients(QVector<int> _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ClientNamespace::ClientSocket::signalGetID(int _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ClientNamespace::ClientSocket::signalSendMessage()
{
    QMetaObject::activate(this, &staticMetaObject, 3, nullptr);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
