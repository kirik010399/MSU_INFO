#ifndef READERWRITE_H
#define READERWRITE_H

#include <Qt>
#include <QCoreApplication>
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QString>
#include <Qtime>

const int MaxWait = 100;
const int nWrthreads=20;
const int nRethreads=50;
QString buffer;


QSemaphore read(nReThreads);
QSemaphore cell(1);

class ReThread : public QThread {
    
public:
    ReThread(int i);
    void run(void);
    
private:  int id;
};


class WrThread : public QThread {
    
public:
    WrThread(int i);
    void run(void);
    
private:  int id;
};


#endif // READERWRITE_H
