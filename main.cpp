#include "widget.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
/*
采用MVC分层架构
客户端：
    1.登录注册界面
        a.共登录、注册界面、找回密码三个界面，界面切换使用滚动方式，并且能够返回登录界面
        b.点击登录/注册按钮后进行服务器连接
        c.登录或者注册的密码框用*代替明文，增加一个眼睛符号，按住可以查看密码
        d.注册时需要填入的信息：用户名，密码，email，验证码
        e.验证码尝试使用stmp
        f.账号密码输入不符合规则，实时呈现错误原因
        g.登录界面实现记住密码
        h.去掉窗口框，并增加鼠标拖拽窗口普通区域均可实现窗口移动
    2.选择房间界面
    3.直播间界面
基础：
    1.采用TCP通信
    2.心跳检测，每5s同服务器进行一次收发，检测用户是否还在线上，若丢失则将数据库中用户状态置0
    3.创建一个pack类，用来进行通信过程中的数据打包
        a.包的内容包括：数据包整体大小packSize,操作行为:operationType,返回状态returnStatus,数据缓存区:dataBuff[1024]
        b.oeprationType包括：登录，注册
        c.returnStatus是个uchar类型,存储对应operationType的返回状态值
        d.在数据读取时需要注意数据的分包以及粘包
    4.数据库user表内容：
        id (INT, PRIMARY KEY, AUTO_INCREMENT): 用户的唯一标识符，通常是自增的整数。
        username (VARCHAR): 用户名，用于用户登录。应确保唯一性（UNIQUE约束）。
        email (VARCHAR): 用户的电子邮件地址，用于找回密码等。应确保唯一性（UNIQUE约束）。
        password_hash (VARCHAR): 存储用户密码的哈希值，而非明文密码。建议使用安全的哈希算法，如 bcrypt、Argon2、PBKDF2 等。
        salt (VARCHAR): 如果使用盐值（Salt），可以存储在这个字段中。每个用户的盐值应是唯一的。
        created_at (TIMESTAMP): 账号创建时间。
        updated_at (TIMESTAMP): 账号信息最近更新的时间。
        last_login (TIMESTAMP): 最近一次登录的时间。
        status (TINYINT): 账号状态（例如，0=未激活，1=激活，2=封禁等）。
    5.

*/
