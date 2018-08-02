#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QCheckBox>
#include <QMouseEvent>
#include <QPoint>
#include <QTableWidget>
#include <mybutton.h>
#include <QLineEdit>
#include <QTextEdit>
#include <QKeyEvent>
#include <QTimer>

#include <QAbstractNativeEventFilter>
#include "Adb.h"
#include "Windows.h"
#include "mainwidget.h"
#include "authoriza.h"

class LoginWidget : public QDialog, public QAbstractNativeEventFilter
{
    Q_OBJECT

public:
    LoginWidget(QWidget *parent = 0);
    ~LoginWidget();
    void paintEvent(QPaintEvent *);

    //使窗体变为顶层窗体
    //void activateWindow();

    //void setExport();

    //void setMessageInfo(QString,QString);

protected:

    bool nativeEventFilter(const QByteArray &eventType, void *message, long *);
    //bool nativeEvent(const QByteArray &eventType, void *message, long *result);
    bool winEvent(MSG *message, long *result);
    bool eventFilter(QObject *object, QEvent *event);

    void keyPressEvent(QKeyEvent *event);

    QString EncryPassword(QString str);

private:

    //bool AuthorizaInitialize();


signals:

     void msgChecked(bool, bool);

     void okMessageHidden(bool);

public slots:

    void okOperate();
    void cancelOperate();
    void LoginSlot();

    void UsernameSlot();
    void PassWordSlot();

    void timedone();

protected:

    //鼠标移动事件
    void mousePressEvent(QMouseEvent * event );
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);

//private:
public:

    static QString Username;
    static QString PassWord;
    static QString UserInfo;
    static QString Userpart;

    bool mouse_press;
    QPushButton *close_button;
    QLabel *title_label;
    QWidget *upwidget;
    //QWidget *downwidget;
    QLabel *downwidget;
    QPushButton  *cancel_button;
    QPushButton  *ok_button;
    QCheckBox *check_box;
    QLabel *msg_label;
    QLabel *ask_label;

    QString ok_text;
    QString cancel_text;
    QPoint  move_point;
    QTableWidget *m_table;

    ButtonFour *m_closebtn;
    ButtonFour *m_minbtn;

    QLabel *namelabel;
    QLineEdit *nameEdit;

    QLabel *passlaber;
    QLineEdit *passEdit;


    QPushButton *Loginbutton;
    QPushButton *exportcancel;

    QLabel *LoginPrompt;

    QTextEdit *MessageInfoText;

    mainwidget *m_mainwidget;

    static QStringList userlist;

    Authoriza *m_authoriza;
    QTimer *timer;

};

#endif // LOGINWIDGET_H
