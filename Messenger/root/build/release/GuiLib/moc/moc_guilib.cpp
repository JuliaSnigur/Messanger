/****************************************************************************
** Meta object code from reading C++ file 'guilib.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.10.0)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../../../../src/GuiLib/guilib.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'guilib.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.10.0. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
QT_WARNING_PUSH
QT_WARNING_DISABLE_DEPRECATED
struct qt_meta_stringdata_GuiLib_t {
    QByteArrayData data[14];
    char stringdata0[121];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_GuiLib_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_GuiLib_t qt_meta_stringdata_GuiLib = {
    {
QT_MOC_LITERAL(0, 0, 6), // "GuiLib"
QT_MOC_LITERAL(1, 7, 11), // "loginChange"
QT_MOC_LITERAL(2, 19, 0), // ""
QT_MOC_LITERAL(3, 20, 14), // "passwordChange"
QT_MOC_LITERAL(4, 35, 10), // "portChange"
QT_MOC_LITERAL(5, 46, 8), // "ipChange"
QT_MOC_LITERAL(6, 55, 8), // "setLogin"
QT_MOC_LITERAL(7, 64, 11), // "setPassword"
QT_MOC_LITERAL(8, 76, 7), // "setPort"
QT_MOC_LITERAL(9, 84, 5), // "setIP"
QT_MOC_LITERAL(10, 90, 7), // "m_login"
QT_MOC_LITERAL(11, 98, 10), // "m_password"
QT_MOC_LITERAL(12, 109, 6), // "m_port"
QT_MOC_LITERAL(13, 116, 4) // "m_ip"

    },
    "GuiLib\0loginChange\0\0passwordChange\0"
    "portChange\0ipChange\0setLogin\0setPassword\0"
    "setPort\0setIP\0m_login\0m_password\0"
    "m_port\0m_ip"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_GuiLib[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       8,   14, // methods
       4,   78, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       4,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   54,    2, 0x06 /* Public */,
       3,    1,   57,    2, 0x06 /* Public */,
       4,    1,   60,    2, 0x06 /* Public */,
       5,    1,   63,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       6,    1,   66,    2, 0x0a /* Public */,
       7,    1,   69,    2, 0x0a /* Public */,
       8,    1,   72,    2, 0x0a /* Public */,
       9,    1,   75,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,

 // properties: name, type, flags
      10, QMetaType::QString, 0x00495003,
      11, QMetaType::QString, 0x00495003,
      12, QMetaType::QString, 0x00495003,
      13, QMetaType::QString, 0x00495003,

 // properties: notify_signal_id
       0,
       1,
       2,
       3,

       0        // eod
};

void GuiLib::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        GuiLib *_t = static_cast<GuiLib *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->loginChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->passwordChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->portChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->ipChange((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 4: _t->setLogin((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 5: _t->setPassword((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 6: _t->setPort((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        case 7: _t->setIP((*reinterpret_cast< const QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        {
            typedef void (GuiLib::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GuiLib::loginChange)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (GuiLib::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GuiLib::passwordChange)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (GuiLib::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GuiLib::portChange)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (GuiLib::*_t)(QString );
            if (*reinterpret_cast<_t *>(_a[1]) == static_cast<_t>(&GuiLib::ipChange)) {
                *result = 3;
                return;
            }
        }
    }
#ifndef QT_NO_PROPERTIES
    else if (_c == QMetaObject::ReadProperty) {
        GuiLib *_t = static_cast<GuiLib *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: *reinterpret_cast< QString*>(_v) = _t->getLogin(); break;
        case 1: *reinterpret_cast< QString*>(_v) = _t->getPassword(); break;
        case 2: *reinterpret_cast< QString*>(_v) = _t->getPort(); break;
        case 3: *reinterpret_cast< QString*>(_v) = _t->getIP(); break;
        default: break;
        }
    } else if (_c == QMetaObject::WriteProperty) {
        GuiLib *_t = static_cast<GuiLib *>(_o);
        Q_UNUSED(_t)
        void *_v = _a[0];
        switch (_id) {
        case 0: _t->setLogin(*reinterpret_cast< QString*>(_v)); break;
        case 1: _t->setPassword(*reinterpret_cast< QString*>(_v)); break;
        case 2: _t->setPort(*reinterpret_cast< QString*>(_v)); break;
        case 3: _t->setIP(*reinterpret_cast< QString*>(_v)); break;
        default: break;
        }
    } else if (_c == QMetaObject::ResetProperty) {
    }
#endif // QT_NO_PROPERTIES
}

const QMetaObject GuiLib::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_GuiLib.data,
      qt_meta_data_GuiLib,  qt_static_metacall, nullptr, nullptr}
};


const QMetaObject *GuiLib::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *GuiLib::qt_metacast(const char *_clname)
{
    if (!_clname) return nullptr;
    if (!strcmp(_clname, qt_meta_stringdata_GuiLib.stringdata0))
        return static_cast<void*>(this);
    return QObject::qt_metacast(_clname);
}

int GuiLib::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
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
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 8;
    }
#ifndef QT_NO_PROPERTIES
   else if (_c == QMetaObject::ReadProperty || _c == QMetaObject::WriteProperty
            || _c == QMetaObject::ResetProperty || _c == QMetaObject::RegisterPropertyMetaType) {
        qt_static_metacall(this, _c, _id, _a);
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyDesignable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyScriptable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyStored) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyEditable) {
        _id -= 4;
    } else if (_c == QMetaObject::QueryPropertyUser) {
        _id -= 4;
    }
#endif // QT_NO_PROPERTIES
    return _id;
}

// SIGNAL 0
void GuiLib::loginChange(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void GuiLib::passwordChange(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void GuiLib::portChange(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void GuiLib::ipChange(QString _t1)
{
    void *_a[] = { nullptr, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_WARNING_POP
QT_END_MOC_NAMESPACE
