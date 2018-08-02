#include "mainwidget.h"
#include <QDebug>
#include "Common/applist.h"


int mainwidget::screenshotfun()
{
    qDebug()<<"ScreenShot...";
    AppList::number = 0;
    m_adb->AdbScreenShot();
    //m_adb->GetMobileIP();
    return 0;

}
