#include "sub_thread.h"
#include <windows.h>

transThread::transThread(QObject* parent):QThread(parent) {}

void transThread::rcv_str(std::string str)
{
    _str=str;
}

void transThread::run()
{
    std::string text=voice_transfer(_str);
    emit(send_text(text));
}

