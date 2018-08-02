#include "parsejson.h"
#include <QDebug>
#include <Protocal/protocal.h>
#include <QFile>
#include <iostream>
#include <QIODevice>
#include <QDataStream>
#include <Common/applist.h>
#include <QBuffer>
#include <QImage>
#include <QImageReader>
#include <QPixmap>
#include <QDateTime>
#include <QMovie>
#include <QPainter>
#include <QCoreApplication>
#include <QString>
#include <QImageReader>
#include <QtPlugin>
#include <QDir>
#include <QCryptographicHash>


QString ParseJson::appname = "";
int ParseJson::pngi = 0;
ParseJson::ParseJson()
{
    m_data = new cmdData;
    //imagelabel = new QLabel;

}
ParseJson::~ParseJson()
{

}
void ParseJson::parseJsonSlot(QByteArray Revcmsg)
{
    qDebug()<<"start parse";

    QJsonParseError error;
    qDebug()<<"12345";
    QJsonDocument jsondoc=QJsonDocument::fromJson(Revcmsg,&error);
    if(error.error==QJsonParseError::NoError)
    {
        if(!jsondoc.isNull() || jsondoc.isEmpty())
        {
            if(jsondoc.isObject())
            {
                QJsonObject obj = jsondoc.object();
                if(obj.contains("opType"))
                {
                   QJsonValue OpeType_value = obj.take("opType");
                   if(!OpeType_value.isNull())
                   {
                      QString opetype = OpeType_value.toString();
                      qDebug()<<opetype <<"======"<<"yjyjjj";
                      int OpeType = opetype.toInt()+ '0' ;

                      qDebug()<<OpeType<<"uuuuu";
                      switch (OpeType)
                      {
                         case MSG_USER_OPERATE_Right: parseRightJson(obj);   break;
                         //case MSG_USER_OPERATE_Virus: ParseVirseJson(obj);   break;
                         case MSG_USER_OPERATE_Detail : parseDetailJson(obj); break;
                         case MSG_USER_OPERATE_NetTCP: parseNetTCPJson(obj); break;
                         case MSG_USER_OPERATE_Contact: parseContactJson(obj); break;
                         case MSG_USER_OPERATE_Records: parseRecondsJson(obj); break;
                         case MSG_USER_OPERATE_Message: parseMessageJson(obj); break;
                         case MSG_USER_OPERATE_Message_Export_ALL: parseMessageExport(obj); break;
                         case MSG_USER_OPERATE_SD_Document: parseSDDocument(obj);break;
                         case MSG_USER_OPERATE_APPList: parseAppList(obj);
                         default: break;
                      }
                   }
               }

            }else if(jsondoc.isArray())
            {
                qDebug()<<"3456789765";
            }else
            {
            }

        }else
        {
            qDebug()<<error.error;
            qDebug()<<"ParseJson Error";

     }
    }else
    {
          qDebug()<<"Data is Empty";
          //qDebug()<<error.errorString();

          parseAppIcon(Revcmsg);
          return;
    }

    qDebug()<<"12345++";
}


//分类别进行解码
QString ParseJson::RightInfoTransCode(QString data)
{
    QString code;
    QString transdate;

    if(!data.isEmpty())
    {
        code = data.left(6);
        transdate = data.mid(6);

    }else
    {
        return NULL;
    }
    //qDebug()<<code<<transdate<<"+++++";

    if("EFBBBD" == code)     //明文编码
    {
        return transdate;
    }else if("EFBBBE" == code)  //16进制图片编码
    {
        transImage(transdate);
        return code;

    }else if("EFBBBF" == code)  //UTF-8编码
    {
        qDebug()<<transdate<<"jjjjj";
        //QString str3 =   "00680065006c006c006f00200077006f0072006c0064ff014f60597d";
        QByteArray transdateHex = QByteArray::fromHex(transdate.toLocal8Bit());
        QString str = uniCodeToStr(transdateHex);
        return str;
    }

}

//检测手机和病毒信息
bool ParseJson::parseRightJson(QJsonObject object)
{

    qDebug()<<"start parseRightJson";

    emit singalSafeResult(object);
    qDebug()<<"emit right";

    QJsonValue ret_vaue = object.take("ret");
    QString ret = ret_vaue.toString();
    qDebug()<<ret<<"result";
    if(ret == "200")
    {
        QJsonObject  json= object.take("appInfo").toObject();
        QString appName =  json.value("appName").toString();

        QString packageName = json.value("packageName").toString();
        QString versionName = json.value("versionName").toString();
        QString codePath = json.value("codePath").toString();
        QString sourceDir = json.value("codePath").toString();
        QString iconContent = json.value("iconContent").toString();
        QString MD5 = json.value("MD5").toString();
        QString apkPermission = json.value("opPerssion").toString();

        QJsonObject vInfojson = json.value("vInfo").toObject();

        QString vNanme = vInfojson.value("vName").toString();


       /************************************************************/
       // 解析图片数据
       ParseJson::appname = RightInfoTransCode(appName);
       RightInfoTransCode(iconContent);



       qDebug()<<RightInfoTransCode(appName)<<RightInfoTransCode(packageName)<<
                 RightInfoTransCode(apkPermission)<<RightInfoTransCode(vNanme)
                  <<"++++appname123++++";

       //发送进度条信号
       //QString Appname = RightInfoTransCode(appName);
       emit ProgressbarApp(ParseJson::appname);

       return true;
    }else if(ret == "210")
    {
        QString desc = object.value("desc").toString();

        qDebug()<<desc<<"jjjjjj";

        QString IconNULL = NULL;

        transImage(IconNULL);

        /************************************************************/
        // 解析图片数据
//        RightInfoTransCode(iconContent);


//               qDebug()<<RightInfoTransCode(appName)<<RightInfoTrans
//                          <<"++++appname123++++";

        //发送进度条信号
        int count = AppList::AppNameList.count();

        QString str = AppList::AppNameList.at(count -1);

        qDebug()<<AppList::AppNameList.at(pngi-1)<<";;popop";

        if(AppList::AppNameList.at(pngi-1) == str)
        {
            QString str1 = "LastOne";
            emit ProgressbarApp(str1);

        }

    }else
    {
        qDebug()<<"parseRightJson Error";
        return false;
    }
}

//检测病毒信息
bool ParseJson::ParseVirseJson(QJsonObject object)
{

    QJsonValue ret_vaue = object.take("ret");
    QJsonValue opetype_value = object.take("opType");
    int ret = ret_vaue.toInt();
    int opetype = opetype_value.toInt();
    qDebug()<<ret<<"result";
    if(ret == 0)
    {
        QJsonArray VriusArray= object.take("vInfo").toArray();

        int tag = VriusArray.at(0).toInt();
        qDebug() << "tag:" << tag;
        for(int i = 1; i < VriusArray.size(); ++i)
        {
                QJsonObject json = VriusArray.at(i).toObject();
                QString vName =  json.value("vName").toString();
                int vType = json.value("vType").toInt();
                QString vDetail = json.value("vDetail").toString();
                QString remark = json.value("remark").toString();

                if(vType == -1)
                {
                    qDebug()<<"该应用无病毒";
                }
                qDebug()<<"Virse: "<<opetype <<vName <<vType <<vDetail <<remark;

       }

        return true;
    }else
    {

        qDebug()<<"parseVriseJson Error";
        return false;
    }

    return true;
}

//解析手机有关参数信息
bool ParseJson::parseDetailJson(QJsonObject object)
{

    qDebug()<<"start praseDatailJson";
    QJsonValue ret_vaue = object.take("ret");
    QJsonValue opetype_value = object.take("opType");
    QString ret = ret_vaue.toString();
    QString opetype = opetype_value.toString();
    qDebug()<<ret<<"result";
    if(ret == "200")
    {
        QJsonObject hardInfo = object.take("hardwareInfo").toObject();

        QJsonValue moType = hardInfo.take("moType");
        QString motype = moType.toString();

        QJsonValue verdor = hardInfo.take("verdor");
        QString Verdor = verdor.toString();

        QJsonValue OS = hardInfo.take("OS");
        QString os = OS.toString();

        QJsonValue OSVerson = hardInfo.take("OSVerson");
        QString osverson = OSVerson.toString();

        QJsonValue SDKVersion = hardInfo.take("SDKVersion");
        QString sdkverson = SDKVersion.toString();

        QJsonValue imei = hardInfo.take("imei");
        QString Imei = imei.toString();   
        AppList::MobileImei = RightInfoTransCode(Imei);

        QJsonValue imsi = hardInfo.take("ismi");
        QString Imsi = imsi.toString();

        QString ICCID = hardInfo.take("ICCID").toString();
        QString internalStorageTotalSize = hardInfo.take("internalStorageTotalSize").toString();
        QString internalStorageAvailableSize = hardInfo.take("internalStorageAvailableSize").toString();
        QString cpuType = hardInfo.take("cpuType").toString();
        QString macAdress = hardInfo.take("macAdress").toString();
        QString hardwareSerialNumber = hardInfo.take("hardwareSerialNumber").toString();
        QString providerID = hardInfo.take("providerID").toString();
        QString root = hardInfo.take("root").toString();

//        bool OK = cmdData::mobilecheck_add(motype,Verdor,os,osverson,sdkverson,Imei,Imsi,ICCID,internalStorageTotalSize,
//                                           internalStorageAvailableSize,cpuType,macAdress,hardwareSerialNumber,
//                                           providerID,root);
//        if(!OK)
//        {
//           qDebug()<<"Error AddInfo MobileTable";

//        }else
//        {
//           qDebug()<<"AddInfo into table successful";

//        }
//        if(!hardInfo.value("moType").toString().isEmpty())
//        {

         AppList::mobileinfo = RightInfoTransCode(motype).append(MSG_DATA_ITEMS_SEPARATOR).append(RightInfoTransCode(os)).
                 append(MSG_DATA_ITEMS_SEPARATOR).append(RightInfoTransCode(Verdor)).append(MSG_DATA_ITEMS_SEPARATOR).
                 append(RightInfoTransCode(osverson)).append(MSG_DATA_ITEMS_SEPARATOR).append(RightInfoTransCode(sdkverson)).
                 append(MSG_DATA_ITEMS_SEPARATOR).append(RightInfoTransCode(cpuType)).append(MSG_DATA_ITEMS_SEPARATOR).
                 append(RightInfoTransCode(macAdress)).append(MSG_DATA_ITEMS_SEPARATOR).append(RightInfoTransCode(providerID)).
                 append(MSG_DATA_ITEMS_SEPARATOR).append(RightInfoTransCode(root));

        emit signalmobile(AppList::mobileinfo);

        qDebug()<<"emit...."<<AppList::mobileinfo;
        qDebug()<<"hardinfo: "<<opetype <<motype <<Verdor <<os <<osverson
                <<sdkverson <<Imei <<Imsi << ICCID<< internalStorageTotalSize<<internalStorageAvailableSize
                  <<cpuType<< macAdress << hardwareSerialNumber <<providerID <<providerID<<"+++++++++";
        return true;
    }else
    {
        qDebug()<<"parseDetailJson Error";
        return false;
    }
}

//解析网络数据
bool ParseJson::parseNetTCPJson(QJsonObject object)
{
    QJsonValue ret_vaue = object.take("ret");   
    int ret = ret_vaue.toInt();
    qDebug()<<ret<<"result";
    if(ret == 0)
    {
        return true;
    }else
    {
        qDebug()<<"parseNetcpJson Error";
        return false;
    }
    return true;
}


//解析APP图标
bool ParseJson::parseAppIcon(QByteArray Revcmsg)
{ 

        //qDebug() << QImageReader::supportedImageFormats();

        //QString dir = "../../image";
        //QString saveFileName = dir.append(QString::number(i)).append(".jpeg");

        qDebug() <<"55"<<Revcmsg.data()<<"222";

        if(Revcmsg.size() == 0)
        {
            qDebug()<<"Date Error";
            return false;
        }

        QBuffer buffer(&Revcmsg);

        buffer.open(QIODevice::ReadWrite);

        QImageReader reader(&buffer, "PNG");
        reader.setFormat("PNG");


        qDebug()<<Revcmsg.data();
        qDebug()<<buffer.data().size()<<"===";


        QImage image = reader.read();


        //QString saveFileName=QCoreApplication::applicationDirPath()+ "/33.PNG";

        qDebug()<<reader.errorString()<<reader.error();

        QString saveFileName= QDir::currentPath();

        qDebug()<<saveFileName ;


         int count = AppList::AppNameList.count();
         qDebug()<<count;

//         if(pngi  == count)
//         {
//             return false;
//         }

         //QString pathname = saveFileName.append("/appIcon/").append(AppList::AppNameList.at(pngi)).append(".PNG");
         QString pathname = saveFileName.append("/appIcon/").append(QString::number(pngi)).append(".PNG");

         image.save(pathname);

         pngi++;

         qDebug()<<"Count:====="<<pngi;


       // }


//        QString pathname = saveFileName.append("/appIcon/").append(QString::number(pngi)).append("22.PNG");

//        image.save(pathname);


        return true;

}

//获取手机通讯录
bool ParseJson::parseContactJson(QJsonObject object)
{
    qDebug()<<"start praseContact";

    singalContactInfo(object);


    QJsonValue ret_vaue = object.take("ret");
    QJsonValue opetype_value = object.take("opType");
    QString ret = ret_vaue.toString();
    QString opetype = opetype_value.toString();
    qDebug()<<ret<<opetype<<"result";

    if(ret == "200")
    {

        QJsonArray contact= object.take("contact").toArray();

        int tag = contact.at(0).toInt();
        qDebug() << "tag:" << tag;

        for(int i = 0; i < contact.size(); i++)
        {

           QJsonObject json = contact.at(i).toObject();

           //QJsonObject contact  = object.take("contact").toObject();

           QJsonValue phoneNum = json.take("phoneNum");
           QString phonename = phoneNum.toString();

           QJsonValue contactName = json.take("contactName");
           QString contactname = contactName.toString();

           QJsonValue contactId = json.take("contactId");
           QString contactid = contactId.toString();

           qDebug()<<"IphonContact: "<<phonename <<contactname <<contactid<<"+++++++++";

        }

         return true;
    }else
    {
        qDebug()<<"parseContactJson Error";
        return false;
    }

}

//解析手机通话记录
bool ParseJson::parseRecondsJson(QJsonObject object)
{

    qDebug()<<"start parseRecondJson";

    signalCallhistoryInfo(object);

    return true;

//    QJsonValue ret_vaue = object.take("ret");
//    QJsonValue opetype_value = object.take("opType");
//    QString ret = ret_vaue.toString();
//    QString opetype = opetype_value.toString();
//    qDebug()<<ret<<opetype<<"result";

//    if(ret == "0")
//    {
//        QJsonArray  CallHistoryArray= object.take("callHistory").toArray();

//        int tag = CallHistoryArray.at(0).toInt();
//        qDebug() << "tag:" << tag;
//        for(int i = 0; i < CallHistoryArray.size(); i++)
//        {
//                QJsonObject json = CallHistoryArray.at(i).toObject();
//                QString destNum =  json.value("desNum").toString();
//                QString duration = json.value("duration").toString();
//                QString action = json.value("action").toString();
//                QString date = json.value("date").toString();

//                qDebug()<<"RecordInfo: "<<destNum <<duration <<action <<date<<"++++++=====";
//        }

//       return true;
//    }else
//    {
//        qDebug()<<"parseRecordJson Error";
//        return false;
//    }


}

//解析手机短信数据
bool ParseJson::parseMessageJson(QJsonObject object)
{

    qDebug()<<"start praseMessageJson";

    emit signalMessageInfo(object);


    QJsonValue ret_vaue = object.take("ret");
    QJsonValue opetype_value = object.take("opType");
    QString ret = ret_vaue.toString();
    QString opetype = opetype_value.toString();

    int type = opetype.toInt()+ '0' ;;

    qDebug()<<ret<<opetype<<type<<"result";

    return true;

//    if(type == MSG_USER_OPERATE_Message_Export_ALL)
//    {
//        emit  signalMessageExport(object);

//        return true;
//    }else
//    {
//        emit  signalMessageInfo(object);
//        return true;
//    }

//    if(ret == "0")
//    {
//        QJsonArray message= object.take("message").toArray();

//        int tag = message.at(0).toInt();
//        qDebug() << "tag:" << tag;
//        for(int i = 0; i < message.size(); i++)
//        {

//           QJsonObject json = message.at(i).toObject();
//          //QJsonObject message = object.take("message").toObject();

//           QString destnum = json.take("desNum").toString();
//           QString content = json.take("content").toString();
//           QString action = json.take("action").toString();
//           QString date = json.take("date").toString();


//           qDebug()<<"IphonContact:"<<destnum<<content <<action<<date<<"+++++++++";
//        }

//        return true;
//    }else
//    {
//        qDebug()<<"parseMessageJson Error";
//        return false;
//    }

}

bool ParseJson::parseMessageExport(QJsonObject object)
{
    qDebug()<<"start praseMessageJson export";

    emit signalMessageExport(object);

    return true;

}


//解析手机SD卡数据
bool ParseJson::parseSDDocument(QJsonObject object)
{
    qDebug()<<"start praseSDDocumentJson";

    signalFileInfo(object);

    QJsonValue ret_vaue = object.take("ret");
    QJsonValue opetype_value = object.take("opType");

    QString ret = ret_vaue.toString();
    QString opetype = opetype_value.toString();

    qDebug()<<ret<<opetype<<"result";

    if(ret == "0")
    {

        QJsonArray fileNameList= object.take("fileList").toArray();

        int tag = fileNameList.at(0).toInt();
        qDebug() << "tag:" << tag;
        for(int i = 0; i < fileNameList.size(); i++)
        {

           QJsonObject json = fileNameList.at(i).toObject();

           QString fileName = json.take("fileName").toString();

           //QString filename = json.take("fileName").toString();
           //QString filepath = json.take("filePath").toString();

           qDebug()<<"filename:"<<fileName<<"+++++++++";

           //qDebug()<<"filename:"<<filename<<filepath<<"+++++++++";
        }

        return true;
    }else
    {
        qDebug()<<"parseFileJson Error";
        return false;
    }

}

//解析图片信息
void ParseJson::transImage(QString rStr)
{

    //QByteArray read = file1.readAll();
    //qDebug()<<read.data()<<"+++";

    //QString rStr = QString::fromLatin1(read.data(), read.size());

    //qDebug()<<rStr<<"-----";

    qDebug()<<"Str:"<<"iiiiiiiiiiiiii";

    if(rStr != NULL)
    {

        QByteArray hexed = QByteArray::fromHex(rStr.toLatin1());

       qDebug()<<hexed.data()<<hexed.size();

       //QByteArray compressed = qUncompress(hexed);
       //QBuffer buffer(&compressed);

       QBuffer buffer(&hexed);
       buffer.open(QIODevice::ReadWrite);

       QImageReader reader(&buffer, "PNG");
       reader.setFormat("PNG");
       QImage image = reader.read();
       qDebug()<<reader.errorString()<<reader.error();

       QString saveFileName= QDir::currentPath();

       //AppList::IconSrcdate = saveFileName.append("/appIcon/").append(AppList::AppNameList.at(pngi)).append(".png");
       QString pathname = saveFileName.append("/AppIcon/").append(ParseJson::appname).append(".png");
       //QString name = QString("\"%1\"").arg(pathname);
       image.save(pathname);
       qDebug()<<pathname<<"kkkkkkk";

       emit signalpicture(pathname);

       qDebug()<<"emit .....";

       pngi++;
       qDebug()<<"Count:====="<<pngi;
    }else
    {
        pngi++;

        qDebug()<<"IconInfo is NULL";
    }

}

//Unicode转换为字符串编码
QString ParseJson::uniCodeToStr(const QByteArray &data)
{
    QByteArray data_1;

    for(int i= 0;i<data.length ();i+=2)
    {
        if(!(data[i] == 0x20 && data[i+1] == 0x20))
        {
            data_1.append (data[i]);
            data_1.append (data[i+1]);
        }
    }
    QString str = data_1.toHex ().data ();

    int temp[40000];

    QChar qchar[10000];
//    int temp[400];

//    QChar qchar[100];
    QString strOut;
    bool ok;
    int count=str.count();
    int len=count/4;
    for(int i=0;i<count;i+=4)
    {
         temp[i]=str.mid(i,4).toInt(&ok,16);//每四位转化为16进制整型
         qchar[i/4]=temp[i];
         QString str0(qchar, len);
         strOut=str0;
     }
     qDebug ()<<"unicode to string:"<<strOut;
     return strOut;

}

//解析APP列表
bool ParseJson::parseAppList(QJsonObject object)
{
    qDebug()<<"start parseAppList";
    QJsonValue ret_vaue = object.take("ret");
    QJsonValue opetype_value = object.take("opType");
    QString ret = ret_vaue.toString();
    QString opetype = opetype_value.toString();
    qDebug()<<ret<<"result";
    if(ret == "200")
    {
        QJsonArray  RightArray= object.take("appList").toArray();

        int tag = RightArray.at(0).toInt();
        qDebug() << "tag:" << tag;
        for(int i = 0; i < RightArray.size(); i++)
        {
                QJsonObject json = RightArray.at(i).toObject();
                QString appName =  json.value("appName").toString();
                QString packageName = json.value("packageName").toString();
                if(!json.value("packageName").toString().isEmpty()||!json.value("appName").toString().isEmpty())
                {
                    AppList::CheckAllApk++;
                    QStringList list = cmdData::selectWhitelist(RightInfoTransCode(packageName));
                    if(list.isEmpty())
                    {
                        AppList::AppPackageList.append(RightInfoTransCode(packageName));
                        AppList::AppNameList.append(RightInfoTransCode(appName));
                    }
                }
                qDebug()<<"RightInfo: "<<RightInfoTransCode(appName) <<RightInfoTransCode(packageName);

       }

       qDebug()<<AppList::AppPackageList.join(",")<<"";
       qDebug()<<AppList::AppNameList.join(",")<<"==+++==";

       /************************************************************/

       emit signalAppList(AppList::AppPackageList);

       qDebug()<<"emit list...";
       qDebug()<<"Package count:"<<AppList::AppPackageList.count()<<"==++==";
       qDebug()<<"APPName count:"<<AppList::AppNameList.count()<<"==++==";

       return true;
    }else
    {
        qDebug()<<"parseAppList Error";
        return false;
    }

}

void ParseJson::writeRightCong(QString package,QString ApkPremission)
{

    QFile Rightfile("../RightConfig.dat");

    Rightfile.open(QIODevice::WriteOnly|QIODevice::Text|QIODevice::Append);

    QString appname = package + ":" + "\n";

    Rightfile.write(appname.toStdString().c_str(),strlen(appname.toStdString().c_str()));

    QStringList right = ApkPremission.split(MSG_DATA_ITEMS_SEPARATOR);

    for(int i=0; i < right.count() - 1; i++)
    {
        QString item = QString::number(i+1)+":"+ right.at(i)+"\n";
        Rightfile.write(item.toStdString().c_str(),strlen(item.toStdString().c_str()));

    }

    Rightfile.close();

}

//bool ParseJson::parseRightJson(QJsonObject object)
//{

//    qDebug()<<"start parseRightJson";

//    emit singalSafeResult(object);
//    QJsonValue ret_vaue = object.take("ret");
//    QJsonValue opetype_value = object.take("opType");
//    QString ret = ret_vaue.toString();
//    //QString opetype = opetype_value.toString();
//    qDebug()<<ret<<"result";
//    if(ret == "0")
//    {
//        QJsonArray  RightArray= object.take("appList").toArray();

//        int tag = RightArray.at(0).toInt();
//        qDebug() << "tag:" << tag;
//        for(int i = 0; i < RightArray.size(); i++)
//        {
//                QJsonObject json = RightArray.at(i).toObject();
//                QString appName =  json.value("appName").toString();
//                QString packageName = json.value("packageName").toString();
//                QString versionName = json.value("versionName").toString();
//                QString codePath = json.value("codePath").toString();
//                QString sourceDir = json.value("codePath").toString();
//                QString iconContent = json.value("iconContent").toString();
//                QString MD5 = json.value("MD5").toString();
//                QString apkPermission = json.value("opPerssion").toString();

//                QJsonObject vInfojson = json.value("vInfo").toObject();

//                QString vNanme = vInfojson.value("vName").toString();
//                QString vType = vInfojson.value("vType").toString();
//                QString vDetail = vInfojson.value("vDetail").toString();
//                QString remark = vInfojson.value("remark").toString();

//                qDebug()<<vNanme<<"病毒";

//                //writeRightCong(json.value("packageName").toString(),json.value("opPerssion").toString());
//                if(!json.value("packageName").toString().isEmpty()||!json.value("appName").toString().isEmpty())
//                {
//                  AppList::AppPackageList.append(RightInfoTransCode(packageName));
//                  AppList::AppNameList.append(RightInfoTransCode(appName));
//                }
//                qDebug()<<"RightInfo: "<<RightInfoTransCode(appName) <<RightInfoTransCode(packageName)<<
//                          RightInfoTransCode(versionName) << RightInfoTransCode(codePath) << RightInfoTransCode(sourceDir)<<
//                          RightInfoTransCode(iconContent)<<RightInfoTransCode(MD5) <<RightInfoTransCode(apkPermission);
//       }

//       qDebug()<<AppList::AppPackageList.join(",")<<"+++++==++++";
//       qDebug()<<AppList::AppNameList.join(",")<<"==+++==";

//       /************************************************************/

//       emit singalAppList(AppList::AppNameList);

//       qDebug()<<"Package count:"<<AppList::AppPackageList.count()<<"======";
//       qDebug()<<"APPName count:"<<AppList::AppNameList.count()<<"+++++++++";

//       return true;
//    }else
//    {
//        qDebug()<<"parseRightJson Error";
//        return false;
//    }
//}
