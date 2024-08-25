#ifndef SIGNIN_H
#define SIGNIN_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>
#include <QTcpSocket>
#include "pack.h"
#include <QRegularExpression> //正则表达式，用来实现邮箱规范检测
#include <QMessageBox>

namespace Ui {
class signIn;
}

class signIn : public QWidget
{
    Q_OBJECT

public:
    explicit signIn(QWidget *parent = nullptr);
    ~signIn();

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void backToLog();

private slots:
    void pressSignButton();
    void sendLoginData();
    void onConnected();
    void onConnectionError(QAbstractSocket::SocketError socketError);

private:
    Ui::signIn *ui;
    bool isDragging; // 标志是否正在拖动
    QPoint lastPos;  // 记录鼠标点击的位置
    QTcpSocket* clientSocket;

private:
    void initWidget();
    bool checkNameRule(QString& username) const;
    bool checkPwdRule(QString& password) const;
    bool checkEmailRule(QString& email) const;
};

#endif // SIGNIN_H
