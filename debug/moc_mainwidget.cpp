/****************************************************************************
** Meta object code from reading C++ file 'mainwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../mainwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'mainwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_mainwidget_t {
    QByteArrayData data[18];
    char stringdata0[249];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_mainwidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_mainwidget_t qt_meta_stringdata_mainwidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "mainwidget"
QT_MOC_LITERAL(1, 11, 9), // "signalMax"
QT_MOC_LITERAL(2, 21, 0), // ""
QT_MOC_LITERAL(3, 22, 18), // "slot_iconIsActived"
QT_MOC_LITERAL(4, 41, 33), // "QSystemTrayIcon::ActivationRe..."
QT_MOC_LITERAL(5, 75, 6), // "reason"
QT_MOC_LITERAL(6, 82, 11), // "opentgpmenu"
QT_MOC_LITERAL(7, 94, 18), // "slotShowMaxRestore"
QT_MOC_LITERAL(8, 113, 10), // "menuAction"
QT_MOC_LITERAL(9, 124, 17), // "slot_setcurstack0"
QT_MOC_LITERAL(10, 142, 17), // "slot_setcurstack1"
QT_MOC_LITERAL(11, 160, 17), // "slot_setcurstack2"
QT_MOC_LITERAL(12, 178, 17), // "slot_setcurstack3"
QT_MOC_LITERAL(13, 196, 17), // "slot_setcurstack4"
QT_MOC_LITERAL(14, 214, 7), // "slotbai"
QT_MOC_LITERAL(15, 222, 8), // "Homepage"
QT_MOC_LITERAL(16, 231, 7), // "slotMin"
QT_MOC_LITERAL(17, 239, 9) // "slotClose"

    },
    "mainwidget\0signalMax\0\0slot_iconIsActived\0"
    "QSystemTrayIcon::ActivationReason\0"
    "reason\0opentgpmenu\0slotShowMaxRestore\0"
    "menuAction\0slot_setcurstack0\0"
    "slot_setcurstack1\0slot_setcurstack2\0"
    "slot_setcurstack3\0slot_setcurstack4\0"
    "slotbai\0Homepage\0slotMin\0slotClose"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_mainwidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      14,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       1,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,   84,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       3,    1,   87,    2, 0x0a /* Public */,
       6,    0,   90,    2, 0x0a /* Public */,
       7,    0,   91,    2, 0x0a /* Public */,
       8,    0,   92,    2, 0x0a /* Public */,
       9,    0,   93,    2, 0x0a /* Public */,
      10,    0,   94,    2, 0x0a /* Public */,
      11,    0,   95,    2, 0x0a /* Public */,
      12,    0,   96,    2, 0x0a /* Public */,
      13,    0,   97,    2, 0x0a /* Public */,
      14,    0,   98,    2, 0x0a /* Public */,
      15,    0,   99,    2, 0x0a /* Public */,
      16,    0,  100,    2, 0x0a /* Public */,
      17,    0,  101,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QSize,    2,

 // slots: parameters
    QMetaType::Void, 0x80000000 | 4,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void mainwidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        mainwidget *_t = static_cast<mainwidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->signalMax((*reinterpret_cast< QSize(*)>(_a[1]))); break;
        case 1: _t->slot_iconIsActived((*reinterpret_cast< QSystemTrayIcon::ActivationReason(*)>(_a[1]))); break;
        case 2: _t->opentgpmenu(); break;
        case 3: _t->slotShowMaxRestore(); break;
        case 4: _t->menuAction(); break;
        case 5: _t->slot_setcurstack0(); break;
        case 6: _t->slot_setcurstack1(); break;
        case 7: _t->slot_setcurstack2(); break;
        case 8: _t->slot_setcurstack3(); break;
        case 9: _t->slot_setcurstack4(); break;
        case 10: _t->slotbai(); break;
        case 11: _t->Homepage(); break;
        case 12: _t->slotMin(); break;
        case 13: _t->slotClose(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (mainwidget::*_t)(QSize );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&mainwidget::signalMax)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject mainwidget::staticMetaObject = {
    { &QDialog::staticMetaObject, qt_meta_stringdata_mainwidget.data,
      qt_meta_data_mainwidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *mainwidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *mainwidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_mainwidget.stringdata0))
        return static_cast<void*>(const_cast< mainwidget*>(this));
    return QDialog::qt_metacast(_clname);
}

int mainwidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QDialog::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 14)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 14;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 14)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 14;
    }
    return _id;
}

// SIGNAL 0
void mainwidget::signalMax(QSize _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
QT_END_MOC_NAMESPACE
