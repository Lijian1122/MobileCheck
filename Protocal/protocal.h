#ifndef PROTOCAL_H
#define PROTOCAL_H

#include <QObject>
#include <QString>
#include <qmath.h>
#include <QtWidgets/QMessageBox>
#include <QDataStream>
#include <QByteArray>

/*开始结束位定义*/
#define MSG_BEGIN_BIT          '@'
#define MSG_END_BIT            '#'

/*信息序列定义*/
#define MSG_CAMMAND_ORDER_NONE 256     //2^8

/*信息长度定义*/
#define MSG_SIZE_NONE          270     //2^8 + 14
#define MSG_SIZE_BASIC         269     //MSG_BASIC_SIZE - 1

/*数据长度定义*/
#define MSG_DATA_SIZE_NONE      256     //2^8
#define MSG_DATA_SIZE_BASIC    0     //MSG_COUNT_BASIC - 1

/*数据内容定义*/
#define MSG_DATA_ORDER_SEPARATOR  " "
#define MSG_DATA_ITEMS_SEPARATOR  "|"
#define MSG_DATA_ITEMS_POINT  "."
//#define MSG_USER_OPERATE_Message_Export_ALL  "21"

/*校验位定义*/
#define MSG_CHECKOUT          '#'

/*命令定义*/

//具体操作
enum MSG_USER_OPERATE{
    MSG_USER_OPERATE_NONE = '0',
    MSG_USER_OPERATE_SD_Document = '1',
    MSG_USER_OPERATE_Message = '2',
    MSG_USER_OPERATE_Contact = '3',
    MSG_USER_OPERATE_Right= '4',
    MSG_USER_OPERATE_Message_Export_ALL= '5',
    MSG_USER_OPERATE_Detail= '6',
    MSG_USER_OPERATE_NetTCP= '7',
    MSG_USER_OPERATE_APPList = '8',
    MSG_USER_OPERATE_Records = '9',
    MSG_USER_OPERATE_IfConnect,
};

enum MSG_OPERATE_CMD{
    MSG_OPERATE_CMD_NONE = '0',
    MSG_OPERATE_CMD_ADD = '1',
    MSG_OPERATE_CMD_MODIF = '2',
    MSG_OPERATE_CMD_DELETE_ONE = '3',
    MSG_OPERATE_CMD_DELETE_ALL = '4',
    MSG_OPERATE_CMD_SELECT_ONE = '5',
    MSG_OPERATE_CMD_SELECT_ALL = '6'
};

class Protocal : public QObject
{
    Q_OBJECT

public:
    explicit Protocal(QObject *parent = 0);
    ~Protocal();

    void initMsgPackage();
    void clearMsgPackage();
    void printMsgInfo(void);

    void updataMsg(Protocal *m_protocal);
    QString updataMsg(quint16 useoperator,
                          quint16 operatecmd,int datasize,QString datadetail);


    QString packageMsg(void);
    void unpackageMsg(QDataStream &in);


    quint8 getBeginBit(void) const;
    void setBeginBit(const quint8 beginbit);
    quint16 getMsgOrder(void) const;
    void setMsgOrder(const quint16 msgorder);
    quint16 getMsgSize(void) const;
    void setMsgSize(const quint16 msgsize);
    quint16 getUserOperate(void) const;
    void setUserOperate(const quint16 useroperate);
    quint16 getOperateCmd(void) const;
    void setOperateCmd(const quint16 operatecmd);
    int getDataSize(void) const;
    void setDataSize(const int datasize);
    QString getDataDetail(void) const;
    void setDataDetail(const QString datadetail);
    quint8 getEndBit(void) const;
    void setEndBit(const quint8 endbit);


private:

    /*protocol detail*/
    quint8 m_BeginBit;      //'@'
    quint16 m_MsgOrder;      //
    quint16 m_MsgSize;      //
    quint16 m_UserOperate;   //
    quint16 m_OperateCmd;    //
    int m_DataSize;     //
    QString m_DataDetail;   //
    quint8 m_EndBit;        //'#'


signals:

public slots:


};

#endif // PROTOCAL_H
