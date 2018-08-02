#ifndef PARSEJSON_H
#define PARSEJSON_H

#include <QObject>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QByteArray>
#include <QJsonValue>
#include <Database/mdatabase.h>
#include <Database/cmddata.h>
#include <QStringList>
#include <QLabel>


class ParseJson : public QObject
{
    Q_OBJECT
public:
    ParseJson();
    ~ParseJson();

    bool parseRightJson(QJsonObject object);
    bool ParseVirseJson(QJsonObject object);
    bool parseDetailJson(QJsonObject object);
    bool parseNetTCPJson(QJsonObject object);
    bool parseAppIcon(QByteArray msg);
    bool parseContactJson(QJsonObject object);
    bool parseRecondsJson(QJsonObject object);
    bool parseMessageJson(QJsonObject object);
    bool parseSDDocument(QJsonObject object);
    bool parseMessageExport(QJsonObject object);

    bool parseAppList(QJsonObject object);

    void writeRightCong(QString package,QString ApkPerm);

    QString RightInfoTransCode(QString data);

    void transImage(QString data);

    QString uniCodeToStr(const QByteArray &data);

    static int pngi;

signals:

    void signalmobile(QString);
    void signalpicture(QString);
    void ProgressbarApp(QString);
    void signalAppList(QStringList);
    void singalSafeResult(QJsonObject json);

    void singalContactInfo(QJsonObject json);
    void signalCallhistoryInfo(QJsonObject json);
    void signalMessageInfo(QJsonObject json);
    void signalMessageExport(QJsonObject json);
    void signalFileInfo(QJsonObject json);

    void singalcheckMessage(QJsonObject json);

public slots:

    void parseJsonSlot(QByteArray msg);

private:

    cmdData *m_data;

    static QString appname;

    //QLabel *imagelabel;

};

#endif // PARSEJSON_H
