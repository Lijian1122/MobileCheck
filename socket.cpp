#include "socket.h"
#include "QDebug"
#include <adb.h>
#include <QDataStream>
#include <QTextCodec>
#include <Common/applist.h>
#include <tcpthread.h>


extern QString ServerIP;
QString  Socket::m_type;
QTcpSocket *Socket::m_tcpsocket;
Socket::Socket()
{
    m_tcpsocket = new QTcpSocket;
    m_protocal = new Protocal;
    m_executecmd = new executecmd;
    m_parsejson = new ParseJson;

    connect(this,SIGNAL(singalJson(QByteArray)),m_parsejson,SLOT(parseJsonSlot(QByteArray)));

}

Socket::~Socket()
{

}
bool Socket::linkServer(void)
{
    qDebug()<<"Link.....";
    initAllConnect();

    qDebug()<<"234+++";

    m_tcpsocket->connectToHost("127.0.0.1",12580);

    qDebug()<<12345;

    if(!m_tcpsocket->waitForConnected(50000))
    {
        qDebug()<<"Connected Error";
        return false;

    }else
    {
       return true;
    }

}

void Socket:: breakServer()
{
    m_tcpsocket->close();
}

void Socket::initAllConnect(void)
{

   connect(m_tcpsocket,SIGNAL(readyRead()),
            this,SLOT(readyToRead()));

   qDebug()<<9876;
}
void Socket::readyToRead()
{
    qDebug()<<"hhtehh";
    recvMsg();
}

void Socket::CheckIfConnection()
{

    qDebug()<<"thread..";


    TcpThread *thread = new TcpThread(this);

    //Demo *newDemo = new Demo；
    //QThread *thread = new QThread;

    //threaddemo->moveToThread(thread);

    //将线程结束信号与线程的deleteLater槽关联
    //connect(thread, SIGNAL(finished()),
    //thread, SLOT(deleteLater()));

    //关联相应的UI更新槽
    //connect(thread,SIGNAL(bytesArrived(qint64,qint32,int)),
    //this,SIGNAL(bytesArrived(qint64,qint32,int)));

    //QT的线程都是从start开始，调用run()函数

    //connect(thread,SIGNAL(sendIfConnect(quint16,quint16,int,QString)),this,SLOT());

    thread->start();
    //thread->run();

    qDebug()<<"thread start ...";


}

//处理子线程发来的信号
void Socket::readIfConnct(quint16 useroperate,quint16 operatecmd,
                  int datasize,QString datadetail)
{
    sendMsg(useroperate,operatecmd,datasize,datadetail);
}


void Socket::sendMsg(std::string msg)
{

//    QString messg;
//    messg = QString::fromStdString(msg);

//    qDebug()<<messg;



//    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");

//    QString SendMsg = utf8->toUnicode(messg.toUtf8());  // gbk  convert utf8

//    //m_tcpsocket->waitForBytesWritten();

//    m_tcpsocket->write(SendMsg.toStdString().c_str(),strlen(SendMsg.toStdString().c_str())); //发送


//    QDataStream out(&buffer,QIODevice::ReadWrite);
//    out.setVersion(QDataStream::Qt_5_5);

    //设置发送长度初始值为0
    //out<<(quint16)0;

    //回到字节流起始位置
    //out.device()->seek(0);
    //重置字节流长度
    //out<<buffer.size();
    //out <<(quint16)(buffer.size()-sizeof(quint16));

    //qDebug()<<"++++"<<QString(buffer);

    //往套接字缓存中写入数据，并发送
    //m_tcpsocket->write(buffer);

    qDebug()<<666;


    //m_tcpsocket->write(msg,msg.length());

}

void Socket::sendMsg(quint16 useroperate,quint16 operatecmd,
                    int datasize,QString datadetail)
{

    QString send = m_protocal->updataMsg(
                useroperate,operatecmd,
                datasize, datadetail);
    qDebug() << m_protocal->getDataDetail();
    qDebug()<<m_protocal->getDataSize();


    QTextCodec *utf8 = QTextCodec::codecForName("UTF-8");

    QString SendMsg = utf8->toUnicode(send.toUtf8());  // gbk  convert utf8

    qDebug()<<SendMsg;

    //m_tcpsocket->write(*buffer);

    //m_tcpsocket->waitForBytesWritten();

    m_tcpsocket->write(SendMsg.toStdString().c_str(),strlen(SendMsg.toStdString().c_str())); //发送

    qDebug()<<666;

}

void Socket::recvMsg(void)
{

    m_tcpsocket->setSocketOption(
                   QAbstractSocket::ReceiveBufferSizeSocketOption,
                   1024*1024*1024);
    m_tcpsocket->setReadBufferSize(1024*1024*1024);
//    int MAX_BUFFER_SIZE = 1024*100;
//    qDebug()<<"7788";


//    QDataStream in(m_tcpsocket);
//    in.setVersion(QDataStream::Qt_5_5);  //设置数据流版本

//    int blockSize = 0;  //如果刚开始接收数据


//    if(blockSize == 0)
//    {
//        if(m_tcpsocket->bytesAvailable() < int(sizeof(qint16)))
//            return;
//        in>>blockSize;
//    }
//    if(m_tcpsocket->bytesAvailable()<blockSize)
//    {
//           //如果没有数据则返回
//            return ;
//    }
//    in>>message;

//    if(m_tcpsocket->bytesAvailable()<(int)sizeof(quint16))
//    {
//         //如果没有数据则返回
//          return ;
//    }
//    in>>blockSize;
//    qDebug()<<message<<"收到消息";
     QByteArray MsgSize;
     QByteArray RecMsg;

     if(AppList::number == 0)
     {
        MsgSize = m_tcpsocket->read(10);

        QString msg = MsgSize.data();

        ReciveSize = msg.toInt();

        qDebug()<<msg<<""<<ReciveSize<<"++++接收长度+++++";

        if(ReciveSize == 0)
        {
            return;
        }

        AppList::number = AppList::number + 1;
     }
     if(m_tcpsocket->bytesAvailable()< ReciveSize) //如果数据没有接收完全，则继续接收数据
     {
         return;
         //RecMsg.append(m_tcpsocket->readAll());
     }


     RecMsg = m_tcpsocket->read(ReciveSize);


//     if(ReciveSize > 100000)
//     {
//         m_tcpsocket->waitForReadyRead(5000);
//         //m_tcpsocket->waitForReadyRead(1000);
//     }
     //m_tcpsocket->waitForReadyRead(10000000);
     //m_tcpsocket->waitForReadyRead(10000);
     AppList::number = 0;

     QString msg = RecMsg.data();
     qDebug()<<msg<<"-----";
     singalJson(RecMsg);

     RecMsg = "";

//     if(m_tcpsocket->bytesAvailable()< 9580) //如果数据没有接收完全，则继续接收数据

//      return;

//       while(m_tcpsocket->bytesAvailable())
//       {


     //m_tcpsocket->waitForReadyRead(100000);

//     RecMsg = m_tcpsocket->read(ReciveSize);
//     if(m_tcpsocket->bytesAvailable() <  )
//     {

//       RecMsg = m_tcpsocket->read(ReciveSize);

//                RecMsg.append(m_tcpsocket->read(MAX_BUFFER_SIZE));
//     }
//      else
//      {

//             RecMsg = m_tcpsocket->readAll();

//             // RecMsg.append(m_tcpsocket->readAll());

//      }
 //      }
//       }
//    if(m_tcpsocket->bytesAvailable()< 28068) //如果数据没有接收完全，则继续接收数据
//    {
//        return;
//    }

//     long mm =  RecMsg.length();
//     qDebug()<<"接受数据长度"<<mm;

//    if(RecMsg.size() != 0 )
//    {
//        QString msg = RecMsg.data();
//        qDebug()<<msg<<"-----";
//        singalJson(RecMsg);
//    }

//    m_tcpsocket->waitForReadyRead(100000);
    return;
}
