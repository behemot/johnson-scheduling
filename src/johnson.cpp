/**
 * 
 * @author Michał Białas <michal.bialas@mbialas.pl>
 *
 */

#include "johnson.h"
#include <cstdlib>
#include <QDebug>

Task::Task(QString name, int resource) : name(name), resource(resource) {}

Johnson::Johnson()
{
    amountOfTasks = 0;
    amountOfProcessors = 0;
}

void Johnson::setTasks(Task*** tasks, int p, int n)
{
    taskTable = tasks;
    amountOfTasks = n;
    amountOfProcessors = p;
}

int compare_TaskA(const void *a, const void *b)
{
    return (int)(((DoubleTask*)a)->p1->resource >= ((DoubleTask*)b)->p1->resource);
}

int compare_TaskB(const void *a, const void *b)
{
    return (int)(((DoubleTask*)a)->p2->resource <= ((DoubleTask*)b)->p2->resource);
}

bool cmp_toA(Task* a, Task* b)
{
    return a->resource <= b->resource;
}

void Johnson::run()
{
    DoubleTask A[100];
    DoubleTask B[100];

    int aidx = 0;
    int bidx = 0;
    for (int i = 0; i < amountOfTasks; ++i) {
        if (cmp_toA(taskTable[0][i], taskTable[1][i])) {
            A[aidx].p1 = taskTable[0][i];
            A[aidx].p2 = taskTable[1][i];
            ++aidx;
        } else {
            B[bidx].p1 = taskTable[0][i];
            B[bidx].p2 = taskTable[1][i];
            ++bidx;
        }
    }

    qsort(A, aidx, sizeof(DoubleTask), compare_TaskA);
    qsort(B, bidx, sizeof(DoubleTask), compare_TaskB);

    result = new Task**[2];
    result[0] = new Task*[amountOfTasks];
    result[1] = new Task*[amountOfTasks];

    int idx = 0;
    for (int i = 0; i < aidx; ++i) {
        result[0][idx] = A[i].p1;
        result[1][idx] = A[i].p2;
        ++idx;
    }
    for (int i = 0; i < bidx; ++i) {
        result[0][idx] = B[i].p1;
        result[1][idx] = B[i].p2;
        ++idx;
    }
    
    int end1 = 0;
    int end2 = 0;

    result[0][0]->startAt = 0;
    result[1][0]->startAt = result[0][0]->startAt + result[0][0]->resource;
    for (int i = 1; i < amountOfTasks; ++i) {
        result[0][i]->startAt = result[0][i - 1]->startAt + result[0][i - 1]->resource;

        end1 = result[0][i]->startAt + result[0][i]->resource;
        end2 = result[1][i - 1]->startAt + result[1][i - 1]->resource;
        result[1][i]->startAt = end1 > end2 ? end1 : end2;
    }

    delete[] taskTable[0];
    delete[] taskTable[1];
    delete[] taskTable;
    taskTable = NULL;
}

Task*** Johnson::getResult()
{
    return result;
}

