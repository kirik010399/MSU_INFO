#include "critical.h"

int next(int i)
{
    int result = i + 1;
    
    if (result >= nPhilosophers)
        result = 0;
    
    return result;
}

int prev(int i)
{
    int result = i - 1;
    
    if (result < 0)
        result = nPhilosophers - 1;
    
    return result;
}

void PhThread::run(void)
{
    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
    msleep(qrand()%MaxWait);
    
    forkSem.acquire(1);//чтобы никто не смог изменять значения вилок когда хоть кто-то изменяет его
    
    while (!(forks[id] && forks[next(id)]))//пока хотя бы одна занята
    {
        forkSem.release(1);
        
        mutex.lock();
        sleepWaiters[id].wait(&mutex);
        mutex.unlock();
        
        forkSem.acquire(1);
    }
    
    forks[id] = false;
    forks[next(id)] = false;
    
    forkSem.release(1);
    
    qDebug() << "\"I'm eating\" - said Philosopher " << id;
    
    forkSem.acquire(1);
    
    forks[id] = true;
    forks[next(id)] = true;
    
    sleepWaiters[next(id)].wakeAll();
    sleepWaiters[prev(id)].wakeAll();
    
    forkSem.release(1);
    
    qDebug() << "\"I'm thinking\" - said Philosopher " << id;
    
    msleep(qrand()%MaxWait);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    PhThread *Philosophers[nPhilosophers];
    
    for (int k = 0; k < nPhilosophers; k++)
    {
        forks[k] = true;
    }
    
    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
    
    for (int k = 0; k < nPhilosophers; k++)
    {
        Philosophers[k] = new PhThread(k);
    }
    
    for (int k = 0; k < 1000; k++)
    {
        int i = qrand()%nPhilosophers;
        Philosophers[i]->wait();
        Philosophers[i]->start();
    }
    
    return a.exec();
}

