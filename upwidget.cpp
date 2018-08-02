#include "upwidget.h"
#include <QRect>
#include <mybutton.h>
#include <qwidget.h>
#include <QAction>
#include <QMenu>
#include <QMessageBox>
#include <QIcon>
//#include <msgbox.h>
#include <loginwidget.h>
#include <mdatabase.h>
#include <protocal.h>
#include <applist.h>


QString upwidget::Oldpass;
QString upwidget::NewPass;
QString upwidget::ReNewpass;

upwidget::upwidget(QWidget *parent) : QWidget(parent)
{
    setAttribute(Qt::WA_TranslucentBackground,true);
    setWindowFlags(Qt::FramelessWindowHint);
    setMinimumHeight(130);
    setMaximumHeight(130);
    //setMaximumHeight(130);
    //resize(1290,130);
    resize(1360,130);

    //qDebug()<<this->width()<<"MAX____";

    //isMax_ = false; //窗口正常化

    //menubuttonaction();

    //connect(m_maxbtn,SIGNAL(clicked()),this,SLOT(slotShowMaxRestore()));
    //maxsize();
    setwidgetshow();
    wide = this->width() - 165;
    setwidgetLayout();

    //m_closebtn->setDefault(false);

    m_homepagebtn->setFocus();

    connect(m_homepagebtn,SIGNAL(clicked()),this,SLOT(slotIconHome()));


}
void upwidget::paintEvent(QPaintEvent *event)
{

    QPainter painter(this);
    painter.setBrush(QColor(0, 85, 0));
    //painter.setBrush(QColor(255, 255, 255));
    painter.setPen(Qt::NoPen);
     //painter.drawRect(QRect::QRect(this->maximumWidth(),this->minimumHeight()));
    //painter.drawRect(this->rect());
    painter.drawRect(QRect::QRect(0,0,this->width(),this->height()));

    //setwidgetshow();
    //setwidgetLayout();

    if(!this->isMaximized())
    {

        //qDebug()<<this->width()<<"MAX++++";
        //mainlayout->setMargin(5);
        //this->resize(this->maximumWidth(),this->height());
        setGeometry(0,0,this->maximumWidth(),this->height());
        setwidgetshow();
        setwidgetLayout();
        //upwidget();
        //winbuttonlayout->setGeometry(QRect((this->maximumWidth()-165),0,155,25));
    }
}

void upwidget::setwidgetshow()
{

//    m_closebtn = new QPushButton(this);
//    m_closebtn->setFixedSize(31,25);
//    m_closebtn->setStyleSheet("background-image:url(:/skin/source/icon/close.png);background-color:transparent;");

    m_closebtn = new ButtonFour(":/skin/source/icon1/close.png",this);
    m_closebtn->setFixedSize(29,24);

//    m_maxbtn = new checkButton(":/skin/source/icon/Btn_MainForm_Max.png",this);
//    m_closebtn->setFixedSize(29,24);

    m_minbtn = new ButtonFour(":/skin/source/icon1/min.png",this);
    m_minbtn->setFixedSize(29,24);

    m_menubtn = new ButtonFour(":/skin/source/icon1/menu.png",this);
    m_menubtn->setFixedSize(29,24);

//    m_menubtn = new QPushButton(this);
//    m_menubtn->setFixedSize(29,24);
//    m_menubtn->setStyleSheet("background-image:url(:/source/icon1/567.jpg);background-color:transparent;QPushButton::menu-indicator{image:none;}");

   if(AppList::IfAmdin == QStringLiteral("管理员"))
   {
       setAdminMenu();

   }else
   {
       setNoAdminMenu();
   }

//    remove_menu = new QMenu();
//    m_menubtn->setStyleSheet("QPushButton::menu-indicator{image:none;}");

//    usercation = new QAction(QIcon("screen/user.png"),QStringLiteral("用户管理"),remove_menu);
//    WhiteList = new QAction(QIcon("screen/list.png"),QStringLiteral("白名单管理"),remove_menu);
//    Password = new QAction(QIcon("screen/password.png"),QStringLiteral("修改密码"),remove_menu);

//    remove_menu->addAction(usercation);
//    remove_menu->addAction(Password);
//    remove_menu->addAction(WhiteList);


//    m_menubtn->setMenu(remove_menu);

//    remove_menu->setFont(QFont("微软雅黑", 9, QFont::Normal));
//    remove_menu->setStyleSheet("QMenu{background: rgb(255,255,255); border: 1px solid rgb(169,159,142);}"
//                  "QMenu::item {width: 65; height: 28px; padding: 0px 0px 0px 23px; color: white;}"
//                  "QMenu::item:enabled {color: black;}"
//                  "QMenu::item:!enabled {color: rgb(155, 155, 155);}"
//                  "QMenu::item:enabled:selected {color: white;background: rgb(0, 149, 255);}"
//                  );

    m_skinbtn = new ButtonFour(":/skin/source/icon1/skin.png",this);
    m_skinbtn->setFixedSize(29,24);


    m_wordlabel = new QLabel(this);
    m_wordlabel->setFixedSize(230,70);
    m_wordlabel->setStyleSheet("background-image:url(:/sourceskin/titleitem.png);background-color:transparent;");
    //m_wordlabel->setGeometry(QRect(810,30,230,70));
    m_wordlabel->setGeometry(QRect(956,30,230,70));


//    m_homepagebtn = new mainButton(":/skin/source/icon/home.png",":/skin/source/icon/home1.png",":/skin/source/icon/home1.png",this);
//    m_homepagebtn->setFixedSize(107,100);

//    m_Safeguardsbtn = new mainButton(":/skin/source/icon/safe.png",":/skin/source/icon/safe1.png",":/skin/source/icon/safe.png",this);
//    m_Safeguardsbtn->setFixedSize(107,100);

//    m_moni_resultbtn = new mainButton(":/skin/source/icon/result.png",":/skin/source/icon/result1.png",":/skin/source/icon/result.png",this);
//    m_moni_resultbtn->setFixedSize(107,100);

    m_homepagebtn = new QPushButton(this);
    m_homepagebtn->setFixedSize(107,100);
    //m_homepagebtn->setStyleSheet("background-image:url(:/skin/source/icon/homeUp.png);background-color:transparent;");
    m_homepagebtn->setStyleSheet("QPushButton{border-image: url(:/sourceskin/homeinit.png);}"
                                            "QPushButton:hover{border-image: url(:/sourceskin/homehover.png);}"
                                            "QPushButton:pressed{border-image: url(:/sourceskin/homepress.png);}");

    m_Safeguardsbtn = new QPushButton(this);
    m_Safeguardsbtn->setFixedSize(107,100);
    m_Safeguardsbtn->setStyleSheet("background-image:url(:/skin/source/icon/safeUp.png);background-color:transparent;");
    m_Safeguardsbtn->setStyleSheet("QPushButton{border-image: url(:/sourceskin/homemenuhover.png);}"
                                            "QPushButton:hover{border-image: url(:/sourceskin/homemenu.png);}"
                                            "QPushButton:pressed{border-image: url(:/sourceskin/homemenucheck.png);}");

    m_moni_resultbtn = new QPushButton(this);
    m_moni_resultbtn->setFixedSize(107,100);
    //m_moni_resultbtn->setStyleSheet("background-image:url(:/skin/source/icon/InfoUp.png);background-color:transparent;");
    m_moni_resultbtn->setStyleSheet("QPushButton{border-image: url(:/sourceskin/Infomenuinit.png);}"
                                            "QPushButton:hover{border-image: url(:/sourceskin/Infomenuhover.png);}"
                                            "QPushButton:pressed{border-image: url(:/sourceskin/Infomenupress.png);}");

    m_countbtn= new QPushButton(this);
    m_countbtn->setFixedSize(107,100);
    //m_countbtn->setStyleSheet("background-image:url(:/skin/source/icon/countUp.png);background-color:transparent;");
    m_countbtn->setStyleSheet("QPushButton{border-image: url(:/sourceskin/countmenuinit.png);}"
                                            "QPushButton:hover{border-image: url(:/sourceskin/countmenuhover.png);}"
                                            "QPushButton:pressed{border-image: url(:/sourceskin/countmenupress.png);}");

    m_qrcodebtn = new QPushButton(this);
    m_qrcodebtn->setFixedSize(107,100);
    //m_qrcodebtn->setStyleSheet("background-image:url(:/skin/source/icon/erweiUp.png);background-color:transparent;");
    m_qrcodebtn->setStyleSheet("QPushButton{border-image: url(:/sourceskin/qrmenuinit.png);}"
                                            "QPushButton:hover{border-image: url(:/sourceskin/qrmenuhover.png);}"
                                            "QPushButton:pressed{border-image: url(:/sourceskin/qrmenupress.png);}");


//    connect(usercation, SIGNAL(triggered()), this, SLOT(slotUserManage()));
//    connect(WhiteList, SIGNAL(triggered()), this, SLOT(slotWhiteList()));
//    connect(Password, SIGNAL(triggered()), this, SLOT(slotPassModify()));

}

void upwidget::setAdminMenu()
{
    remove_menu = new QMenu();
    m_menubtn->setStyleSheet("QPushButton::menu-indicator{image:none;}");
    //不显示下拉图片

    usercation = new QAction(QIcon("screen/user.png"),QStringLiteral("用户管理"),remove_menu);
    WhiteList = new QAction(QIcon("screen/list.png"),QStringLiteral("白名单管理"),remove_menu);
    Password = new QAction(QIcon("screen/password.png"),QStringLiteral("修改密码"),remove_menu);
    About = new QAction(QIcon("screen/about.png"),QStringLiteral("关于产品"),remove_menu);

    remove_menu->addAction(usercation);
    remove_menu->addAction(Password);
    remove_menu->addAction(WhiteList);
    remove_menu->addAction(About);

    m_menubtn->setMenu(remove_menu);

    remove_menu->setFont(QFont("微软雅黑", 9, QFont::Normal));
    remove_menu->setStyleSheet("QMenu{background: rgb(255,255,255); border: 1px solid rgb(169,159,142);}"
                  "QMenu::item {width: 65; height: 28px; padding: 0px 0px 0px 23px; color: white;}"
                  "QMenu::item:enabled {color: black;}"
                  "QMenu::item:!enabled {color: rgb(155, 155, 155);}"
                  "QMenu::item:enabled:selected {color: white;background: rgb(0, 149, 255);}"
                  );


    connect(usercation, SIGNAL(triggered()), this, SLOT(slotUserManage()));
    connect(WhiteList, SIGNAL(triggered()), this, SLOT(slotWhiteList()));
    connect(Password, SIGNAL(triggered()), this, SLOT(slotPassModify()));
    connect(About,SIGNAL(triggered()),this,SLOT(slotAboutInfo()));
}

void upwidget::setNoAdminMenu()
{

    remove_menu = new QMenu();
    m_menubtn->setStyleSheet("QPushButton::menu-indicator{image:none;}");
    //不显示下拉图片

    //usercation = new QAction(QIcon("screen/user.png"),QStringLiteral("用户管理"),remove_menu);
    //WhiteList = new QAction(QIcon("screen/list.png"),QStringLiteral("白名单管理"),remove_menu);
    Password = new QAction(QIcon("screen/password.png"),QStringLiteral("修改密码"),remove_menu);
    About = new QAction(QIcon("screen/about.png"),QStringLiteral("关于产品"),remove_menu);

    remove_menu->addAction(Password);
    remove_menu->addAction(About);

    m_menubtn->setMenu(remove_menu);

    remove_menu->setFont(QFont("微软雅黑", 9, QFont::Normal));
    remove_menu->setStyleSheet("QMenu{background: rgb(255,255,255); border: 1px solid rgb(169,159,142);}"
                  "QMenu::item {width: 65; height: 28px; padding: 0px 0px 0px 23px; color: white;}"
                  "QMenu::item:enabled {color: black;}"
                  "QMenu::item:!enabled {color: rgb(155, 155, 155);}"
                  "QMenu::item:enabled:selected {color: white;background: rgb(0, 149, 255);}"
                  );


    //connect(usercation, SIGNAL(triggered()), this, SLOT(slotUserManage()));
    //connect(WhiteList, SIGNAL(triggered()), this, SLOT(slotWhiteList()));
    connect(Password, SIGNAL(triggered()), this, SLOT(slotPassModify()));
    connect(About,SIGNAL(triggered()),this,SLOT(slotAboutInfo()));

}

void upwidget::slotUserManage()
{
    qDebug()<<"k65kk57ukj57ukj567";
//    QString safeResultInfo = QStringLiteral("检测结果已经导出，请查阅！！！");
//    QMessageBox::information(NULL, QStringLiteral("导出提示"),
//                                   safeResultInfo, QStringLiteral("确定"));
    UserManage = new MsgBox(this);
    UserManage->setUserManageInfo();
    UserManage->show();

    connect(UserManage->userAdd,SIGNAL(clicked()),this,SLOT(slotAdduserinfo()));

}


//黑白名单管理
void upwidget::slotWhiteList()
{
    WhiteListManage = new MsgBox(this);
    WhiteListManage->setWhiteListManage();
    WhiteListManage->show();
}


//修改密码
void upwidget::slotPassModify()
{

    modifypass = new MsgBox(this);
    modifypass->ModifyPassword(LoginWidget::Username);
    modifypass->show();

    connect(modifypass->exportbutton,SIGNAL(clicked()),this,SLOT(slotModifyPass()));

}

//关于产品
void upwidget::slotAboutInfo()
{
     AboutInfo = new MsgBox(this);
     AboutInfo->AboutInfo();
     AboutInfo->show();

}

void upwidget::slotModifyPass()
{
    qDebug()<<"fffffff";

    Oldpass = modifypass->unitEdit->text();
    NewPass = modifypass->phoneEdit->text();
    ReNewpass = modifypass->remarkEdit->text();

    QString userinfo = cmdData::userLogin(LoginWidget::Username);
    QStringList UserInfo = userinfo.split(MSG_DATA_ITEMS_SEPARATOR);
    QString password = UserInfo.at(1);
    QString despassword = modifypass->decrypPassword(password);


    if(Oldpass.isEmpty())
    {
        QMessageBox box(QMessageBox::Question,QStringLiteral("修改提示"),QStringLiteral("原密码不允许为空，请输入！！！"));
        box.setStandardButtons(QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        box.setWindowIcon(QIcon("screen/edit.png"));

        if(box.exec() == QMessageBox::Ok)
        {
            modifypass->unitEdit->setFocus();
            box.close();
            return;
        }else
        {
            modifypass->unitEdit->setFocus();
            box.close();
            return;
        }
    }

    if(Oldpass == despassword)
    {
        if(NewPass.isEmpty() || ReNewpass.isEmpty())
        {
            QMessageBox box(QMessageBox::Question,QStringLiteral("修改提示"),QStringLiteral("密码不允许为空，请重新输入！！！"));
            box.setStandardButtons(QMessageBox::Ok);
            box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
            box.setWindowIcon(QIcon("screen/edit.png"));
            modifypass->phoneEdit->clear();
            modifypass->remarkEdit->clear();
            modifypass->phoneEdit->setFocus();

            if(box.exec() == QMessageBox::Ok)
            {
                box.close();
                return;
            }else
            {
                box.close();
                return;
            }
        }else
        {
            if(NewPass == ReNewpass)
            {
                if(NewPass == Oldpass)
                {
                    QMessageBox box(QMessageBox::Question,QStringLiteral("修改提示"),QStringLiteral("重置密码与原密码相同，请重置！！！"));
                    box.setStandardButtons(QMessageBox::Ok);
                    box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
                    box.setWindowIcon(QIcon("screen/edit.png"));

                    modifypass->phoneEdit->clear();
                    modifypass->remarkEdit->clear();
                    modifypass->phoneEdit->setFocus();

                    if(box.exec() == QMessageBox::Ok)
                    {
                        box.close();
                        return;
                    }else
                    {
                        box.close();
                        return;
                    }
                }

                QString despass = modifypass->EncryPassword(NewPass);
                bool ok = cmdData::updataUserPassWord(LoginWidget::Username,despass);

                //modifypass->EncryPassword(NewPass);



                if(ok == true)
                {
                    modifypass->close();

                    QMessageBox box(QMessageBox::Question,QStringLiteral("修改提示"),QStringLiteral("恭喜您，重置密码成功！！！"));
                    box.setStandardButtons(QMessageBox::Ok);
                    box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
                    box.setWindowIcon(QIcon("screen/edit.png"));

                    if(box.exec() == QMessageBox::Ok)
                    {
                        box.close();
                        return;
                    }else
                    {
                        box.close();
                        return;
                    }
                }else
                {
                    QMessageBox box(QMessageBox::Question,QStringLiteral("修改提示"),QStringLiteral("重置密码失败，请重新操作！！！"));
                    box.setStandardButtons(QMessageBox::Ok);
                    box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
                    box.setWindowIcon(QIcon("screen/edit.png"));

                    if(box.exec() == QMessageBox::Ok)
                    {
                        box.close();
                        return;
                    }else
                    {
                        box.close();
                        return;
                    }

                }

            }else
            {
                QMessageBox box(QMessageBox::Question,QStringLiteral("修改提示"),QStringLiteral("两次输入密码不同，请重置密码！！！"));
                box.setStandardButtons(QMessageBox::Ok);
                box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
                box.setWindowIcon(QIcon("screen/edit.png"));

                if(box.exec() == QMessageBox::Ok)
                {
                    modifypass->phoneEdit->clear();
                    modifypass->remarkEdit->clear();
                    modifypass->phoneEdit->setFocus();
                    box.close();
                    return;
                }else
                {
                    modifypass->phoneEdit->clear();
                    modifypass->remarkEdit->clear();
                    modifypass->phoneEdit->setFocus();
                    box.close();
                    return;
                }
            }

        }

        return;
    }else
    {
        QMessageBox box(QMessageBox::Question,QStringLiteral("修改提示"),QStringLiteral("原密码错误，请重新输入！！！"));
        box.setStandardButtons(QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        //box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
        box.setWindowIcon(QIcon("screen/edit.png"));

        if(box.exec() == QMessageBox::Ok)
        {
            //QDesktopServices::openUrl(QUrl::fromLocalFile(AppList::currentExportDir));
            modifypass->unitEdit->clear();
            modifypass->phoneEdit->clear();
            modifypass->remarkEdit->clear();
            modifypass->unitEdit->setFocus();
            box.close();
            return;
        }else
        {
            box.close();
            return;
        }


    }
    qDebug()<<"123456"<<Oldpass<<NewPass<<ReNewpass;
}
void upwidget::slotAdduserinfo()
{
    qDebug()<<"grwggwr";

    AddUserinfo = new MsgBox(this);
    AddUserinfo->AddUserInfo();

    AddUserinfo->show();
    connect(AddUserinfo->exportbutton,SIGNAL(clicked()),this,SLOT(slotAddUserOK()));


}
void upwidget::slotAddUserOK()
{
     qDebug()<<"grwggwr"<<"12345";

     QString username = AddUserinfo->adduserEdit->text();
     QString password = AddUserinfo->addpassEdit->text();
     //QString role = AddUserinfo->addRoleedit->text();
     QString role = AddUserinfo->addRoleedit->currentText().trimmed();
     QString deparment = AddUserinfo->addDepartmentedit->text();
     int isAdmin;
     int isEnable = 1;

     if(username.isEmpty())
     {

         QMessageBox box(QMessageBox::Question,QStringLiteral("添加提示"),QStringLiteral("用户名不允许为空，请输入！"));
         box.setStandardButtons(QMessageBox::Ok);
         box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
         box.setWindowIcon(QIcon("screen/edit.png"));
         box.exec();
         AddUserinfo->adduserEdit->setFocus();
         return;

     }
     if(password.isEmpty())
     {
         QMessageBox box(QMessageBox::Question,QStringLiteral("添加提示"),QStringLiteral("密码不允许为空，请输入！"));
         box.setStandardButtons(QMessageBox::Ok);
         box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
         box.setWindowIcon(QIcon("screen/edit.png"));
         box.exec();
         AddUserinfo->addpassEdit->setFocus();
         return;

     }
     if(deparment.isEmpty())
     {
         QMessageBox box(QMessageBox::Question,QStringLiteral("添加提示"),QStringLiteral("所属部门不允许为空，请输入！"));
         box.setStandardButtons(QMessageBox::Ok);
         box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
         box.setWindowIcon(QIcon("screen/edit.png"));
         box.exec();
         AddUserinfo->addDepartmentedit->setFocus();
         return;
     }

     if(role == QStringLiteral("管理员"))
     {
         isAdmin = 1;

     }else
     {
         isAdmin = 0;
     }

     QString checkUserInfo = cmdData::userLogin(username);

     if(!checkUserInfo.isEmpty())
     {
         QMessageBox box(QMessageBox::Question,QStringLiteral("添加提示"),QStringLiteral("该用户名已存在，请重新输入用户名！！！"));
         box.setStandardButtons(QMessageBox::Ok);
         box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
         box.setWindowIcon(QIcon("screen/edit.png"));

         if(box.exec() == QMessageBox::Ok)
         {
             AddUserinfo->adduserEdit->clear();

             AddUserinfo->addpassEdit->clear();
             //AddUserinfo->addRoleedit->clear();
             AddUserinfo->addDepartmentedit->clear();

             AddUserinfo->adduserEdit->setFocus();
             box.close();
             return;
         }
     }

     QString despassword = AddUserinfo->EncryPassword(password);
     QString allocation = AppList::UserInfolist.at(0);
     bool ok = cmdData::addUserInfo(username,despassword,role,deparment,isAdmin,isEnable,allocation);

     qDebug()<<allocation<<"tttttt";

     if(ok == true)
     {

         QStringList list = cmdData::selectAllUserInfo();

         UserManage->addUpdateUserInfo(list);

         AddUserinfo->close();

         qDebug() <<"insert into table  successful";
         QMessageBox box(QMessageBox::Question,QStringLiteral("操作提示"),QStringLiteral("新增用户操作成功！！！"));
         box.setStandardButtons(QMessageBox::Ok);
         box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
         box.setWindowIcon(QIcon("screen/edit.png"));

         if(box.exec() == QMessageBox::Ok)
         {
             box.close();
             return;
         }else
         {
             box.close();
             return;
         }
     }else
     {
         QMessageBox box(QMessageBox::Question,QStringLiteral("操作提示"),QStringLiteral("新增用户操作失败，请重新增加！！！"));
         box.setStandardButtons(QMessageBox::Ok);
         box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
         box.setWindowIcon(QIcon("screen/edit.png"));

         if(box.exec() == QMessageBox::Ok)
         {
             box.close();
             return;
         }else
         {
             box.close();
             return;
         }

     }
}

void upwidget::resizeEvent(QResizeEvent *event)
{

}

void upwidget::setwidgetLayout()
{

    QHBoxLayout *winbuttonlayout = new QHBoxLayout;
    winbuttonlayout->addWidget(m_skinbtn);
    winbuttonlayout->addWidget(m_menubtn);
    winbuttonlayout->addWidget(m_minbtn);
    //winbuttonlayout->addWidget(m_maxbtn);
    winbuttonlayout->addWidget(m_closebtn);
    winbuttonlayout->setSpacing(0);
    //winbuttonlayout->setGeometry(QRect((this->width()-135),0,125,25));
    winbuttonlayout->setGeometry(QRect(1241,0,125,25));
    //winbuttonlayout->setGeometry(QRect(wide,0,155,25));

    QHBoxLayout *controlalyout = new QHBoxLayout;
    controlalyout->addWidget(m_homepagebtn);
    controlalyout->addWidget(m_Safeguardsbtn);
    controlalyout->addWidget(m_moni_resultbtn);
    controlalyout->addWidget(m_countbtn);
    controlalyout->addWidget(m_qrcodebtn);
    controlalyout->setSpacing(0);
    controlalyout->setGeometry(QRect(0,15,745,100));

}

void upwidget::slotIconHome()
{
   qDebug()<<"kkkkkk";

   m_homepagebtn->setStyleSheet("background-image:url(:/skin/source/icon/home.png);background-color:transparent;");
   m_Safeguardsbtn->setStyleSheet("background-image:url(:/skin/source/icon/safeUp.png);background-color:transparent;");
   m_moni_resultbtn->setStyleSheet("background-image:url(:/skin/source/icon/resultUp.png);background-color:transparent;");
   m_countbtn->setStyleSheet("background-image:url(:/skin/source/icon/countUp.png);background-color:transparent;");
   m_qrcodebtn->setStyleSheet("background-image:url(:/skin/source/icon/erweiUp.png);background-color:transparent;");

}

void upwidget::menubuttonaction()
{
    QAction *usercation = new QAction(QStringLiteral("用户管理"),m_menubtn);
    QAction *WhiteList = new QAction(QStringLiteral("白名管理"),m_menubtn);
    QAction *Password = new QAction(QStringLiteral("修改密码"),m_menubtn);
    m_menubtn->addAction(usercation);
    m_menubtn->addAction(WhiteList);
    m_menubtn->addAction(Password);

}
void upwidget::slotShowMaxRestore(QSize size)
{
    setGeometry(0,0,size.width(),size.height());
    //setwidgetshow();
    //qDebug()<<this->width()<<"MAX++++";
    setwidgetLayout();
}
