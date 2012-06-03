/**
 * 
 * @author Michał Białas <michal.bialas@mbialas.pl>
 *
 */

#ifndef _TASKS_H
#define _TASKS_H

#include <QWidget>
#include <QGridLayout>
#include <QSpinBox>
#include <QString>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>

#include "johnson.h"

class TasksWidget: public QWidget
{
    Q_OBJECT
    public:
        TasksWidget();
        void setFirstTaskVisible(int n);
        Task*** getTasks(int n);
    private:
        QSpinBox* tasks[2][10];
        QLabel* labels[10];
        QVBoxLayout* topLayout;
        QGridLayout* gridLayout;
        QPushButton* generateButton;
    public slots:
        void generate();
};

#endif //_TASKS_H

