#include "tcpthread.h"
#include <QtGui>
#include <QtNetwork>
#include <protocal.h>
#include <QApplication>
#include <QTcpSocket>
#include <QTextCodec>
#include <socket.h>

int TcpThread::time = 0;
int TcpThread::time2 = 0;


//构造函数完成简单的赋值/
//TcpThread::TcpThread(int socketDescriptor, QObject *parent):
//QThread(parent),socketDescriptor(socketDescriptor)
//{

//}

TcpThread::TcpThread(QObject *parent)
{
    tcpSocket = new QTcpSocket;
    connect(tcpSocket,SIGNAL(readyRead()),
                this,SLOT(readyToRead()));
}

TcpThread::~TcpThread()
{

    this->tcpSocket->deleteLater();
    quit();
    wait();
}

 //因为QT的线程的执行都是从run()开始，
 //所以在此函数里完成tcpsocket的创建，相关信号的绑定
void TcpThread::run()
{
    qDebug()<<"fefff";
    tcpSocket->connectToHost("127.0.0.1",12580);

    bytesReceived = 0;
    threadprotocal = new Protocal;
    threadparsejson = new ParseJson();

    qDebug()<<socketDescriptor;
//这是重中之重，必须加Qt::BlockingQueuedConnection！
//这里困扰了我好几天，原因就在与开始没加，默认用的Qt::AutoConnection。
//简单介绍一下QT信号与槽的连接方式： //Qt::AutoConnection表示系统自动选择相应的连接方式，如果信号与槽在同一线程，就采用Qt::DirectConnection，如果信号与槽不在同一线程，将采用Qt::QueuedConnection的连接方式。
//Qt::DirectConnection表示一旦信号产生，立即执行槽函数。
 //Qt::QueuedConnection表示信号产生后，将发送Event给你的receiver所在的线程，postEvent(QEvent::MetaCall,...)，slot函数会在receiver所在的线程的event loop中进行处理。
//Qt::BlockingQueuedConnection表示信号产生后调用sendEvent(QEvent::MetaCall,...),在receiver所在的线程处理完成后才会返回;只能当sender,receiver不在同一线程时才可以。
//Qt::UniqueConnection表示只有它不是一个重复连接，连接才会成功。如果之前已经有了一个链接（相同的信号连接到同一对象的同一个槽上），那么连接将会失败并将返回false。
//Qt::AutoCompatConnection与QT3保持兼容性
//说明一下，对于任何的QThread来说，其线程只存在于run()函数内，其它的函数都不在线程内，所以此处要采用Qt::BlockingQueuedConnection，
//因为当SOCKET有数据到达时就会发出readyRead()信号，但是此时可能之前的receiveFile()还未执行完毕，之前使用的Qt::AutoConnection，
//结果传输大文件的时候就会出错，原因就在于只要有数据到达的时候，就会连接信号，但是数据接收还没处理完毕，而Qt::BlockingQueuedConnection会阻塞
//此连接，直到receiveFile()处理完毕并返回后才发送信号。

// connect(tcpSocket, SIGNAL(readyRead()),
// this, SLOT(receiveFile()),Qt::BlockingQueuedConnection);


  //定时器定时发送判断服务器是否连接
   timer = new QTimer;

   timer->setInterval(5000);
   timer->start();
   connect(timer,SIGNAL(timeout()),this,SLOT(timedone()),Qt::DirectConnection);

   connect(this, SIGNAL(finished()),
   this, SLOT(deleteLater()));

   connect(this,SIGNAL(sendIfConnect(int,quint16,int,QString)),this,SLOT(slotsendInfo(int,quint16,int,QString)));

   connect(tcpSocket,SIGNAL(readyRead()),
               this,SLOT(readyToRead()));

   connect(this,SIGNAL(singalJson(QByteArray)),threadparsejson,SLOT(parseJsonSlot(QByteArray)));

   //initAllConnect();


   exec();

   qDebug()<<"timer start";

}

void TcpThread::timedone()
{
    qDebug()<<"emit timeimit";

    time = 0;

    emit sendIfConnect(10,MSG_OPERATE_CMD_NONE,0,NULL);

    qDebug()<<"emit 123";
}

bool TcpThread::linkServer()
{
    qDebug()<<"Link.....";

    initAllConnect();

    qDebug()<<"234+++";

    //tcpSocket->abort();

    //tcpSocket->connectToHost("127.0.0.1",12580);

    qDebug()<<12345;

    if(!tcpSocket->waitForConnected(50000))
    {
        qDebug()<<"Connected Error";
        return false;

    }else
    {

       return true;
    }

}

void TcpThread::breakServer()
{
    tcpSocket->close();
}

void TcpThread::initAllConnect(void)
{

   connect(tcpSocket,SIGNAL(readyRead()),
            this,SLOT(readyToRead()));

   qDebug()<<9876;
}

void TcpThread::readyToRead()
{
    //qDebug()<<"read msg";
    reviceIfConnection();
    //receiveFile();
}

void TcpThread::slotsendInfo(int useroperate,quint16 operatecmd,int datasize,QString datadetail)
{

//    if(this->linkServer())
//    {

//      qDebug()<<"Link Server";

      QString msg;
      msg.append(QString::number(10)).append(MSG_DATA_ITEMS_SEPARATOR).append(MSG_OPERATE_CMD_NONE);
      qDebug()<<msg<<"++++===";

      sendCheckConn(10,MSG_OPERATE_CMD_NONE,msg.size(),msg);

      qDebug()<<"12345 link scussful";

//    }else
//    {
//        qDebug()<<"Server Conn Filed";
//    }

}

void TcpThread::sendCheckConn(int useroperate,quint16 operatecmd,
                   int datasize,QString datadetail)
{


     QString send = threadprotocal->updataMsg(
                useroperate,operatecmd,
                datasize, datadetail);
     qDebug()<<threadprotocal->getDataDetail();
     qDebug()<<threadprotocal->getDataSize();


     QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");

     QString SendMsg = utf8->toUnicode(send.toUtf8());  // gbk  convert utf8

     qDebug()<<SendMsg;

     tcpSocket->write(SendMsg.toStdString().c_str(),strlen(SendMsg.toStdString().c_str())); //发送

     qDebug()<<"send infomation scussfull";

}

void TcpThread::reviceIfConnection()
{

    //qDebug()<<6668888;

    tcpSocket->setSocketOption(
                   QAbstractSocket::ReceiveBufferSizeSocketOption,
                   1024*1024*1024);
    tcpSocket->setReadBufferSize(1024*1024*1024);
    //int MAX_BUFFER_SIZE = 1024*100;

    QByteArray MsgSize;
    QByteArray RecMsg;
    int ReciveSize;

    if(time == 0)
    {
        MsgSize = tcpSocket->read(10);

        QString msg = MsgSize.data();

         ReciveSize = msg.toInt();

        qDebug()<<msg<<""<<ReciveSize<<"++++接收长度+++++";

        if(ReciveSize == 0)
        {
            return;
        }

        time = time + 1;
   }
   if(tcpSocket->bytesAvailable()< ReciveSize) //如果数据没有接收完全，则继续接收数据
   {
        return;

   }

   RecMsg = tcpSocket->read(ReciveSize);
   time= 0;

   QString msg = RecMsg.data();
   qDebug()<<msg<<"-----";
   singalJson(RecMsg);

   RecMsg = "";

}
void TcpThread::receiveFile()
{

  //将tcpsocket封装到QDataStream里，便于使用操作符>>
  QDataStream in(tcpSocket);
  if(bytesReceived < sizeof(qint32))
  {

    //先接收32bit的文件大小
    if(tcpSocket->bytesAvailable() >= sizeof(qint32))
    {

      in.setByteOrder(QDataStream::LittleEndian); //必须的,因为发送端为LINUX系统

      in>>TotalBytes;

      TotalBytes += 4;
      qDebug()<<TotalBytes;

      bytesReceived += sizeof(qint32);

      fileName = tcpSocket->peerAddress();
      quint16 port = tcpSocket->peerPort();
      localFile = new QFile(fileName.toString()+(tr(".%1").arg(port))); //用户端的IP地址作为保存文件名
     if(!localFile->open(QFile::WriteOnly ))

     {

     }
   }

 }

 //如果读取的文件小于文件大小就继续读
  if (bytesReceived < TotalBytes){
  byteToRead = tcpSocket->bytesAvailable();
  bytesReceived += byteToRead;
  inBlock = tcpSocket->readAll();

  qDebug()<<"bytesReceived is:"<<bytesReceived;
     localFile->write(inBlock);
  inBlock.resize(0);
  }

  emit bytesArrived(bytesReceived,TotalBytes,socketDescriptor);

  if (bytesReceived == TotalBytes)
  {

    localFile->close();
    qDebug()<<bytesReceived;

  //emit finished();

  QApplication::restoreOverrideCursor();
  }

}
