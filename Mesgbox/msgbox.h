#ifndef MSGBOX_H
#define MSGBOX_H

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
#include <QCheckBox>
#include <QComboBox>
#include <QStringList>

class MsgBox : public QDialog
{
    Q_OBJECT

public:
    MsgBox(QWidget *parent = 0);
    ~MsgBox();

    void translateLanguage();
    void MsgBox::paintEvent(QPaintEvent *);

    void setInfo(QString , QString , QString);

    void setUserManageInfo();

    void setExport(QString);

    void setMessageInfo(QString,QString);

    void ModifyPassword(QString str);

    void AddUserInfo();

    void modifyUserInfo();

    void setWhiteListManage();

    void setWhiteListIntoSql(QString);

    void setSwepQrcodeInfo();

    void AboutInfo();

    void PasswordtoMd5(QString str);

    QString EncryPassword(QString str);

    QString decrypPassword(QString str);

signals:

     void msgChecked(bool, bool);

     void okMessageHidden(bool);

public slots:

    void okOperate();
    void cancelOperate();

    void slotanmeEditPress();
    void slotunitEditPress();
    void slotphoneEditPress();
    void slotremarkEditPress();

    void slotAddUserEditPress();
    void slotAddPassPress();
    void slotAddRolePress();
    void slotAddDepartPress();

    void slotModifyPass();
    void slotModifyUserInfo();
    void slotDeleteUserInfo();

    //void slotModifyPassok(QString str);

    void slotModifyPassok();

    void slotModifyUserInfook();

    void addUpdateUserInfo(QStringList list);

    void slotSelectUserInfo();

    void selectUsernamepress();
    void selectRolepress();
    void selectDeparmentpress();

    void UpdateWhiteListTable(QStringList list);

    void slotdeleteWhiteListInfo();

    void slotSelectWhiteListInfo();

protected:

    //鼠标移动事件
    void mousePressEvent(QMouseEvent * event );
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);

public:

    bool mouse_press;
    QPushButton *close_button;
    QLabel *title_label;
    QWidget *upwidget;
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
    QLineEdit *anmeEdit;

    QLabel *unitlaber;
    QLineEdit *unitEdit;

    QLabel *phonelabel;
    QLineEdit *phoneEdit;

    QLabel *remarklabel;
    QLineEdit *remarkEdit;

    QPushButton *exportbutton;
    QPushButton *exportcancel;
    QPushButton *modifypassok;

    QTextEdit *MessageInfoText;


    QLabel *usernamelabel;
    QLabel *nichenglabel;
    QLabel *Departmentlabel;

    QLineEdit *userEdit;
    QComboBox *nichengEdit;
    //QComboBox *nichengEdit;
    QLineEdit *DepartmentEdit;

    QPushButton *userAdd;
    QPushButton *userselect;

    QTableWidget *userTable;


    //增加用户信息
    QLabel *adduserlabel;
    QLineEdit *adduserEdit;

    QLabel *addpasslabel;
    QLineEdit *addpassEdit;

//    QLabel *addRepasslabel;
//    QLineEdit *addRepassedit;

    QLabel *addRolelabel;
    //QLineEdit *addRoleedit;
    QComboBox *addRoleedit;

    QLabel *addDepartmentlabel;
    QLineEdit *addDepartmentedit;


    QPushButton *modifyPsssbutton[1000];
    QPushButton *modifyInfobutton[1000];
    QPushButton *deleteInfobutton[1000];

    MsgBox *modifypass;
    MsgBox *modifyuserinfo;
    MsgBox *deleteuserinfo;

    static QString Oldpass;
    static QString NewPass;
    static QString ReNewpass;
    static QString CurrentUsername;
    static QString CurrentRole;
    static QString CurrentDepartment;
    static int CurrentRow;


    //白名单管理
    QLabel *WhiteListlabel;
    QLabel *PackageNamelabel;
    QLineEdit *PackageEdit;
    QPushButton *PackageSelect;
    QTableWidget *WhiteListWidget;

    QPushButton *deleteWhiteList[100000];


    //扫码信息
    QLineEdit *swepQrcodeEdit;
    QPushButton *QrcodeButton;
    QLabel *picsweplabel;
    QLabel *swepwordlabel;
    QLabel *swepUniquelabel;


    //关于产品
    QLabel *IconLabel;
    QLabel *productLabel;
    QLabel *CompanyLabel;
    QLabel *CopyrightLabel;
};

#endif // MSGBOX_H
