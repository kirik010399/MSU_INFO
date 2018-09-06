#ifndef CRITICAL_H
#define CRITICAL_H

#include <Qt>
#include <QCoreApplication>
#include <QThread>
#include <QDebug>
#include <QString>
#include <QTime>
#include <QTimer>

const int MaxWait =500;

class Threads : public QThread {

private:  int id;

public:
    Threads(int i):
        id(i){};
    
    static bool* array;
    static int turn;
    
    void Critical_section(int);
    void Reminder_section(int);
    void run(void);

};



#endif // CRITICAL_H
