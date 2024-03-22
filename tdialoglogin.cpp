#include "tdialoglogin.h"
#include "ui_tdialoglogin.h"

TDialogLogin::TDialogLogin(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::TDialogLogin)
    ,timer(new QTimer)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::SplashScreen);
    QApplication::setOrganizationName("WWB-Qt");
    QApplication::setApplicationName("voice transferer");
    setStyleSheet("E:\\Qt projects\\DirectTransfer\\resources\\login.jpg");
    timer->setInterval(1000);
    timer->start();
    connect(timer,&QTimer::timeout,[=](){this->accept();timer->stop();});

}

TDialogLogin::~TDialogLogin()
{
    delete ui;
}

void TDialogLogin::mousePressEvent(QMouseEvent* event)
{
    if(event->button()==Qt::LeftButton)
    {
        m_moving=true;
        m_lastPos=event->globalPosition().toPoint()-this->pos();
    }
    return QDialog::mousePressEvent(event);
}

void TDialogLogin::mouseMoveEvent(QMouseEvent* event)
{
    QPoint eventPos=event->globalPosition().toPoint();
    if(m_moving&&(event->buttons()&Qt::LeftButton)&&(eventPos-m_lastPos).manhattanLength()>QApplication::startDragDistance())
    {
        move(eventPos-m_lastPos);
        m_lastPos=eventPos-this->pos();
    }
    return QDialog::mouseMoveEvent(event);
}

void TDialogLogin::mouseReleaseEvent(QMouseEvent* event)
{
    m_moving=false;
    event->accept();
}

void TDialogLogin::paintEvent(QPaintEvent* event)
{
    QPainter painter(this);
    painter.drawPixmap(rect(),QPixmap("E:\\Qt projects\\DirectTransfer\\resources\\image.jpg"),QRect());
}









void TDialogLogin::on_btnGoin_clicked()
{
    this->accept();
}

