#ifndef CMDDATA_H
#define CMDDATA_H

#include <QObject>
#include <mdatabase.h>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QStringList>
#include <QString>
#include <QSettings>
#include <QDateTime>

class cmdData : public QObject
{
    Q_OBJECT
public:
    explicit cmdData(QObject *parent = 0);

    ~cmdData();

    static bool mobilecheck_add(QString MoType,QString Verdor,QString OS,QString OSVerson,
                    QString SDKVersion,QString Imei,QString Imsi,QString ICCID,QString internalStorageTotalSize,
                    QString internalStorageAvailableSize,QString cpuType,QString macAdress,
                    QString HardwareSerialNumber,QString ProviderID,QString isRoot);

    static QString userLogin(QString username);
    static int userid(QString username);

    static QString selectperDetail(QString permission);
    static QString selectperdetail(QString perDetail);

    static bool updataUserPassWord(QString username,QString password);
    static bool addUserInfo(QString userName,QString password,QString role,QString deparment,int admin,int enadble,QString allocation);
    static QStringList selectAllUserInfo();
    static QStringList selectAllUserInfo(QString userinfo,QString role, QString deparment);

    static bool updataUserInfo(QString username,QString newusername,QString role,QString deparment);
    static bool deleteUserInfo(QString username);

    static QStringList selectAllWhiteListInfo();
    static bool deleteWhiteListInfo(QString package);
    static bool addWhiteListInfo(QString package,QString remark);
    static QStringList selectWhitelist(QString package);

    static bool addCheckInfo(QString CheckTime,QString Checkedname,QString Checkedpart,QString Checkedphone,QString CheckedIMEI,
                             QString PathOfReport,QString Remark,QString Checkername,QString Checkerpart,int allApkNum,int dangerousApkNum,
                             int higyestDNum,int higyerDNum,int safeApkNum,int virusNum,int Score);

    //static QStringList selectCheckInfo(QString starttime,QString endtime);
    static QStringList selectCheckInfo(QString starttime,QString endtime,QString checkername,QString checkerunit,
                                         QString checkedname,QString checkedunit,QString checkedphone,QString checkedremark);

    static QStringList selectCheckByQcrode(QString qcrodestr);

signals:

public slots:
};

#endif // CMDDATA_H
