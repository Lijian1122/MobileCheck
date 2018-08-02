#ifndef MDATABASE_H
#define MDATABASE_H
#include <QSqlDatabase>
#include <QSql>

#include <QObject>

class mDatabase : public QObject
{
    Q_OBJECT
public:
    explicit mDatabase(QObject *parent = 0);

    bool createConnection();
    void closeConnection(QSqlDatabase);

    void readSqlConfg();
    void select();

signals:

public slots:

private:

    QString localhost;
    int  port;
    QString username;
    QString password;
    QString database;
};

#endif // MDATABASE_H
