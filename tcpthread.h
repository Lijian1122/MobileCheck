#ifndef TCPTHREAD_H
#define TCPTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QtNetwork>
#include <QTimer>
#include <protocal.h>
#include <parseJson/parsejson.h>

class TcpThread : public QThread
{
    Q_OBJECT
public:
    //TcpThread();
    TcpThread(QObject *parent = 0);

    void run();

   ~TcpThread();

    bool linkServer(void);

    void breakServer();

    void initAllConnect(void);

    void sendCheckConn(int useroperate,quint16 operatecmd,
                       int datasize,QString datadetail);

    void reviceIfConnection();

    ParseJson *threadparsejson;
    QTcpSocket *tcpSocket;


signals:

   void error(QTcpSocket::SocketError socketError);
   void sendIfConnect(int useroperate,quint16 operatecmd,
                      int datasize,QString datadetail);
   void bytesArrived(qint64,qint32,int);

   void singalJson(QByteArray);



public slots:
   void receiveFile();

   void slotsendInfo(int,quint16,int,QString);

   void timedone();

   void readyToRead();

private:
   int socketDescriptor;
   qint64 bytesReceived; //收到的总字节
   qint64 byteToRead; //准备读取的字节
   qint32 TotalBytes; //总共传输的字节

   QHostAddress fileName; //文件名
   QFile *localFile;
   QByteArray inBlock; //读取缓存
   QTimer *timer;

   Protocal  *threadprotocal;


   static int time;
   static int time2;

};

#endif // TCPTHREAD_H
