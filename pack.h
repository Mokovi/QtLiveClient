#ifndef PACK_H
#define PACK_H

#include <QStringList>
#include <QString>

enum OperationType{
    INVALID_TYPE,
    LOGIN,
    SIGNIN
};

enum LogStatus{
    INVALID_LOG_STATUS,
    LOG_NAME_RULE_ERROR,
    LOG_PWD_RULE_ERROR,
    LOG_REAPEAT_LOG_ERROR,
    LOG_DB_ERROR,
    LOG_SUCCESS
};

enum SignStatus{
    INVALID_SIGN_STATUS,
    SIGN_NAME_RULE_ERROR,
    SIGN_PWD_RULE_ERROR,
    SIGN_NAME_EXIST_ERROR,
    SIGN_DB_ERROR,
    SIGN_SUCCESS
};

class Pack
{
public:
    Pack();
    ~Pack();

    char* data() {return (char*)this;}
    unsigned int size() {return packSize;}
    void setOperationType(OperationType operationType){this->operationType = operationType;}
    void setLogStatus(LogStatus logStatus){this->status = logStatus;}
    void setSignStatus(SignStatus signStatus){this->status = signStatus;}

    unsigned char getOperationType(){return operationType;}
    unsigned char getLogStatus(){return status;}
    unsigned char getSignStatus(){return status;}


    void clear();
    void append(const QString& str);
    QStringList getData();


private:
    unsigned int packSize;
    unsigned char operationType;
    unsigned char status;
    char dataBuff[1024];

};

#endif // PACK_H