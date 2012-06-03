/**
 * 
 * @author Michał Białas <michal.bialas@mbialas.pl>
 *
 */

#include "tasks.h"

TasksWidget::TasksWidget()
{
    topLayout = new QVBoxLayout();
    gridLayout = new QGridLayout();

    gridLayout->addWidget(new QLabel(QString::fromUtf8("Pik")), 1, 1);
    gridLayout->addWidget(new QLabel(QString::fromUtf8("P1")), 2, 1);
    gridLayout->addWidget(new QLabel(QString::fromUtf8("P2")), 3, 1);
    
    QSpinBox* tmp = NULL;
    for (int i = 0; i < 10; ++i) {
        labels[i] = new QLabel(QString::fromUtf8("Z") + QString::number(i + 1));
        gridLayout->addWidget(labels[i], 1, i + 2, Qt::AlignCenter);
        for (int k = 1; k < 3; ++k) {
            tmp = new QSpinBox(this);
            tmp->setRange(1, 10);
            tmp->setValue(qrand() % 11);
            tasks[k - 1][i] = tmp;
            gridLayout->addWidget(tmp, k + 1, i + 2);
        }
    }

    generateButton = new QPushButton(QString::fromUtf8("generuj losowo"));
    generateButton->setFixedWidth(150);
    connect(generateButton, SIGNAL(pressed()), this, SLOT(generate()));
    
    topLayout->addLayout(gridLayout);
    topLayout->addSpacing(10);
    topLayout->addWidget(generateButton);
    setLayout(topLayout);
}

void TasksWidget::setFirstTaskVisible(int n)
{
    for (int i = 0; i < n; ++i) {
        tasks[0][i]->show();
        tasks[1][i]->show();
        labels[i]->show();
    }

    for (int i = n; i < 10; ++i) {
        tasks[0][i]->hide();
        tasks[1][i]->hide();
        labels[i]->hide();
    }
}

void TasksWidget::generate()
{
    for (int i = 0; i < 10; ++i) {
        tasks[0][i]->setValue(qrand() % 10 + 1);
        tasks[1][i]->setValue(qrand() % 10 + 1);
    }
}

Task*** TasksWidget::getTasks(int n)
{
    Task*** tmp = new Task**[2];
    tmp[0] = new Task*[n];
    tmp[1] = new Task*[n];

    if (n <= 10) {
        for (int i = 0; i < n; ++i) {
            tmp[0][i] = new Task("Z" + QString::number(i + 1), tasks[0][i]->value());
            tmp[1][i] = new Task("Z" + QString::number(i + 1), tasks[1][i]->value());
        }
    } else {
        for (int i = 0; i < n; ++i) {
            tmp[0][i] = new Task("Z" + QString::number(i + 1), qrand() % 10 + 1);
            tmp[1][i] = new Task("Z" + QString::number(i + 1), qrand() % 10 + 1);
        }
    }

    return tmp;
}

