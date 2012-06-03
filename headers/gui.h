/**
 * 
 * @author Michał Białas <michal.bialas@mbialas.pl>
 *
 */

#ifndef _TOP_H
#define _TOP_H

#include <QWidget>
#include <QMainWindow>
#include <QSlider>
#include <QLabel>
#include <QMenuBar>
#include <QMenu>
#include <QString>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QAction>
#include <QPushButton>
#include <QProgressBar>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

#include "choose.h"
#include "tasks.h"
#include "johnson.h"
#include "gant.h"

class TopWindow: public QMainWindow
{
    Q_OBJECT
    private:
        int taskAmount;
        QWidget* mainWidget;
        ChooseWidget* chooseWidget;
        QMenu* aboutMenu;
        TasksWidget* tasksWidget;
        QVBoxLayout* mainLayout;
        QPushButton* scheduleButton;
        QProgressBar* scheduleProgressBar;
        Johnson* algorithm;

        void createMenu();
        void createEvents();
        void saveToFile(Task*** tasks, int n);
    public:
        TopWindow();
        void setAlgorithm(Johnson* al);
    public slots:
        void authorWindow();
        void setTasks(int n);
        void runAlgorithm();
};

#endif //_TOP_H

