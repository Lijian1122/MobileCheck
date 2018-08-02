#ifndef MYBUTTON_H
#define MYBUTTON_H
#include <QObject>
#include <QWidget>
#include <QPaintEvent>
#include <QEvent>
#include <QPushButton>
#include <qpropertyanimation.h>
#include <QDebug>
#include <QList>
#include <QToolButton>

class mainButton:public QPushButton
{
    Q_OBJECT
public:
    mainButton(QString pixnormal,QString pixenter,QString pixleave,QWidget*parent);
    ~mainButton();
protected:
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void paintEvent(QPaintEvent*);

    QPropertyAnimation*m_enteranimation;
    QPropertyAnimation*m_leaveanimation;

    QList<QPixmap> m_enterlist;
    QList<QPixmap> m_leavelist;
    QPixmap m_pixnormal;
    int m_enterIndex;
    int m_leaveIndex;
    bool m_enter;
    bool m_leave;
public slots:
    void entervaluechange(QVariant var){m_enterIndex=var.toInt();update();}
    void leavevaluechange(QVariant var){m_leaveIndex=var.toInt();update();}
};


class ButtonFour:public QPushButton   //用于四态图片
{
    Q_OBJECT
public:
    ButtonFour(QString pixnormal, QWidget*parent);
    ~ButtonFour();
protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent*);
    void mousePressEvent(QMouseEvent *e);
    void mouseReleaseEvent(QMouseEvent *e) override;
private:
    QList<QPixmap> m_pixlist;
    int m_index;
    bool m_enter;
};

class checkButton:public QPushButton    //加载两态图
{
    Q_OBJECT
public:
    checkButton(QString pixcheckurl,QWidget *parent);
protected:
    void paintEvent(QPaintEvent*);
    void enterEvent(QEvent*);
    void leaveEvent(QEvent*);
    void mousePressEvent(QMouseEvent*);
private:
    bool m_checked;
    int m_enter;
    QList<QPixmap> m_checklist;
    QList<QPixmap> m_pixlist;
    QPixmap m_pixcheck;
    int m_checkindex;
    int m_uncheckindex;

};

class main4Button:public QPushButton//8个图与4个图
{
    Q_OBJECT
public:
    main4Button(QString pixanima,QString pixurl,QWidget*parent=0);
protected:
    void paintEvent(QPaintEvent *);
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
private:
    QList<QPixmap> m_animalist;
    QList<QPixmap> m_normallist;
    QPropertyAnimation *m_animation;
    int animaindex;
    bool m_enter;
private slots:
    void slot_valuechange(QVariant var){animaindex=var.toInt();update();}
  //  void slot_aniamtion();

};


#endif // MYBUTTON_H
