#ifndef SUB_THREAD_H
#define SUB_THREAD_H

#include <QThread>
#include "external_functions.h"

class transThread: public QThread
{
    Q_OBJECT;
public:
    transThread(QObject* parent=nullptr);
    void rcv_str(std::string str);
protected:
    void run();
signals:
    void send_text(std::string text);
private:
    std::string _str;

};


class A
{
private:
    int _num;
};

#endif // SUB_THREAD_H
