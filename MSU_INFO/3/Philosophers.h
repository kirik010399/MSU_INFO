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
#include <QWaitCondition>

const int MaxWait = 100;
const int countPhilosophers = 10;
bool* forks = new bool[countPhilosophers];

QWaitCondition* sleepPhilosopher = new QWaitCondition[countPhilosophers];
QMutex forksMutex;
QMutex mutex;

class PhilosopherThread : public QThread
{
public:
    PhilosopherThread(int i):id(i){};
    void run(void);
    
private:
    int id;
};


#endif // CRITICAL_H

