#ifndef UPWIDGET_H
#define UPWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QLayout>
#include <QPaintEvent>
#include <mybutton.h>
#include <QObject>
#include <QToolButton>
#include <QMenu>
#include <QAction>
#include <msgbox.h>


class upwidget : public QWidget
{
    Q_OBJECT
public:
    explicit upwidget(QWidget *parent = 0);

    void setwidgetshow();
    void setwidgetLayout();
    void paintEvent(QPaintEvent *event);

    void setAdminMenu();

    void setNoAdminMenu();

    void resizeEvent(QResizeEvent *event);

signals:

public slots:

   void menubuttonaction();

   void slotIconHome();

   void slotShowMaxRestore(QSize size);

   //void slotMenufun();

   void slotUserManage();
   void slotWhiteList();
   void slotPassModify();

   void slotModifyPass();

   void slotAdduserinfo();

   void slotAddUserOK();

   void slotAboutInfo();

public:

   bool isMax_;

   int wide;

//    QPushButton *m_skinbtn;
//    QPushButton *m_maxbtn;
//  QPushButton *m_menubtn;
//    QPushButton *m_minbtn;
//    QPushButton *m_closebtn;

    ButtonFour *m_skinbtn;
    checkButton *m_maxbtn;
    ButtonFour *m_menubtn;
    ButtonFour *m_minbtn;
    ButtonFour *m_closebtn;

    QPushButton *m_homepagebtn;
    QPushButton *m_Safeguardsbtn;
    QPushButton *m_moni_resultbtn;
    QPushButton *m_countbtn;
    QPushButton *m_qrcodebtn;

//    main4Button *m_homepagebtn;
//    main4Button *m_Safeguardsbtn;
//    main4Button *m_moni_resultbtn;

//    mainButton *m_homepagebtn;
//    mainButton *m_Safeguardsbtn;
//    mainButton *m_moni_resultbtn;

    QLabel *m_label;
    QLabel *m_wordlabel;

    QHBoxLayout *mainlayout;
    QHBoxLayout *winbuttonlayout;
    QHBoxLayout *operatelayout;

    QMenu *remove_menu;

    QAction *usercation;
    QAction *WhiteList;
    QAction *Password;
    QAction *About;

    MsgBox *modifypass;
    MsgBox *UserManage;
    MsgBox *AddUserinfo;
    MsgBox *WhiteListManage;
    MsgBox *AboutInfo;

 private:

    static QString Oldpass;
    static QString NewPass;
    static QString ReNewpass;


};

#endif // UPWIDGET_H
