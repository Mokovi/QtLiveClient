#ifndef LIVEROOM_H
#define LIVEROOM_H

#include <QWidget>
#include <QPoint>
#include <QMouseEvent>

namespace Ui {
class LiveRoom;
}

class LiveRoom : public QWidget
{
    Q_OBJECT

public:
    explicit LiveRoom(QWidget *parent = nullptr,QString roomId = "invalid");
    ~LiveRoom();
    void setRoomId(QString roomId);
    QString getRoomOwner() const;
    void setRoomOwner(const QString &value);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
private:
    void initWidget();
private:
    Ui::LiveRoom *ui;
    bool isDragging; // 标志是否正在拖动
    QPoint lastPos;  // 记录鼠标点击的位置
    QString roomId;
    QString roomOwner;
};

#endif // LIVEROOM_H
