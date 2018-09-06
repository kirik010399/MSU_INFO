// n процессов (Заготовка).
#include "critical.h"

const int nThreads=2;
int cr=0;

bool* Threads::array = new bool [1];
int Threads::turn = 0;

void Threads::run(void)
{
    while (1)
    {
        // код писать сюда
        array[id] = true;
        turn = 1 - id;
        while (turn == 1 - id && array[1-id] == true)
        {}

        Critical_section(id);
        
        // код писать сюда
        array[id] = false;
        
        msleep(qrand()%MaxWait);
        Reminder_section(id);
    }
}

void Threads::Critical_section(int i)
{
    if (cr++) qDebug() <<  " Critical section " << i << " alarm  "  ;
    
    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
    msleep(qrand()%MaxWait);
    cr--;
}

void Threads::Reminder_section(int i)
{
    qDebug() <<  " Process " << i ;
    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
    msleep(qrand()%MaxWait);
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    Threads *Thread[nThreads];
    
    Threads::array = new bool[nThreads];
    for (int i = 0; i < nThreads; ++i)
        Threads::array[i] = false; 
        
    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
    
    for (int k = 0; k < nThreads; k++)
    {
        Thread[k] = new Threads(k);
        Thread[k]->start();
    }
    return a.exec();
}

