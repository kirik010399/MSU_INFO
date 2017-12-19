#ifndef CRITICAL_H
#define CRITICAL_H

#include <Qt>
#include <QCoreApplication>
#include <QThread>
#include <QDebug>
#include <QString>
#include <QTime>
#include <QTimer>
#include <QMutex>
#include <QSemaphore>
#include <QWaitCondition>

const int MaxWait = 100;
const int nPhilosophers = 5;

QWaitCondition* sleepWaiters = new QWaitCondition[nPhilosophers];

QSemaphore forkSem(1);

QMutex mutex;

bool* forks = new bool[nPhilosophers];

class PhThread : public QThread
{
public:
    PhThread(int i):
    id(i){};
    void run(void);
    
private:
    int id;
};


#endif // CRITICAL_H

