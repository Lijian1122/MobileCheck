#include "executecmd.h"
#include <QDebug>

executecmd::executecmd(QObject *parent) : QObject(parent)
{
    m_protocol = new Protocal;
}

executecmd::~executecmd()
{
}

void executecmd::execUserCommand(Protocal *protocol)
{
    m_protocol = protocol;

    qDebug()<<2334;
}

void executecmd::execUserOperate(void)
{
   switch (m_protocol->getUserOperate())
   {

//      case MSG_USER_OPERATE_LOGIN: execUserOperate_Login(); break;
//      case MSG_USER_OPERATE_UserManage: execUserOperate_UserManage(); break;
//      case MSG_USER_OPERATE_WhiteManage: execUserOperate_WhiteManage(); break;
      case MSG_USER_OPERATE_Right: execUserOperate_Right(); break;
//      case MSG_USER_OPERATE_Virus: execUserOperate_Vrius(); break;
      case MSG_USER_OPERATE_Detail: execUserOperate_Datail(); break;
      case MSG_USER_OPERATE_NetTCP: execUserOperate_NetTCP();break;

   }
   qDebug()<<"hhhhhhhhhh";

}

/*执行类别操作命令*/


void executecmd::execUserOperate_Right(void)
{
    switch(m_protocol->getOperateCmd())
    {
       case MSG_OPERATE_CMD_NONE: execUserOperate_Right__CMD_None(); break;
       case MSG_OPERATE_CMD_SELECT_ALL: execUserOperate_Right_CMD_SELETE_ALL(); break;
    }

    qDebug()<<"operate right";

}

void executecmd::execUserOperate_Vrius(void)
{
    switch(m_protocol->getOperateCmd())
    {
       case MSG_OPERATE_CMD_NONE: execUserOperate_Vrius__CMD_None(); break;
       case MSG_OPERATE_CMD_SELECT_ALL: execUserOperate_Vrius_CMD_SELETE_ALL(); break;
    }

    qDebug()<<"operate Vrius";

}

void executecmd::execUserOperate_Datail(void)
{
    switch(m_protocol->getOperateCmd())
    {
       case MSG_OPERATE_CMD_NONE: execUserOperate_Datail__CMD_None(); break;
       case MSG_OPERATE_CMD_SELECT_ALL: execUserOperate_Datail_CMD_SELETE_ALL(); break;
    }

    qDebug()<<"operate Vrius";

}

void executecmd::execUserOperate_NetTCP(void)
{
    switch(m_protocol->getOperateCmd())
    {
       case MSG_OPERATE_CMD_NONE: execUserOperate_NetTCP__CMD_None(); break;
       case MSG_OPERATE_CMD_SELECT_ALL: execUserOperate_NetTCP_CMD_SELETE_ALL(); break;
    }

    qDebug()<<"operate Vrius";

}
void executecmd::execUserOperate_Login(void)
{

}

void executecmd::execUserOperate_UserManage(void)
{

}

void executecmd::execUserOperate_WhiteManage(void)
{

}





//执行具体操作命令
void executecmd::execUserOperate_Login_CMD_None(void)
{

}

void executecmd::execUserOperate_Login_CMD_SELETE_ONE(void)
{

}


void executecmd::execUserOperate_UserManage_CMD_None(void)
{

}

void executecmd::execUserOperate_UserManage_CMD_ADD(void)
{

}

void executecmd::execUserOperate_UserManage_CMD_MODIF(void)
{

}

void executecmd::execUserOperate_UserManage_CMD_DELETE_ONE(void)
{

}

void executecmd::execUserOperate_UserManage_CMD_DELETE_ALL(void)
{

}

void executecmd::execUserOperate_UserManage_CMD_SELETE_ONE(void)
{

}

void executecmd::execUserOperate_UserManage_CMD_SELETE_ALL(void)
{

}



void executecmd::execUserOperate_Right__CMD_None(void)
{

}

void executecmd::execUserOperate_Right_CMD_SELETE_ALL(void)
{

}



void executecmd::execUserOperate_Vrius__CMD_None(void)
{

}

void executecmd::execUserOperate_Vrius_CMD_SELETE_ALL(void)
{

}
void executecmd::execUserOperate_Datail__CMD_None(void)
{

}

void executecmd::execUserOperate_Datail_CMD_SELETE_ALL(void)
{

}


void executecmd::execUserOperate_NetTCP__CMD_None(void)
{

}

void executecmd::execUserOperate_NetTCP_CMD_SELETE_ALL(void)
{

}
void executecmd::printErrorInfo(QString msg)
{

}
