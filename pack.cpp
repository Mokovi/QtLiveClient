#include "pack.h"
#include <cstring>  // 包含memset, memcpy等函数

Pack::Pack()
    : packSize(6)  // 前6个字节为包头
    , operationType(INVALID_TYPE)
    , status(INVALID_LOG_STATUS)
{
    memset(dataBuff, 0, sizeof(dataBuff));
}

Pack::~Pack()
{
}

void Pack::clear()
{
    packSize = 6;
    operationType = INVALID_TYPE;
    status = INVALID_LOG_STATUS;
    memset(dataBuff, 0, sizeof(dataBuff));
}

void Pack::append(const QString &str)
{
    QByteArray byteArray = str.toUtf8();  // 转为UTF-8字节数组
    unsigned short strSize = byteArray.size();  // 获取字节数组的大小
    if (packSize + 2 + strSize > sizeof(dataBuff)) {
        // 防止越界
        return;
    }

    memcpy(dataBuff + packSize, &strSize, 2);  // 复制字符串长度
    packSize += 2;

    memcpy(dataBuff + packSize, byteArray.data(), strSize);  // 复制字符串内容
    packSize += strSize;
}

QStringList Pack::getData()
{
    unsigned int readCount = 0;  // 记录已读取的字节数
    unsigned short size = 0;  // 用于存储一条语句的长度
    QStringList strList;

    while (readCount + 2 <= packSize) {  // 确保有足够的字节读取长度
        memcpy(&size, dataBuff + readCount, 2);  // 读取字符串长度
        readCount += 2;

        if (readCount + size > packSize || size >= sizeof(dataBuff)) {
            break;  // 防止越界读取
        }

        QByteArray byteArray(dataBuff + readCount, size);  // 提取对应长度的字节数据
        readCount += size;

        QString strData = QString::fromUtf8(byteArray);  // 从UTF-8字节数组转为QString
        if (!strData.isEmpty()) {
            strList.append(strData);
        }
    }

    return strList;
}
