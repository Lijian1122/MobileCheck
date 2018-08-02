#include "qrcodegenerate.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QrcodeGenerate w;
    w.generateString(QStringLiteral("李薇最美，最漂亮666"));
    w.show();

    return a.exec();
}
