#ifndef LOGIN_H
#define LOGIN_H

#include <QDialog>
#include <QLineEdit>
#include <QSettings>
#include <QCheckBox>
#include <QtEvents>
#include <QMessageBox>
#include <QBitArray>
#include <QCryptographicHash>

namespace Ui {
class TDialogLogin;
}

class TDialogLogin : public QDialog
{
    Q_OBJECT

private:
    bool m_moving=false;
    QPoint m_lastPos;
    QString m_user="user";
    QString m_pswd="12345";
    int m_tryCount=0;
    void readSettings();
    void writeSettings();
    QString encrypt(const QString& str);


protected:
    void mousePressEvent(QMouseEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

public:
    explicit TDialogLogin(QWidget *parent = nullptr);
    ~TDialogLogin();


private slots:

    void on_btnOK_clicked();
    void on_btnCancel_clicked();

private:
    Ui::TDialogLogin *ui;
};

#endif // LOGIN_H
