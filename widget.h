#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include "external_functions.h"
#include <QFileDialog>
#include "sub_thread.h"
#include <QMessageBox>
#include <QtMultimedia/QAudioSource>

struct WAVFILEHEADER
{
    // RIFF 头
    char RiffName[4];
    unsigned long nRiffLength;

    // 数据类型标识符
    char WavName[4];

    // 格式块中的块头
    char FmtName[4];
    unsigned long nFmtLength;

    // 格式块中的块数据
    unsigned short nAudioFormat;
    unsigned short nChannleNumber;
    unsigned long nSampleRate;
    unsigned long nBytesPerSecond;
    unsigned short nBytesPerSample;
    unsigned short nBitsPerSample;

    // 数据块中的块头
    char    DATANAME[4];
    unsigned long   nDataLength;
};


QT_BEGIN_NAMESPACE
namespace Ui {
class Widget;
}
QT_END_NAMESPACE

class Widget : public QWidget
{
    Q_OBJECT

public:
    QAudioSource* audio;
    QFile* destinationFile;
    qint64 addWavHeader(QString catheFileName , QString wavFileName);
    void onStateChanged(QAudio::State state);

public:
    Widget(QWidget *parent = nullptr);
    ~Widget();

private slots:
    void on_btnStartTransfer_clicked();
    void on_btnChooseFile_clicked();
    void on_btnSave_clicked();
    void on_btnStopTransfer_clicked();

    void on_btnStartRecord_clicked();

    void on_btnStopRecord_clicked();

    void on_btnChooseDir_clicked();

    void on_btnPauseRecord_clicked();

private:

    transThread* thread;

    Ui::Widget *ui;

signals:
    void startran();
    void threadstop();
};
#endif // WIDGET_H
