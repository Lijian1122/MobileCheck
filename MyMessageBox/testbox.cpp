#include "testbox.h"
#include "ui_testbox.h"

TestBox::TestBox(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TestBox)
{
    ui->setupUi(this);

    connect(ui->pushButtonInformation, SIGNAL(clicked()), this, SLOT(showInformationBox()));
    connect(ui->pushButtonWarning, SIGNAL(clicked()), this, SLOT(showWarningBox()));
    connect(ui->pushButtonCritical, SIGNAL(clicked()), this, SLOT(showCriticalBox()));
    connect(ui->pushButtonQuestion, SIGNAL(clicked()), this, SLOT(showQuestionBox()));
}

TestBox::~TestBox()
{
    delete ui;
}

void TestBox::showInformationBox()
{
    MyMessageBox *msgBox;
    msgBox = newMessageBox(tr("Information"), tr("This is information box!"),
                                        QPixmap(":/resources/information.png"), true, tr("OK"), tr("Cancel"));
    msgBox->exec();
}

void TestBox::showWarningBox()
{
    MyMessageBox *msgBox;
    msgBox = newMessageBox(tr("Warning"), tr("This is warning box!"),
                                        QPixmap(":/resources/warning.png"), true, tr("OK"), tr("Cancel"));
    msgBox->exec();
}

void TestBox::showCriticalBox()
{
    MyMessageBox *msgBox;
    msgBox = newMessageBox(tr("Critical"), tr("This is critical box!"),
                                        QPixmap(":/resources/critical.png"), true, tr("OK"), tr("Cancel"));
    msgBox->exec();
}

void TestBox::showQuestionBox()
{
    MyMessageBox *msgBox;
    msgBox = newMessageBox(tr("Question"), tr("This is question box!"),
                                        QPixmap(":/resources/question.png"), true, tr("OK"), tr("Cancel"));
    msgBox->exec();
}

MyMessageBox *TestBox::newMessageBox(QString title, QString tips, QPixmap pixmap,
                                               bool isCancelHidden, QString okText, QString cancelText)
{
    MyMessageBox *msgBox = new MyMessageBox(this);
    msgBox->setBoxInformation(title, tips, pixmap, isCancelHidden, okText, cancelText);
    return msgBox;
}

