#include "Philosophers.h"

int nextPhilosopher(int i);
int previousPhilosopher(int i);

void PhilosopherThread::run(void)
{
    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
    msleep(qrand()%MaxWait);
    
    forksMutex.lock();//чтобы никто не смог изменять значения вилок когда хоть кто-то изменяет его
    
    while (!forks[id] || !forks[nextPhilosopher(id)])//пока хотя бы одна занята
    {
        forksMutex.unlock();
        
        mutex.lock();
        sleepPhilosopher[id].wait(&mutex);
        mutex.unlock();
        
        forksMutex.lock();
    }
    
    forks[id] = false;
    forks[nextPhilosopher(id)] = false;
    
    forksMutex.unlock();
    
    qDebug() << "I'm eating " << id;
    
    forksMutex.lock();
    
    forks[id] = true;
    forks[nextPhilosopher(id)] = true;
    
    sleepPhilosopher[previousPhilosopher(id)].wakeAll();
    sleepPhilosopher[nextPhilosopher(id)].wakeAll();
    
    forksMutex.unlock();
    
    qDebug() << "I'm thinking " << id;
    
    msleep(qrand()%MaxWait);
}

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    PhilosopherThread *Philosophers[countPhilosophers];
    
    for (int i = 0; i < countPhilosophers; ++i)
    {
        Philosophers[i] = new PhilosopherThread(i);
    }
    
    for (int i = 0; i < countPhilosophers; ++i)
    {
        forks[i] = true;
    }
    
    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
    
    for (int i = 0; i < 1000; ++i)
    {
        int index = qrand() % countPhilosophers;
        Philosophers[index]->wait();
        Philosophers[index]->start();
    }
    
    return a.exec();
}

int nextPhilosopher(int i)
{
    return (i+1) % countPhilosophers;
}

int previousPhilosopher(int i)
{
    return (i - 1 + countPhilosophers) % countPhilosophers;
}

