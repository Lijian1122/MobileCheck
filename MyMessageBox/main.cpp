//#include "testbox.h"
#include <QApplication>
#include <mymessagebox.h>

int main(int argc, char *argv[])
{
   QApplication a(argc, argv);

   MyMessageBox *msgBox = new MyMessageBox();
   msgBox->showInformationBox(QStringLiteral("提示"), QStringLiteral("这是一个消息框!"),
                             QPixmap(":/resources/information.png"), true, QStringLiteral("确定"), QStringLiteral("取消"));
   msgBox->show();

    //TestBox w;
    //w.show();
    return a.exec();
}
