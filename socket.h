#ifndef SOCKET_H
#define SOCKET_H

#include <QObject>
#include <QTcpSocket>
#include <string>
#include <QByteArray>
#include <QProgressBar>
#include <QWidget>
#include "protocal.h"
#include "executecmd.h"
#include "parseJson/parsejson.h"

static QByteArray buffer;
//static int number = 0;
struct mobile
{
   QString type;
   QString name;
};

class Socket : public QObject
{
    Q_OBJECT
public:
    Socket();
    ~Socket();

    bool linkServer(void);
    void breakServer();

    void initAllConnect(void);

    void sendMsg(std::string msg);
    void recvMsg(void);


    void sendMsg(quint16 useroperate,quint16 operatecmd,
                        int datasize,QString datadetail);


    void CheckIfConnection();

//    static void setMobileType(QString type);
//    static QString getMobileType();
    ParseJson *m_parsejson;

    static QTcpSocket *m_tcpsocket;

signals:

   void signaltype(mobile m_mobile);
   void singalJson(QByteArray m_message);

public slots:
   void readyToRead();

   void readIfConnct(quint16 useroperate,quint16 operatecmd,
                     int datasize,QString datadetail);


private:


    quint16 blockSize; //存放文件的大小信息
    static QString m_type;
    QString message;

    int ReciveSize;

    mobile m_mobile;

    Protocal  *m_protocal;
    executecmd  *m_executecmd;

};

#endif // SOCKET_H
