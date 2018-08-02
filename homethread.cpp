#include <downwidget.h>
#include <applist.h>

HomeThread::HomeThread(QObject *parent)
{
    stopped = false;
}

HomeThread::~HomeThread()
{


}

void HomeThread::run()
{
    qDebug()<<"12344 run run ";
    //emit started("yjyj");
}
void HomeThread::stop()
{
    stopped = true;
}

void HomeThread::ResetSlot()
{

}
