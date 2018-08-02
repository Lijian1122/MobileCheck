#ifndef QPRINTQCRODE_H
#define QPRINTQCRODE_H

#include <QWidget>
#include <QPainter>
#include <QLabel>
#include <QObject>
#include <qrencode.h>
#include <QImage>

class QPrintQcrode : public QWidget
{
    Q_OBJECT

public:
    QPrintQcrode(QWidget *parent = 0);
    ~QPrintQcrode();

    void generateString(QString str);
    bool saveImage(QString fileName, int size ,QString checked ,QString checker,QString time);

    void setBackground();

    void draw(QPainter &painter, int width, int height);
    QString string;
    QRcode *qr;

    void paintEvent(QPaintEvent *);
    QSize sizeHint() const;
    QSize minimumSizeHint() const;

    QLabel *Qrcodelabel;

    QLabel *checker;
    QLabel *checkername;

    QLabel *checked;
    QLabel *checkedname;

    QLabel *checktime;
    QLabel *checktimedit;

    static QImage *image1;

};

#endif // QPRINTQCRODE_H
