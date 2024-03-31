#include "widget.h"
#include "./ui_widget.h"

class transThread;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->btnStopTransfer->setEnabled(false);
    connect(ui->btnStartTransfer,SIGNAL(clicked()),this,SLOT(do_actStart_clicked()));
    thread=new transThread;
    this->setWindowIcon(QIcon("..\\DirectTransfer\\resources\\image.jpg"));
    // connect(this,&Widget::startran,[=](){ui->textResult->setPlainText("转换中，请等待"); });
    QAudioFormat format;
    format.setSampleRate(8000);
    format.setChannelCount(1);
    format.setSampleFormat(QAudioFormat::Int16);
    audio=new QAudioSource(format,this);
    connect(this,&Widget::startran,[=](){QMetaObject::invokeMethod(ui->textResult,"setPlainText",Qt::QueuedConnection,Q_ARG(QString,tr("转换中，请等待")));ui->btnStartTransfer->setEnabled(false);ui->btnChooseFile->setEnabled(false);ui->btnSave->setEnabled(false);ui->filePathEdit->setEnabled(false);ui->textResult->setEnabled(false);ui->btnStopTransfer->setEnabled(true);});
    connect(this,&Widget::startran,[=](){thread->rcv_str(ui->filePathEdit->text().toStdString());thread->start();});
    // connect(thread,&transThread::send_text,[=](std::string text){qDebug()<<"textrcvd\n";ui->textResult->setPlainText(QString::fromLocal8Bit(text));});
    connect(thread,&transThread::send_text,[=](std::string text){QMetaObject::invokeMethod(ui->textResult,"setPlainText",Qt::QueuedConnection,QString::fromLocal8Bit(text));QMetaObject::invokeMethod(ui->btnStartTransfer,"setEnabled",Qt::QueuedConnection,true);
                        QMetaObject::invokeMethod(ui->btnChooseFile,"setEnabled",Qt::QueuedConnection,true);
QMetaObject::invokeMethod(ui->btnSave,"setEnabled",Qt::QueuedConnection,true);
                        QMetaObject::invokeMethod(ui->filePathEdit,"setEnabled",Qt::QueuedConnection,true);
QMetaObject::invokeMethod(ui->textResult,"setEnabled",Qt::QueuedConnection,true);
    QMetaObject::invokeMethod(ui->btnStopTransfer,"setEnabled",Qt::QueuedConnection,false);});
    connect(this,&Widget::threadstop,[=](){QMetaObject::invokeMethod(ui->textResult,"setPlainText",Qt::QueuedConnection,Q_ARG(QString,tr("转换已中止")));
QMetaObject::invokeMethod(ui->btnStartTransfer,"setEnabled",Qt::QueuedConnection,true);
                        QMetaObject::invokeMethod(ui->btnChooseFile,"setEnabled",Qt::QueuedConnection,true);
QMetaObject::invokeMethod(ui->btnSave,"setEnabled",Qt::QueuedConnection,true);
                        QMetaObject::invokeMethod(ui->filePathEdit,"setEnabled",Qt::QueuedConnection,true);
QMetaObject::invokeMethod(ui->textResult,"setEnabled",Qt::QueuedConnection,true);
    QMetaObject::invokeMethod(ui->btnStopTransfer,"setEnabled",Qt::QueuedConnection,false);});
    connect(this->audio,&QAudioSource::stateChanged,this,&Widget::onStateChanged);
}
Widget::~Widget()
{
    delete thread;
    delete audio;
    delete destinationFile;
    delete ui;
}


void Widget::on_btnStartTransfer_clicked()
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

void Widget::on_btnStopTransfer_clicked()
{
    qDebug()<<"stop\n";
    thread->terminate();
    ui->btnStartTransfer->setEnabled(true);
    ui->btnChooseFile->setEnabled(true);
    ui->btnStopTransfer->setEnabled(true);
    ui->filePathEdit->setEnabled(true);
    ui->textResult->setEnabled(true);
    emit(threadstop());
}



void Widget::on_btnStartRecord_clicked()
{
    qDebug()<<"startRecord\n";
    QString pos=ui->dirPathEdit->text();
    QString fname=ui->fileNameEdit->text();
    pos.append("/");
    pos.append(fname);
    pos.append(".raw");
    destinationFile =new QFile(pos);
    destinationFile->open(QIODevice::WriteOnly);

    audio->start(destinationFile);
}


void Widget::on_btnStopRecord_clicked()
{

    qDebug()<<"stopRecord\n";
    QString pos=ui->dirPathEdit->text();
    QString fname=ui->fileNameEdit->text();
    QString raw=pos+"/"+fname+".raw",wav=pos+"/"+fname+".wav";

    audio->stop();
    this->addWavHeader(raw,wav);
    destinationFile->close();
    ui->filePathEdit->setText(wav);
}

qint64 Widget::addWavHeader(QString catheFileName , QString wavFileName)
{
    // 开始设置WAV的文件头
    // 这里具体的数据代表什么含义请看上一篇文章（Qt之WAV文件解析）中对wav文件头的介绍
    WAVFILEHEADER WavFileHeader;
    qstrcpy(WavFileHeader.RiffName, "RIFF");
    qstrcpy(WavFileHeader.WavName, "WAVE");
    qstrcpy(WavFileHeader.FmtName, "fmt ");
    qstrcpy(WavFileHeader.DATANAME, "data");

    // 表示 FMT块 的长度
    WavFileHeader.nFmtLength = 16;
    // 表示 按照PCM 编码;
    WavFileHeader.nAudioFormat = 1;
    // 声道数目;
    WavFileHeader.nChannleNumber = 1;
    // 采样频率;
    WavFileHeader.nSampleRate = 8000;

    // nBytesPerSample 和 nBytesPerSecond这两个值通过设置的参数计算得到;
    // 数据块对齐单位(每个采样需要的字节数 = 通道数 × 每次采样得到的样本数据位数 / 8 )
    WavFileHeader.nBytesPerSample = 2;
    // 波形数据传输速率
    // (每秒平均字节数 = 采样频率 × 通道数 × 每次采样得到的样本数据位数 / 8  = 采样频率 × 每个采样需要的字节数 )
    WavFileHeader.nBytesPerSecond = 16000;

    // 每次采样得到的样本数据位数;
    WavFileHeader.nBitsPerSample = 16;

    QFile cacheFile(catheFileName);
    QFile wavFile(wavFileName);

    if (!cacheFile.open(QIODevice::ReadWrite))
    {
        return -1;
    }
    if (!wavFile.open(QIODevice::WriteOnly))
    {
        return -2;
    }

    int nSize = sizeof(WavFileHeader);
    qint64 nFileLen = cacheFile.bytesAvailable();

    WavFileHeader.nRiffLength = nFileLen - 8 + nSize;
    WavFileHeader.nDataLength = nFileLen;

    // 先将wav文件头信息写入，再将音频数据写入;
    wavFile.write((char *)&WavFileHeader, nSize);
    wavFile.write(cacheFile.readAll());

    cacheFile.close();
    wavFile.close();

    return nFileLen;
}

void Widget::on_btnChooseDir_clicked()
{
    QFileDialog fileDialog= QFileDialog(this);
    fileDialog.setFileMode(QFileDialog::Directory);
    QString selectDir = QFileDialog::getExistingDirectory();
    qDebug()<<selectDir<<'\n';
    ui->dirPathEdit->setText(selectDir);
}

void Widget::on_btnPauseRecord_clicked()
{

    qDebug()<<"pauseRecord\n";
    audio->suspend();
}

void Widget::onStateChanged(QAudio::State state)
{
    switch (state) {
    case QAudio::State::ActiveState:
        ui->btnStartRecord->setEnabled(false);
        ui->btnPauseRecord->setEnabled(true);
        ui->btnStopRecord->setEnabled(true);
        ui->btnPauseRecord->setText("暂停录音");
        break;
    case QAudio::State::SuspendedState:
        ui->btnPauseRecord->setEnabled(true);
        ui->btnStopRecord->setEnabled(true);
        ui->btnPauseRecord->setText("继续录音");
        break;
    case QAudio::State::StoppedState:
        ui->btnPauseRecord->setText("暂停录音");
        ui->btnStartRecord->setEnabled(true);
        ui->btnPauseRecord->setEnabled(false);
        ui->btnStopRecord->setEnabled(false);
        break;
    }

}



