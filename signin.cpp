#include "signin.h"
#include "ui_signin.h"

signIn::signIn(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::signIn)
{
    ui->setupUi(this);
}

signIn::~signIn()
{
    delete ui;
}
