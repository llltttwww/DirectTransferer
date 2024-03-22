#ifndef TDIALOGLOGIN_H
#define TDIALOGLOGIN_H

#include <QDialog>
#include <QLineEdit>
#include <QSettings>
#include <QCheckBox>
#include <QtEvents>
#include <QMessageBox>
#include <QBitArray>
#include <QCryptographicHash>
#include "Windows.h"
#include <QTimer>
#include <QPainter>

namespace Ui {
class TDialogLogin;
}

class TDialogLogin : public QDialog
{
    Q_OBJECT

private:
    bool m_moving=false;
    QPoint m_lastPos;
    int m_tryCount=0;
    QTimer* timer;


protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

public:
    explicit TDialogLogin(QWidget *parent = nullptr);
    ~TDialogLogin();

    void paintEvent(QPaintEvent* event);



private slots:
    void on_btnGoin_clicked();

private:
    Ui::TDialogLogin *ui;
};

#endif // TDIALOGLOGIN_H
