#ifndef APPLIST_H
#define APPLIST_H
#include <QStringList>
#include <QJsonObject>

class AppList
{
public:
    AppList();
    ~AppList();
    static QStringList AppPackageList;
    static QStringList AppPackageDanger;
    static QStringList AppNameListDanger;
    static QStringList AppNameList;
    static QStringList MobileInfo;
    static QString MobileImei;
    static int number;
    static QString mobileinfo;
    static QString IconSrcdate;
    static int Iconi;
    static int AppNanmei;
    static QString ApkPermission[1000];
    static int currentrow;
    static int riskcount;
    static QString permisson[1000];
    static QString ContactsInfo[1000];
    static QString CallhistoryInfo[1000];
    static QString MessageInfo[10000];
    static QString FileInfo[1000002];

    static QString MessageExportInfo[10000];
    static QString currentExportDir;
    static QString IfAmdin;
    static QStringList UserInfolist;
    static int CheckAllApk;
    static int Viruscount;
    static QStringList AuthInfo;

};

#endif // APPLIST_H
