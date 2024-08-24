#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QTcpSocket>
#include <QDebug>
#include <QLineEdit>
#include <QToolButton>
#include "mycontrolwidgets.h"
#include "pack.h"
#include <QMessageBox>


QT_BEGIN_NAMESPACE
namespace Ui { class Widget; }
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private:
    bool connectToServer();
    void initWidgets();

private slots:
    void pressMinButton();
    void pressCloseButton();
    void pressLogButton();
private:
    Ui::Widget *ui;
    QTcpSocket *clientSocket;
};
#endif // WIDGET_H
