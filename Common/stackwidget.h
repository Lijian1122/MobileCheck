#ifndef STACKWIDGET_H
#define STACKWIDGET_H

#include <QWidget>

static QString MessageExportInfo[10000];

class stackwidget : public QWidget
{
    Q_OBJECT
public:
    explicit stackwidget(QWidget *parent = 0);

signals:

public slots:

    void slotHomePageshow();

public:

};

#endif // STACKWIDGET_H
