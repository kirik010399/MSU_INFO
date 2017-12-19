#include "ReadWrite.h"

ReThread::ReThread(int i): id(i){}
bool flag = true;

void ReThread::run(void)
{
    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
    msleep(qrand()%MaxWait);
    
    while(flag)
    {}
    
    cell.acquire(0);
    read.acquire(1);
    
    // Printf.lock();
    qDebug() << buffer.toLocal8Bit().constData() << " Reader " << id ;
    qDebug() << "Some Readers Debug information";
    //  Printf.unlock();
    
    read.release(1);
    cell.release(0);
    
    msleep(qrand()%MaxWait);
}



WrThread::WrThread(int i): id(i){}

void WrThread::run(void)
{
    flag = true;
    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
    msleep(qrand()%MaxWait);
    
    while(read.available() != nRethreads)
    {}
    
    cell.acquire(1);
    
    buffer.clear();
    buffer.append("I Wrote my ID ");
    buffer.append(QString::number(id));
    qDebug() << buffer.toLocal8Bit().constData() << " Writer" << id;
    qDebug() << "Some Writers Debug information";
    
    cell.release(1);
    flag = false;
    
    msleep(qrand()%MaxWait);
}


int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    
    ReThread *Rethreads[nRethreads];
    WrThread *Wrthreads[nWrthreads];
    
    qsrand(QTime(0,0,0).msecsTo(QTime::currentTime()));
    
    for (int k = 0; k < nRethreads; k++)
    {
        Rethreads[k] = new ReThread(k);
    }
    for (int k = 0; k < nWrthreads; k++)
    {
        Wrthreads[k] = new WrThread(k);
    }
    
    Wrthreads[0]->start();
    Wrthreads[0]->wait();
    
    for (int k = 0; k < 1000; k++)
    {
        if (qrand()%2 > 0)
        {
            int i = qrand()%nRethreads;
            Rethreads[i]->wait();
            Rethreads[i]->start();
        }
        else
        {
            int i = qrand()%nWrthreads;
            Wrthreads[i]->wait();
            Wrthreads[i]->start();
        }
    }
    
    return 0;
}
