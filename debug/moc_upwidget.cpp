/****************************************************************************
** Meta object code from reading C++ file 'upwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../upwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'upwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_upwidget_t {
    QByteArrayData data[13];
    char stringdata0[167];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_upwidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_upwidget_t qt_meta_stringdata_upwidget = {
    {
QT_MOC_LITERAL(0, 0, 8), // "upwidget"
QT_MOC_LITERAL(1, 9, 16), // "menubuttonaction"
QT_MOC_LITERAL(2, 26, 0), // ""
QT_MOC_LITERAL(3, 27, 12), // "slotIconHome"
QT_MOC_LITERAL(4, 40, 18), // "slotShowMaxRestore"
QT_MOC_LITERAL(5, 59, 4), // "size"
QT_MOC_LITERAL(6, 64, 14), // "slotUserManage"
QT_MOC_LITERAL(7, 79, 13), // "slotWhiteList"
QT_MOC_LITERAL(8, 93, 14), // "slotPassModify"
QT_MOC_LITERAL(9, 108, 14), // "slotModifyPass"
QT_MOC_LITERAL(10, 123, 15), // "slotAdduserinfo"
QT_MOC_LITERAL(11, 139, 13), // "slotAddUserOK"
QT_MOC_LITERAL(12, 153, 13) // "slotAboutInfo"

    },
    "upwidget\0menubuttonaction\0\0slotIconHome\0"
    "slotShowMaxRestore\0size\0slotUserManage\0"
    "slotWhiteList\0slotPassModify\0"
    "slotModifyPass\0slotAdduserinfo\0"
    "slotAddUserOK\0slotAboutInfo"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_upwidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      10,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       0,       // signalCount

 // slots: name, argc, parameters, tag, flags
       1,    0,   64,    2, 0x0a /* Public */,
       3,    0,   65,    2, 0x0a /* Public */,
       4,    1,   66,    2, 0x0a /* Public */,
       6,    0,   69,    2, 0x0a /* Public */,
       7,    0,   70,    2, 0x0a /* Public */,
       8,    0,   71,    2, 0x0a /* Public */,
       9,    0,   72,    2, 0x0a /* Public */,
      10,    0,   73,    2, 0x0a /* Public */,
      11,    0,   74,    2, 0x0a /* Public */,
      12,    0,   75,    2, 0x0a /* Public */,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QSize,    5,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,

       0        // eod
};

void upwidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        upwidget *_t = static_cast<upwidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->menubuttonaction(); break;
        case 1: _t->slotIconHome(); break;
        case 2: _t->slotShowMaxRestore((*reinterpret_cast< QSize(*)>(_a[1]))); break;
        case 3: _t->slotUserManage(); break;
        case 4: _t->slotWhiteList(); break;
        case 5: _t->slotPassModify(); break;
        case 6: _t->slotModifyPass(); break;
        case 7: _t->slotAdduserinfo(); break;
        case 8: _t->slotAddUserOK(); break;
        case 9: _t->slotAboutInfo(); break;
        default: ;
        }
    }
}

const QMetaObject upwidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_upwidget.data,
      qt_meta_data_upwidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *upwidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *upwidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_upwidget.stringdata0))
        return static_cast<void*>(const_cast< upwidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int upwidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 10)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 10;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 10)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 10;
    }
    return _id;
}
QT_END_MOC_NAMESPACE
