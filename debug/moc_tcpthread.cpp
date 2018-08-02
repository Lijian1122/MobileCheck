/****************************************************************************
** Meta object code from reading C++ file 'tcpthread.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../tcpthread.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'tcpthread.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_TcpThread_t {
    QByteArrayData data[16];
    char stringdata0[180];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_TcpThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_TcpThread_t qt_meta_stringdata_TcpThread = {
    {
QT_MOC_LITERAL(0, 0, 9), // "TcpThread"
QT_MOC_LITERAL(1, 10, 5), // "error"
QT_MOC_LITERAL(2, 16, 0), // ""
QT_MOC_LITERAL(3, 17, 23), // "QTcpSocket::SocketError"
QT_MOC_LITERAL(4, 41, 11), // "socketError"
QT_MOC_LITERAL(5, 53, 13), // "sendIfConnect"
QT_MOC_LITERAL(6, 67, 11), // "useroperate"
QT_MOC_LITERAL(7, 79, 10), // "operatecmd"
QT_MOC_LITERAL(8, 90, 8), // "datasize"
QT_MOC_LITERAL(9, 99, 10), // "datadetail"
QT_MOC_LITERAL(10, 110, 12), // "bytesArrived"
QT_MOC_LITERAL(11, 123, 10), // "singalJson"
QT_MOC_LITERAL(12, 134, 11), // "receiveFile"
QT_MOC_LITERAL(13, 146, 12), // "slotsendInfo"
QT_MOC_LITERAL(14, 159, 8), // "timedone"
QT_MOC_LITERAL(15, 168, 11) // "readyToRead"

    },
    "TcpThread\0error\0\0QTcpSocket::SocketError\0"
    "socketError\0sendIfConnect\0useroperate\0"
    "operatecmd\0datasize\0datadetail\0"
    "bytesArrived\0singalJson\0receiveFile\0"
    "slotsendInfo\0timedone\0readyToRead"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_TcpThread[] = {

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
       5,    4,   57,    2, 0x06 /* Public */,
      10,    3,   66,    2, 0x06 /* Public */,
      11,    1,   73,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      12,    0,   76,    2, 0x0a /* Public */,
      13,    4,   77,    2, 0x0a /* Public */,
      14,    0,   86,    2, 0x0a /* Public */,
      15,    0,   87,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, 0x80000000 | 3,    4,
    QMetaType::Void, QMetaType::Int, QMetaType::UShort, QMetaType::Int, QMetaType::QString,    6,    7,    8,    9,
    QMetaType::Void, QMetaType::LongLong, QMetaType::Int, QMetaType::Int,    2,    2,    2,
    QMetaType::Void, QMetaType::QByteArray,    2,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int, QMetaType::UShort, QMetaType::Int, QMetaType::QString,    2,    2,    2,    2,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void TcpThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        TcpThread *_t = static_cast<TcpThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->error((*reinterpret_cast< QTcpSocket::SocketError(*)>(_a[1]))); break;
        case 1: _t->sendIfConnect((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 2: _t->bytesArrived((*reinterpret_cast< qint64(*)>(_a[1])),(*reinterpret_cast< qint32(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3]))); break;
        case 3: _t->singalJson((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        case 4: _t->receiveFile(); break;
        case 5: _t->slotsendInfo((*reinterpret_cast< int(*)>(_a[1])),(*reinterpret_cast< quint16(*)>(_a[2])),(*reinterpret_cast< int(*)>(_a[3])),(*reinterpret_cast< QString(*)>(_a[4]))); break;
        case 6: _t->timedone(); break;
        case 7: _t->readyToRead(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (TcpThread::*_t)(QTcpSocket::SocketError );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpThread::error)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (TcpThread::*_t)(int , quint16 , int , QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpThread::sendIfConnect)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (TcpThread::*_t)(qint64 , qint32 , int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpThread::bytesArrived)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (TcpThread::*_t)(QByteArray );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&TcpThread::singalJson)) {
                *result = 3;
                return;
            }
        }
    }
}

const QMetaObject TcpThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_TcpThread.data,
      qt_meta_data_TcpThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *TcpThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *TcpThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_TcpThread.stringdata0))
        return static_cast<void*>(const_cast< TcpThread*>(this));
    return QThread::qt_metacast(_clname);
}

int TcpThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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

// SIGNAL 0
void TcpThread::error(QTcpSocket::SocketError _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void TcpThread::sendIfConnect(int _t1, quint16 _t2, int _t3, QString _t4)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)), const_cast<void*>(reinterpret_cast<const void*>(&_t4)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void TcpThread::bytesArrived(qint64 _t1, qint32 _t2, int _t3)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)), const_cast<void*>(reinterpret_cast<const void*>(&_t2)), const_cast<void*>(reinterpret_cast<const void*>(&_t3)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void TcpThread::singalJson(QByteArray _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}
QT_END_MOC_NAMESPACE
