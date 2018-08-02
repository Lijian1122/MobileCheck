#ifndef AUTHORIZA_H
#define AUTHORIZA_H
#include <Windows.h>
//#include <afx.h>
#include <QObject>
#include <QAbstractNativeEventFilter>
#include <QNetworkInterface>
#include <QList>

//, public QAbstractNativeEventFilter
class Authoriza : public QObject
{
    Q_OBJECT

public:
    Authoriza();

    ~Authoriza();

    bool AuthorizaInitialize();

    bool AuthorizaInitializeRemove();

    QString getHostMacAddress();

    QString getDiskNumber();

};

#endif // AUTHORIZA_H
