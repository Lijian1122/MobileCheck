#ifndef EXECUTECMD_H
#define EXECUTECMD_H

#include <QObject>
#include "protocal.h"

class executecmd : public QObject
{
    Q_OBJECT
public:
    explicit executecmd(QObject *parent = 0);   
    ~executecmd();
    void  execUserCommand(Protocal *protocol);

private:

    Protocal  *m_protocol;

    /*
      * 执行操作
     **/

     void execUserOperate(void);

     /*执行类别操作命令*/
     void execUserOperate_Login(void);
     void execUserOperate_UserManage(void);
     void execUserOperate_WhiteManage(void);
     void execUserOperate_Right(void);
     void execUserOperate_Vrius(void);
     void execUserOperate_Datail(void);
     void execUserOperate_NetTCP(void);



     //执行具体操作命令
     void execUserOperate_Login_CMD_None(void);
     void execUserOperate_Login_CMD_SELETE_ONE(void);


     void execUserOperate_UserManage_CMD_None(void);
     void execUserOperate_UserManage_CMD_ADD(void);
     void execUserOperate_UserManage_CMD_MODIF(void);
     void execUserOperate_UserManage_CMD_DELETE_ONE(void);
     void execUserOperate_UserManage_CMD_DELETE_ALL(void);
     void execUserOperate_UserManage_CMD_SELETE_ONE(void);
     void execUserOperate_UserManage_CMD_SELETE_ALL(void);

     void execUserOperate_Right__CMD_None(void);
     void execUserOperate_Right_CMD_SELETE_ALL(void);

     void execUserOperate_Vrius__CMD_None(void);
     void execUserOperate_Vrius_CMD_SELETE_ALL(void);

     void execUserOperate_Datail__CMD_None(void);
     void execUserOperate_Datail_CMD_SELETE_ALL(void);

     void execUserOperate_NetTCP__CMD_None(void);
     void execUserOperate_NetTCP_CMD_SELETE_ALL(void);


     void printErrorInfo(QString msg);


};

#endif // EXECUTECMD_H
