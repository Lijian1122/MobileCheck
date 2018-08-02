/****************************************************************************
** Meta object code from reading C++ file 'socket.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../socket.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'socket.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_Socket_t {
    QByteArrayData data[13];
    char stringdata0[124];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_Socket_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_Socket_t qt_meta_stringdata_Socket = {
    {
QT_MOC_LITERAL(0, 0, 6), // "Socket"
QT_MOC_LITERAL(1, 7, 10), // "signaltype"
QT_MOC_LITERAL(2, 18, 0), // ""
QT_MOC_LITERAL(3, 19, 6), // "mobile"
QT_MOC_LITERAL(4, 26, 8), // "m_mobile"
QT_MOC_LITERAL(5, 35, 10), // "singalJson"
QT_MOC_LITERAL(6, 46, 9), // "m_message"
QT_MOC_LITERAL(7, 56, 11), // "readyToRead"
QT_MOC_LITERAL(8, 68, 12), // "readIfConnct"
QT_MOC_LITERAL(9, 81, 11), // "useroperate"
QT_MOC_LITERAL(10, 93, 10), // "operatecmd"
QT_MOC_LITERAL(11, 104, 8), // "datasize"
QT_MOC_LITERAL(12, 113, 10) // "datadetail"

    },
    "Socket\0signaltype\0\0mobile\0m_mobile\0"
    "singalJson\0m_message\0readyToRead\0"
    "readIfConnct\0useroperate\0operatecmd\0"
    "datasize\0datadetail"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_Socket[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       4,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   34,    2, 0x06 /* Public */,
       5,    1,   37,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       7,    0,   40,    2, 0x0a /* Public */,
       8,    4,   41,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::QByteArray,    6,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::UShort, QMetaType::UShort, QMetaType::Int, QMetaType::QString,    9,   10,   11,   12,

       0        // eod
};

void Socket::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        Socket *_t = static_cast<Socket *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signaltype((*reinterpret_cast< mobile(*)>(_a[1]))); break;
        case 1: _t->singalJson((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 2: _t->readyToRead(); break;
        case 3: _t->readIfConnct((*reinterpret_cast< quint16(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (Socket::*_t)(mobile );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Socket::signaltype)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (Socket::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&Socket::singalJson)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject Socket::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_Socket.data,
      qt_meta_data_Socket,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *Socket::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *Socket::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_Socket.stringdata0))
        return static_cast<void*>(const_cast< Socket*>(this));
    return QObject::qt_metacast(_clname);
}

int Socket::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void Socket::signaltype(mobile _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void Socket::singalJson(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}
QT_END_MOC_NAMESPACE
