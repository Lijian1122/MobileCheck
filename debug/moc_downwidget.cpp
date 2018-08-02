/****************************************************************************
** Meta object code from reading C++ file 'downwidget.h'
**
** Created by: The Qt Meta Object Compiler version 67 (Qt 5.6.3)
**
** WARNING! All changes made in this file will be lost!
*****************************************************************************/

#include "../downwidget.h"
#include <QtCore/qbytearray.h>
#include <QtCore/qmetatype.h>
#if !defined(Q_MOC_OUTPUT_REVISION)
#error "The header file 'downwidget.h' doesn't include <QObject>."
#elif Q_MOC_OUTPUT_REVISION != 67
#error "This file was generated using the moc from 5.6.3. It"
#error "cannot be used with the include files from this version of Qt."
#error "(The moc has changed too much.)"
#endif

QT_BEGIN_MOC_NAMESPACE
struct qt_meta_stringdata_HomeThread_t {
    QByteArrayData data[5];
    char stringdata0[39];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_HomeThread_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_HomeThread_t qt_meta_stringdata_HomeThread = {
    {
QT_MOC_LITERAL(0, 0, 10), // "HomeThread"
QT_MOC_LITERAL(1, 11, 12), // "UpdateSignal"
QT_MOC_LITERAL(2, 24, 0), // ""
QT_MOC_LITERAL(3, 25, 3), // "num"
QT_MOC_LITERAL(4, 29, 9) // "ResetSlot"

    },
    "HomeThread\0UpdateSignal\0\0num\0ResetSlot"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_HomeThread[] = {

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
       4,    0,   27,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::Int,    3,

 // slots: parameters
    QMetaType::Void,

       0        // eod
};

void HomeThread::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        HomeThread *_t = static_cast<HomeThread *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->UpdateSignal((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 1: _t->ResetSlot(); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (HomeThread::*_t)(int );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&HomeThread::UpdateSignal)) {
                *result = 0;
                return;
            }
        }
    }
}

const QMetaObject HomeThread::staticMetaObject = {
    { &QThread::staticMetaObject, qt_meta_stringdata_HomeThread.data,
      qt_meta_data_HomeThread,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *HomeThread::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *HomeThread::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_HomeThread.stringdata0))
        return static_cast<void*>(const_cast< HomeThread*>(this));
    return QThread::qt_metacast(_clname);
}

int HomeThread::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QThread::qt_metacall(_c, _id, _a);
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
void HomeThread::UpdateSignal(int _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}
struct qt_meta_stringdata_downwidget_t {
    QByteArrayData data[75];
    char stringdata0[1177];
};
#define QT_MOC_LITERAL(idx, ofs, len) \
    Q_STATIC_BYTE_ARRAY_DATA_HEADER_INITIALIZER_WITH_OFFSET(len, \
    qptrdiff(offsetof(qt_meta_stringdata_downwidget_t, stringdata0) + ofs \
        - idx * sizeof(QByteArrayData)) \
    )
static const qt_meta_stringdata_downwidget_t qt_meta_stringdata_downwidget = {
    {
QT_MOC_LITERAL(0, 0, 10), // "downwidget"
QT_MOC_LITERAL(1, 11, 18), // "SiganlUpdateQrcode"
QT_MOC_LITERAL(2, 30, 0), // ""
QT_MOC_LITERAL(3, 31, 3), // "num"
QT_MOC_LITERAL(4, 35, 18), // "runsafecheckSignal"
QT_MOC_LITERAL(5, 54, 17), // "slotHomePageshow2"
QT_MOC_LITERAL(6, 72, 12), // "slotHomePage"
QT_MOC_LITERAL(7, 85, 14), // "ScreenShotShow"
QT_MOC_LITERAL(8, 100, 15), // "slotMobileState"
QT_MOC_LITERAL(9, 116, 3), // "str"
QT_MOC_LITERAL(10, 120, 14), // "slotQrcodeSave"
QT_MOC_LITERAL(11, 135, 11), // "slotAppIcon"
QT_MOC_LITERAL(12, 147, 8), // "icondata"
QT_MOC_LITERAL(13, 156, 14), // "slotmobileinfo"
QT_MOC_LITERAL(14, 171, 13), // "slotSafecheck"
QT_MOC_LITERAL(15, 185, 19), // "slotsafecheckSignal"
QT_MOC_LITERAL(16, 205, 14), // "safeResultshow"
QT_MOC_LITERAL(17, 220, 15), // "parseSafeResult"
QT_MOC_LITERAL(18, 236, 6), // "object"
QT_MOC_LITERAL(19, 243, 14), // "slotSafeResult"
QT_MOC_LITERAL(20, 258, 14), // "slotslidevalue"
QT_MOC_LITERAL(21, 273, 20), // "slotRequestCheckInfo"
QT_MOC_LITERAL(22, 294, 11), // "packagelist"
QT_MOC_LITERAL(23, 306, 8), // "getScore"
QT_MOC_LITERAL(24, 315, 6), // "number"
QT_MOC_LITERAL(25, 322, 14), // "IfCheckPackage"
QT_MOC_LITERAL(26, 337, 16), // "slotExportReport"
QT_MOC_LITERAL(27, 354, 14), // "safeResultJson"
QT_MOC_LITERAL(28, 369, 15), // "slotCheckDetail"
QT_MOC_LITERAL(29, 385, 16), // "slotSetWhiteList"
QT_MOC_LITERAL(30, 402, 13), // "slotUninstall"
QT_MOC_LITERAL(31, 416, 13), // "slotExportApp"
QT_MOC_LITERAL(32, 430, 10), // "slotReport"
QT_MOC_LITERAL(33, 441, 12), // "setWhiteList"
QT_MOC_LITERAL(34, 454, 18), // "slotProgressUpdate"
QT_MOC_LITERAL(35, 473, 18), // "slotContactsbutton"
QT_MOC_LITERAL(36, 492, 21), // "slotCallhistorybutton"
QT_MOC_LITERAL(37, 514, 18), // "slotMessagesbutton"
QT_MOC_LITERAL(38, 533, 14), // "slotFilebutton"
QT_MOC_LITERAL(39, 548, 17), // "slotContactsclick"
QT_MOC_LITERAL(40, 566, 20), // "slotCallhistoryclick"
QT_MOC_LITERAL(41, 587, 17), // "slotMessagesclick"
QT_MOC_LITERAL(42, 605, 13), // "slotFileclick"
QT_MOC_LITERAL(43, 619, 16), // "slotContactJoson"
QT_MOC_LITERAL(44, 636, 16), // "parseContactInfo"
QT_MOC_LITERAL(45, 653, 17), // "slotContactExport"
QT_MOC_LITERAL(46, 671, 15), // "slotContaReport"
QT_MOC_LITERAL(47, 687, 19), // "slotCallhistoryJson"
QT_MOC_LITERAL(48, 707, 21), // "slotCallhistoryExport"
QT_MOC_LITERAL(49, 729, 21), // "slotCallhistoryReport"
QT_MOC_LITERAL(50, 751, 15), // "slotMessageJson"
QT_MOC_LITERAL(51, 767, 16), // "slotMessagexport"
QT_MOC_LITERAL(52, 784, 19), // "slotMessageNextPage"
QT_MOC_LITERAL(53, 804, 13), // "slotFrontPage"
QT_MOC_LITERAL(54, 818, 20), // "slotMessageFirstPage"
QT_MOC_LITERAL(55, 839, 18), // "slotMessageLatPage"
QT_MOC_LITERAL(56, 858, 20), // "slotMessageCurrentOk"
QT_MOC_LITERAL(57, 879, 18), // "insertMessagetable"
QT_MOC_LITERAL(58, 898, 3), // "row"
QT_MOC_LITERAL(59, 902, 17), // "slotMessageExport"
QT_MOC_LITERAL(60, 920, 17), // "slotMessageReport"
QT_MOC_LITERAL(61, 938, 17), // "slotMessageDetail"
QT_MOC_LITERAL(62, 956, 12), // "slotFileJson"
QT_MOC_LITERAL(63, 969, 14), // "slotFileExport"
QT_MOC_LITERAL(64, 984, 14), // "slotFileReport"
QT_MOC_LITERAL(65, 999, 18), // "slotCountCheckInfo"
QT_MOC_LITERAL(66, 1018, 15), // "slotPrintQrcode"
QT_MOC_LITERAL(67, 1034, 17), // "slotOpenCheckInfo"
QT_MOC_LITERAL(68, 1052, 15), // "slotSummaryInfo"
QT_MOC_LITERAL(69, 1068, 19), // "slotQCountCheckInfo"
QT_MOC_LITERAL(70, 1088, 16), // "slotQPrintQrcode"
QT_MOC_LITERAL(71, 1105, 18), // "slotQOpenCheckInfo"
QT_MOC_LITERAL(72, 1124, 16), // "slotQSummaryInfo"
QT_MOC_LITERAL(73, 1141, 18), // "slotSelectByQcrode"
QT_MOC_LITERAL(74, 1160, 16) // "slotUpdateQrcode"

    },
    "downwidget\0SiganlUpdateQrcode\0\0num\0"
    "runsafecheckSignal\0slotHomePageshow2\0"
    "slotHomePage\0ScreenShotShow\0slotMobileState\0"
    "str\0slotQrcodeSave\0slotAppIcon\0icondata\0"
    "slotmobileinfo\0slotSafecheck\0"
    "slotsafecheckSignal\0safeResultshow\0"
    "parseSafeResult\0object\0slotSafeResult\0"
    "slotslidevalue\0slotRequestCheckInfo\0"
    "packagelist\0getScore\0number\0IfCheckPackage\0"
    "slotExportReport\0safeResultJson\0"
    "slotCheckDetail\0slotSetWhiteList\0"
    "slotUninstall\0slotExportApp\0slotReport\0"
    "setWhiteList\0slotProgressUpdate\0"
    "slotContactsbutton\0slotCallhistorybutton\0"
    "slotMessagesbutton\0slotFilebutton\0"
    "slotContactsclick\0slotCallhistoryclick\0"
    "slotMessagesclick\0slotFileclick\0"
    "slotContactJoson\0parseContactInfo\0"
    "slotContactExport\0slotContaReport\0"
    "slotCallhistoryJson\0slotCallhistoryExport\0"
    "slotCallhistoryReport\0slotMessageJson\0"
    "slotMessagexport\0slotMessageNextPage\0"
    "slotFrontPage\0slotMessageFirstPage\0"
    "slotMessageLatPage\0slotMessageCurrentOk\0"
    "insertMessagetable\0row\0slotMessageExport\0"
    "slotMessageReport\0slotMessageDetail\0"
    "slotFileJson\0slotFileExport\0slotFileReport\0"
    "slotCountCheckInfo\0slotPrintQrcode\0"
    "slotOpenCheckInfo\0slotSummaryInfo\0"
    "slotQCountCheckInfo\0slotQPrintQrcode\0"
    "slotQOpenCheckInfo\0slotQSummaryInfo\0"
    "slotSelectByQcrode\0slotUpdateQrcode"
};
#undef QT_MOC_LITERAL

static const uint qt_meta_data_downwidget[] = {

 // content:
       7,       // revision
       0,       // classname
       0,    0, // classinfo
      66,   14, // methods
       0,    0, // properties
       0,    0, // enums/sets
       0,    0, // constructors
       0,       // flags
       2,       // signalCount

 // signals: name, argc, parameters, tag, flags
       1,    1,  344,    2, 0x06 /* Public */,
       4,    0,  347,    2, 0x06 /* Public */,

 // slots: name, argc, parameters, tag, flags
       5,    0,  348,    2, 0x0a /* Public */,
       6,    0,  349,    2, 0x0a /* Public */,
       7,    0,  350,    2, 0x0a /* Public */,
       8,    1,  351,    2, 0x0a /* Public */,
      10,    0,  354,    2, 0x0a /* Public */,
      11,    1,  355,    2, 0x0a /* Public */,
      13,    1,  358,    2, 0x0a /* Public */,
      14,    0,  361,    2, 0x0a /* Public */,
      15,    0,  362,    2, 0x0a /* Public */,
      16,    0,  363,    2, 0x0a /* Public */,
      17,    1,  364,    2, 0x0a /* Public */,
      19,    0,  367,    2, 0x0a /* Public */,
      20,    0,  368,    2, 0x0a /* Public */,
      21,    1,  369,    2, 0x0a /* Public */,
      23,    1,  372,    2, 0x0a /* Public */,
      25,    1,  375,    2, 0x0a /* Public */,
      26,    0,  378,    2, 0x0a /* Public */,
      27,    1,  379,    2, 0x0a /* Public */,
      28,    0,  382,    2, 0x0a /* Public */,
      29,    0,  383,    2, 0x0a /* Public */,
      30,    0,  384,    2, 0x0a /* Public */,
      31,    0,  385,    2, 0x0a /* Public */,
      32,    0,  386,    2, 0x0a /* Public */,
      33,    0,  387,    2, 0x0a /* Public */,
      34,    1,  388,    2, 0x0a /* Public */,
      35,    0,  391,    2, 0x0a /* Public */,
      36,    0,  392,    2, 0x0a /* Public */,
      37,    0,  393,    2, 0x0a /* Public */,
      38,    0,  394,    2, 0x0a /* Public */,
      39,    0,  395,    2, 0x0a /* Public */,
      40,    0,  396,    2, 0x0a /* Public */,
      41,    0,  397,    2, 0x0a /* Public */,
      42,    0,  398,    2, 0x0a /* Public */,
      43,    1,  399,    2, 0x0a /* Public */,
      44,    1,  402,    2, 0x0a /* Public */,
      45,    0,  405,    2, 0x0a /* Public */,
      46,    0,  406,    2, 0x0a /* Public */,
      47,    1,  407,    2, 0x0a /* Public */,
      48,    0,  410,    2, 0x0a /* Public */,
      49,    0,  411,    2, 0x0a /* Public */,
      50,    1,  412,    2, 0x0a /* Public */,
      51,    1,  415,    2, 0x0a /* Public */,
      52,    0,  418,    2, 0x0a /* Public */,
      53,    0,  419,    2, 0x0a /* Public */,
      54,    0,  420,    2, 0x0a /* Public */,
      55,    0,  421,    2, 0x0a /* Public */,
      56,    0,  422,    2, 0x0a /* Public */,
      57,    1,  423,    2, 0x0a /* Public */,
      59,    0,  426,    2, 0x0a /* Public */,
      60,    0,  427,    2, 0x0a /* Public */,
      61,    0,  428,    2, 0x0a /* Public */,
      62,    1,  429,    2, 0x0a /* Public */,
      63,    0,  432,    2, 0x0a /* Public */,
      64,    0,  433,    2, 0x0a /* Public */,
      65,    0,  434,    2, 0x0a /* Public */,
      66,    0,  435,    2, 0x0a /* Public */,
      67,    0,  436,    2, 0x0a /* Public */,
      68,    0,  437,    2, 0x0a /* Public */,
      69,    0,  438,    2, 0x0a /* Public */,
      70,    0,  439,    2, 0x0a /* Public */,
      71,    0,  440,    2, 0x0a /* Public */,
      72,    0,  441,    2, 0x0a /* Public */,
      73,    0,  442,    2, 0x0a /* Public */,
      74,    1,  443,    2, 0x0a /* Public */,

 // signals: parameters
    QMetaType::Void, QMetaType::QString,    3,
    QMetaType::Void,

 // slots: parameters
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,   12,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QStringList,   22,
    QMetaType::Int, QMetaType::Int,   24,
    QMetaType::Void, QMetaType::QString,    9,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QString,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,   18,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void, QMetaType::QJsonObject,    2,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::Int,   58,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void,
    QMetaType::Void, QMetaType::QJsonObject,    2,
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
    QMetaType::Void, QMetaType::QString,    3,

       0        // eod
};

void downwidget::qt_static_metacall(QObject *_o, QMetaObject::Call _c, int _id, void **_a)
{
    if (_c == QMetaObject::InvokeMetaMethod) {
        downwidget *_t = static_cast<downwidget *>(_o);
        Q_UNUSED(_t)
        switch (_id) {
        case 0: _t->SiganlUpdateQrcode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 1: _t->runsafecheckSignal(); break;
        case 2: _t->slotHomePageshow2(); break;
        case 3: _t->slotHomePage(); break;
        case 4: _t->ScreenShotShow(); break;
        case 5: _t->slotMobileState((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 6: _t->slotQrcodeSave(); break;
        case 7: _t->slotAppIcon((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 8: _t->slotmobileinfo((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 9: _t->slotSafecheck(); break;
        case 10: _t->slotsafecheckSignal(); break;
        case 11: _t->safeResultshow(); break;
        case 12: _t->parseSafeResult((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 13: _t->slotSafeResult(); break;
        case 14: _t->slotslidevalue(); break;
        case 15: _t->slotRequestCheckInfo((*reinterpret_cast< QStringList(*)>(_a[1]))); break;
        case 16: { int _r = _t->getScore((*reinterpret_cast< int(*)>(_a[1])));
            if (_a[0]) *reinterpret_cast< int*>(_a[0]) = _r; }  break;
        case 17: _t->IfCheckPackage((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 18: _t->slotExportReport(); break;
        case 19: _t->safeResultJson((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 20: _t->slotCheckDetail(); break;
        case 21: _t->slotSetWhiteList(); break;
        case 22: _t->slotUninstall(); break;
        case 23: _t->slotExportApp(); break;
        case 24: _t->slotReport(); break;
        case 25: _t->setWhiteList(); break;
        case 26: _t->slotProgressUpdate((*reinterpret_cast< QString(*)>(_a[1]))); break;
        case 27: _t->slotContactsbutton(); break;
        case 28: _t->slotCallhistorybutton(); break;
        case 29: _t->slotMessagesbutton(); break;
        case 30: _t->slotFilebutton(); break;
        case 31: _t->slotContactsclick(); break;
        case 32: _t->slotCallhistoryclick(); break;
        case 33: _t->slotMessagesclick(); break;
        case 34: _t->slotFileclick(); break;
        case 35: _t->slotContactJoson((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 36: _t->parseContactInfo((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 37: _t->slotContactExport(); break;
        case 38: _t->slotContaReport(); break;
        case 39: _t->slotCallhistoryJson((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 40: _t->slotCallhistoryExport(); break;
        case 41: _t->slotCallhistoryReport(); break;
        case 42: _t->slotMessageJson((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 43: _t->slotMessagexport((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 44: _t->slotMessageNextPage(); break;
        case 45: _t->slotFrontPage(); break;
        case 46: _t->slotMessageFirstPage(); break;
        case 47: _t->slotMessageLatPage(); break;
        case 48: _t->slotMessageCurrentOk(); break;
        case 49: _t->insertMessagetable((*reinterpret_cast< int(*)>(_a[1]))); break;
        case 50: _t->slotMessageExport(); break;
        case 51: _t->slotMessageReport(); break;
        case 52: _t->slotMessageDetail(); break;
        case 53: _t->slotFileJson((*reinterpret_cast< QJsonObject(*)>(_a[1]))); break;
        case 54: _t->slotFileExport(); break;
        case 55: _t->slotFileReport(); break;
        case 56: _t->slotCountCheckInfo(); break;
        case 57: _t->slotPrintQrcode(); break;
        case 58: _t->slotOpenCheckInfo(); break;
        case 59: _t->slotSummaryInfo(); break;
        case 60: _t->slotQCountCheckInfo(); break;
        case 61: _t->slotQPrintQrcode(); break;
        case 62: _t->slotQOpenCheckInfo(); break;
        case 63: _t->slotQSummaryInfo(); break;
        case 64: _t->slotSelectByQcrode(); break;
        case 65: _t->slotUpdateQrcode((*reinterpret_cast< QString(*)>(_a[1]))); break;
        default: ;
        }
    } else if (_c == QMetaObject::IndexOfMethod) {
        int *result = reinterpret_cast<int *>(_a[0]);
        void **func = reinterpret_cast<void **>(_a[1]);
        {
            typedef void (downwidget::*_t)(QString );
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&downwidget::SiganlUpdateQrcode)) {
                *result = 0;
                return;
            }
        }
        {
            typedef void (downwidget::*_t)();
            if (*reinterpret_cast<_t *>(func) == static_cast<_t>(&downwidget::runsafecheckSignal)) {
                *result = 1;
                return;
            }
        }
    }
}

const QMetaObject downwidget::staticMetaObject = {
    { &QWidget::staticMetaObject, qt_meta_stringdata_downwidget.data,
      qt_meta_data_downwidget,  qt_static_metacall, Q_NULLPTR, Q_NULLPTR}
};


const QMetaObject *downwidget::metaObject() const
{
    return QObject::d_ptr->metaObject ? QObject::d_ptr->dynamicMetaObject() : &staticMetaObject;
}

void *downwidget::qt_metacast(const char *_clname)
{
    if (!_clname) return Q_NULLPTR;
    if (!strcmp(_clname, qt_meta_stringdata_downwidget.stringdata0))
        return static_cast<void*>(const_cast< downwidget*>(this));
    return QWidget::qt_metacast(_clname);
}

int downwidget::qt_metacall(QMetaObject::Call _c, int _id, void **_a)
{
    _id = QWidget::qt_metacall(_c, _id, _a);
    if (_id < 0)
        return _id;
    if (_c == QMetaObject::InvokeMetaMethod) {
        if (_id < 66)
            qt_static_metacall(this, _c, _id, _a);
        _id -= 66;
    } else if (_c == QMetaObject::RegisterMethodArgumentMetaType) {
        if (_id < 66)
            *reinterpret_cast<int*>(_a[0]) = -1;
        _id -= 66;
    }
    return _id;
}

// SIGNAL 0
void downwidget::SiganlUpdateQrcode(QString _t1)
{
    void *_a[] = { Q_NULLPTR, const_cast<void*>(reinterpret_cast<const void*>(&_t1)) };
    QMetaObject::activate(this, &staticMetaObject, 0, _a);
}

// SIGNAL 1
void downwidget::runsafecheckSignal()
{
    QMetaObject::activate(this, &staticMetaObject, 1, Q_NULLPTR);
}
QT_END_MOC_NAMESPACE
