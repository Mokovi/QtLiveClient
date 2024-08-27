#include "roomselect.h"
#include "ui_roomselect.h"

RoomSelect::RoomSelect(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::RoomSelect),
    listModel(new QStringListModel),
    roomId("invalid")
{
    ui->setupUi(this);
    initWidget();
    connect(ui->pushButton_create_room, &QPushButton::clicked, this, [this](){
       emit createRoom();
    });
    QObject::connect(ui->listView_room, &QListView::clicked, [&](const QModelIndex &index) {
            roomId = listModel->data(index, Qt::DisplayRole).toString();
            qDebug() << roomId;
        });
    connect(ui->pushButton_join_room, &QPushButton::clicked, this, [this](){
        if(roomId != "invalid")
        {
            emit joinRoom(roomId);
        }
        QMessageBox::warning(this,"warning", "请选择一个房间。");
    });
}

RoomSelect::~RoomSelect()
{
    delete ui;
}

QString RoomSelect::getRoomId()
{
    return roomId;
}

void RoomSelect::mousePressEvent(QMouseEvent *event)
{
    // 当鼠标按下时，记录当前位置，并设置拖动标志
    if (event->button() == Qt::LeftButton) {
        isDragging = true;
        lastPos = event->globalPos(); // 获取全局鼠标位置
    }
}

void RoomSelect::mouseMoveEvent(QMouseEvent *event)
{
    if (isDragging) {
        // 计算鼠标移动的距离
        QPoint delta = event->globalPos() - lastPos;
        move(pos() + delta); // 移动窗口
        lastPos = event->globalPos(); // 更新上次位置
    }
}

void RoomSelect::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        // 鼠标释放时，取消拖动标志
        isDragging = false;
    }
}

void RoomSelect::handleGotRoomId(QString roomId)
{
    this->roomId = roomId;
}



void RoomSelect::initWidget()
{
    setWindowFlags(Qt::FramelessWindowHint | windowFlags());//去除边框
    connect(ui->toolButton_min_2, &QToolButton::clicked, this, [this](){
        this->showMinimized();
    });
    connect(ui->toolButton_close_2, &QToolButton::clicked, this, [this](){
        this->close();
        exit(1);
        //emit disconnected();
    });
    ui->listView_room->setModel(listModel);
    ui->label_name->setText(username);
}

QString RoomSelect::getUsername() const
{
    return username;
}

void RoomSelect::setUsername(const QString &value)
{
    username = value;
    ui->label_name->setText(username);
}
