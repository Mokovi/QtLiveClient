#include "liveroom.h"
#include "ui_liveroom.h"

LiveRoom::LiveRoom(QWidget *parent, QString roomId)
    : QWidget(parent)
    , ui(new Ui::LiveRoom)
    , roomId(roomId)
{
    ui->setupUi(this);
    initWidget();

}

LiveRoom::~LiveRoom()
{
    delete ui;
}

void LiveRoom::setRoomId(QString roomId)
{
    this->roomId = roomId;
}


void LiveRoom::mousePressEvent(QMouseEvent *event)
{
    // 当鼠标按下时，记录当前位置，并设置拖动标志
    if (event->button() == Qt::LeftButton) {
        isDragging = true;
        lastPos = event->globalPos(); // 获取全局鼠标位置
    }
}

void LiveRoom::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging) {
        // 计算鼠标移动的距离
        QPoint delta = event->globalPos() - lastPos;
        move(pos() + delta); // 移动窗口
        lastPos = event->globalPos(); // 更新上次位置
    }
}

void LiveRoom::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // 鼠标释放时，取消拖动标志
        isDragging = false;
    }
}

void LiveRoom::initWidget()
{
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去除边框
    connect(ui->toolButton_min, &QToolButton::clicked, this, [this](){
        this->showMinimized();
    });
    connect(ui->toolButton_close, &QToolButton::clicked, this, [this](){
        this->close();
        exit(1);
        //emit disconnected();
    });
    ui->label_name->setText(roomOwner+"'s room");
}

QString LiveRoom::getRoomOwner() const
{
    return roomOwner;
}

void LiveRoom::setRoomOwner(const QString &value)
{
    roomOwner = value;
    ui->label_name->setText(roomOwner+"'s room");
}
