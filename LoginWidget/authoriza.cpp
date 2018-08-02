#include "authoriza.h"
#include <string.h>
#include <string>
#include <QObject>
#include <QMessageBox>
#include <QDateTime>
#include <qstring.h>
#include <QDebug>
#include <QIcon>
#include <applist.h>
#include <tchar.h>
#include <Windows.h>

BOOL (WINAPI *My_GetFileLicenseInfo)(__in CHAR *LpPath);
BOOL (WINAPI *My_GetFileLicenseValue)(__in CHAR *LpKey,__out CHAR *LpValue,__in int nLen);
BOOL (WINAPI *My_GetDiskNum)(__out CHAR *LpValue,__in int nLen);

Authoriza::Authoriza()
{

}
Authoriza::~Authoriza()
{

}

QString Authoriza::getDiskNumber()
{
//      QString lpRootPathName = "C:\\";
//      LPTSTR lpVolumeNameBuffer=new TCHAR[12];//磁盘卷标
//      DWORD nVolumeNameSize=12;// 卷标的字符串长度
//      DWORD VolumeSerialNumber;//硬盘序列号
//      DWORD MaximumComponentLength;// 最大的文件长度
//      LPTSTR lpFileSystemNameBuffer=new TCHAR[10];// 存储所在盘符的分区类型的长指针变量
//      DWORD nFileSystemNameSize=10;// 分区类型的长指针变量所指向的字符串长度
//      DWORD FileSystemFlags;// 文件系统的一此标志
//      GetVolumeInformation((LPTSTR)lpRootPathName.utf16(),
//      lpVolumeNameBuffer, nVolumeNameSize,
//      &VolumeSerialNumber, &MaximumComponentLength,
//      &FileSystemFlags,
//      lpFileSystemNameBuffer, nFileSystemNameSize);
//      qDebug() << VolumeSerialNumber<<"iiiiii";


//      LPCTSTR lpRootPathName=("c:\\"); //取C盘
//      LPTSTR lpVolumeNameBuffer=new char[12];//磁盘卷标
//      DWORD nVolumeNameSize=12;// 卷标的字符串长度
//      DWORD VolumeSerialNumber;//硬盘序列号
//      DWORD MaximumComponentLength;// 最大的文件长度
//      LPTSTR lpFileSystemNameBuffer=new char[10];// 存储所在盘符的分区类型的长指针变量
//      DWORD nFileSystemNameSize=10;// 分区类型的长指针变量所指向的字符串长度
//      DWORD FileSystemFlags;// 文件系统的一此标志
//      ::GetVolumeInformation(lpRootPathName,
//       lpVolumeNameBuffer, nVolumeNameSize,
//       &VolumeSerialNumber, &MaximumComponentLength,
//       &FileSystemFlags,
//       lpFileSystemNameBuffer, nFileSystemNameSize);
//       qDebug() << VolumeSerialNumber<<"iiiiii";

//      CString str;
//      str.Format("Seria Num is %lx ",VolumeSerialNumber);
//      AfxMessageBox(str);


      QString str;
      return str;
}

QString Authoriza::getHostMacAddress()
{

    QList<QNetworkInterface> nets = QNetworkInterface::allInterfaces();// 获取所有网络接口列表
    int nCnt = nets.count();
    QString strMacAddr = "";
    for(int i = 0; i < nCnt; i ++)
    {
        // 如果此网络接口被激活并且正在运行并且不是回环地址，则就是我们需要找的Mac地址
        if(nets[i].flags().testFlag(QNetworkInterface::IsUp) && nets[i].flags().testFlag(QNetworkInterface::IsRunning) && !nets[i].flags().testFlag(QNetworkInterface::IsLoopBack))
        {

                if (!(nets[i].humanReadableName().contains("VMware",Qt::CaseInsensitive)))
                {
                    strMacAddr = nets[i].hardwareAddress();
                    break;
                   //strMac = iface.hardwareAddress();
                  //mac_list.append(strMac);
                }
        }
    }

    qDebug()<<strMacAddr<<"llll";

    return strMacAddr;

//    QString strMacAddr = "";
//    QList<QNetworkInterface> nets  = QNetworkInterface::allInterfaces();
//    int i = 0;
//    foreach(QNetworkInterface ni,nets)
//    {
//            i++;
//            qDebug()<<i<<ni.name()<<ni.hardwareAddress()<<ni.humanReadableName();

//            if(ni.humanReadableName() == QStringLiteral("本地连接"))
//            {
//                strMacAddr = ni.hardwareAddress();
//                break;
//            }

//            //qDebug() << "HardwareAddress:" << ni.hardwareAddress();
//            strMacAddr =  ni.hardwareAddress();

//    }

//    QString macstr = strMacAddr.replace(QRegExp("\\:"), "-");

//    qDebug()<<macstr;

//    return macstr;

}

bool Authoriza::AuthorizaInitialize()
{

    //getDiskNumber();

    QString stime = NULL;
    QString etime = NULL;

    AppList::AuthInfo.clear();

    HMODULE m_Hm = LoadLibraryW(L"PrintLicense.dll");
    if (!m_Hm)
    {
        QMessageBox box(QMessageBox::Information,QStringLiteral("授权提示"),QStringLiteral("授权 DLL 加载失败！"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        //box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
        box.setWindowIcon(QIcon("screen/carful.ico"));
        box.exec();

        return false;
    }
    My_GetFileLicenseInfo	= (BOOL (WINAPI *)(__in CHAR *LpPath))GetProcAddress(m_Hm,("GetFileLicenseInfo"));
    My_GetFileLicenseValue	= (BOOL (WINAPI *)(__in CHAR *LpKey,__out CHAR *LpValue,__in int nLen))GetProcAddress(m_Hm,("GetFileLicenseValue"));
    My_GetDiskNum = (BOOL (WINAPI *)(__out CHAR *LpValue,__in int nLen))GetProcAddress(m_Hm,("GetDiskNum"));

    if (!My_GetFileLicenseInfo || !My_GetFileLicenseValue)
    {
        QMessageBox box(QMessageBox::Information,QStringLiteral("授权提示"),QStringLiteral("函数加载失败！"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        //box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
        box.setWindowIcon(QIcon("screen/carful.ico"));
        box.exec();

        FreeLibrary(m_Hm);
        return false;
    }

    My_GetFileLicenseInfo("介质");

    //授权产品标题
    CHAR Value_title[256];
    My_GetFileLicenseValue("title", Value_title, 256);
    QString title = QString::fromLocal8Bit(Value_title);
    QString current_title = QStringLiteral("智能手机安全检测系统 (MobileCheck)");
    AppList::AuthInfo.append(current_title);
    if(title != current_title)
    {
        QMessageBox box(QMessageBox::Information,QStringLiteral("授权提示"),QStringLiteral("未授权！"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        //box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
        box.setWindowIcon(QIcon("screen/carful.ico"));
        box.exec();

        FreeLibrary(m_Hm);
        return false;
    }
    //授权部门或单位
    CHAR Value_username[256];
    My_GetFileLicenseValue("UserName", Value_username, 256);
    QString username = QString::fromLocal8Bit(Value_username);
    QString current_username = QStringLiteral("北京研发部");
    AppList::AuthInfo.append(current_username);
    if(username != current_username)
    {
        QMessageBox box(QMessageBox::Information,QStringLiteral("授权提示"),QStringLiteral("该部门或单位未授权！"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        //box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
        box.setWindowIcon(QIcon("screen/carful.ico"));
        box.exec();

        FreeLibrary(m_Hm);
        return false;
    }

    //授权公司
    CHAR Value_Company[256];
    My_GetFileLicenseValue("LicensingCompany", Value_Company, 256);
    QString Company = QString::fromLocal8Bit(Value_Company);
    //qDebug()<<Company<<"fgggggg";
    QString current_company = QStringLiteral("北京峰盛博远科技股份有限公司");
    AppList::AuthInfo.append(current_company);
    if(Company != current_company)
    {
        QMessageBox box(QMessageBox::Information,QStringLiteral("授权提示"),QStringLiteral("本产品为非法公司授权！"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        box.setWindowIcon(QIcon("screen/carful.ico"));
        box.exec();

        FreeLibrary(m_Hm);
        return false;
    }

    //授权版本类型
//    CHAR Value_title[256];
//    My_GetFileLicenseValue("LicensingCompany", Value_title, 256);
//    QString title = QString::fromLocal8Bit(Value_title);
//    qDebug()<<title<<"fgggggg";


    //开始授权日期
    CHAR Value_stime[256];
    My_GetFileLicenseValue("stime", Value_stime, 256);
    stime = QString::fromLocal8Bit(Value_stime);

    //结束授权日期
    CHAR Value_etime[256];
    My_GetFileLicenseValue("etime", Value_etime, 256);
    etime = QString::fromLocal8Bit(Value_etime);
    //qDebug()<<etime<<"fgggggg";

    //当前时间
    QString currenttime = QDateTime::currentDateTime().toString("yyyy-MM-dd");
    qDebug()<<currenttime<<"fgggggg";

    QDateTime sdatetime = QDateTime::fromString(stime,"yyyy-MM-dd");
    QDateTime edatetime = QDateTime::fromString(etime,"yyyy-MM-dd");
    QDateTime currentdate = QDateTime::fromString(currenttime,"yyyy-MM-dd");
    //QDateTime currentdate = QDateTime::fromString("2018-03-02","yyyy-MM-dd");
    //QDateTime currentdate = QDateTime::fromString("2017-03-02","yyyy-MM-dd");
    QString stimestr = sdatetime.toString("yyyy.MM.dd");
    QString etimestr = edatetime.toString("yyyy.MM.dd");
    QString timestr = stimestr.append("-").append(etimestr);
    AppList::AuthInfo.append(timestr);

    if(currentdate < sdatetime || currentdate > edatetime)
    {
        QMessageBox box(QMessageBox::Information,QStringLiteral("授权提示"),QStringLiteral("本产品未授权或授权过期！"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        box.setWindowIcon(QIcon("screen/carful.ico"));
        box.exec();

        FreeLibrary(m_Hm);
        return false;

    }

    //授权匹配设备
    CHAR Value_root[256];
    My_GetFileLicenseValue("DefaultRootOrg", Value_root, 256);
    QString root = QString::fromLocal8Bit(Value_root);
    qDebug()<<root<<"LLLL";

    CHAR diskNum[128];
    My_GetDiskNum(diskNum,128);

    QString disknum = QString::fromLocal8Bit(diskNum);

    qDebug()<<disknum<<"disk";

    FreeLibrary(m_Hm);

    return true;

}

bool Authoriza::AuthorizaInitializeRemove()
{

    //QString stime = NULL;
    //QString etime = NULL;

    HMODULE m_Hm = LoadLibraryW(L"PrintLicense.dll");
//    if (!m_Hm)
//    {

//        return false;
//    }
    My_GetFileLicenseInfo	= (BOOL (WINAPI *)(__in CHAR *LpPath))GetProcAddress(m_Hm,("GetFileLicenseInfo"));
    My_GetFileLicenseValue	= (BOOL (WINAPI *)(__in CHAR *LpKey,__out CHAR *LpValue,__in int nLen))GetProcAddress(m_Hm,("GetFileLicenseValue"));

//    if(!My_GetFileLicenseInfo || !My_GetFileLicenseValue)
//    {
//        FreeLibrary(m_Hm);
//        return false;
//    }

    My_GetFileLicenseInfo("介质");

    //授权产品标题
    CHAR Value_title[256];
    My_GetFileLicenseValue("title", Value_title, 256);
    QString title = QString::fromLocal8Bit(Value_title);
    QString current_title = QStringLiteral("智能手机安全检测系统 (MobileCheck)");

    qDebug()<<title<<"fffff";

    if(title.isEmpty())
    {
        FreeLibrary(m_Hm);
        return false;

    }

    return true;
}


