/****************************************************************************
** Meta object code from reading C++ file 'parsejson.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../parseJson/parsejson.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'parsejson.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_ParseJson_t {
    QByteArrayData data[16];
    char stringdata0[219];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_ParseJson_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_ParseJson_t qt_meta_stringdata_ParseJson = {
    {
QT_MOC_LITERAL(0, 0, 9), // "ParseJson"
QT_MOC_LITERAL(1, 10, 12), // "signalmobile"
QT_MOC_LITERAL(2, 23, 0), // ""
QT_MOC_LITERAL(3, 24, 13), // "signalpicture"
QT_MOC_LITERAL(4, 38, 14), // "ProgressbarApp"
QT_MOC_LITERAL(5, 53, 13), // "signalAppList"
QT_MOC_LITERAL(6, 67, 16), // "singalSafeResult"
QT_MOC_LITERAL(7, 84, 4), // "json"
QT_MOC_LITERAL(8, 89, 17), // "singalContactInfo"
QT_MOC_LITERAL(9, 107, 21), // "signalCallhistoryInfo"
QT_MOC_LITERAL(10, 129, 17), // "signalMessageInfo"
QT_MOC_LITERAL(11, 147, 19), // "signalMessageExport"
QT_MOC_LITERAL(12, 167, 14), // "signalFileInfo"
QT_MOC_LITERAL(13, 182, 18), // "singalcheckMessage"
QT_MOC_LITERAL(14, 201, 13), // "parseJsonSlot"
QT_MOC_LITERAL(15, 215, 3) // "msg"

    },
    "ParseJson\0signalmobile\0\0signalpicture\0"
    "ProgressbarApp\0signalAppList\0"
    "singalSafeResult\0json\0singalContactInfo\0"
    "signalCallhistoryInfo\0signalMessageInfo\0"
    "signalMessageExport\0signalFileInfo\0"
    "singalcheckMessage\0parseJsonSlot\0msg"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_ParseJson[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      12,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
      11,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   74,    2, 0x06 /* Public */,
       3,    1,   77,    2, 0x06 /* Public */,
       4,    1,   80,    2, 0x06 /* Public */,
       5,    1,   83,    2, 0x06 /* Public */,
       6,    1,   86,    2, 0x06 /* Public */,
       8,    1,   89,    2, 0x06 /* Public */,
       9,    1,   92,    2, 0x06 /* Public */,
      10,    1,   95,    2, 0x06 /* Public */,
      11,    1,   98,    2, 0x06 /* Public */,
      12,    1,  101,    2, 0x06 /* Public */,
      13,    1,  104,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
      14,    1,  107,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void, QMetaType::QStringList,    2,
    QMetaType::Void, QMetaType::QJsonObject,    7,
    QMetaType::Void, QMetaType::QJsonObject,    7,
    QMetaType::Void, QMetaType::QJsonObject,    7,
    QMetaType::Void, QMetaType::QJsonObject,    7,
    QMetaType::Void, QMetaType::QJsonObject,    7,
    QMetaType::Void, QMetaType::QJsonObject,    7,
    QMetaType::Void, QMetaType::QJsonObject,    7,

 // slots: parameters
    QMetaType::Void, QMetaType::QByteArray,   15,

       0        // eod
};

void ParseJson::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        ParseJson *_t = static_cast<ParseJson *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalmobile((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->signalpicture((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 2: _t->ProgressbarApp((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 3: _t->signalAppList((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 4: _t->singalSafeResult((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 5: _t->singalContactInfo((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 6: _t->signalCallhistoryInfo((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 7: _t->signalMessageInfo((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 8: _t->signalMessageExport((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 9: _t->signalFileInfo((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 10: _t->singalcheckMessage((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 11: _t->parseJsonSlot((*reinterpret_cast< QByteArray(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (ParseJson::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParseJson::signalmobile)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (ParseJson::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParseJson::signalpicture)) {
                *result = 1;
                return;
            }
        }
        {
            typedef void (ParseJson::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParseJson::ProgressbarApp)) {
                *result = 2;
                return;
            }
        }
        {
            typedef void (ParseJson::*_t)(QStringList );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParseJson::signalAppList)) {
                *result = 3;
                return;
            }
        }
        {
            typedef void (ParseJson::*_t)(QJsonObject );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParseJson::singalSafeResult)) {
                *result = 4;
                return;
            }
        }
        {
            typedef void (ParseJson::*_t)(QJsonObject );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParseJson::singalContactInfo)) {
                *result = 5;
                return;
            }
        }
        {
            typedef void (ParseJson::*_t)(QJsonObject );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParseJson::signalCallhistoryInfo)) {
                *result = 6;
                return;
            }
        }
        {
            typedef void (ParseJson::*_t)(QJsonObject );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParseJson::signalMessageInfo)) {
                *result = 7;
                return;
            }
        }
        {
            typedef void (ParseJson::*_t)(QJsonObject );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParseJson::signalMessageExport)) {
                *result = 8;
                return;
            }
        }
        {
            typedef void (ParseJson::*_t)(QJsonObject );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParseJson::signalFileInfo)) {
                *result = 9;
                return;
            }
        }
        {
            typedef void (ParseJson::*_t)(QJsonObject );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&ParseJson::singalcheckMessage)) {
                *result = 10;
                return;
            }
        }
    }
}

const QMetaObject ParseJson::staticMetaObject = {
    { &QObject::staticMetaObject, qt_meta_stringdata_ParseJson.data,
      qt_meta_data_ParseJson,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *ParseJson::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *ParseJson::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_ParseJson.stringdata0))
        return static_cast<void*>(const_cast< ParseJson*>(this));
    return QObject::qt_metacast(_clname);
}

int ParseJson::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QObject::qt_metacall(_c, _id, _a);
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
void ParseJson::signalmobile(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void ParseJson::signalpicture(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 1, _a);
}

// SIGNAL 2
void ParseJson::ProgressbarApp(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 2, _a);
}

// SIGNAL 3
void ParseJson::signalAppList(QStringList _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 3, _a);
}

// SIGNAL 4
void ParseJson::singalSafeResult(QJsonObject _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 4, _a);
}

// SIGNAL 5
void ParseJson::singalContactInfo(QJsonObject _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 5, _a);
}

// SIGNAL 6
void ParseJson::signalCallhistoryInfo(QJsonObject _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 6, _a);
}

// SIGNAL 7
void ParseJson::signalMessageInfo(QJsonObject _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 7, _a);
}

// SIGNAL 8
void ParseJson::signalMessageExport(QJsonObject _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 8, _a);
}

// SIGNAL 9
void ParseJson::signalFileInfo(QJsonObject _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 9, _a);
}

// SIGNAL 10
void ParseJson::singalcheckMessage(QJsonObject _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 10, _a);
}
QT_END_MOC_NAMESPACE
