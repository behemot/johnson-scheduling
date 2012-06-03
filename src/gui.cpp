/**
 * 
 * @author Michał Białas <michal.bialas@mbialas.pl>
 *
 */

#include "gui.h"

TopWindow::TopWindow()
{
    createMenu();

    taskAmount = 3;
    mainLayout = new QVBoxLayout();
    chooseWidget = new ChooseWidget();
    tasksWidget = new TasksWidget();
    tasksWidget->setFirstTaskVisible(3);
    mainWidget = new QWidget();
    scheduleButton = new QPushButton(QString::fromUtf8("Szereguj"));
    scheduleButton->setFixedWidth(150);

    scheduleProgressBar = new QProgressBar();
    scheduleProgressBar->setMinimumWidth(300);
    scheduleProgressBar->hide();

    mainLayout->addWidget(chooseWidget);    
    mainLayout->addWidget(tasksWidget);
    mainLayout->addSpacing(20);
    mainLayout->addWidget(scheduleButton, 0, Qt::AlignRight);
    mainLayout->addSpacing(40);
    mainLayout->addWidget(scheduleProgressBar, 0, Qt::AlignHCenter);

    mainLayout->setAlignment(Qt::AlignTop);
    mainWidget->setLayout(mainLayout);
    setCentralWidget(mainWidget);

    createEvents();
}

void TopWindow::createMenu()
{
    QAction *author = new QAction(QString::fromUtf8("Autor"), this);
    QObject::connect(author, SIGNAL(triggered()), this, SLOT(authorWindow()));

    aboutMenu = menuBar()->addMenu(QString::fromUtf8("About"));
    aboutMenu->addAction(author);
}

void TopWindow::authorWindow()
{
    QMessageBox msgBox;
    msgBox.setText(QString::fromUtf8("Autor: Michał Białas <michal.bialas@mbialas.pl>"));
    msgBox.exec();
}

void TopWindow::setTasks(int n)
{
    taskAmount = n;
    if (n <= 10) {
        tasksWidget->show();
        tasksWidget->setFirstTaskVisible(n);
    } else {
        tasksWidget->hide();
    }
}

void TopWindow::createEvents()
{
    connect(chooseWidget, SIGNAL(setChanged(int)), this, SLOT(setTasks(int)));
    connect(scheduleButton, SIGNAL(pressed()), this, SLOT(runAlgorithm()));
}

void TopWindow::setAlgorithm(Johnson* al)
{
    algorithm = al;
}

void TopWindow::runAlgorithm()
{
    algorithm->setTasks(tasksWidget->getTasks(taskAmount), 2, taskAmount);
    algorithm->run();
    Task*** tasks = algorithm->getResult();
    if (taskAmount > 10) {
        saveToFile(tasks, taskAmount);
    } else {
        //saveToFile(tasks, taskAmount);
        GantDialog gant(tasks, taskAmount);
        gant.exec();
    }
    delete[] tasks[0];
    delete[] tasks[1];
    delete[] tasks;
    tasks = NULL;
}

void TopWindow::saveToFile(Task*** tasks, int n)
{
    QString content("");
    content.append("P1\n");
    content.append("name\tresource\tstartAt\n");
    for (int i = 0; i < n; ++i) {
        content.append(tasks[0][i]->name + "\t" + QString::number(tasks[0][i]->resource) + "\t\t" + QString::number(tasks[0][i]->startAt) + "\n");
    }
    content.append("\n\nP2\n");
    content.append("name\tresource\tstartAt\n");
    for (int i = 0; i < n; ++i) {
        content.append(tasks[1][i]->name + "\t" + QString::number(tasks[1][i]->resource) + "\t\t" + QString::number(tasks[1][i]->startAt) + "\n");
    }
    
    QString fileName = QFileDialog::getSaveFileName(this, QString::fromUtf8("Zapisz plik z danymi"), "wynik.txt", "");
    if ("" == fileName) {
        return;
    }
    
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);

    QTextStream out(&file);
    out << content;
    file.close();
}

