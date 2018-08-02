#include "qprintqcrode.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPrintQcrode w;

    QString pathname = ("printqrcode.png");

    w.generateString("123456");

    w.saveImage(pathname,300);

    w.show();

    return a.exec();
}
