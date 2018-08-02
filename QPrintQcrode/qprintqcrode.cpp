#include "qprintqcrode.h"
#include <QHBoxLayout>
#include <QGuiApplication>
#include <QScreen>

QImage *QPrintQcrode::image1;
QPrintQcrode::QPrintQcrode(QWidget *parent)
    : QWidget(parent)
{

    setWindowFlags(Qt::FramelessWindowHint);

    setAttribute(Qt::WA_PaintUnclipped);

    this->setFixedSize(280,120);
    qr = NULL;

    Qrcodelabel = new QLabel(this);

    Qrcodelabel->setGeometry(10, 10, 100, 100);
    //Qrcodelabel->setStyleSheet("background-color:lightgray;");

    checker = new QLabel(this);
    checker->setGeometry(125, 10, 50, 30);
    checker->setText(QStringLiteral("受检人："));
    checker->setStyleSheet("font: 10pt,Microsoft YaHei");

    checkername = new QLabel(this);
    checkername->setGeometry(190, 10, 80, 30);
    checkername->setText(QStringLiteral("admin11eff"));
    checkername->setStyleSheet("font: 10pt,Microsoft YaHei");

    checked = new QLabel(this);
    checked->setGeometry(125, 40, 50, 30);
    checked->setText(QStringLiteral("检查人："));
    checked->setStyleSheet("font: 10pt,Microsoft YaHei");

    checkedname = new QLabel(this);
    checkedname->setGeometry(190, 40, 80, 30);
    checkedname->setText(QStringLiteral("admin11feff"));
    checkedname->setStyleSheet("font: 10pt,Microsoft YaHei");

    checktime = new QLabel(this);
    checktime->setGeometry(125, 70,60, 30);
    checktime->setText(QStringLiteral("检测时间："));
    checktime->setStyleSheet("font: 10pt,Microsoft YaHei");

    checktimedit = new QLabel(this);
    checktimedit->setGeometry(190, 70, 80, 30);
    checktimedit->setText(QStringLiteral("2016.03.03"));
    checktimedit->setStyleSheet("font: 10pt,Microsoft YaHei");

    image1 = new QImage(330, 120, QImage::Format_ARGB32_Premultiplied);

}

QPrintQcrode::~QPrintQcrode()
{
    if(qr != NULL)
    {
       QRcode_free(qr);
    }

   // delete this;
}
bool QPrintQcrode::saveImage(QString fileName, int size, QString checked ,QString checker,QString time)
{

    if(size != 0 && !fileName.isEmpty())
    {
        //Format_Mono

        //QImage image(330, 120, QImage::Format_ARGB32_Premultiplied);

        QPainter painter1(image1);
        QColor background(Qt::white);
        painter1.setBrush(background);
        painter1.setPen(Qt::NoPen);

        painter1.drawRect(5, 10, 100, 100);
        if(qr != NULL)
        {
            draw(painter1, 100, 100);
        }

        QFont font;
        font.setPointSize(14);
        //font.setBold(true);
        font.setFamily("Microsoft YaHei");
        painter1.setFont(font);

        //QFontMetrics fm = painter1.fontMetrics();
        painter1.setPen(Qt::SolidLine);
        QString str1 = QStringLiteral("受检人： ");

        QRectF rect(110, 10, 85, 30);
        painter1.drawText(rect,str1);

        QRectF rect1(195, 10, 90, 50);
        QString str2 = QStringLiteral("lijianmaomao");
        painter1.drawText(rect1,checked);

        QRectF rect2(110, 40, 85, 30);
        QString str3 = QStringLiteral("检查人： ");
        painter1.drawText(rect2,str3);

        QRectF rect4(195, 40, 90, 50);
        //checkedname->setText(QStringLiteral("admin11feff"));
        painter1.drawText(rect4,checker);

        QRectF rect5(110,70,110,30);
        QString str4 = QStringLiteral("检测时间：");
        painter1.drawText(rect5,str4);

        QRectF rect6(210, 70, 115, 30);
        //checktimedit->setText(QStringLiteral("2016.03.03"));
        painter1.drawText(rect6,time);

        return image1->save(fileName);

    }
    else
    {
        this->setStyleSheet("background-color:transparent");
        return false;
    }
}

void QPrintQcrode::generateString(QString str)
{
    string = str;
    if(qr != NULL)
    {
        QRcode_free(qr);
    }
    qr = QRcode_encodeString(string.toStdString().c_str(),
                             1,
                             QR_ECLEVEL_L,
                             QR_MODE_8,
                             1);
    update();

}

void QPrintQcrode::setBackground()
{
    this->setStyleSheet("background-color:transparent;");
}

void QPrintQcrode::draw(QPainter &painter, int width, int height)
{

    QColor foreground(Qt::black);
    painter.setBrush(foreground);
    const int qr_width = qr->width > 0 ? qr->width : 1;
    double scale_x = width / qr_width;
    double scale_y = height / qr_width;
    for( int y = 0; y < qr_width; y ++)
    {
        for(int x = 0; x < qr_width; x++)
        {
            unsigned char b = qr->data[y * qr_width + x];
            if(b & 0x01)
            {
                //QRectF r(10, 10, scale_x, scale_y);
                QRectF r(x * scale_x+10, y * scale_y+10, scale_x, scale_y);
                painter.drawRects(&r, 1);
            }
        }
    }
}
//Qrcodelabel->width(), Qrcodelabel->height()
void QPrintQcrode::paintEvent(QPaintEvent*)
{
    QPainter painter;
    painter.begin(this);
    QColor background(Qt::white);
    painter.setBrush(background);
    painter.setPen(Qt::NoPen);
    //painter.setWindow(10,10,100,100);

    painter.drawRect(10, 10, 120,120);


    if(qr != NULL)
    {
        draw(painter, 120, 120);
    }
    painter.begin(this);
}

QSize QPrintQcrode::sizeHint()  const
{
    QSize s;
    if(qr != NULL)
    {
        int qr_width = qr->width > 0 ? qr->width : 1;
        s = QSize(qr_width * 4, qr_width * 4);
    }
    else
    {
        s = QSize(50, 50);
    }
    return s;
}

QSize QPrintQcrode::minimumSizeHint()  const
{
    QSize s;
    if(qr != NULL)
    {
        int qr_width = qr->width > 0 ? qr->width : 1;
        s = QSize(qr_width, qr_width);
    }
    else
    {
        s = QSize(50, 50);
    }
    return s;
}
