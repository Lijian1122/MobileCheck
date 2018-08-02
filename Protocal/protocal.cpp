#include "protocal.h"
#include <QString>
#include <QDebug>

Protocal::Protocal(QObject *parent) : QObject(parent)
{

}

Protocal::~Protocal()
{

}
void Protocal::initMsgPackage()
{
    clearMsgPackage();

}

void Protocal::clearMsgPackage()
{
    m_BeginBit = MSG_BEGIN_BIT;
    m_MsgOrder = MSG_CAMMAND_ORDER_NONE;
    m_MsgSize = MSG_DATA_SIZE_NONE;
    m_UserOperate = MSG_USER_OPERATE_NONE;
    m_OperateCmd = MSG_OPERATE_CMD_NONE;
    m_DataSize = MSG_DATA_SIZE_NONE;
    m_DataDetail.clear();
    //m_CheckoutBit = MSG_CHECKOUT;
    m_EndBit = MSG_END_BIT;

}

void Protocal::printMsgInfo(void)
{

    qDebug()<<"aduprotocol::prinMsginfo==========";
    qDebug()<<"aduprotocol::BeginBit"<<m_BeginBit;
    qDebug()<<"aduprotocol::MsgOrder"<<m_MsgOrder;
    qDebug()<<"aduprotocol::MsgSize"<<m_MsgSize;
    qDebug()<<"aduprotocol::UserOperate"<<m_UserOperate;
    qDebug()<<"aduprotocol::OperateCmd"<<m_OperateCmd;
    qDebug()<<"aduprotocol::DataSize"<<m_DataSize;
    qDebug()<<"aduprotocol::DataDetail"<<m_DataDetail;
    qDebug()<<"aduprotocol::EdnBit"<<m_EndBit;
    //qDebug()<<"aduprotocol::CheckoutBit"<<m_CheckoutBit;
}

void Protocal::updataMsg(Protocal *m_protocal)
{
    m_BeginBit = m_protocal->getBeginBit();
    m_MsgOrder = m_protocal->getMsgOrder();
    m_MsgSize = m_protocal->getMsgSize();
    m_UserOperate = m_protocal->getUserOperate();
    m_OperateCmd = m_protocal->getOperateCmd();

    m_DataSize = m_protocal->getDataSize();
    m_DataDetail.clear();
    m_DataDetail.append(m_protocal->getDataDetail());
    m_EndBit = m_protocal->getEndBit();

}


QString Protocal::updataMsg(quint16 useroperat,
                     quint16 operatecmd,
                      int datasize,QString datadetail)
{

    m_BeginBit = MSG_BEGIN_BIT;
    m_MsgOrder = MSG_CAMMAND_ORDER_NONE;
    m_MsgSize = MSG_SIZE_BASIC + datasize;
    m_UserOperate = useroperat;
    m_OperateCmd = operatecmd;
    m_DataSize = MSG_DATA_SIZE_BASIC + datasize;
    m_DataDetail.clear();
    m_DataDetail.append(datadetail);

    m_EndBit = MSG_END_BIT;

    return packageMsg();
}

QString Protocal::packageMsg(void)
{

    //QByteArray *buffer = new QByteArray;
    //QDataStream out(buffer,QIODevice::WriteOnly);
    //out.setVersion(QDataStream::Qt_5_5);


    QString send;
    QString size = QString::number(m_DataSize);
    send.append(m_BeginBit).append(MSG_DATA_ITEMS_SEPARATOR).
        append(size).append(MSG_DATA_ITEMS_SEPARATOR).append(m_DataDetail).append(MSG_DATA_ITEMS_SEPARATOR).append(m_EndBit);

    qDebug()<<send;

    return send;
}

void Protocal::unpackageMsg(QDataStream &in)
{
    in>>m_BeginBit;
    in>>m_MsgOrder;
    in>>m_MsgSize;

    in>>m_UserOperate;
    in>>m_OperateCmd;
    in>>m_DataSize;
    in>>m_DataDetail;

    in>>m_EndBit;

}


quint8 Protocal::getBeginBit(void) const
{
    return m_BeginBit;

}
void Protocal::setBeginBit(const quint8 beginbit)
{
    m_BeginBit = beginbit;
}

quint16 Protocal::getMsgOrder(void) const
{
    return m_MsgOrder;
}

void Protocal::setMsgOrder(const quint16 msgorder)
{
    m_MsgOrder = msgorder;
}

quint16 Protocal::getMsgSize(void) const
{
    return m_MsgSize;
}
void Protocal::setMsgSize(const quint16 msgsize)
{
    m_MsgSize = msgsize;

}

quint16 Protocal::getUserOperate(void) const
{
    return m_UserOperate;

}
void Protocal::setUserOperate(const quint16 useroperate)
{
    m_UserOperate = useroperate;
}

quint16 Protocal::getOperateCmd(void) const
{
    return m_OperateCmd;
}
void Protocal::setOperateCmd(const quint16 operatecmd)
{
    m_OperateCmd = operatecmd;
}
int Protocal::getDataSize(void) const
{
     return m_DataSize;
}

void Protocal::setDataSize(const int datasize)
{
     m_DataSize = datasize;
}

QString Protocal::getDataDetail(void) const
{
    return m_DataDetail;

}

void Protocal::setDataDetail(const QString datadetail)
{
    m_DataDetail = datadetail;
}


quint8 Protocal::getEndBit(void) const
{
    return m_EndBit;
}
void Protocal::setEndBit(const quint8 endbit)
{
    m_EndBit = endbit;
}
