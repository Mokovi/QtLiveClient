#ifndef ROOMSELECT_H
#define ROOMSELECT_H

#include <QWidget>
#include "qtmaterialscrollbar.h"
#include <QMouseEvent>
#include <QPoint>
#include <QToolButton>
#include <QListView>
#include <QStringListModel>
#include <QDebug>
#include <QMessageBox>

namespace Ui {
class RoomSelect;
}

class RoomSelect : public QWidget
{
    Q_OBJECT

public:
    explicit RoomSelect(QWidget *parent = nullptr);
    ~RoomSelect();
    QString getRoomId();

    QString getUsername() const;
    void setUsername(const QString &value);

protected:
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;

signals:
    void disconnected();
    void createRoom();
    void joinRoom(QString roomId);

public slots:
    void handleGotRoomId(QString roomId);

private:
    void initWidget();

private:
    Ui::RoomSelect *ui;
    bool isDragging; // 标志是否正在拖动
    QPoint lastPos;  // 记录鼠标点击的位置
    QStringListModel* listModel;
    QString roomId;
    QString username;
};

#endif // ROOMSELECT_H
