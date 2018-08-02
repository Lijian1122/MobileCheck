#include "msgbox.h"
#include <QFont>
#include <QPainter>
#include <QBitmap>
#include <QPixmap>
#include <QHeaderView>
#include <QDebug>
#include <QHBoxLayout>
#include <QStringList>
#include <protocal.h>
#include <QIcon>
#include <QtMath>
#include <QPainterPath>
#include <QDialog>
#include <QProgressDialog>
#include <QScrollBar>
#include <QHeaderView>
#include <QTableWidgetItem>
#include <QStringList>
#include <Database/cmddata.h>
#include <QModelIndex>
#include <QPixmap>
#include <applist.h>

QString MsgBox::Oldpass;
QString MsgBox::NewPass;
QString MsgBox::ReNewpass;
QString MsgBox::CurrentUsername;
QString MsgBox::CurrentRole;
QString MsgBox::CurrentDepartment;
int MsgBox::CurrentRow;

MsgBox::~MsgBox()
{

}
MsgBox::MsgBox(QWidget *parent)
 : QDialog(parent)
{

//  setAttribute(Qt::WA_TranslucentBackground,true);
//  setWindowFlags(Qt::FramelessWindowHint);

  this->resize(800, 600);
  //获取主界面的宽度
  //int width = this->width();
  //int height = this->height();
  //初始化为未按下鼠标左键
  mouse_press = false;
  //设置标题栏隐藏
  this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

//  close_button = new QPushButton(this);
//  close_button->setGeometry(width-30, 0, 30, 30);
//  close_button->setFixedSize(30,30);
//  close_button->setStyleSheet("background-image:url(:/pic/close_normal.png)");

//  setWindowIcon(QIcon(":../source/logo.ico"));
  //setIcon(QIcon(":../source/logo.ico"));
  upwidget = new QWidget(this);
  upwidget->setGeometry(2, 2, this->width()-4, 38);
  upwidget->setStyleSheet("background-color:rgb(0,85,0)");

  //设置标题
  title_label = new QLabel(upwidget);
  title_label->setStyleSheet("color:rgb(255,255,0);font: 10pt;background-color:rgb(0,85,0)");
  title_label->setObjectName(QString::fromUtf8("labelOne"));
  QFont font = title_label->font();
  font.setBold(true);
  title_label->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
  title_label->setFont(font);
  title_label->setGeometry(0, 0, 150, 40);

  m_closebtn = new ButtonFour(":/pic/close.png",upwidget);
  m_closebtn->setFixedSize(29,24);
  m_closebtn->setGeometry(upwidget->width()-34,2,29,24);

//  m_minbtn = new ButtonFour(":/pic/min.png",upwidget);
//  m_minbtn->setFixedSize(29,24);
//  m_minbtn->setGeometry(upwidget->width()-64,2,29,24);

//  QHBoxLayout *winbuttonlayout = new QHBoxLayout();

  //winbuttonlayout->addWidget(m_minbtn);
 /* winbuttonlayout->addWidget(m_closebtn);
  winbuttonlayout->setSpacing(0);
  winbuttonlayout->setGeometry(QRect(this->width()-63,0,60,25))*/;

//  close_button = new QPushButton(title_label);
//  close_button->setGeometry(width-30, 0, 30, 30);
//  close_button->setFixedSize(30,30);
//  close_button->setStyleSheet("background-image:url(:/pic/close_normal.png)");

  //设置提示图片
  msg_label = new QLabel(this);
  msg_label->setGeometry(20, 50, 36, 36);
  msg_label->setScaledContents(true);
//  QPixmap pixpic;
//  pixpic.load("logo.ico");
//  msg_label->setPixmap(pixpic);

  //msg_label->setPixmap(QIcon("../source/logo.ico"));

//  ok_button = new QPushButton(QStringLiteral("确定"),this);
//  ok_button->setFixedSize(100,50);
//  ok_button->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
//  ok_button->setGeometry(width - 110,height - 55,100,50);

//QObject::connect(ok_button, SIGNAL(clicked()), this, SLOT(close()));
  QObject::connect(m_closebtn, SIGNAL(clicked()), this, SLOT(close()));
//  QObject::connect(m_minbtn,SIGNAL(clicked()),this,SLOT(showMinimized()));

}


void MsgBox::translateLanguage()
{

}

//密码加密
QString MsgBox::EncryPassword(QString str)
{
        QByteArray byte_array;
        byte_array.append(str);
        QByteArray hash_byte_array = byte_array.toBase64();
        QString encrypt = hash_byte_array.data();

        qDebug()<<"encrypt data:"<<encrypt;

        return encrypt;
}

//密码解密
QString MsgBox::decrypPassword(QString str)
{
    QByteArray byte_array;
    byte_array.append(str);
    QByteArray hash_byte_array = QByteArray::fromBase64(byte_array);
    QString decryp = hash_byte_array.data();

    qDebug()<<"decryp data:"<<decryp;

    return decryp;
}

void MsgBox::setInfo(QString title_info, QString info, QString pixmap)
{

    QStringList result = info.split("|");
    int count;
    count= result.count();

    qDebug()<<count<<info<<"000000";

   qDebug()<<"info++++=====";
   m_table = new QTableWidget(this);
   m_table->setGeometry(15,55,770,530);
   m_table->setAlternatingRowColors(true);
   m_table->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);//垂直滚动条按项移动
   m_table->setStyleSheet("font:12");
   m_table->setColumnCount(1);

   m_table->setEditTriggers(QAbstractItemView::NoEditTriggers);
   m_table->setColumnWidth(0,770);
   m_table->setShowGrid(false); //设置不显示格子线
   QHeaderView *columnhead = m_table->verticalHeader();
   columnhead->setVisible(false);

   QHeaderView *rowhead = m_table->horizontalHeader();
   rowhead->setVisible(false);


   title_label->setText(QString("  ") + title_info);
   //设置提示信息
   //ask_label->setText(info);

   QPixmap pixpic;
   pixpic.load(pixmap);
   msg_label->setPixmap(pixpic);


   qDebug()<<"123456";
   if(result.at(1) == QStringLiteral("二、病毒检测风险:"))
   {

      int j = 0;
      m_table->insertRow(j);
      m_table->insertRow(j+1);
      m_table->setItem(j, 0, new QTableWidgetItem(result.at(0)));
      m_table->setItem(j+1, 0, new QTableWidgetItem(QStringLiteral("未发现任何风险权限")));

      for(int i = 2 ; i < count+1 ; i++)
      {
         m_table->insertRow(i);
         QString str1 = result.at(i-1);

         qDebug()<<str1<<"strtrtrrr";

         m_table->setItem(i, 0, new QTableWidgetItem(result.at(i-1)));

         if(str1.contains(QStringLiteral("(高危)")) == true)
         {
             m_table->item(i, 0)->setForeground(Qt::red);
         }

         if(str1.contains(QStringLiteral("病毒名称")) == true)
         {
             m_table->item(i, 0)->setForeground(Qt::red);
         }
         if(str1.contains(QStringLiteral("病毒类型")) == true)
         {
             m_table->item(i, 0)->setForeground(Qt::red);

         }
         if(str1.contains(QStringLiteral("病毒详细"))== true)
         {
             m_table->item(i, 0)->setForeground(Qt::red);
         }

      }

   }else
   {

      for(int i = 0 ; i < count ; i++)
      {
         m_table->insertRow(i);

         QString str = result.at(i);

         qDebug()<<str<<"ffeqfef";

         m_table->setItem(i, 0, new QTableWidgetItem(result.at(i)));

         //qDebug()<<str<<"ffeqfef";

         if(str.contains(QStringLiteral("(高危)")) == true)
         {
             m_table->item(i, 0)->setForeground(Qt::red);
         }

         if(str.contains(QStringLiteral("病毒名称")) == true)
         {
             m_table->item(i, 0)->setForeground(Qt::red);
         }
         if(str.contains(QStringLiteral("病毒类型")) == true)
         {
             m_table->item(i, 0)->setForeground(Qt::red);

         }
         if(str.contains(QStringLiteral("病毒详细"))== true)
         {
             m_table->item(i, 0)->setForeground(Qt::red);
         }
      }
   }

   int nRow = m_table->rowCount();

   qDebug()<<nRow<<"All Count";
   for(int i = 0 ; i < nRow; i++)
   {
        m_table->setRowHeight(i,20);
        m_table->item(i,0)->setTextAlignment(Qt::AlignLeft|Qt::AlignVCenter);
   }

}


//白名单管理界面
void MsgBox::setWhiteListManage()
{

    title_label->setText(QStringLiteral("  白名单管理"));
    QFont titlefont = title_label->font();
    titlefont.setBold(true);
    //namelabel->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    title_label->setStyleSheet("font: 15pt;color:rgb(255,255,0)");
    title_label->setFont(titlefont);

    WhiteListlabel = new QLabel(this);
    WhiteListlabel->setGeometry(340, 60, 120, 40);
    QFont font = WhiteListlabel->font();
    font.setBold(true);
    //namelabel->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    WhiteListlabel->setStyleSheet("font: 15pt");
    WhiteListlabel->setFont(font);
    WhiteListlabel->setText(QStringLiteral("白名单列表"));

    PackageNamelabel = new QLabel(this);
    PackageNamelabel->setGeometry(10, 120, 40, 35);
    QFont font1 = PackageNamelabel->font();
    font1.setBold(true);
    PackageNamelabel->setStyleSheet("font: 10pt");
    PackageNamelabel->setFont(font1);
    PackageNamelabel->setText(QStringLiteral("包名:"));

    PackageEdit = new QLineEdit(this);
    PackageEdit->setGeometry(60, 120, 400, 35);
    QFont font3 = PackageEdit->font();
    font1.setBold(true);
    PackageEdit->setStyleSheet("font: 10pt");
    PackageEdit->setFont(font3);

    PackageSelect = new QPushButton(this);
    PackageSelect->setGeometry(480,120,110,35);
    PackageSelect->setStyleSheet("QPushButton{border-image: url(:/sourceskin/flaginit.png);}"
                                 "QPushButton:hover{border-image: url(:/sourceskin/flaghover.png);}"
                                 "QPushButton:pressed{border-image: url(:/sourceskin/flagpress.png);}");

    //setStyleSheet("color:rgb(255,255,0);font: 15pt;background-color:rgb(0,85,0)");
    //exportbutton->setStyleSheet("background-image:url(:/pic/export.png);background-color:transparent;");
    //PackageSelect->setStyleSheet("font: 10pt;");
    //PackageSelect->setText(QStringLiteral("标记"));


    WhiteListWidget = new QTableWidget(this);
    WhiteListWidget->setGeometry(10,170,780,420);
    WhiteListWidget->setAlternatingRowColors(true);
    WhiteListWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);//垂直滚动条按项移动

    WhiteListWidget->setStyleSheet("alternate-background-color:rgb(211, 211, 211);color:rgb(68,68,68);font:12pt,黑体;");
    WhiteListWidget->setStyleSheet("color:rgb(68,68,68);font:11pt,Microsoft YaHei");

    //WhiteListWidget->setStyleSheet("alternate-background-color:rgb(211, 211, 211);color:rgb(68,68,68);font:10pt,黑体;");
    //userTable->setStyleSheet("color:rgb(68,68,68);font:13pt,黑体;");

    QScrollBar *Resulbar1 = WhiteListWidget->verticalScrollBar();
    Resulbar1->setStyleSheet("QScrollBar{background:lightgray;}");

    QHeaderView *columnhead12 = WhiteListWidget->verticalHeader();
    columnhead12->setVisible(false);


    //userTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    WhiteListWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    //safeResultTable->setFrameShape(QFrame::NoFrame); //设置边框


    QStringList header1;
    header1<<QStringLiteral("序号")<<QStringLiteral("包名")<<QStringLiteral("说明")<<QStringLiteral("操作");

    QFont font36 =WhiteListWidget->horizontalHeader()->font();    //设置表头字体加粗
    font36.setBold(true);

    WhiteListWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(106, 168, 79);color:rgb(0, 0, 0);padding-left: 1px;border: 1px solid #93c47d;}"); //设置表头背景色

    WhiteListWidget->setColumnCount(4);
    WhiteListWidget->setHorizontalHeaderLabels(header1);

    WhiteListWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    WhiteListWidget->setColumnWidth(0,40);
    WhiteListWidget->setColumnWidth(1,300);
    WhiteListWidget->setColumnWidth(2,340);
    WhiteListWidget->setColumnWidth(3,100);

    WhiteListWidget->setShowGrid(true); //设置不显示格子线

    WhiteListWidget->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为时每次选择一行

    QStringList whitelist = cmdData::selectAllWhiteListInfo();

    UpdateWhiteListTable(whitelist);

    connect(PackageSelect,SIGNAL(clicked()),this,SLOT(slotSelectWhiteListInfo()));


}

void MsgBox::UpdateWhiteListTable(QStringList list)
{
    int  Row =  WhiteListWidget->rowCount();
    for(int i= 0; i <Row ; i++)
    {
        WhiteListWidget->removeRow(0);
    }

    //QStringList list = cmdData::selectAllUserInfo();

    int count  = list.count();

    qDebug()<<count <<"white ...";

    for(int i = 0; i < count; i++)
    {
        WhiteListWidget->insertRow(i);

        QString info = list.at(i);

        QStringList userlist = info.split(MSG_DATA_ITEMS_SEPARATOR);


        deleteWhiteList[i] = new QPushButton();
        deleteWhiteList[i]->setStyleSheet("QPushButton{border-image: url(:/sourceskin/whitedeinit.png);}"
                                          "QPushButton:hover{border-image: url(:/sourceskin/whitedehover.png);}"
                                          "QPushButton:pressed{border-image: url(:/sourceskin/whitedepress.png);}");

        deleteWhiteList[i]->setFixedSize(99,29);

        WhiteListWidget->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        WhiteListWidget->setItem(i,1,new QTableWidgetItem(userlist.at(0)));
        WhiteListWidget->setItem(i,2,new QTableWidgetItem(userlist.at(1)));


        WhiteListWidget->setCellWidget(i,3,deleteWhiteList[i]);
        WhiteListWidget->setItem(i,3,new QTableWidgetItem(QStringLiteral("")));

        connect(deleteWhiteList[i],SIGNAL(clicked()),this,SLOT(slotdeleteWhiteListInfo()));

    }

    int nRow =WhiteListWidget->rowCount();

    qDebug()<<nRow<<"All Count";
    for(int i1 = 0 ; i1 < nRow; i1++)
    {
       for(int j=0;j<4;j++)
       {
          WhiteListWidget->item(i1,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
       }
    }

}

void MsgBox::slotdeleteWhiteListInfo()
{


    qDebug()<<"8jtutmjnt  666";
    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
    if(senderObj == 0)
    {
            return;
    }
    QModelIndex index =WhiteListWidget->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    //int currentrow=index.row();

    int row = index.row();
    qDebug()<<"dangqian row:"<<row;

    QString currentpackage = index.sibling(row,1).data().toString();

    QString str = QStringLiteral("确定要删除该白名单应用吗？");
    QMessageBox box(QMessageBox::Warning,QStringLiteral("删除提示"),str);
    box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
    box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
    box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
    box.setWindowIcon(QIcon("screen/unstall.ico"));


    if(box.exec() == QMessageBox::Ok)
    {
        bool ok = cmdData::deleteWhiteListInfo(currentpackage);

        if(ok == true)
        {

            //WhiteListWidget->removeRow(row);

            QStringList whitelist = cmdData::selectAllWhiteListInfo();

            UpdateWhiteListTable(whitelist);
            return;
//            QString str2  = QStringLiteral("删除白名单应用成功！！！");
//            QMessageBox box(QMessageBox::Question,QStringLiteral("删除提示"),str2);
//            box.setStandardButtons(QMessageBox::Ok);
//            box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
//            box.setWindowIcon(QIcon("screen/unstall.ico"));

//            if(box.exec() == QMessageBox::Ok)
//            {
//                box.close();
//                return;
//            }else
//            {
//                box.close();
//                return;
//            }
        }else
        {
            QMessageBox box(QMessageBox::Question,QStringLiteral("删除提示"),QStringLiteral("删除异常，请重新操作！！！"));
            box.setStandardButtons(QMessageBox::Ok);
            box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
            box.setWindowIcon(QIcon("screen/unstall.ico"));

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
        box.close();
        return;
    }

}

void MsgBox::slotSelectWhiteListInfo()
{

    QString package = PackageEdit->text().trimmed();

    if(package.isEmpty())
    {
        QStringList whitelist = cmdData::selectAllWhiteListInfo();

        UpdateWhiteListTable(whitelist);
        return;
    }

    QStringList SelectWhiteList = cmdData::selectWhitelist(package);

    if(SelectWhiteList.isEmpty())
    {
//        int  Row =  userTable->rowCount();
//        for(int i= 0; i <Row ; i++)
//        {
//            userTable->removeRow(0);
//        }
        QMessageBox box(QMessageBox::Question,QStringLiteral("查询提示"),QStringLiteral("请输入正确的包名！！！"));
        box.setStandardButtons(QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        box.setWindowIcon(QIcon("screen/select.ico"));

        if(box.exec() == QMessageBox::Ok)
        {
            box.close();
            return;
        }else
        {
            box.close();
            return;
        }

        PackageEdit->clear();
        PackageEdit->setFocus();
        return;
    }else
    {

        //addUpdateUserInfo(SelectUserList);
        UpdateWhiteListTable(SelectWhiteList);

        return;
    }

}


//用户管理界面
void MsgBox::setUserManageInfo()
{
    title_label->setText(QStringLiteral("  用户管理"));

    usernamelabel = new QLabel(this);
    usernamelabel->setGeometry(20, 60, 60, 35);
    QFont font = usernamelabel->font();
    font.setBold(true);
    //namelabel->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    usernamelabel->setStyleSheet("font: 12pt");
    usernamelabel->setFont(font);
    usernamelabel->setText(QStringLiteral("登录名:"));

    userEdit = new QLineEdit(this);
    userEdit->setGeometry(98, 60, 160, 35);
    QFont font1 = userEdit->font();
    font1.setBold(true);
    userEdit->setStyleSheet("font: 12pt");
    userEdit->setFont(font1);

    nichenglabel = new QLabel(this);
    nichenglabel->setGeometry(286, 60, 60, 35);
    QFont font2 = nichenglabel->font();
    font.setBold(true);
    //namelabel->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    nichenglabel->setStyleSheet("font: 12pt");
    nichenglabel->setFont(font2);
    nichenglabel->setText(QStringLiteral("角色:"));

    nichengEdit = new QComboBox(this);
    nichengEdit->setGeometry(364, 60, 160, 35);
    QFont font3 = nichengEdit->font();
    font1.setBold(true);
    nichengEdit->setStyleSheet("font: 12pt");
    nichengEdit->setFont(font3);

    nichengEdit->addItem(QStringLiteral("管理员"));
    nichengEdit->addItem(QStringLiteral("普通用户"));


    Departmentlabel = new QLabel(this);
    Departmentlabel->setGeometry(552, 60, 60, 35);
    QFont font4 = Departmentlabel->font();
    font.setBold(true);
    //namelabel->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    Departmentlabel->setStyleSheet("font: 12pt");
    Departmentlabel->setFont(font4);
    Departmentlabel->setText(QStringLiteral("部门:"));

    DepartmentEdit = new QLineEdit(this);
    DepartmentEdit->setGeometry(620, 60, 160, 35);
    QFont font5 = DepartmentEdit->font();
    font1.setBold(true);
    DepartmentEdit->setStyleSheet("font: 12pt");
    DepartmentEdit->setFont(font5);

    userAdd = new QPushButton(this);
    userAdd->setGeometry(20,120,130,55);
    userAdd->setStyleSheet("QPushButton{border-image: url(:/sourceskin/adduserinit.png);}"
                           "QPushButton:hover{border-image: url(:/sourceskin/adduserhover.png);}"
                           "QPushButton:pressed{border-image: url(:/sourceskin/adduserpress.png);}");


     //       setStyleSheet("color:rgb(255,255,0);font: 15pt;background-color:rgb(0,85,0)");
    //exportbutton->setStyleSheet("background-image:url(:/pic/export.png);background-color:transparent;");
    //userAdd->setStyleSheet("font: 15pt;");
    //userAdd->setText(QStringLiteral("添加用户"));

    userselect = new QPushButton(this);
    userselect->setGeometry(650,120,130,55);
    userselect->setStyleSheet("QPushButton{border-image: url(:/sourceskin/selelctuserinit.png);}"
                              "QPushButton:hover{border-image: url(:/sourceskin/selectuserhover.png);}"
                              "QPushButton:pressed{border-image: url(:/sourceskin/selectuserpress.png);}");

    //        setStyleSheet("color:rgb(255,255,0);font: 15pt;background-color:rgb(0,85,0)");
    //exportbutton->setStyleSheet("background-image:url(:/pic/export.png);background-color:transparent;");
    //userselect->setStyleSheet("font: 12pt;");
    //userselect->setText(QStringLiteral("查询"));

    userTable = new QTableWidget(this);
    userTable->setGeometry(10,200,780,390);
    userTable->setAlternatingRowColors(true);
    userTable->setStyleSheet("alternate-background-color:rgb(211, 211, 211);color:rgb(68,68,68);font:12pt,黑体;");
    userTable->setStyleSheet("color:rgb(68,68,68);font:11pt,Microsoft YaHei");

    userTable->setVerticalScrollMode(QAbstractItemView::ScrollPerItem);//垂直滚动条按项移动
    //userTable->setStyleSheet("alternate-background-color:rgb(211, 211, 211);color:rgb(68,68,68);font:12pt,黑体;");
    //userTable->setStyleSheet("color:rgb(68,68,68);font:13pt,黑体;");

    QScrollBar *Resulbar1 = userTable->verticalScrollBar();
    Resulbar1->setStyleSheet("QScrollBar{background:lightgray;}");

    //userTable->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    userTable->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    QHeaderView *columnhead12 = userTable->verticalHeader();
    columnhead12->setVisible(false);

    QStringList header1;
    header1<<QStringLiteral("编号")<<QStringLiteral("登录名")<<QStringLiteral("角色")<<QStringLiteral("部门")<<QStringLiteral("修改密码")
          <<QStringLiteral("编辑")<<QStringLiteral("删除");

    QFont font36 =userTable->horizontalHeader()->font();    //设置表头字体加粗
    font36.setBold(true);

    userTable->horizontalHeader()->setStyleSheet("QHeaderView::section{background-color:rgb(106, 168, 79);color:rgb(0, 0, 0);padding-left: 1px;border: 1px solid #93c47d;}"); //设置表头背景色

    QFont font11 = userTable->horizontalHeader()->font();
    font11.setBold(true);
    userTable->horizontalHeader()->setFixedHeight(40);

    userTable->setColumnCount(7);
    userTable->setHorizontalHeaderLabels(header1);

    userTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    userTable->setColumnWidth(0,40);
    userTable->setColumnWidth(1,170);
    userTable->setColumnWidth(2,170);
    userTable->setColumnWidth(3,170);
    userTable->setColumnWidth(4,100);
    userTable->setColumnWidth(5,65);
    userTable->setColumnWidth(6,65);

    userTable->setShowGrid(true); //设置不显示格子线


    userTable->setSelectionBehavior(QAbstractItemView::SelectRows); //设置选择行为时每次选择一行


    QStringList list = cmdData::selectAllUserInfo();


    addUpdateUserInfo(list);


    connect(userselect,SIGNAL(clicked()),this,SLOT(slotSelectUserInfo()));

    connect(userEdit,SIGNAL(returnPressed()),this,SLOT(selectUsernamepress()));
    connect(nichengEdit,SIGNAL(returnPressed()),this,SLOT(selectRolepress()));
    connect(DepartmentEdit,SIGNAL(returnPressed()),this,SLOT(selectDeparmentpress()));

}

void MsgBox::addUpdateUserInfo(QStringList list)
{
    int  Row =  userTable->rowCount();
    for(int i= 0; i <Row ; i++)
    {
        userTable->removeRow(0);
    }

    //QStringList list = cmdData::selectAllUserInfo();

    int count  = list.count();

    for(int i = 0; i < count; i++)
    {
        userTable->insertRow(i);

        QString info = list.at(i);

        QStringList userlist = info.split(MSG_DATA_ITEMS_SEPARATOR);

        modifyPsssbutton[i] = new QPushButton();
        modifyPsssbutton[i]->setStyleSheet("QPushButton{border-image: url(:/sourceskin/modifypassinit.png);}"
                                           "QPushButton:hover{border-image: url(:/sourceskin/modifypasshover.png);}"
                                           "QPushButton:pressed{border-image: url(:/sourceskin/modifypasspress.png);}");

        modifyPsssbutton[i]->setFixedSize(99,29);

        modifyInfobutton[i] = new QPushButton();
        modifyInfobutton[i]->setStyleSheet("QPushButton{border-image: url(:/sourceskin/modifyinfoinit.png);}"
                                           "QPushButton:hover{border-image: url(:/sourceskin/modifyinfohover.png);}"
                                           "QPushButton:pressed{border-image: url(:/sourceskin/modifyinfopress.png);}");

        modifyInfobutton[i]->setFixedSize(64,29);

        deleteInfobutton[i] = new QPushButton();
        deleteInfobutton[i]->setStyleSheet("QPushButton{border-image: url(:/sourceskin/deleteinfoinit.png);}"
                                           "QPushButton:hover{border-image: url(:/sourceskin/deleteinfohover.png);}"
                                           "QPushButton:pressed{border-image: url(:/sourceskin/deleteinfopress.png);}");
        deleteInfobutton[i]->setFixedSize(64,29);


        userTable->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
        userTable->setItem(i,1,new QTableWidgetItem(userlist.at(0)));
        userTable->setItem(i,2,new QTableWidgetItem(userlist.at(2)));
        userTable->setItem(i,3,new QTableWidgetItem(userlist.at(3)));

        userTable->setCellWidget(i,4,modifyPsssbutton[i]);
        userTable->setItem(i, 4, new QTableWidgetItem(QStringLiteral("")));
        connect(modifyPsssbutton[i],SIGNAL(clicked()),this,SLOT(slotModifyPass()));

        userTable->setCellWidget(i,5,modifyInfobutton[i]);
        userTable->setItem(i, 5, new QTableWidgetItem(QStringLiteral("")));
        connect(modifyInfobutton[i],SIGNAL(clicked()),this,SLOT(slotModifyUserInfo()));

        userTable->setCellWidget(i,6,deleteInfobutton[i]);
        userTable->setItem(i, 6, new QTableWidgetItem(QStringLiteral("")));
        connect(deleteInfobutton[i],SIGNAL(clicked()),this,SLOT(slotDeleteUserInfo()));

    }

    int nRow = userTable->rowCount();

    qDebug()<<nRow<<"All Count";
    for(int i1 = 0 ; i1 < nRow; i1++)
    {
       for(int j=0;j<7;j++)
       {
          userTable->item(i1,j)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
       }
    }

}

//信息管理查询
void MsgBox::slotSelectUserInfo()
{
    qDebug()<<"tghththth";

     QStringList SelectUserList;
     CurrentUsername = userEdit->text().trimmed();
     CurrentRole = nichengEdit->currentText().trimmed();
     CurrentDepartment = DepartmentEdit->text().trimmed();

     qDebug()<<CurrentUsername << CurrentRole <<CurrentDepartment <<"current user";

     if(CurrentUsername.isEmpty() && CurrentDepartment.isEmpty())
     {

         QStringList list = cmdData::selectAllUserInfo(CurrentUsername,CurrentRole, CurrentDepartment);
         //int count  = list.count();
         addUpdateUserInfo(list);
         return;

     }else
     {
         SelectUserList = cmdData::selectAllUserInfo(CurrentUsername,CurrentRole, CurrentDepartment);

         if(SelectUserList.isEmpty())
         {

             QMessageBox box(QMessageBox::Question,QStringLiteral("查询提示"),QStringLiteral("请输入正确的信息！！！"));
             box.setStandardButtons(QMessageBox::Ok);
             box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
             box.setWindowIcon(QIcon("screen/select.ico"));

             userEdit->clear();
             //nichengEdit->clear();
             DepartmentEdit->clear();
             userEdit->setFocus();

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
             int count  = SelectUserList.count();

             qDebug()<<count<<SelectUserList.at(0)<<"hthhht";

             addUpdateUserInfo(SelectUserList);

             return;
         }

     }

}
void MsgBox::setExport(QString str)
{
    this->resize(390, 350);
    title_label->setText(QString("  ") + str);
    //title_label->setText(str);
    upwidget->setFixedSize(390,40);
    upwidget->setGeometry(0,0,390, 60);
    upwidget->setStyleSheet("background-color:rgb(0,85,0)");

    title_label->setGeometry(0, 0, 180, 45);
    m_closebtn->setGeometry(upwidget->width()-34,2,29,24);
    //m_minbtn->setGeometry(upwidget->width()-64,2,29,24);

    namelabel = new QLabel(this);
    namelabel->setGeometry(60, 65, 70, 40);
    QFont font = namelabel->font();
    font.setBold(true);
    //namelabel->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    namelabel->setStyleSheet("font: 14pt");
    namelabel->setFont(font);
    namelabel->setText(QStringLiteral("单  位:"));

    anmeEdit = new QLineEdit(this);
    anmeEdit->setGeometry(155, 65, 170, 35);
    QFont font1 = anmeEdit->font();
    font1.setBold(true);
    anmeEdit->setStyleSheet("font: 14pt");
    anmeEdit->setFont(font1);

    unitlaber = new QLabel(this);
    unitlaber->setGeometry(60,120, 70, 40);
    QFont font2 = unitlaber->font();
    font2.setBold(true);
    //unitlaber->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    unitlaber->setStyleSheet("font: 14pt");
    unitlaber->setFont(font2);
    unitlaber->setText(QStringLiteral("姓  名:"));

    unitEdit = new QLineEdit(this);
    unitEdit->setGeometry(155, 120, 170, 35);
    QFont font3 = unitEdit->font();
    font3.setBold(true);
    unitEdit->setStyleSheet("font: 14pt");
    unitEdit->setFont(font3);

    phonelabel = new QLabel(this);
    phonelabel->setGeometry(60, 175, 70, 40);
    QFont font4 = namelabel->font();
    font4.setBold(true);
    //namelabel->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    phonelabel->setStyleSheet("font: 14pt");
    phonelabel->setFont(font4);
    phonelabel->setText(QStringLiteral("手机号:"));

    phoneEdit = new QLineEdit(this);
    phoneEdit->setGeometry(155, 175, 170, 35);
    QFont font5= phoneEdit->font();
    font5.setBold(true);
    phoneEdit->setStyleSheet("font: 14pt");
    phoneEdit->setFont(font5);

    remarklabel = new QLabel(this);
    remarklabel->setGeometry(60, 230, 70, 40);
    QFont font6 = remarklabel->font();
    font6.setBold(true);
    remarklabel->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    remarklabel->setStyleSheet("font: 14pt");
    remarklabel->setFont(font6);
    remarklabel->setText(QStringLiteral("备  注:"));

    remarkEdit = new QLineEdit(this);
    remarkEdit->setGeometry(155, 230, 170, 35);
    QFont font7= remarkEdit->font();
    font7.setBold(true);
    remarkEdit->setStyleSheet("font: 14pt");
    remarkEdit->setFont(font7);

    exportbutton = new QPushButton(this);
    exportbutton->setGeometry(150, 285, 75, 40);
    exportbutton->setStyleSheet("QPushButton{border-image: url(:/skin/sourceskin/exportmsginit.png);}"
                                            "QPushButton:hover{border-image: url(:/skin/sourceskin/exportmsghover.png);}"
                                            "QPushButton:pressed{border-image: url(:/skin/sourceskin/exportmsghover.png);}");
    //exportbutton->setStyleSheet("color:rgb(255,255,0);font: 15pt;background-color:rgb(0,85,0)");



    exportcancel = new QPushButton(this);
    exportcancel->setGeometry(250, 285, 75, 40);
    exportcancel->setStyleSheet("background-image:url(:/pic/cancel.png);background-color:transparent;");
    //exportcancel->setStyleSheet("color:rgb(255,255,0);font: 15pt;background-color:rgb(0,85,0);font: 16pt");
    //exportcancel->setStyleSheet("font: 15pt;");
    //exportcancel->setText(QStringLiteral("取 消"));
    exportcancel->setStyleSheet("QPushButton{border-image: url(:/skin/sourceskin/exportcaninit.png);}"
                                            "QPushButton:hover{border-image: url(:/skin/sourceskin/exporthover.png);}"
                                            "QPushButton:pressed{border-image: url(:/skin/sourceskin/exportcanpress.png);}");


    connect(exportcancel,SIGNAL(clicked()),this,SLOT(close()));

    connect(anmeEdit,SIGNAL(returnPressed()),this,SLOT(slotanmeEditPress()));
    connect(unitEdit,SIGNAL(returnPressed()),this,SLOT(slotunitEditPress()));
    connect(phoneEdit,SIGNAL(returnPressed()),this,SLOT(slotphoneEditPress()));
    connect(remarkEdit,SIGNAL(returnPressed()),this,SLOT(slotremarkEditPress()));

}


//设置进入白名单
void MsgBox::setWhiteListIntoSql(QString package)
{

     this->resize(440, 260);
     title_label->setText(QStringLiteral(" 设置白名单"));
     //title_label->setText(str);
     upwidget->setFixedSize(436,38);
     upwidget->setGeometry(2, 2, 600, 60);
     upwidget->setStyleSheet("background-color:rgb(0,85,0)");

     title_label->setGeometry(5, 0, 180, 45);
     m_closebtn->setGeometry(upwidget->width()-34,2,29,24);
     //m_minbtn->setGeometry(upwidget->width()-64,2,29,24);

     namelabel = new QLabel(this);
     namelabel->setGeometry(20, 65, 70, 40);
     QFont font = namelabel->font();
     font.setBold(true);
     //namelabel->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
     namelabel->setStyleSheet("font: 14pt");
     namelabel->setFont(font);
     namelabel->setText(QStringLiteral("包  名:"));

     anmeEdit = new QLineEdit(this);
     anmeEdit->setGeometry(115, 65, 250, 35);
     QFont font1 = anmeEdit->font();
     font1.setBold(true);
     anmeEdit->setStyleSheet("font: 14pt");
     anmeEdit->setFont(font1);
     anmeEdit->setText(package);
     anmeEdit->setEnabled(false);

     unitlaber = new QLabel(this);
     unitlaber->setGeometry(20,120, 70, 40);
     QFont font2 = unitlaber->font();
     font2.setBold(true);
     //unitlaber->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
     unitlaber->setStyleSheet("font: 14pt");
     unitlaber->setFont(font2);
     unitlaber->setText(QStringLiteral("说  明:"));

     unitEdit = new QLineEdit(this);
     unitEdit->setGeometry(115, 120, 250, 35);
     QFont font3 = unitEdit->font();
     font3.setBold(true);
     unitEdit->setStyleSheet("font: 14pt");
     unitEdit->setFont(font3);


     exportbutton = new QPushButton(this);
     exportbutton->setGeometry(345, 200, 75, 40);
     //exportbutton->setStyleSheet("color:rgb(255,255,0);font: 15pt;background-color:rgb(0,85,0)");
     exportbutton->setStyleSheet("QPushButton{border-image: url(:/sourceskin/setwhinit.png);}"
                                 "QPushButton:hover{border-image: url(:/sourceskin/setwhhover.png);}"
                                 "QPushButton:pressed{border-image: url(:/sourceskin/setwhpress.png);}");

     //setStyleSheet("background-image:url(:/pic/export.png);background-color:transparent;");
     //exportbutton->setStyleSheet("font: 15pt;");
     //exportbutton->setText(QStringLiteral("导 出"));

     exportcancel = new QPushButton(this);
     exportcancel->setGeometry(20, 200, 75, 40);
     exportcancel->setStyleSheet("QPushButton{border-image: url(:/sourceskin/exportcaninit.png);}"
                                 "QPushButton:hover{border-image: url(:/sourceskin/exporthover.png);}"
                                 "QPushButton:pressed{border-image: url(:/sourceskin/exportcanpress.png);}");

     connect(exportcancel,SIGNAL(clicked()),this,SLOT(close()));

     connect(anmeEdit,SIGNAL(returnPressed()),this,SLOT(slotanmeEditPress()));
//     connect(unitEdit,SIGNAL(returnPressed()),this,SLOT(slotunitEditPress()));
//     connect(phoneEdit,SIGNAL(returnPressed()),this,SLOT(slotphoneEditPress()));
//     connect(remarkEdit,SIGNAL(returnPressed()),this,SLOT(slotremarkEditPress()));


}

//修改密码对话框
void MsgBox::ModifyPassword(QString str)
{
    this->resize(390, 350);

    title_label->setText(QString("  ") + QStringLiteral("修改密码"));


    upwidget->setFixedSize(390,40);
    upwidget->setGeometry(2, 2, 390, 36);
    upwidget->setStyleSheet("background-color:rgb(0,85,0)");

    title_label->setGeometry(0, 0, 180, 45);
    m_closebtn->setGeometry(upwidget->width()-34,2,29,24);
    //m_minbtn->setGeometry(upwidget->width()-64,2,29,24);

    namelabel = new QLabel(this);
    namelabel->setGeometry(60, 65, 90, 40);
    QFont font = namelabel->font();
    font.setBold(true);
    //namelabel->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    namelabel->setStyleSheet("font: 14pt");
    namelabel->setFont(font);
    namelabel->setText(QStringLiteral("登 录 名:"));

    anmeEdit = new QLineEdit(this);
    anmeEdit->setGeometry(155, 65, 170, 35);
    QFont font1 = anmeEdit->font();
    font1.setBold(true);
    anmeEdit->setStyleSheet("font: 14pt");
    anmeEdit->setFont(font1);
    anmeEdit->setText(str);
    anmeEdit->setEnabled(false);

    unitlaber = new QLabel(this);
    unitlaber->setGeometry(60,120, 90, 40);
    QFont font2 = unitlaber->font();
    font2.setBold(true);
    //unitlaber->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    unitlaber->setStyleSheet("font: 14pt");
    unitlaber->setFont(font2);
    unitlaber->setText(QStringLiteral("原 密 码:"));

    unitEdit = new QLineEdit(this);
    unitEdit->setGeometry(155, 120, 170, 35);
    QFont font3 = unitEdit->font();
    font3.setBold(true);
    unitEdit->setStyleSheet("font: 14pt");
    unitEdit->setFont(font3);
    unitEdit->setEchoMode(QLineEdit::Password);

    phonelabel = new QLabel(this);
    phonelabel->setGeometry(60, 175, 90, 40);
    QFont font4 = namelabel->font();
    font4.setBold(true);
    //namelabel->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    phonelabel->setStyleSheet("font: 14pt");
    phonelabel->setFont(font4);
    phonelabel->setText(QStringLiteral("新 密 码:"));

    phoneEdit = new QLineEdit(this);
    phoneEdit->setGeometry(155, 175, 170, 35);
    QFont font5= phoneEdit->font();
    font5.setBold(true);
    phoneEdit->setStyleSheet("font: 14pt");
    phoneEdit->setFont(font5);
    phoneEdit->setEchoMode(QLineEdit::Password);

    remarklabel = new QLabel(this);
    remarklabel->setGeometry(60, 230, 90, 40);
    QFont font6 = remarklabel->font();
    font6.setBold(true);
    remarklabel->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    remarklabel->setStyleSheet("font: 14pt");
    remarklabel->setFont(font6);
    remarklabel->setText(QStringLiteral("确认密码:"));

    remarkEdit = new QLineEdit(this);
    remarkEdit->setGeometry(155, 230, 170, 35);
    QFont font7= remarkEdit->font();
    font7.setBold(true);
    remarkEdit->setStyleSheet("font: 14pt");
    remarkEdit->setFont(font7);
    remarkEdit->setEchoMode(QLineEdit::Password);

    exportbutton = new QPushButton(this);
    exportbutton->setGeometry(150, 285, 75, 40);
    //exportbutton->setStyleSheet("color:rgb(255,255,0);font: 15pt;background-color:rgb(0,85,0)");
    exportbutton->setStyleSheet("QPushButton{border-image: url(:/sourceskin/passmodifyinit.png);}"
                                "QPushButton:hover{border-image: url(:/sourceskin/passmodifyhover.png);}"
                                "QPushButton:pressed{border-image: url(:/sourceskin/passmodifypress.png);}");


    exportcancel = new QPushButton(this);
    exportcancel->setGeometry(250, 285, 75, 40);
    exportcancel->setStyleSheet("QPushButton{border-image: url(:/sourceskin/exportcaninit.png);}"
                                "QPushButton:hover{border-image: url(:/sourceskin/exporthover.png);}"
                                "QPushButton:pressed{border-image: url(:/sourceskin/exportcanpress.png);}");


    connect(exportcancel,SIGNAL(clicked()),this,SLOT(close()));

    //connect(anmeEdit,SIGNAL(returnPressed()),this,SLOT(slotanmeEditPress()));
    unitEdit->setFocus();

    connect(unitEdit,SIGNAL(returnPressed()),this,SLOT(slotunitEditPress()));
    connect(phoneEdit,SIGNAL(returnPressed()),this,SLOT(slotphoneEditPress()));
    connect(remarkEdit,SIGNAL(returnPressed()),this,SLOT(slotremarkEditPress()));

}

//修改用户信息
void MsgBox::modifyUserInfo()
{

    this->resize(390, 300);
    title_label->setText(QStringLiteral(" 修改用户信息"));


    upwidget->setFixedSize(390,40);
    upwidget->setGeometry(2, 2, 390, 36);
    upwidget->setStyleSheet("background-color:rgb(0,85,0)");

    title_label->setGeometry(0, 0, 180, 45);
    m_closebtn->setGeometry(upwidget->width()-34,2,29,24);
    //m_minbtn->setGeometry(upwidget->width()-64,2,29,24);

    adduserlabel = new QLabel(this);
    adduserlabel->setGeometry(60, 65, 70, 40);
    QFont font = adduserlabel->font();
    font.setBold(true);
    //namelabel->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    adduserlabel->setStyleSheet("font: 14pt");
    adduserlabel->setFont(font);
    adduserlabel->setText(QStringLiteral("登录名:"));

    adduserEdit = new QLineEdit(this);
    adduserEdit->setGeometry(155, 65, 170, 35);
    QFont font1 = adduserEdit->font();
    font1.setBold(true);
    adduserEdit->setStyleSheet("font: 14pt");
    adduserEdit->setFont(font1);

    addRolelabel = new QLabel(this);
    addRolelabel->setGeometry(60, 120, 70, 40);
    QFont font4 = addRolelabel->font();
    font4.setBold(true);

    //namelabel->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    addRolelabel->setStyleSheet("font: 14pt");
    addRolelabel->setFont(font4);
    addRolelabel->setText(QStringLiteral("角  色:"));

    addRoleedit = new QComboBox(this);
    addRoleedit->setGeometry(155, 120, 170, 35);
    QFont font5= addRoleedit->font();
    addRoleedit->addItem(QStringLiteral("管理员"));
    addRoleedit->addItem(QStringLiteral("普通用户"));

    font5.setBold(true);
    addRoleedit->setStyleSheet("font: 14pt");
    addRoleedit->setFont(font5);

    addDepartmentlabel = new QLabel(this);
    addDepartmentlabel->setGeometry(60, 175, 70, 40);
    QFont font6 = addDepartmentlabel->font();
    font6.setBold(true);
    addDepartmentlabel->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
    addDepartmentlabel->setStyleSheet("font: 14pt");
    addDepartmentlabel->setFont(font6);
    addDepartmentlabel->setText(QStringLiteral("部  门:"));

    addDepartmentedit = new QLineEdit(this);
    addDepartmentedit->setGeometry(155, 175, 170, 35);
    QFont font7= addDepartmentedit->font();
    font7.setBold(true);
    addDepartmentedit->setStyleSheet("font: 14pt");
    addDepartmentedit->setFont(font7);

    exportbutton = new QPushButton(this);
    exportbutton->setGeometry(150, 235, 75, 40);
    //exportbutton->setStyleSheet("color:rgb(255,255,0);font: 15pt;background-color:rgb(0,85,0)");
    exportbutton->setStyleSheet("QPushButton{border-image: url(:/sourceskin/passmodifyinit.png);}"
                                "QPushButton:hover{border-image: url(:/sourceskin/passmodifyhover.png);}"
                                "QPushButton:pressed{border-image: url(:/sourceskin/passmodifypress.png);}");
    //setStyleSheet("background-image:url(:/pic/modify.png);background-color:transparent;");
    //exportbutton->setStyleSheet("font: 15pt;");
    //exportbutton->setText(QStringLiteral("导 出"));

    exportcancel = new QPushButton(this);
    exportcancel->setGeometry(250, 235, 75, 40);
    exportcancel->setStyleSheet("QPushButton{border-image: url(:/sourceskin/exportcaninit.png);}"
                                "QPushButton:hover{border-image: url(:/sourceskin/exporthover.png);}"
                                "QPushButton:pressed{border-image: url(:/sourceskin/exportcanpress.png);}");

    //setStyleSheet("background-image:url(:/pic/cancel.png);background-color:transparent;");

    connect(exportcancel,SIGNAL(clicked()),this,SLOT(close()));

    addDepartmentedit->setFocus();

    //connect(adduserEdit,SIGNAL(returnPressed()),this,SLOT(slotAddUserEditPress()));
    //connect(addpassEdit,SIGNAL(returnPressed()),this,SLOT(slotAddPassPress()));
    //connect(addRoleedit,SIGNAL(returnPressed()),this,SLOT(slotAddRolePress()));
    connect(addDepartmentedit,SIGNAL(returnPressed()),this,SLOT(slotAddDepartPress()));

}

//增加用户信息
void MsgBox::AddUserInfo()
{

     this->resize(390, 350);
     title_label->setText(QStringLiteral(" 添加用户"));

     upwidget->setFixedSize(390,40);
     upwidget->setGeometry(2, 2, 390, 60);
     upwidget->setStyleSheet("background-color:rgb(0,85,0)");

     title_label->setGeometry(0, 0, 180, 45);
     m_closebtn->setGeometry(upwidget->width()-34,2,29,24);
     //m_minbtn->setGeometry(upwidget->width()-64,2,29,24);

     adduserlabel = new QLabel(this);
     adduserlabel->setGeometry(60, 65, 70, 40);
     QFont font = adduserlabel->font();
     font.setBold(true);
     //namelabel->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
     adduserlabel->setStyleSheet("font: 14pt");
     adduserlabel->setFont(font);
     adduserlabel->setText(QStringLiteral("登录名:"));

     adduserEdit = new QLineEdit(this);
     adduserEdit->setGeometry(155, 65, 170, 35);
     QFont font1 = adduserEdit->font();
     font1.setBold(true);
     adduserEdit->setStyleSheet("font: 14pt");
     adduserEdit->setFont(font1);

     addpasslabel = new QLabel(this);
     addpasslabel->setGeometry(60,120, 70, 40);
     QFont font2 = addpasslabel->font();
     font2.setBold(true);
     //unitlaber->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
     addpasslabel->setStyleSheet("font: 14pt");
     addpasslabel->setFont(font2);
     addpasslabel->setText(QStringLiteral("密  码:"));

     addpassEdit = new QLineEdit(this);
     addpassEdit->setGeometry(155, 120, 170, 35);
     QFont font3 = addpassEdit->font();
     font3.setBold(true);
     addpassEdit->setStyleSheet("font: 14pt");
     addpassEdit->setFont(font3);
     addpassEdit->setEchoMode(QLineEdit::Password);

     addRolelabel = new QLabel(this);
     addRolelabel->setGeometry(60, 175, 70, 40);
     QFont font4 = addRolelabel->font();
     font4.setBold(true);

     //namelabel->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
     addRolelabel->setStyleSheet("font: 14pt");
     addRolelabel->setFont(font4);
     addRolelabel->setText(QStringLiteral("角  色:"));

     addRoleedit = new QComboBox(this);
     addRoleedit->setGeometry(155, 175, 170, 35);
     QFont font5= addRoleedit->font();
     addRoleedit->addItem(QStringLiteral("管理员"));
     addRoleedit->addItem(QStringLiteral("普通用户"));

     font5.setBold(true);
     addRoleedit->setStyleSheet("font: 14pt");
     addRoleedit->setFont(font5);

     addDepartmentlabel = new QLabel(this);
     addDepartmentlabel->setGeometry(60, 230, 70, 40);
     QFont font6 = addDepartmentlabel->font();
     font6.setBold(true);
     addDepartmentlabel->setStyleSheet("color:rgb(255,255,0);font: 16pt;background-color:rgb(0,85,0)");
     addDepartmentlabel->setStyleSheet("font: 14pt");
     addDepartmentlabel->setFont(font6);
     addDepartmentlabel->setText(QStringLiteral("部  门:"));

     addDepartmentedit = new QLineEdit(this);
     addDepartmentedit->setGeometry(155, 230, 170, 35);
     QFont font7= addDepartmentedit->font();
     font7.setBold(true);
     addDepartmentedit->setStyleSheet("font: 14pt");
     addDepartmentedit->setFont(font7);

     exportbutton = new QPushButton(this);
     exportbutton->setGeometry(150, 285, 75, 40);
     //exportbutton->setStyleSheet("color:rgb(255,255,0);font: 15pt;background-color:rgb(0,85,0)");
     exportbutton->setStyleSheet("QPushButton{border-image: url(:/image/sourceskin/useraddinit.png);}"
                                 "QPushButton:hover{border-image: url(:/image/sourceskin/useraddhover.png);}"
                                 "QPushButton:pressed{border-image: url(:/image/sourceskin/useraddpress.png);}");

     exportcancel = new QPushButton(this);
     exportcancel->setGeometry(250, 285, 75, 40);
     exportcancel->setStyleSheet("QPushButton{border-image: url(:/sourceskin/exportcaninit.png);}"
                                 "QPushButton:hover{border-image: url(:/sourceskin/exporthover.png);}"
                                 "QPushButton:pressed{border-image: url(:/sourceskin/exportcanpress.png);}");


      // ("background-image:url(:/pic/cancel.png);background-color:transparent;");
     //exportcancel->setStyleSheet("color:rgb(255,255,0);font: 15pt;background-color:rgb(0,85,0);font: 16pt");
     //exportcancel->setStyleSheet("font: 15pt;");
     //exportcancel->setText(QStringLiteral("取 消"));


     QString allocation = AppList::UserInfolist.at(7);

     if(!allocation.isEmpty())
     {

        addRoleedit->setCurrentIndex(1);
        addRoleedit->setEnabled(false);

     }

     connect(exportcancel,SIGNAL(clicked()),this,SLOT(close()));

     adduserEdit->setFocus();

     connect(adduserEdit,SIGNAL(returnPressed()),this,SLOT(slotAddUserEditPress()));
     connect(addpassEdit,SIGNAL(returnPressed()),this,SLOT(slotAddPassPress()));
     //connect(addRoleedit,SIGNAL(returnPressed()),this,SLOT(slotAddRolePress()));
     connect(addDepartmentedit,SIGNAL(returnPressed()),this,SLOT(slotAddDepartPress()));

}

//关于产品
void MsgBox::AboutInfo()
{
    this->resize(390, 350);
    title_label->setText(QStringLiteral(" 关于产品"));

    upwidget->setFixedSize(390,40);
    upwidget->setGeometry(2, 2, 390, 60);
    upwidget->setStyleSheet("background-color:rgb(0,85,0)");

    title_label->setGeometry(0, 0, 180, 45);
    m_closebtn->setGeometry(upwidget->width()-34,2,29,24);

    IconLabel = new QLabel(this);
    IconLabel->setGeometry(105, 60, 180, 180);
    QPixmap pixmap;
    pixmap.load("screen/logo.ico");
    QPixmap fitpixmap=pixmap.scaled(180,180,Qt::KeepAspectRatio);
    IconLabel->setPixmap(fitpixmap);


    productLabel = new QLabel(this);
    productLabel->setGeometry(110, 260, 170, 20);
    productLabel->setText(QStringLiteral("智能手机安全检测系统"));
    productLabel->setStyleSheet("font: 12pt,Microsoft YaHei");

    CompanyLabel = new QLabel(this);
    CompanyLabel->setGeometry(30, 290, 330, 20);
    QString str1 = AppList::AuthInfo.at(2);
    QString str2 = AppList::AuthInfo.at(1);
    QString str3 = str1.append("|").append(str2);
    CompanyLabel->setText(str3);
    CompanyLabel->setStyleSheet("font: 12pt,Microsoft YaHei");

    CopyrightLabel = new QLabel(this);
    CopyrightLabel->setGeometry(5, 320, 380, 20);
    QString str4 = AppList::AuthInfo.at(3);
    QString str5 = "Copyright@";
    QString str6 = ". All rights reserved.";
    QString str7 = str5.append(str4).append(str6);
    CopyrightLabel->setText(str7);
    CopyrightLabel->setStyleSheet("font: 12pt,Microsoft YaHei");

    QObject::connect(m_closebtn, SIGNAL(clicked()), this, SLOT(close()));

}

void MsgBox::slotAddUserEditPress()
{
    m_closebtn->setDefault(false);
    exportbutton->setDefault(false);
    addpassEdit->setFocus();
}

void MsgBox::slotAddPassPress()
{
    addDepartmentedit->setFocus();
    exportbutton->setDefault(false);
}

void MsgBox::slotAddRolePress()
{
    addDepartmentedit->setFocus();
    exportbutton->setDefault(false);
}

void MsgBox::slotAddDepartPress()
{
    exportbutton->setFocus();
    //exportbutton->setDefault(false);
}

void MsgBox::slotanmeEditPress()
{
    m_closebtn->setDefault(false);
    exportcancel->setDefault(false);
    unitEdit->setFocus();

}

void MsgBox::slotunitEditPress()
{
    exportbutton->setDefault(false);
    phoneEdit->setFocus();


}

void MsgBox::slotphoneEditPress()
{
    exportbutton->setDefault(false);
    remarkEdit->setFocus();
}

void MsgBox::slotremarkEditPress()
{
    exportbutton->setFocus();
}

//查看短信详细信息
void MsgBox::setMessageInfo(QString str,QString pixmap)
{
    this->resize(500, 380);

    title_label->setText(QStringLiteral("短信详细"));
    upwidget->setFixedSize(500,40);
    upwidget->setGeometry(0, 0, 600, 60);
    upwidget->setStyleSheet("background-color:rgb(0,85,0)");

    title_label->setGeometry(5, 0, 180, 45);
    m_closebtn->setGeometry(upwidget->width()-34,2,29,24);
    //m_minbtn->setGeometry(upwidget->width()-64,2,29,24);

    MessageInfoText = new QTextEdit(this);
    MessageInfoText->setGeometry(26, 68, 440, 280);
    QFont font1 = MessageInfoText->font();
    font1.setBold(true);
    MessageInfoText->setStyleSheet("font:12pt,黑体");
    MessageInfoText->setFont(font1);
    MessageInfoText->setDisabled(false);
    MessageInfoText->setText(str);
    MessageInfoText->setDisabled(true);
}

void MsgBox::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
//    painter.setBrush(QColor(255, 255, 255));
//    painter.setPen(Qt::NoPen);
//    painter.drawRect(QRect::QRect(0,0,this->width(),this->height()));


    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(2, 2, this->width()-4, this->height()-4);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(0, 0, 0, 50);

    for(int i=0; i<2; i++)
    {
            QPainterPath path;
            path.setFillRule(Qt::WindingFill);
            path.addRect(2-i, 2-i, this->width()-(2-i)*2, this->height()-(2-i)*2);
            color.setAlpha(150 - qSqrt(i)*50);
            painter.setPen(color);
            painter.drawPath(path);
    }
}

void MsgBox::slotModifyPass()
{
    qDebug()<<"8jtutmjnt  666";
    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
    if(senderObj == 0)
    {
            return;
    }
    QModelIndex index =userTable->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    //int currentrow=index.row();

    int row = index.row();
    qDebug()<<"dangqian row:"<<row;

    MsgBox::CurrentUsername = index.sibling(row,1).data().toString();

    qDebug()<<MsgBox::CurrentUsername;

    modifypass = new MsgBox(this);
    modifypass->ModifyPassword(MsgBox::CurrentUsername);
    modifypass->show();

    connect(modifypass->exportbutton,SIGNAL(clicked()),this,SLOT(slotModifyPassok()));

}

void MsgBox::slotModifyUserInfo()
{
    qDebug()<<"8jtutmjnt  666";
    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
    if(senderObj == 0)
    {
            return;
    }
    QModelIndex index =userTable->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    //int currentrow=index.row();

    int row = index.row();
    qDebug()<<"dangqian row:"<<row;

    CurrentRow = row;

    MsgBox::CurrentUsername = index.sibling(row,1).data().toString();
    MsgBox::CurrentRole = index.sibling(row,2).data().toString();
    MsgBox::CurrentDepartment = index.sibling(row,3).data().toString();

    qDebug()<<MsgBox::CurrentUsername;

    modifyuserinfo = new MsgBox(this);
    modifyuserinfo->modifyUserInfo();
    modifyuserinfo->show();

    modifyuserinfo->adduserEdit->setText(MsgBox::CurrentUsername);
    modifyuserinfo->adduserEdit->setEnabled(false);
    modifyuserinfo->addRoleedit->setCurrentText(MsgBox::CurrentRole);
    modifyuserinfo->addDepartmentedit->setText(MsgBox::CurrentDepartment);

    connect(modifyuserinfo->exportbutton,SIGNAL(clicked()),this,SLOT(slotModifyUserInfook()));

}

void MsgBox::slotDeleteUserInfo()
{

    qDebug()<<"8jtutmjnt  666";
    QPushButton * senderObj=qobject_cast<QPushButton *>(sender());
    if(senderObj == 0)
    {
            return;
    }
    QModelIndex index =userTable->indexAt(QPoint(senderObj->frameGeometry().x(),senderObj->frameGeometry().y()));
    //int currentrow=index.row();

    int row = index.row();
    qDebug()<<"dangqian row:"<<row;

    MsgBox::CurrentUsername = index.sibling(row,1).data().toString();

    QString str = QStringLiteral("确定要删除用户 %1吗？").arg(MsgBox::CurrentUsername);
    QMessageBox box(QMessageBox::Warning,QStringLiteral("删除提示"),str);
    box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
    box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
    box.setButtonText(QMessageBox::Cancel,QStringLiteral("取消"));
    box.setWindowIcon(QIcon("screen/unstall.ico"));


    if(box.exec() == QMessageBox::Ok)
    {
        bool ok = cmdData::deleteUserInfo(MsgBox::CurrentUsername);

        if(ok == true)
        {

//            int row = userTable->rowCount();
//            for(int i = 0; i< row; row++)
//            {
//                userTable->removeRow(i);
//            }

            QStringList list = cmdData::selectAllUserInfo();
            addUpdateUserInfo(list);
            //userTable->removeRow(row);

            QString str2  = QStringLiteral("删除用户 %1成功！！！").arg(MsgBox::CurrentUsername);
            QMessageBox box(QMessageBox::Question,QStringLiteral("删除提示"),str2);
            box.setStandardButtons(QMessageBox::Ok);
            box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
            box.setWindowIcon(QIcon("screen/unstall.ico"));

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
            QMessageBox box(QMessageBox::Question,QStringLiteral("删除提示"),QStringLiteral("删除用户信息异常，请重新操作！！！"));
            box.setStandardButtons(QMessageBox::Ok);
            box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
            box.setWindowIcon(QIcon("screen/unstall.ico"));

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
        box.close();
        return;
    }

}

void MsgBox::slotModifyUserInfook()
{

   QString username = modifyuserinfo->adduserEdit->text();
   QString role = modifyuserinfo->addRoleedit->currentText().trimmed();
   QString deparment = modifyuserinfo->addDepartmentedit->text();

   if(deparment.isEmpty())
   {
       QMessageBox box(QMessageBox::Question,QStringLiteral("修改提示"),QStringLiteral("所属部门不能为空！"));
       box.setStandardButtons(QMessageBox::Ok);
       box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
       box.setWindowIcon(QIcon("screen/edit.png"));
       box.exec();
       return;
   }

   bool ok = cmdData::updataUserInfo(CurrentUsername,username,role,deparment);

   if(ok == true)
   {


       userTable->setItem(CurrentRow,1,new QTableWidgetItem(username));
       userTable->setItem(CurrentRow,2,new QTableWidgetItem(role));
       userTable->setItem(CurrentRow,3,new QTableWidgetItem(deparment));

       userTable->item(CurrentRow,1)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
       userTable->item(CurrentRow,2)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);
       userTable->item(CurrentRow,3)->setTextAlignment(Qt::AlignHCenter|Qt::AlignVCenter);

       modifyuserinfo->close();

       QMessageBox box(QMessageBox::Question,QStringLiteral("修改提示"),QStringLiteral("修改用户信息成功！！！"));
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
       QMessageBox box(QMessageBox::Question,QStringLiteral("修改提示"),QStringLiteral("修改用户信息异常，请重新操作！！！"));
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

void MsgBox::slotModifyPassok()
{
    qDebug()<<"fffffff";
    QString str;

    Oldpass = modifypass->unitEdit->text();
    NewPass = modifypass->phoneEdit->text();
    ReNewpass = modifypass->remarkEdit->text();

    //QString strpass = decrypPassword(Oldpass);
    QString userinfo = cmdData::userLogin(MsgBox::CurrentUsername);
    QStringList UserInfo = userinfo.split(MSG_DATA_ITEMS_SEPARATOR);
    QString password = UserInfo.at(1);
    QString decpassword = decrypPassword(password);
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

    if(Oldpass == decpassword)
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

                QString desnewpass =  this->EncryPassword(NewPass);
                bool ok = cmdData::updataUserPassWord(CurrentUsername,desnewpass);

                if(ok == true)
                {
                    modifypass->close();

                    QMessageBox box(QMessageBox::Question,QStringLiteral("修改提示"),QStringLiteral("重置密码成功！！！"));
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


void MsgBox::selectUsernamepress()
{
    m_closebtn->setDefault(false);
    //exportbutton->setDefault(false);
    nichengEdit->setFocus();
}

void MsgBox::selectRolepress()
{
     m_closebtn->setDefault(false);
     DepartmentEdit->setFocus();
}

void MsgBox::selectDeparmentpress()
{
     m_closebtn->setDefault(false);
     userselect->setFocus();

}


//扫码结果信息框
void MsgBox::setSwepQrcodeInfo()
{
    this->resize(440, 250);
    title_label->setText(QString(" ") + QStringLiteral("扫描二维码"));
    //title_label->setText(str);
    upwidget->setFixedSize(440,40);
    upwidget->setGeometry(0, 0, 350, 60);
    upwidget->setStyleSheet("background-color:rgb(0,85,0);font:10pt,Microsoft YaHei");

    title_label->setGeometry(0, 5, 130, 30);
    m_closebtn->setGeometry(upwidget->width()-34,2,29,24);
    //m_minbtn->setGeometry(upwidget->width()-64,2,29,24);

    picsweplabel = new QLabel(this);
    picsweplabel->setGeometry(20, 65, 170, 120);
    //picsweplabel->setStyleSheet("background-color:rgb(0,85,0)");

    QPixmap pixmap;
    pixmap.load("screen/swep.jpg");
    QPixmap fitpixmap=pixmap.scaled(170,120,Qt::KeepAspectRatio);
    picsweplabel->setPixmap(fitpixmap);

    swepwordlabel = new QLabel(this);
    swepwordlabel->setGeometry(200, 95, 190, 40);
    QFont font2 = swepwordlabel->font();
    font2.setBold(true);
    swepwordlabel->setStyleSheet("font: 15pt,Microsoft YaHei");
    swepwordlabel->setFont(font2);
    swepwordlabel->setText(QStringLiteral(" 请扫描二维码..."));

    swepUniquelabel = new QLabel(this);
    swepUniquelabel->setGeometry(20, 195, 80, 40);
    QFont font3 = swepUniquelabel->font();
    font3.setBold(true);
    swepUniquelabel->setStyleSheet("font: 15pt,Microsoft YaHei");
    swepUniquelabel->setFont(font3);
    swepUniquelabel->setText(QStringLiteral("唯一码："));

    swepQrcodeEdit = new QLineEdit(this);
    swepQrcodeEdit->setGeometry(120, 195, 270, 40);
    QFont font1 = swepQrcodeEdit->font();
    font1.setBold(true);
    swepQrcodeEdit->setStyleSheet("font: 15pt,Microsoft YaHei");
    swepQrcodeEdit->setFont(font1);

//    QrcodeButton = new QPushButton(this);
//    QrcodeButton->setGeometry(230, 75, 100, 45);
//    QrcodeButton->setStyleSheet("color:rgb(255,255,0);font: 12pt;background-color:rgb(0,85,0)");
//    //QrcodeButton->setStyleSheet("background-image:url(:/pic/export.png);background-color:transparent;");
//    //exportbutton->setStyleSheet("font: 15pt;");
//    QrcodeButton->setText(QStringLiteral("查 询"));

    swepQrcodeEdit->setFocus();

   // QObject::connect(m_closebtn, SIGNAL(clicked()), this, SLOT(close()));



}

void MsgBox::mousePressEvent( QMouseEvent * event )
{
  //只能是鼠标左键移动和改变大小
  if(event->button() == Qt::LeftButton)
  {
    mouse_press = true;
  }
  //窗口移动距离
  move_point = event->globalPos() - pos();
}


void MsgBox::mouseReleaseEvent( QMouseEvent *)
{
  mouse_press = false;
}
void MsgBox::mouseMoveEvent(QMouseEvent *event)
{
    //移动窗口
      if(mouse_press)
      {
        QPoint move_pos = event->globalPos();
        move(move_pos - move_point);
      }
}

void MsgBox::okOperate()
{
  bool is_hidden = check_box->isHidden();
  if(!is_hidden)
  {
    bool is_checked = check_box->isChecked();
    emit msgChecked(is_checked, true);
  }
  this->accept();
}


void MsgBox::cancelOperate()
{
  bool is_check_hidden = check_box->isHidden();
  bool is_ok_hidden = ok_button->isHidden();
  if(!is_check_hidden)
  {
    bool is_checked = check_box->isChecked();
    if(!is_ok_hidden)
    {
      emit msgChecked(is_checked, false);
    }
   else
   {
     emit okMessageHidden(is_checked);
   }
  }
  this->reject();
}
