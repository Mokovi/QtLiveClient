#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QDebug>
#include <QLineEdit>
#include <QToolButton>
#include "mycontrolwidgets.h"
#include "pack.h"
#include <QMessageBox>
#include "qtmaterialautocomplete.h"
#include "qtmaterialcircularprogress.h"
#include "signin.h"
#include "roomselect.h"
#include <QTimer>
#include "liveroom.h"


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    bool connectToServer();
    void initWidgets();
    bool checkNameRule(QString& username) const;
    bool checkPwdRule(QString& password) const;
    void toRoomSelectPic(Pack &pack);


protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;


private slots:
    void pressMinButton();
    void pressCloseButton();
    void pressLogButton();
    void pressToSign();
    void sendLoginData();
    void onConnected();
    void onConnectionError(QAbstractSocket::SocketError socketError);
    void handleLogBackData();

private:
    Ui::Widget *ui;
    QTcpSocket *clientSocket;
    signIn *picSign;
    bool isDragging; // 标志是否正在拖动
    QPoint lastPos;  // 记录鼠标点击的位置
    QString username;
    QString roomId;
    RoomSelect *picRoomSelect;
    QTimer *heartbeatTimer;//用于心跳检测
    LiveRoom *picLiveRoom;
};
#endif // WIDGET_H
