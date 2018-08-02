#include "msgbox.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

     MsgBox *msg_box2 = new MsgBox();
     //QString msg= QStringLiteral("文件名||不能||包含||下列||任何||字符||tyuuuju");
     //msg_box2->setInfo(QStringLiteral("检测详细信息"), msg, QString("../source/logo.ico"));
     msg_box2->setExport(QStringLiteral("检测报表导出"));
     msg_box2->show();

     return a.exec();
}
