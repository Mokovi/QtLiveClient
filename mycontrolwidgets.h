#ifndef MYCONTROLWIDGETS_H
#define MYCONTROLWIDGETS_H

#include <QWidget>
#include <QToolButton>

class MyToolButtonClose : public QToolButton{
    Q_OBJECT
public:

    explicit MyToolButtonClose(QWidget *parent = nullptr);

protected:

    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

};

class MyToolButtonMin : public QToolButton{
    Q_OBJECT
public:

    explicit MyToolButtonMin(QWidget *parent = nullptr);

protected:

    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

};

class MyToolButtonFont : public QToolButton{
    Q_OBJECT
public:

    explicit MyToolButtonFont(QWidget *parent = nullptr);

protected:

    void enterEvent(QEvent *event) override;
    void leaveEvent(QEvent *event) override;

};

#endif // MYCONTROLWIDGETS_H
