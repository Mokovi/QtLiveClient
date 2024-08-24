#ifndef SIGNIN_H
#define SIGNIN_H

#include <QWidget>

namespace Ui {
class signIn;
}

class signIn : public QWidget
{
    Q_OBJECT

public:
    explicit signIn(QWidget *parent = nullptr);
    ~signIn();

private:
    Ui::signIn *ui;
};

#endif // SIGNIN_H
