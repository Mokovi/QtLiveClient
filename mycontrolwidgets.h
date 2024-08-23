#ifndef MYCONTROLWIDGETS_H
#define MYCONTROLWIDGETS_H

#include <QWidget>
#include <QToolButton>

class MyToolButton : public QToolButton{
    Q_OBJECT
public:

    explicit MyToolButton(QWidget *parent = nullptr);

protected:

    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

};


#endif // MYCONTROLWIDGETS_H
