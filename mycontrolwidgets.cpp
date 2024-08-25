#include "mycontrolwidgets.h"
#include<QDebug>


MyToolButtonClose::MyToolButtonClose(QWidget *parent)
    :QToolButton(parent)
{

}

void MyToolButtonClose::enterEvent(QEvent *event)
{
    this->setStyleSheet("background-color: rgba(251, 115, 115, 180); ");
    QToolButton::enterEvent(event);
}

void MyToolButtonClose::leaveEvent(QEvent *event)
{
    this->setStyleSheet("background-color: rgba(251, 115, 115, 0);");
    QToolButton::leaveEvent(event);
}

MyToolButtonMin::MyToolButtonMin(QWidget *parent)
    :QToolButton(parent)
{

}

void MyToolButtonMin::enterEvent(QEvent *event)
{
    this->setStyleSheet("background-color: rgba(240, 240, 240, 100); ");
    QToolButton::enterEvent(event);
}

void MyToolButtonMin::leaveEvent(QEvent *event)
{
    this->setStyleSheet("background-color: rgba(240, 240, 240, 0);");
    QToolButton::leaveEvent(event);
}

MyToolButtonFont::MyToolButtonFont(QWidget *parent)
    :QToolButton(parent)
{

}

void MyToolButtonFont::enterEvent(QEvent *event)
{
    // 获取当前字体
    QFont font = this->font();
    // 设置字体加粗
    font.setBold(true);
    // 应用新的字体
    this->setFont(font);
    QToolButton::enterEvent(event);
}

void MyToolButtonFont::leaveEvent(QEvent *event)
{
    // 获取当前字体
    QFont font = this->font();
    // 取消字体加粗
    font.setBold(false);
    // 应用新的字体
    this->setFont(font);
    QToolButton::leaveEvent(event);
}

