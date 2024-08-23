#include "mycontrolwidgets.h"
#include<QDebug>


MyToolButton::MyToolButton(QWidget *parent)
    :QToolButton(parent)
{

}

void MyToolButton::enterEvent(QEvent *event)
{
    this->setStyleSheet("background-color: rgba(251, 115, 115, 255); ");
    QToolButton::enterEvent(event);
}

void MyToolButton::leaveEvent(QEvent *event)
{
    this->setStyleSheet("background-color: rgba(251, 115, 115, 0);");
    QToolButton::leaveEvent(event);
}
