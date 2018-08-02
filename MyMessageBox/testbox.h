#ifndef TESTBOX_H
#define TESTBOX_H

#include <QMainWindow>
#include "mymessagebox.h"

namespace Ui {
class TestBox;
}

class TestBox : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit TestBox(QWidget *parent = 0);
    ~TestBox();
    
private:
    Ui::TestBox *ui;

    MyMessageBox *newMessageBox(QString title, QString tips, QPixmap pixmap,
                              bool isCancelHidden, QString okText, QString cancelText);

public slots:
    void showInformationBox();
    void showWarningBox();
    void showCriticalBox();
    void showQuestionBox();
};

#endif // TESTBOX_H
