#ifndef MYMESSAGEBOX_H
#define MYMESSAGEBOX_H

#include <QDialog>
#include <QMouseEvent>
#include <QPaintEvent>

namespace Ui {
class MyMessageBox;
}

class MyMessageBox : public QDialog
{
    Q_OBJECT
    
public:
    explicit MyMessageBox(QWidget *parent = 0);
    ~MyMessageBox();

    void paintEvent(QPaintEvent *event);

    void setBoxInformation(QString title, QString tips, QPixmap pixmap,
                           bool isCancelHidden, QString okText, QString cancelText);

    void showInformationBox(QString title, QString tips, QPixmap pixmap,
                            bool isCancelHidden, QString okText, QString cancelText);

    void showWarningBox(QString title, QString tips, QPixmap pixmap,
                                 bool isCancelHidden, QString okText, QString cancelText);

    void showCriticalBox(QString title, QString tips, QPixmap pixmap,
                                  bool isCancelHidden, QString okText, QString cancelText);

    void showQuestionBox(QString title, QString tips, QPixmap pixmap,
                                  bool isCancelHidden, QString okText, QString cancelText);

private:
    Ui::MyMessageBox *ui;

    bool mouse_press;
    QPoint move_point;

protected:
    void mousePressEvent(QMouseEvent * event);
    void mouseReleaseEvent(QMouseEvent *);
    void mouseMoveEvent(QMouseEvent *event);

signals:
    void okClicked();
    void cancelClicked();

public slots:
    void handleOkClicked();
    void handleCancelClicked();
};

#endif // MYMESSAGEBOX_H
