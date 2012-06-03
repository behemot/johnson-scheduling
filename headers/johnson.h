/**
 * 
 * @author Michał Białas <michal.bialas@mbialas.pl>
 *
 */

#ifndef _JOHNSON_H
#define _JOHNSON_H

#include <QString>

struct Task
{
    QString name;
    int resource;
    int startAt;
    Task(QString name, int resource);
};

class Johnson
{
    public:
        Johnson();
        void setTasks(Task*** tasks, int p, int n);
        void run();
        Task*** getResult();
    private:
        Task*** taskTable;
        Task*** result;
        int amountOfTasks;
        int amountOfProcessors;
};

struct DoubleTask
{
    Task* p1;
    Task* p2;
    DoubleTask() { p1 = NULL; p2 = NULL; };
};

#endif //_JOHNSON_H

