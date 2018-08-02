#ifndef QRCODEGENERATE_H
#define QRCODEGENERATE_H

#include <QWidget>
#include <qrcode/QrcodeGenerate/qrencode.h>
#include <QPainter>
#include <QLabel>
#include <QObject>

class QrcodeGenerate : public QWidget
{
    Q_OBJECT

public:
    QrcodeGenerate(QWidget *parent = 0);
    ~QrcodeGenerate();
    void generateString(QString str);
    bool saveImage(QString fileName, int size=100);

    void setBackground();

    void draw(QPainter &painter, int width, int height);
    QString string;
    QRcode *qr;

    void paintEvent(QPaintEvent *);
    QSize sizeHint() const;
    QSize minimumSizeHint() const;


};

#endif // QRCODEGENERATE_H
