#ifndef MASKMAINWIDGET_H
#define MASKMAINWIDGET_H

#include <QWidget>
#include <upwidget.h>
#include <downwidget.h>
#include <QVBoxLayout>
#include <QtPrintSupport/QPrinter>
#include <QPixmap>
#include <QMouseEvent>
#include <QPoint>
#include <QBrush>
#include <QtMath>
#include <QMouseEvent>
#include <QPoint>

class maskmainwidget : public QWidget
{
    Q_OBJECT
public:
    explicit maskmainwidget(QWidget *parent = 0);

    upwidget *m_upwidget;
    downwidget *m_downwidget;

    QVBoxLayout *mainlayout;
    QPixmap *m_backgroundpixmap;

    void paintEvent(QPaintEvent *event);

    //void maxsize();

protected:

    //鼠标移动事件
//    void mousePressEvent(QMouseEvent * event );
//    void mouseReleaseEvent(QMouseEvent *);
//    void mouseMoveEvent(QMouseEvent *event);

signals:

    void signalsize(QSize);

public slots:

   void slotmax(QSize);

private:

   bool isMax_;

};

#endif // MASKMAINWIDGET_H
