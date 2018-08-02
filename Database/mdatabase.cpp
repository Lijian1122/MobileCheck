#include "mdatabase.h"
#include <QSqlError>
#include <QDebug>
#include <QSqlDriverPlugin>
#include <QtSql/QSqlDriver>
#include <QStringList>
#include <QSqlQuery>
#include <QSettings>

mDatabase::mDatabase(QObject *parent) : QObject(parent)
{

}

void mDatabase::readSqlConfg()
{
     QString str = "Sqlconfig.ini";
     QSettings *configIniRead = new QSettings(str, QSettings::IniFormat);
     //将读取到的ini文件保存在QString中，先取值，然后通过toString()函数转换成QString类型

     localhost = configIniRead->value("/Localhost/localhost").toString();
     port = configIniRead->value("/Port/port").toInt();
     username = configIniRead->value("/User/UserName").toString();
     password = configIniRead->value("/User/Password").toString();
     database = configIniRead->value("/Database/database").toString();

     //打印得到的结果
     qDebug() << localhost;
     qDebug() << port;
     qDebug() << username;
     qDebug() << password;
     qDebug() << database;

    //读入入完成后删除指针
    delete configIniRead;
}

bool mDatabase::createConnection()
{
    qDebug() << QSqlDatabase::drivers();

    readSqlConfg();

    QSqlDatabase data_base = QSqlDatabase::addDatabase("QMYSQL");
//    data_base.setHostName("localhost");  //设置主机地址
//    data_base.setPort(3306);  //设置端口
//    data_base.setDatabaseName("dbmobile");  //设置数据库名称
//    data_base.setUserName("root");  //设置用户名
//    data_base.setPassword("ROOT");  //设置密码

    data_base.setHostName(localhost);  //设置主机地址
    data_base.setPort(port);  //设置端口
    data_base.setDatabaseName(database);  //设置数据库名称
    data_base.setUserName(username);  //设置用户名
    data_base.setPassword(password);  //设置密码

    if(!data_base.open())
    {
        qCritical("Can't open database: %s(%s)",
                  data_base.lastError().text().toLocal8Bit().data(),
                  qt_error_string().toLocal8Bit().data());
        qDebug() << "Can't open database";
        return false;
    }else
    {
        qDebug()<<"successful";
    }
    return true;
}
void mDatabase::select()
{
    QString select_all_sql = "select * from provider";

    //查询所有数据
    QSqlQuery sql_query;
    sql_query.prepare(select_all_sql);
    if(!sql_query.exec())
    {
        qDebug()<<sql_query.lastError();
    }
    else
    {
        while(sql_query.next())
        {
            int id = sql_query.value(0).toInt();
            QString templ_name = sql_query.value(1).toString();
            qDebug()<<QString("Id:%1     Templ Name:%2").arg(id).arg(templ_name);
        }
    }

}
void mDatabase::closeConnection(QSqlDatabase db)
{
    db.close();
}
