#include "pack.h"

Pack::Pack()
    : packSize(6)
    , operationType(0)
    , status(0)
{
    memset(dataBuff, 0, 1024);
}

Pack::~Pack()
{

}


void Pack::clear()
{
    packSize = 6;
    operationType = 0;
    status = 0;
    memset(dataBuff, 0, 1024);
}

void Pack::append(const QString &str)
{
    // 获取val里面数据内存里面有多少个字节（所有的数据在内存中都是字节方式存放的）。
    unsigned short strSize = strlen(str.toLocal8Bit().data());  // 获取val里面的数据占多少个字节
    memcpy(dataBuff + packSize, &strSize, 2); // 把size里面前2个字节的内容拷贝到m_buf + m_count里面
    packSize += 2;

    memcpy(dataBuff + packSize, str.toLocal8Bit().data(), strSize);
    packSize += strSize;

}

QStringList Pack::getData()
{
    unsigned int readCount = 0; // 用来记录已经从databuff中读取了多少个字节
    unsigned short size = 0;//用来存储一条语句的长度
    QStringList strlist;
    while(true)
    {
        memcpy(&size, dataBuff + readCount, 2);
        readCount += 2;
        char temp[1024] = {0};
        temp[size] = '\0';//标记结尾

        memcpy(temp, dataBuff + readCount, size); // 读取数据放进temp里面
        readCount += size;

        QString strdata = QString::fromLocal8Bit(temp); // 把temp里面的字节数据转为QString
        if(!strdata.isEmpty())
        {
            strlist.append(strdata);
        }
        if(0 == dataBuff[readCount])  // 如果后续没有数据退出循环,若有数据此处应当为数据长度
        {
            break;
        }
    }

    return strlist;
}
