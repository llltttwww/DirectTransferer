#include "widget.h"
#include "./ui_widget.h"

class transThread;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    connect(ui->btnStart,SIGNAL(clicked()),this,SLOT(do_actStart_clicked()));
    thread=new transThread;
    this->setWindowIcon(QIcon("E:\\Qt projects\\DirectTransfer\\resources\\image.jpg"));
    // connect(this,&Widget::startran,[=](){ui->textResult->setPlainText("转换中，请等待"); });
    connect(this,&Widget::startran,[=](){QMetaObject::invokeMethod(ui->textResult,"setPlainText",Qt::QueuedConnection,Q_ARG(QString,tr("转换中，请等待")));ui->btnStart->setEnabled(false);ui->btnChooseFile->setEnabled(false);ui->btnSave->setEnabled(false);ui->filePathEdit->setEnabled(false);ui->textResult->setEnabled(false);});
    connect(this,&Widget::startran,[=](){thread->rcv_str(ui->filePathEdit->text().toStdString());thread->start();});
    // connect(thread,&transThread::send_text,[=](std::string text){qDebug()<<"textrcvd\n";ui->textResult->setPlainText(QString::fromLocal8Bit(text));});
    connect(thread,&transThread::send_text,[=](std::string text){QMetaObject::invokeMethod(ui->textResult,"setPlainText",Qt::QueuedConnection,QString::fromLocal8Bit(text));QMetaObject::invokeMethod(ui->btnStart,"setEnabled",Qt::QueuedConnection,true);
                        QMetaObject::invokeMethod(ui->btnChooseFile,"setEnabled",Qt::QueuedConnection,true);
QMetaObject::invokeMethod(ui->btnSave,"setEnabled",Qt::QueuedConnection,true);
                        QMetaObject::invokeMethod(ui->filePathEdit,"setEnabled",Qt::QueuedConnection,true);
QMetaObject::invokeMethod(ui->textResult,"setEnabled",Qt::QueuedConnection,true);});
    connect(this,&Widget::threadstop,[=](){QMetaObject::invokeMethod(ui->textResult,"setPlainText",Qt::QueuedConnection,Q_ARG(QString,tr("转换已中止")));
QMetaObject::invokeMethod(ui->btnStart,"setEnabled",Qt::QueuedConnection,true);
                        QMetaObject::invokeMethod(ui->btnChooseFile,"setEnabled",Qt::QueuedConnection,true);
QMetaObject::invokeMethod(ui->btnSave,"setEnabled",Qt::QueuedConnection,true);
                        QMetaObject::invokeMethod(ui->filePathEdit,"setEnabled",Qt::QueuedConnection,true);
QMetaObject::invokeMethod(ui->textResult,"setEnabled",Qt::QueuedConnection,true);});
}
Widget::~Widget()
{
    delete ui;
}


void Widget::on_btnStart_clicked()
{
    // ui->textResult->setPlainText("Waiting");
    // qDebug()<<"clicked\n";
    // std::string path=ui->filePathEdit->text().toStdString();
    // qDebug()<<path<<"\n";
    // QString qstr=QString::fromLocal8Bit(voice_transfer(path));
    // ui->textResult->setPlainText(qstr);
    emit(startran());
}

void Widget::on_btnChooseFile_clicked()
{
    QString pathName;
    pathName = QFileDialog::getOpenFileName(this,tr("打开文件"),
                                            "~/",tr("Wave Files(*.wav)"));
    ui->filePathEdit->setFont(QFont("Times New Roman",10));
    ui->filePathEdit->setText(pathName);
}

void Widget::on_btnSave_clicked()
{
    //创建一个file文件
    QFileDialog fileDialog;
    QString fileName = fileDialog.getSaveFileName(this,tr("Open File"),"/data",tr("Text File(*.txt)"));
    if(fileName == "")
    {
        return;
    }
    QFile file(fileName);//可以自己选择路径来保存文件名
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
        QMessageBox::warning(this,tr("错误"),tr("打开文件失败"));
        return;
    }
    else
    {
        QTextStream textStream(&file);
        QString str = ui->textResult->toPlainText();//从textEdit里面回去内容，然后再直接拿来用
        textStream<<str;
        QMessageBox::warning(this,tr("提示"),tr("保存文件成功"));
        file.close();
    }

}

void Widget::on_btnStop_clicked()
{
    qDebug()<<"stop\n";
    thread->terminate();
    ui->btnStart->setEnabled(true);
    ui->btnChooseFile->setEnabled(true);
    ui->btnStop->setEnabled(true);
    ui->filePathEdit->setEnabled(true);
    ui->textResult->setEnabled(true);
    emit(threadstop());
}
