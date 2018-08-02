#include <QApplication>
#include <mainwidget.h>
#include <QDebug>
#include <QMessageBox>
#include <QTextCodec>
#include <qabstractnativeeventfilter.h>
#include <QAbstractNativeEventFilter>
#include <windows.h>
#include <Database/mdatabase.h>
//#include <QWord/qword.h>
#include <LoginWidget/loginwidget.h>
#include <QSharedMemory>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QEvent>


#pragma comment(lib, "user32.lib")
#if _MSC_VER >= 1600
#pragma execution_character_set("utf-8")
#endif


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    LoginWidget loginwidget;

//    loginwidget.m_mainwidget = new mainwidget();
//    loginwidget.m_mainwidget->close();
    //m_mainwidget = new mainwidget();
    //loginwidget.setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::X11BypassWindowManagerHint);
    loginwidget.show();

    //QEvent *event = new QEvent;

    mDatabase db;
    db.createConnection();
    db.select();
    a.installNativeEventFilter(&loginwidget);
    //a.eventFilter(&loginwidget,QEvent*);

    QSystemSemaphore sema("JAMKey",1,QSystemSemaphore::Open);
    sema.acquire();// 在临界区操作共享内存   SharedMemory

    QSharedMemory mem("SystemObject");// 全局对象名
    if (!mem.create(1))// 如果全局对象以存在则退出
    {
        QMessageBox box(QMessageBox::Warning,QStringLiteral("运行提示"),QStringLiteral("该系统正在运行中！！！"));
        box.setStandardButtons (QMessageBox::Ok);
        box.setButtonText(QMessageBox::Ok,QStringLiteral("确 定"));
        box.setWindowIcon(QIcon("screen/Info2.png"));
        box.exec();
        //QMessageBox::information(0, MESSAGEBOXTXT,"An instance has already been running.");

        sema.release();// 如果是 Unix 系统，会自动释放。

        return 0;
    }

    sema.release();// 临界区

    return a.exec();
}
