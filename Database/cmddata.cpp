#include "cmddata.h"
#include <QVariant>
#include <QDebug>
#include <QSqlError>
#include <protocal.h>
#include <Protocal/protocal.h>
#include <QDateTime>
#include <applist.h>


cmdData::cmdData(QObject *parent) : QObject(parent)
{

}
cmdData::~cmdData()
{

}

//添加检测信息
bool cmdData::addCheckInfo(QString CheckTime,QString Checkedname,QString Checkedpart,QString Checkedphone,QString CheckedIMEI,
                         QString PathOfReport,QString Remark,QString Checkername,QString Checkerpart,int allApkNum,int dangerousApkNum,
                         int higyestDNum,int higyerDNum,int safeApkNum,int virusNum,int Score)

{
    qDebug()<<"insert checkinfo table";
    QString Allocation = AppList::UserInfolist.at(7);
    QSqlQuery userinfoquery;
    userinfoquery.prepare("INSERT INTO checker(Checkedname,Checkedpart,Checkedphone,CheckedIMEI,PathOfReport,Remark,Checkername,Checkerpart,allApkNum,"
                          "dangerousApkNum,higyestDNum,higyerDNum,safeApkNum,virusNum,Score,CheckTime,Allocation)"
                         "VALUES(:Checkedname,:Checkedpart,:Checkedphone,:CheckedIMEI,:PathOfReport,:Remark,:Checkername,:Checkerpart,:allApkNum,:"
                          "dangerousApkNum,:higyestDNum,:higyerDNum,:safeApkNum,:virusNum,:Score,:CheckTime,:Allocation)");

//    userinfoquery.prepare("INSERT INTO checker(CheckerID,Checkedname,Checkedpart,Checkedphone,CheckedIMEI"
//                          "PathOfReport,Remark,Checkername,Checkerpart,allApkNum,dangerousApkNum,"
//                          "higyestDNum,higyerDNum,safeApkNum,virusNum,Score,CheckTime)"
//                         "VALUES(:CheckerID,:Checkedname,:Checkedpart,:Checkedphone,:CheckedIMEI,:PathOfReport,:Remark,:Checkername,:Checkerpart,:allApkNum"
//                          ",:dangerousApkNum,:higyestDNum,:higyerDNum,:safeApkNum,:virusNum,:Score,:CheckTime)");

    userinfoquery.bindValue(":Checkedname",Checkedname);
    userinfoquery.bindValue(":Checkedpart",Checkedpart);
    userinfoquery.bindValue(":Checkedphone",Checkedphone);
    userinfoquery.bindValue(":CheckedIMEI",CheckedIMEI);
    userinfoquery.bindValue(":PathOfReport",PathOfReport);
    userinfoquery.bindValue(":Remark",Remark);
    userinfoquery.bindValue(":Checkername",Checkername);
    userinfoquery.bindValue(":Checkerpart",Checkerpart);
    userinfoquery.bindValue(":allApkNum",allApkNum);
    userinfoquery.bindValue(":dangerousApkNum",dangerousApkNum);
    userinfoquery.bindValue(":higyestDNum",higyestDNum);
    userinfoquery.bindValue(":higyerDNum",higyerDNum);
    userinfoquery.bindValue(":safeApkNum",safeApkNum);
    userinfoquery.bindValue(":virusNum",virusNum);
    userinfoquery.bindValue(":Score",Score);
    userinfoquery.bindValue(":Allocation",Allocation);

    userinfoquery.bindValue(":CheckTime",QDateTime::currentDateTime());

    userinfoquery.setForwardOnly(true);
    qDebug()<<userinfoquery.lastError();
    return  userinfoquery.exec();

}

QStringList cmdData::selectCheckInfo(QString starttime,QString endtime,QString checkername,QString checkerunit,
                                     QString checkedname,QString checkedunit,QString checkedphone,QString checkedremark)
{

    qDebug()<<"select checkInfo";

    qDebug()<<checkerunit<<checkedname<<"user++++";

    QSqlQuery query;
    QString checkInfo;
    QStringList list;
    QString time1 = starttime.append(" 00:00:00");
    QString time2 = endtime.append(" 23:59:59");
    qDebug()<<time1 << time2<<"iiii";

    QString queryString;

    QString basicString = "select * from checker where checker.CheckTime >= '%1' and  checker.CheckTime < '%2'";

    QString sqlstr = basicString.arg(time1).arg(time2);

    QString sql = "select * from checker where checker.CheckTime >= '"+ starttime+"' and  checker.CheckTime < '"+endtime+"'";

    if(checkername.isEmpty()&& checkerunit.isEmpty()&&checkedname.isEmpty()&&checkedunit.isEmpty()&&checkedphone.isEmpty()&&checkedremark.isEmpty())
    {
        queryString = sqlstr;

        qDebug()<< sqlstr;

    }
    if(!checkername.isEmpty())
    {

        sql += " and checker.Checkername = '"+checkername+"'";
        queryString= sql;
        qDebug()<<"111"<<queryString;
    }
    if(!checkerunit.isEmpty())
    {
        sql += " and checker.Checkerpart = '"+checkerunit+"'";
//        sqlstr += (" and checker.Checkerpart = '%2'");
//        QString str2 = sqlstr.arg(checkername).arg(checkerunit);
        queryString= sql;
        qDebug()<<"222"<<queryString;

    }
    if(!checkedname.isEmpty())
    {
        sql += " and checker.Checkedname = '"+checkedname+"'";
        queryString = sql;
        qDebug()<<"333"<<queryString;

    }
    if(!checkedunit.isEmpty())
    {
        sql += " and checker.Checkedpart = '"+checkedunit+"'";
        queryString = sql;
        //sqlstr.append(" and checker.Checkedpart = '%1'");
        //queryString = sqlstr.arg(checkedunit);

    }
    if(!checkedphone.isEmpty())
    {
        sql += " and checker.Checkedphone= '"+checkedphone+"'";
        queryString = sql;
        //sqlstr.append(" and checker.Checkedphone = '%1'");
        //queryString = sqlstr.arg(checkedphone);

    }
    if(!checkedremark.isEmpty())
    {
        sql += " and checker.Remark = '"+checkedremark+"'";
        //sqlstr.append(" and checker.Checkedname = '%1'");
        queryString = sql;
        //sqlstr.append(" and checker.Remark = '%1'");
        //queryString = sqlstr.arg(checkedremark);

        qDebug()<<"2122"<<sql;

    }
    QString Allocation = AppList::UserInfolist.at(7);
    QString isadmin = AppList::UserInfolist.at(4);
    QString Checkedname = AppList::UserInfolist.at(0);

    //QString str = userLogin(Allocation);
    //QStringList list = str.split(MSG_DATA_ITEMS_SEPARATOR);
    //QString str2 = list.at(7);

    qDebug()<<isadmin<<"sssss";

    if(!Allocation.isEmpty())
    {

        if(isadmin == "1")
        {
            sql += " and (checker.Allocation = '"+Checkedname+"' or  checker.Checkername = '"+Checkedname+"')";

            queryString = sql;
        }else
        {
            sql += " and checker.Checkername = '"+Checkedname+"'";
            queryString = sql;
        }

    }

    if(query.exec(queryString))
    {
        int CheckerID_idx = query.record().indexOf("CheckerID");
        int Checkername_idx = query.record().indexOf("Checkername");
        int Checkedname_idx = query.record().indexOf("Checkedname");
        int Checkedpart_idx = query.record().indexOf("Checkedpart");
        int Checkedphone_idx = query.record().indexOf("Checkedphone");
        int allApkNum_idx = query.record().indexOf("allApkNum");
        int higyestDNum_idx = query.record().indexOf("higyestDNum");
        int higyerDNum_idx = query.record().indexOf("higyerDNum");
        int CheckedIMEI_idx = query.record().indexOf("CheckedIMEI");
        //int CheckedIMEI_idx = query.record().indexOf("CheckedIMEI");
        int PathOfReport_idx = query.record().indexOf("PathOfReport");
        int CheckTime_idx = query.record().indexOf("CheckTime");
        while (query.next())
        {
            QString Checkername = query.value(Checkername_idx).toString();
            QString Checkedname = query.value(Checkedname_idx).toString();
            QString Checkedpart = query.value(Checkedpart_idx).toString();
            QString Checkedphone = query.value(Checkedphone_idx).toString();
            int allApkNum = query.value(allApkNum_idx).toInt();
            int higyestDNum = query.value(higyestDNum_idx).toInt();
            int higyerDNum= query.value(higyerDNum_idx).toInt();
            QString CheckedIMEI= query.value(CheckedIMEI_idx).toString();
            QString PathOfReport = query.value(PathOfReport_idx).toString();
            int CheckerID = query.value(CheckerID_idx).toInt();
            QDateTime datetime = query.value(CheckTime_idx).toDateTime();

            qDebug()<<Checkername<<"pass"<<Checkedname<<"====checkInfo";

            checkInfo = checkInfo.append(Checkername).append(MSG_DATA_ITEMS_SEPARATOR).append(Checkedname).append(MSG_DATA_ITEMS_SEPARATOR).
                                append(Checkedpart).append(MSG_DATA_ITEMS_SEPARATOR).append(Checkedphone).append(MSG_DATA_ITEMS_SEPARATOR).append(QString::number(allApkNum)).
                                append(MSG_DATA_ITEMS_SEPARATOR).append(QString::number(higyestDNum)).append(MSG_DATA_ITEMS_SEPARATOR).append(QString::number(higyerDNum)).
                                append(MSG_DATA_ITEMS_SEPARATOR).append(CheckedIMEI).append(MSG_DATA_ITEMS_SEPARATOR).append(PathOfReport).append(MSG_DATA_ITEMS_SEPARATOR).
                                append(QString::number(CheckerID)).append(datetime.toString("yyyy-MM-dd"));

            list.append(checkInfo);

            checkInfo = "";

        }

        return list;
    }else
    {
        list.clear();
        return list;
    }

}

//二维码查询检测记录
QStringList cmdData::selectCheckByQcrode(QString qcrodestr)
{

    qDebug()<<"select checkInfo";

    qDebug()<<qcrodestr<<"user++++";

    QSqlQuery query;
    QString checkInfo;
    QStringList list;
    QString queryString;

    //QString basicString = "select * from checker where checker.CheckedIMEI = '%1'";

    //QString queryString = basicString.arg(qcrodestr);

    QString sql = "select * from checker where checker.CheckedIMEI = '"+ qcrodestr +"'";

    //QString sql = "select * from checker where checker.CheckedIMEI = '"+qcrodestr+"'";
    queryString = sql;

    QString Allocation = AppList::UserInfolist.at(7);
    QString isadmin = AppList::UserInfolist.at(4);
    QString Checkedname = AppList::UserInfolist.at(0);


    qDebug()<<isadmin<<"sssss"<<Checkedname;

    if(!Allocation.isEmpty())
    {

        if(isadmin == "1")
        {
            sql += " and (checker.Allocation = '"+Checkedname+"' or  checker.Checkername = '"+Checkedname+"')";

            queryString = sql;
        }else
        {
            sql += " and checker.Checkername = '"+Checkedname+"'";
            queryString = sql;
        }

    }

    if(query.exec(queryString))
    {
        int CheckerID_idx = query.record().indexOf("CheckerID");
        int Checkername_idx = query.record().indexOf("Checkername");
        int Checkedname_idx = query.record().indexOf("Checkedname");
        int Checkedpart_idx = query.record().indexOf("Checkedpart");
        int Checkedphone_idx = query.record().indexOf("Checkedphone");
        int allApkNum_idx = query.record().indexOf("allApkNum");
        int higyestDNum_idx = query.record().indexOf("higyestDNum");
        int higyerDNum_idx = query.record().indexOf("higyerDNum");
        int CheckedIMEI_idx = query.record().indexOf("CheckedIMEI");
        //int CheckedIMEI_idx = query.record().indexOf("CheckedIMEI");
        int PathOfReport_idx = query.record().indexOf("PathOfReport");
        int CheckTime_idx = query.record().indexOf("CheckTime");
        while (query.next())
        {
            QString Checkername = query.value(Checkername_idx).toString();
            QString Checkedname = query.value(Checkedname_idx).toString();
            QString Checkedpart = query.value(Checkedpart_idx).toString();
            QString Checkedphone = query.value(Checkedphone_idx).toString();
            int allApkNum = query.value(allApkNum_idx).toInt();
            int higyestDNum = query.value(higyestDNum_idx).toInt();
            int higyerDNum= query.value(higyerDNum_idx).toInt();
            QString CheckedIMEI= query.value(CheckedIMEI_idx).toString();
            QString PathOfReport = query.value(PathOfReport_idx).toString();
            int CheckerID = query.value(CheckerID_idx).toInt();
            QDateTime datetime = query.value(CheckTime_idx).toDateTime();

            qDebug()<<Checkername<<"pass"<<Checkedname<<"====checkInfo";

            checkInfo = checkInfo.append(Checkername).append(MSG_DATA_ITEMS_SEPARATOR).append(Checkedname).append(MSG_DATA_ITEMS_SEPARATOR).
                                append(Checkedpart).append(MSG_DATA_ITEMS_SEPARATOR).append(Checkedphone).append(MSG_DATA_ITEMS_SEPARATOR).append(QString::number(allApkNum)).
                                append(MSG_DATA_ITEMS_SEPARATOR).append(QString::number(higyestDNum)).append(MSG_DATA_ITEMS_SEPARATOR).append(QString::number(higyerDNum)).
                                append(MSG_DATA_ITEMS_SEPARATOR).append(CheckedIMEI).append(MSG_DATA_ITEMS_SEPARATOR).append(PathOfReport).append(MSG_DATA_ITEMS_SEPARATOR).
                                append(QString::number(CheckerID)).append(datetime.toString("yyyy-MM-dd"));

            list.append(checkInfo);

            checkInfo = "";

        }

        return list;
    }else
    {
        list.clear();
        return list;
    }

}

QString cmdData::userLogin(QString username)
{

    qDebug()<<"5t5tt";

    QSqlQuery query;
    QString userinfo;
    QString basicString = QString("select * from user "
                                  "where user.Username = '%1'");
    QString queryString = basicString.arg(username);


    if(query.exec(queryString))
    {
        int Username_idx = query.record().indexOf("Username");
        int password_idx = query.record().indexOf("Userpass");
        int Role_idx = query.record().indexOf("Role");
        int Part_idx = query.record().indexOf("Part");
        int isAdmin_idx = query.record().indexOf("isAdmin");
        int isEnable_idx = query.record().indexOf("isEnable");
        int UserID_idx = query.record().indexOf("UserID");
        int Allocationed_idx = query.record().indexOf("Allocationed");

        while (query.next())
        {
            QString Username = query.value(Username_idx).toString();
            QString password = query.value(password_idx).toString();
            QString Role = query.value(Role_idx).toString();
            QString Part = query.value(Part_idx).toString();
            QString isAdmin = query.value(isAdmin_idx ).toString();
            QString isEnable = query.value(isEnable_idx).toString();
            int UserID= query.value(UserID_idx).toInt();
            QString Allocationed = query.value(Allocationed_idx).toString();
            qDebug()<<Username<<"pass"<<Role<<Part<<isAdmin<<isEnable<<"====userinfo";

            userinfo = userinfo.append(Username).append(MSG_DATA_ITEMS_SEPARATOR).append(password).append(MSG_DATA_ITEMS_SEPARATOR).
                                append(Role).append(MSG_DATA_ITEMS_SEPARATOR).append(Part).append(MSG_DATA_ITEMS_SEPARATOR).append(isAdmin).
                                append(MSG_DATA_ITEMS_SEPARATOR).append(isEnable).append(MSG_DATA_ITEMS_SEPARATOR).append(QString::number(UserID)).
                                append(MSG_DATA_ITEMS_SEPARATOR).append(Allocationed);

        }

        //qDebug()<<userinfo<<"9999";
        return userinfo;

    }else
    {
        return NULL;
    }

}
int cmdData::userid(QString username)
{
    qDebug()<<"5t5tt";

    QSqlQuery query;
    QString userinfo;
    int UserID;
    QString basicString = QString("select * from user "
                                  "where user.Username = '%1'");
    QString queryString = basicString.arg(username);


    if(query.exec(queryString))
    {
        int Username_idx = query.record().indexOf("Username");
        int UserID_idx = query.record().indexOf("UserID");

        while (query.next())
        {
            QString Username = query.value(Username_idx).toString();

            UserID= query.value(UserID_idx).toInt();

        }

        return UserID;
    }else
    {
        return 0;
    }
}

//修改用户密码
bool cmdData::updataUserPassWord(QString username,QString password)
{
    qDebug()<<username<<password<<"-------";

    QSqlQuery userinfoquery;
    QString sql=  "update user set Userpass ='" + password
                  +"'where Username = '"+ username +"'";

    return userinfoquery.exec(sql);
    //qDebug()<<"updata into table ok";
}

//修改用户基本信息
bool cmdData::updataUserInfo(QString username,QString newusername,QString role,QString deparment)
{
    qDebug()<<username<<newusername<<"-------";

    QSqlQuery modifyinfoquery;
    QString modifysql=  "update user set Username ='" + newusername+ "',Role='"+role
                  +"' ,Part ='" + deparment+ "'where Username = '"+ username +"'";
    return modifyinfoquery.exec(modifysql);

}

//删除用户信息
bool cmdData::deleteUserInfo(QString username)
{

    qDebug()<<"delete userinfo table";

    QSqlQuery deletequery;
    QString sql = "DELETE FROM user where Username = '"+ username +"'";
    return deletequery.exec(sql);

}

//增加用户信息
bool cmdData::addUserInfo(QString userName,QString password,QString role,QString deparment,int admin,int enadble,QString allocation)
{
    qDebug()<<"insert into userinfo table";

    QSqlQuery userinfoquery;
    userinfoquery.prepare("INSERT INTO user(Username,Userpass,Role,Part,isAdmin,isEnable,Allocationed)"
                         "VALUES(:Username,:Userpass,:Role,:Part,:isAdmin,:isEnable,:Allocationed)");

    userinfoquery.bindValue(":Username",userName);
    userinfoquery.bindValue(":Userpass",password);
    userinfoquery.bindValue(":Role",role);
    userinfoquery.bindValue(":Part",deparment);
    userinfoquery.bindValue(":isAdmin",admin);
    userinfoquery.bindValue(":isEnable",enadble);
    userinfoquery.bindValue(":Allocationed",allocation);

    userinfoquery.setForwardOnly(true);
    qDebug()<<userinfoquery.lastError();
    return  userinfoquery.exec();

}

//删除白名单应用
bool cmdData::deleteWhiteListInfo(QString package)
{
    qDebug()<<"delete userinfo table";

    QSqlQuery deletequery;
    QString sql = "DELETE FROM whitelist where Whitename = '"+ package +"'";
    return deletequery.exec(sql);

}

bool cmdData::addWhiteListInfo(QString package,QString remark)
{

    qDebug()<<"insert into userinfo table";

    QSqlQuery whiteinfoquery;
    whiteinfoquery.prepare("INSERT INTO WhiteList(Whitename,Remark)"
                         "VALUES(:Whitename,:Remark)");

    whiteinfoquery.bindValue(":Whitename",package);
    whiteinfoquery.bindValue(":Remark",remark);

    whiteinfoquery.setForwardOnly(true);
    qDebug()<<whiteinfoquery.lastError();
    return  whiteinfoquery.exec();

}

bool cmdData::mobilecheck_add(QString MoType,QString Verdor,QString OS,QString OSVerson,
                QString SDKVersion,QString Imei,QString Imsi,QString ICCID,
                QString internalStorageTotalSize,
                QString internalStorageAvailableSize,QString cpuType,QString macAdress,
                QString HardwareSerialNumber,QString ProviderID,QString isRoot)
{
     //增加检查手机操作
     qDebug() <<"insert into table";
     QSqlQuery mobilequery;

     mobilequery.prepare("INSERT INTO mobilecheck(CheckID,MoType,Verdor,Version,OS,OSVerson,SDKVersion,Imei,Imsi,ICCID,internalStorageTotalSize,\
                         internalStorageAvailableSize,\
                         cpuType,macAdress,HardwareSerialNumber,ProviID,ProdeID,isRoot)"
                         "VALUES(:CheckID,:MoType,:Verdor,:Version,:OS,:OSVerson,:SDKVersion,:Imei,:Imsi\
                                 ,:ICCID,:internalStorageTotalSize,:internalStorageAvailableSize\
                                 ,:cpuType,:macAdress,:HardwareSerialNumber,:ProviID,:ProdeID,:isRoot)");
     mobilequery.bindValue(":CheckID",0);
     mobilequery.bindValue(":MoType",MoType);
     mobilequery.bindValue(":Verdor",Verdor);
     mobilequery.bindValue(":Version","");
     mobilequery.bindValue(":OS",OS);
     mobilequery.bindValue(":OSVerson",OSVerson);
     mobilequery.bindValue(":SDKVersion",SDKVersion);
     mobilequery.bindValue(":Imei",Imei);
     mobilequery.bindValue(":Imsi",Imsi);
     mobilequery.bindValue(":ICCID",ICCID);
     mobilequery.bindValue(":internalStorageTotalSize",internalStorageTotalSize);
     mobilequery.bindValue(":internalStorageAvailableSize",internalStorageAvailableSize);
     mobilequery.bindValue(":cpuType",cpuType);
     mobilequery.bindValue(":macAdress",macAdress);
     mobilequery.bindValue(":HardwareSerialNumber",HardwareSerialNumber);
     mobilequery.bindValue(":ProviID",ProviderID);
     mobilequery.bindValue(":ProdeID",ProviderID);
     mobilequery.bindValue(":isRoot",isRoot);

     mobilequery.setForwardOnly(true);
     qDebug()<<mobilequery.lastError();
     return  mobilequery.exec();
     qDebug() <<"insert into table ok";

}

//查询所有用户信息
QStringList cmdData::selectAllUserInfo()
{
    QSqlQuery query;
    QString queryString;
    QString allocation = AppList::UserInfolist.at(7);

    QString str = AppList::UserInfolist.at(0);
    qDebug()<<allocation<<"ppppp";

    if(allocation.isEmpty())
    {
        QString basicString = QString("select * from user where user.Username != '%1'");
        queryString = basicString.arg(str);

    }else
    {
        QString basicString = QString("select * from user "
                                      "where user.Allocationed = '%1'");
        queryString = basicString.arg(str);
    }

    QStringList list;
    QString userinfo;

    if(query.exec(queryString))
    {
          int username_idx = query.record().indexOf("Username");
//        int Coursename_idx = query.record().indexOf("CourseName");
//        int Coursehour_idx = query.record().indexOf("CourseHour");
//        int credit_idx = query.record().indexOf("Credit");
//        int prpperty_idx = query.record().indexOf("Prpperty");

        while (query.next())
        {
              QString username = query.value(username_idx).toString();
//            QString name = query.value(Coursename_idx).toString();
//            QString hour = query.value(Coursehour_idx).toString();
//            QString credit = query.value(credit_idx).toString();
//            QString prpperty = query.value(prpperty_idx).toString();

              userinfo = cmdData::userLogin(username);

              //info.updatacouserinfo(selectCourseInfoTable(id));
              list.append(userinfo);
        }
    }

    return list;

}

//查找全部白名单信息
QStringList cmdData::selectAllWhiteListInfo()
{

    QSqlQuery query;
    QString queryString = QString("select * from whitelist");
    QStringList list;
    QString whiteinfo;

    if(query.exec(queryString))
    {

        int Whitename_index = query.record().indexOf("Whitename");
        int Remark_index = query.record().indexOf("Remark");

        while(query.next())
        {
              QString Whitename = query.value(Whitename_index).toString();
              QString Remark = query.value(Remark_index).toString();

              whiteinfo = whiteinfo.append(Whitename).append(MSG_DATA_ITEMS_SEPARATOR).append(Remark);

              list.append(whiteinfo);

              whiteinfo = "";
        }
    }

    return list;

}
QStringList cmdData::selectWhitelist(QString package)
{

    QSqlQuery query;

    QString basicString = QString("select * from whitelist "
                                  "where whitelist.Whitename = '%1'");
    QString queryString = basicString.arg(package);
    QStringList list;
    QString whiteinfo;

    if(query.exec(queryString))
    {

        int Whitename_index = query.record().indexOf("Whitename");
        int Remark_index = query.record().indexOf("Remark");

        while(query.next())
        {
              QString Whitename = query.value(Whitename_index).toString();
              QString Remark = query.value(Remark_index).toString();

              whiteinfo = whiteinfo.append(Whitename).append(MSG_DATA_ITEMS_SEPARATOR).append(Remark);

              list.append(whiteinfo);

              whiteinfo = "";
        }

        return list;
    }else
    {
        list.clear();
        return list;
    }

}

//条件查询所有用户信息
QStringList cmdData::selectAllUserInfo(QString userinfo,QString role, QString deparment)
{
    QStringList list;
    QSqlQuery query;
    QString SelectuserInfo;
    QString queryString;

    QString str1 = AppList::UserInfolist.at(7);
    QString str2 = AppList::UserInfolist.at(0);

    if(str1.isEmpty())
    {
        QString sql = "select * from user where user.Username != '"+str2+"'";

        queryString= sql;

        if(!role.isEmpty())
        {
            sql += " and user.Role = '"+role+"'";
            queryString= sql;
            qDebug()<<"222"<<queryString;

        }

        if(!deparment.isEmpty())
        {
            sql += " and user.Part = '"+deparment+"'";
            queryString = sql;
            qDebug()<<"333"<<queryString;

        }

        if(!userinfo.isEmpty())
        {
            sql += " and user.Username = '"+userinfo+"'";
            queryString= sql;
            qDebug()<<"111"<<queryString;
        }


    }else
    {
        QString sql = "select * from user where user.Allocationed = '"+str2+"'";

        queryString= sql;

        if(!userinfo.isEmpty())
        {

            sql += " and user.Username = '"+userinfo+"'";
            queryString= sql;
            qDebug()<<"111"<<queryString;
        }
        if(!role.isEmpty())
        {
            sql += " and user.Role = '"+role+"'";

            queryString= sql;
            qDebug()<<"222"<<queryString;

        }
        if(!deparment.isEmpty())
        {
            sql += " and user.Part = '"+deparment+"'";
            queryString = sql;
            qDebug()<<"333"<<queryString;
        }

    }

    qDebug()<<queryString<<"kouus";

    if(query.exec(queryString))
    {
        int username_idx = query.record().indexOf("Username");

        while (query.next())
        {
              QString username = query.value(username_idx).toString();

              if(username.isEmpty())
              {
                      list.clear();
                      return list;

               }else
               {

                     SelectuserInfo = cmdData::userLogin(username);
                     list.append(SelectuserInfo);
               }

          }
     }

     return list;
}


//查找权限详细信息
QString cmdData::selectperDetail(QString permission)
{
    qDebug()<<"select premission";
    QString basicString = QString("select * from permissionconfig "
                                  "where permissionconfig.Permission = '%1'");
    QString queryString = basicString.arg(permission);

    QSqlQuery query;
    QString permisson;
    if(query.exec(queryString))
    {
        int perdetail_idx = query.record().indexOf("Perdetail");
        int plevel_idx = query.record().indexOf("PLevel");
        while (query.next())
        {
            QString perdetail = query.value(perdetail_idx).toString();
            QString plevel = query.value(plevel_idx).toString();

            if(!perdetail.isEmpty())
            {
                permisson.append(perdetail).append(MSG_DATA_ITEMS_SEPARATOR).append(plevel);

                qDebug()<<permisson<<"==msyql==";
            }else
            {
                return NULL;
            }


        }
    }

    return permisson;
}


QString cmdData::selectperdetail(QString permisson1)
{
    qDebug()<<"select premission";
    QString basicString = QString("select * from permissionconfig "
                                  "where permissionconfig.Permission = '%1'");
    QString queryString = basicString.arg(permisson1);

    QSqlQuery query;
    QString permisson;
    if(query.exec(queryString))
    {
        int per_idx = query.record().indexOf("Perdetail");
        int plevel_idx = query.record().indexOf("PLevel");
        while (query.next())
        {
            QString perde = query.value(per_idx).toString();
            QString plevel = query.value(plevel_idx).toString();

            if(!perde.isEmpty())
            {
                permisson.append(permisson1).append(MSG_DATA_ITEMS_SEPARATOR).append(perde).append(MSG_DATA_ITEMS_SEPARATOR).append(plevel);
                qDebug()<<permisson<<"==msyql==";
            }else
            {

                return NULL;
            }


        }
    }

    return permisson;
}
