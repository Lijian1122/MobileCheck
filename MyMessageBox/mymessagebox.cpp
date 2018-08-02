#include "mymessagebox.h"
#include "ui_mymessagebox.h"
#include <QFont>
#include <QtMath>
#include <QPainterPath>
#include <QPainter>

MyMessageBox::MyMessageBox(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyMessageBox)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);   //关闭后delete以防内存泄漏
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏

    QFont font = ui->labelTitle->font();
    font.setBold(true);
    ui->labelTitle->setFont(font);

    ui->labelTips->setWordWrap(true);
    ui->labelTips->setAlignment(Qt::AlignTop);

    connect(ui->toolButtonClose, SIGNAL(clicked()), this, SLOT(close()));
    connect(ui->toolButtonOK, SIGNAL(clicked()), this, SLOT(handleOkClicked()));
    connect(ui->toolButtonCancel, SIGNAL(clicked()), this, SLOT(handleCancelClicked()));

    //this->move((parent->width() - this->width())/2, (parent->height() - this->height())/2);
}
void MyMessageBox::paintEvent(QPaintEvent *event)
{
//    QPainter painter(this);
//    painter.setBrush(QColor(255, 255, 255));
//    painter.setPen(Qt::NoPen);
//    painter.drawRect(QRect::QRect(0,0,this->width(),this->height()));


    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    path.addRect(2, 2, this->width()-8, this->height()-8);
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);
    painter.fillPath(path, QBrush(Qt::white));

    QColor color(0, 0, 0, 50);

    for(int i=0; i<4; i++)
    {
            QPainterPath path;
            path.setFillRule(Qt::WindingFill);
            path.addRect(4-i, 4-i, this->width()-(4-i)*2, this->height()-(4-i)*2);
            color.setAlpha(150 - qSqrt(i)*50);
            painter.setPen(color);
            painter.drawPath(path);
    }
}
MyMessageBox::~MyMessageBox()
{
    delete ui;
}

void MyMessageBox::mousePressEvent(QMouseEvent *event)
{
    //只能是鼠标左键移动和改变大小
    if (event->button() == Qt::LeftButton) {
        mouse_press = true;
    }
    //窗口移动距离
    move_point = event->globalPos() - pos();
}

void MyMessageBox::mouseReleaseEvent(QMouseEvent *)
{
    mouse_press = false;
}

void MyMessageBox::mouseMoveEvent(QMouseEvent *event)
{
    //移动窗口
    if (mouse_press)
    {
        QPoint move_pos = event->globalPos();
        move(move_pos - move_point);
    }
}

void MyMessageBox::setBoxInformation(QString title, QString tips, QPixmap pixmap,
                                    bool isCancelHidden, QString okText, QString cancelText)
{
    ui->labelTitle->setText(QString("  ") + title);
    //设置提示信息
    ui->labelTips->setText(tips);
    ui->labelIcon->setPixmap(pixmap);

    ui->toolButtonOK->setText(okText);
    ui->toolButtonCancel->setText(cancelText);
    //是否隐藏取消按钮
    ui->toolButtonCancel->setHidden(isCancelHidden);
    //设置默认按钮为取消按钮
    ui->toolButtonCancel->setFocus();
}
//MyMessageBox *MyMessageBox::newMessageBox(QString title, QString tips, QPixmap pixmap,
//                                               bool isCancelHidden, QString okText, QString cancelText)
//{
//    MyMessageBox *msgBox = new MyMessageBox(this);
//    msgBox->setBoxInformation(title, tips, pixmap, isCancelHidden, okText, cancelText);
//    return msgBox;

//}

//void MyMessageBox::newMessageBox(QString title, QString tips, QPixmap pixmap,
//                                               bool isCancelHidden, QString okText, QString cancelText)
//{
//    //MyMessageBox *msgBox = new MyMessageBox(this);
//    //msgBox->setBoxInformation(title, tips, pixmap, isCancelHidden, okText, cancelText);
//    //return msgBox;

//    return;

//}
void MyMessageBox::showInformationBox(QString title, QString tips, QPixmap pixmap,
                                      bool isCancelHidden, QString okText, QString cancelText)

{
    this->setBoxInformation(title, tips, pixmap, isCancelHidden, okText, cancelText);

    return;
//    MyMessageBox *msgBox;
//    msgBox = newMessageBox(tr("Information"), tr("This is information box!"),
//                                        QPixmap(":/resources/information.png"), true, tr("OK"), tr("Cancel"));
    //msgBox->exec();
}
void MyMessageBox::showWarningBox(QString title, QString tips, QPixmap pixmap,
                             bool isCancelHidden, QString okText, QString cancelText)

{
    setBoxInformation(title, tips, pixmap, isCancelHidden, okText, cancelText);
    return;
//    MyMessageBox *msgBox;
//    msgBox = newMessageBox(tr("Warning"), tr("This is warning box!"),
//                                        QPixmap(":/resources/warning.png"), true, tr("OK"), tr("Cancel"));
//    msgBox->exec();
}

void MyMessageBox::showCriticalBox(QString title, QString tips, QPixmap pixmap,
                              bool isCancelHidden, QString okText, QString cancelText)
{

    setBoxInformation(title, tips, pixmap, isCancelHidden, okText, cancelText);
    return;
//    MyMessageBox *msgBox;
//    msgBox = newMessageBox(tr("Critical"), tr("This is critical box!"),
//                                        QPixmap(":/resources/critical.png"), true, tr("OK"), tr("Cancel"));
//    msgBox->exec();
}

void MyMessageBox::showQuestionBox(QString title, QString tips, QPixmap pixmap,
                              bool isCancelHidden, QString okText, QString cancelText)
{


    setBoxInformation(title, tips, pixmap, isCancelHidden, okText, cancelText);
    return;

//    MyMessageBox *msgBox;
//    msgBox = newMessageBox(tr("Question"), tr("This is question box!"),
//                                        QPixmap(":/resources/question.png"), true, tr("OK"), tr("Cancel"));
//    msgBox->exec();
}
void MyMessageBox::handleOkClicked()
{
    emit okClicked();
    this->accept();
}
void MyMessageBox::handleCancelClicked()
{
    emit cancelClicked();
    this->reject();
}
