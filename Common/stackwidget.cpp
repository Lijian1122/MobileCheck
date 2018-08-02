#include "stackwidget.h"

stackwidget::stackwidget(QWidget *parent) : QWidget(parent)
{

}

void stackwidget::slotHomePageshow()
{
    //分割线框
    QWidget *cutoff1 = new QWidget(this);
    //cutoff1->setFixedSize(930,2);
    cutoff1->setStyleSheet("background-image:url(:/source/Image/cutoff.jpg)");
    //cutoff1->setGeometry(350,105,930,2);
    cutoff1->setGeometry(350,105,(this->maximumWidth() - 350),2);
}
