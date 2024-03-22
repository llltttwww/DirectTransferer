#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "external_functions.h"
#include <QFileDialog>
#include "sub_thread.h"
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnStart_clicked();
    void on_btnChooseFile_clicked();
    void on_btnSave_clicked();
    void on_btnStop_clicked();

private:

    transThread* thread;

    Ui::Widget *ui;

signals:
    void startran();
    void threadstop();
};
#endif // WIDGET_H
