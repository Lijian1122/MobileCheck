/****************************************************************************
** Meta object code from reading C++ file 'maskmainwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../maskmainwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'maskmainwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_maskmainwidget_t {
    QByteArrayData data[4];
    char stringdata0[35];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_maskmainwidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_maskmainwidget_t qt_meta_stringdata_maskmainwidget = {
    {
QT_MOC_LITERAL(0, 0, 14), // "maskmainwidget"
QT_MOC_LITERAL(1, 15, 10), // "signalsize"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 7) // "slotmax"

    },
    "maskmainwidget\0signalsize\0\0slotmax"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_maskmainwidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
       2,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   24,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QSize,    2,

 // slots: parameters
    QMetaType::Void, QMetaType::QSize,    2,

       0        // eod
};

void maskmainwidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        maskmainwidget *_t = static_cast<maskmainwidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalsize((*reinterpret_cast< QSize(*)>(_a[1]))); break;
        case 1: _t->slotmax((*reinterpret_cast< QSize(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (maskmainwidget::*_t)(QSize );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&maskmainwidget::signalsize)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject maskmainwidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_maskmainwidget.data,
      qt_meta_data_maskmainwidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *maskmainwidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *maskmainwidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_maskmainwidget.stringdata0))
        return static_cast<void*>(const_cast< maskmainwidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int maskmainwidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 2)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 2;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 2)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 2;
    }
    return _id;
}

// SIGNAL 0
void maskmainwidget::signalsize(QSize _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
