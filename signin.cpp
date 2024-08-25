#include "signin.h"
#include "ui_signin.h"

signIn::signIn(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::signIn)
    , isDragging(false)
    , clientSocket(new QTcpSocket(this))
{
    ui->setupUi(this);
    initWidget();
    connect(ui->pushButton_signin, &QPushButton::clicked, this, &signIn::pressSignButton);
    connect(ui->toolButton_back, &QToolButton::clicked, this, [this](){
        this->close();
        emit backToLog();
    });

}

signIn::~signIn()
{
    delete ui;
}

void signIn::pressSignButton()
{
    // 禁用登录按钮，显示进度条
    ui->pushButton_signin->setEnabled(false);
    ui->progressBar_2->setVisible(true);

    // 如果已经连接，直接发送登录数据
    if (clientSocket->state() == QAbstractSocket::ConnectedState)
    {
        sendLoginData();
    }
    else
    {
        // 连接服务器并等待连接成功的信号
        connect(clientSocket, &QTcpSocket::connected, this, &signIn::onConnected);
        connect(clientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onConnectionError(QAbstractSocket::SocketError)));

        clientSocket->connectToHost("127.0.0.1", 13145);
    }
}

void signIn::mousePressEvent(QMouseEvent *event)
{
    // 当鼠标按下时，记录当前位置，并设置拖动标志
    if (event->button() == Qt::LeftButton) {
        isDragging = true;
        lastPos = event->globalPos(); // 获取全局鼠标位置
    }
}

void signIn::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging) {
        // 计算鼠标移动的距离
        QPoint delta = event->globalPos() - lastPos;
        move(pos() + delta); // 移动窗口
        lastPos = event->globalPos(); // 更新上次位置
    }
}

void signIn::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // 鼠标释放时，取消拖动标志
        isDragging = false;
    }
}


void signIn::onConnected()
{
    qDebug() << "成功连接到服务器！";

    // 发送登录数据
    sendLoginData();


    // 连接成功，断开与信号的连接，避免重复连接
    disconnect(clientSocket, &QTcpSocket::connected, this, &signIn::onConnected);
    disconnect(clientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onConnectionError(QAbstractSocket::SocketError)));
}

void signIn::onConnectionError(QAbstractSocket::SocketError socketError)
{
    qDebug() << "无法连接到服务器：" << clientSocket->errorString();

    // 重新启用按钮并隐藏进度条
    ui->pushButton_signin->setEnabled(true);
    ui->progressBar_2->setVisible(false);

    // 连接失败，断开与信号的连接
    disconnect(clientSocket, &QTcpSocket::connected, this, &signIn::onConnected);
    disconnect(clientSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(onConnectionError(QAbstractSocket::SocketError)));
}

void signIn::sendLoginData()
{
    QString strUsername = ui->lineEdit_name_2->text();
    QString strPassword = ui->lineEdit_pwd_2->text();
    QString strPasswordRe = ui->lineEdit_pwd_re->text();
    QString strEmail = ui->lineEdit_email->text();

    if(strPassword != strPasswordRe){
        QMessageBox::warning(this,"warning","两次密码不一致");
        // 重新启用按钮并隐藏进度条
        ui->pushButton_signin->setEnabled(true);
        ui->progressBar_2->setVisible(false);
        return;
    }

    if(!checkNameRule(strUsername)){
        QMessageBox::warning(this,"warning","用户名长度不符和规范（3-12）");
        // 重新启用按钮并隐藏进度条
        ui->pushButton_signin->setEnabled(true);
        ui->progressBar_2->setVisible(false);
        return;
    }
    if(!checkNameRule(strPassword)){
        QMessageBox::warning(this,"warning","密码长度不符和规范（3-12）");
        // 重新启用按钮并隐藏进度条
        ui->pushButton_signin->setEnabled(true);
        ui->progressBar_2->setVisible(false);
        return;
    }
    if(!checkEmailRule(strEmail)){
        QMessageBox::warning(this,"warning","邮箱格式错误。");
        // 重新启用按钮并隐藏进度条
        ui->pushButton_signin->setEnabled(true);
        ui->progressBar_2->setVisible(false);
        return;
    }


    Pack pack;
    pack.append(strUsername);
    pack.append(strPassword);
    pack.append(strEmail);
    pack.setOperationType(SIGNIN);
    clientSocket->write(pack.data(), pack.size());
    // 重新启用按钮并隐藏进度条
    ui->pushButton_signin->setEnabled(true);
    ui->progressBar_2->setVisible(false);


}

void signIn::initWidget()
{
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去除边框
    ui->progressBar_2->setVisible(false);
    connect(ui->toolButton_min_2, &QToolButton::clicked, this, [this](){
        this->showMinimized();
    });
    connect(ui->toolButton_close_2, &QToolButton::clicked, this, [this](){
        this->close();
        exit(1);
    });

}

bool signIn::checkNameRule(QString &username) const
{
    if(username.length() < 3 || username.length() > 12)
    {
        return false;
    }
    else {
        return true;
    }
}

bool signIn::checkPwdRule(QString &password) const
{
    if(password.length() < 3 || password.length() > 12)
    {
        return false;
    }
    else {
        return true;
    }
}

bool signIn::checkEmailRule(QString &email) const
{
    QRegularExpression emailRegex(R"((^[a-zA-Z0-9_.+-]+@[a-zA-Z0-9-]+\.[a-zA-Z0-9-.]+$))");
    QRegularExpressionMatch match = emailRegex.match(email);

    return match.hasMatch();
}
