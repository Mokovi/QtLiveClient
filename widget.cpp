#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , clientSocket(new QTcpSocket(this))
{
    ui->setupUi(this);
    initWidgets();
    connect(ui->toolButton_min, &QToolButton::clicked, this, &Widget::pressMinButton);
    connect(ui->toolButton_close, &QToolButton::clicked, this, &Widget::pressCloseButton);
    connect(ui->pushButton_login, &QPushButton::clicked, this, &Widget::pressLogButton);
}

Widget::~Widget()
{
    delete ui;
}

bool Widget::connectToServer()
{
    if(clientSocket->state() == QAbstractSocket::ConnectedState)
    {
        return true;
    }
    else
    {
        clientSocket->connectToHost("127.0.0.1", 13145);
        if(!clientSocket->waitForConnected(3000))
        {
            qDebug() << "无法连接到服务器！";
            return false;
        }
        else {
            qDebug() << "成功连接到服务器！";
            return true;
        }
    }

}

void Widget::initWidgets()
{
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去除边框
    ui->lineEdit_pwd->setEchoMode((QLineEdit::EchoMode)2);//设置密码隐藏
    ui->toolButton_close->setStyleSheet("background-color: rgba(251, 115, 115, 0);");//toolButton去除背景色
}

void Widget::pressMinButton()
{
    this->showMinimized();
}

void Widget::pressCloseButton()
{
    this->close();
}

void Widget::pressLogButton()
{
    if(connectToServer())
    {
        QString strUsername = ui->lineEdit_name->text();
        QString strPassword = ui->lineEdit_pwd->text();
        Pack pack;
        pack.append(strUsername);
        pack.append(strPassword);
        pack.setOperationType(LOGIN);
        clientSocket->write(pack.data(), pack.size());
    }
}

