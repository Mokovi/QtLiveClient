#include "widget.h"
#include "ui_widget.h"

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
    , clientSocket(new QTcpSocket(this))
    , picSign(new signIn(nullptr))
    , isDragging(false)
{
    ui->setupUi(this);
    initWidgets();
    connect(ui->toolButton_min, &QToolButton::clicked, this, &Widget::pressMinButton);
    connect(ui->toolButton_close, &QToolButton::clicked, this, &Widget::pressCloseButton);
    connect(ui->pushButton_login, &QPushButton::clicked, this, &Widget::pressLogButton);
    connect(ui->toolButton_signin, &QPushButton::clicked, this, &Widget::pressToSign);
}

Widget::~Widget()
{
    delete picSign;
    delete ui;
}

void Widget::initWidgets()
{
    setWindowFlags(Qt::FramelessWindowHint | windowFlags()); // 去除边框
    ui->lineEdit_pwd->setEchoMode(QLineEdit::Password); // 设置密码隐藏
    ui->toolButton_close->setStyleSheet("background-color: rgba(251, 115, 115, 0);"); // toolButton去除背景色
    ui->progressBar->setVisible(false);
}

bool Widget::checkNameRule(QString &username) const
{
    if(username.length() < 3 || username.length() > 12)
    {
        return false;
    }
    else {
        return true;
    }
}

bool Widget::checkPwdRule(QString &password) const
{
    if(password.length() < 3 || password.length() > 12)
    {
        return false;
    }
    else {
        return true;
    }
}

void Widget::toRoomSelectPic()
{

}

void Widget::mousePressEvent(QMouseEvent *event)
{
    // 当鼠标按下时，记录当前位置，并设置拖动标志
    if (event->button() == Qt::LeftButton) {
        isDragging = true;
        lastPos = event->globalPos(); // 获取全局鼠标位置
    }
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging) {
        // 计算鼠标移动的距离
        QPoint delta = event->globalPos() - lastPos;
        move(pos() + delta); // 移动窗口
        lastPos = event->globalPos(); // 更新上次位置
    }
}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // 鼠标释放时，取消拖动标志
        isDragging = false;
    }
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
    // 禁用登录按钮，显示进度条
    ui->pushButton_login->setEnabled(false);
    ui->progressBar->setVisible(true);

    // 如果已经连接，直接发送登录数据
    if (clientSocket->state() == QAbstractSocket::ConnectedState)
    {
        sendLoginData();
    }
    else
    {
        // 连接服务器并等待连接成功的信号
        connect(clientSocket, &QTcpSocket::connected, this, &Widget::onConnected);
        connect(clientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onConnectionError(QAbstractSocket::SocketError)));

        clientSocket->connectToHost("127.0.0.1", 13145);
    }
}

void Widget::pressToSign()
{
    hide();
    picSign->show();
    connect(picSign, &signIn::backToLog, this, [this]() {
        show();
        disconnect(picSign, &signIn::backToLog, this, nullptr);
    });
}

void Widget::onConnected()
{
    qDebug() << "成功连接到服务器！";

    // 发送登录数据
    sendLoginData();


    // 连接成功，断开与信号的连接，避免重复连接
    disconnect(clientSocket, &QTcpSocket::connected, this, &Widget::onConnected);
    disconnect(clientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onConnectionError(QAbstractSocket::SocketError)));
}

void Widget::onConnectionError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "无法连接到服务器：" << clientSocket->errorString();

    // 重新启用按钮并隐藏进度条
    ui->pushButton_login->setEnabled(true);
    ui->progressBar->setVisible(false);

    // 连接失败，断开与信号的连接
    disconnect(clientSocket, &QTcpSocket::connected, this, &Widget::onConnected);
    disconnect(clientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onConnectionError(QAbstractSocket::SocketError)));
}


void Widget::handleLogBackData()
{
    Pack pack;
    clientSocket->read(pack.data(), pack.size());
    qDebug()<<pack.getOperationType();
    qDebug() << pack.getLogStatus();
    if(pack.getOperationType() != LOGIN) return;
    switch ((LogStatus)pack.getLogStatus()) {
    case LOG_NAME_RULE_ERROR:
        QMessageBox::warning(this,"警告", "用户名长度不符合规范（3-12）");
        break;
    case LOG_PWD_RULE_ERROR:
        QMessageBox::warning(this,"警告", "密码长度不符合规范（3-12）");
        break;
    case LOG_REAPEAT_LOG_ERROR:
        QMessageBox::warning(this,"警告", "该账户已经登录");
        break;
    case LOG_INPUT_NAME_ERROR:
    case LOG_INPUT_PWD_ERROR:
        QMessageBox::warning(this,"警告", "用户名或者密码错误。");
        break;
    case LOG_DB_ERROR:
        QMessageBox::warning(this,"警告", "数据库错误");
        break;
    case LOG_SUCCESS:
        QMessageBox::information(this,"通知", "登录成功！");
        toRoomSelectPic();
        break;
    }
}

void Widget::sendLoginData()
{
    QString strUsername = ui->lineEdit_name->text();
    QString strPassword = ui->lineEdit_pwd->text();
    if(!checkNameRule(strUsername)){
        QMessageBox::warning(this,"warning","The length of the username does not match the specifications（3-12）");
        // 重新启用按钮并隐藏进度条
        ui->pushButton_login->setEnabled(true);
        ui->progressBar->setVisible(false);

        return;
    }
    if(!checkNameRule(strPassword)){
        QMessageBox::warning(this,"warning","The length of the password does not match the specifications（3-12）");
        // 重新启用按钮并隐藏进度条
        ui->pushButton_login->setEnabled(true);
        ui->progressBar->setVisible(false);

        return;
    }
    Pack pack;
    pack.append(strUsername);
    pack.append(strPassword);
    pack.setOperationType(LOGIN);
    clientSocket->write(pack.data(), pack.size());
    connect(clientSocket,&QTcpSocket::readyRead, this, &Widget::handleLogBackData);
    // 重新启用按钮并隐藏进度条
    ui->pushButton_login->setEnabled(true);
    ui->progressBar->setVisible(false);


}
