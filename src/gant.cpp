/**
 * 
 * @author Michał Białas <michal.bialas@mbialas.pl>
 *
 */

#include "gant.h"

#define MAX_INNER_WIDTH 810

GantDialog::GantDialog(Task*** tasks, int n)
{
    GantPainter* paint = new GantPainter;
    paint->tasks = tasks;
    paint->n = n;
    paint->setFixedSize(MAX_INNER_WIDTH + 70, 350);

    QPushButton* okButton = new QPushButton("OK");
    okButton->setDefault(true);
    okButton->setFixedWidth(70);
    
    layout = new QVBoxLayout();
    layout->addWidget(paint);
    layout->addWidget(okButton);
    setLayout(layout);
    setFixedSize(900, 400);
    //setTitle(QString::fromUtf8("Diagram ganta"));
    connect(okButton, SIGNAL(pressed()), this, SLOT(accept()));
}

GantPainter::GantPainter(QWidget* parent) : QWidget(parent) {}

void GantPainter::paintEvent(QPaintEvent *event)
{
    QBrush colors[6] = {QBrush("#004fc5"), QBrush("#1ac500"), QBrush("#539e47"), QBrush("#c56c00"), QBrush("#c50024"), QBrush("#9e4757")};

    QPainter painter(this);
    painter.setPen(QColor("#d4d4d4"));

    int cMax = tasks[1][n - 1]->startAt + tasks[1][n - 1]->resource;
    int* scale = new int[cMax + 1];
    for (int i = 0; i < cMax; ++i) {
        scale[i] = 0;
    }

    Task* tmp;
    for (int i = 0; i < n; ++i) {
        tmp = tasks[0][i];
        scale[tmp->startAt] = 1;
        scale[tmp->startAt + tmp->resource] = 1;
        painter.setPen(QColor("#d4d4d4"));
        painter.setBrush(colors[i % 6]);
        painter.drawRect(30 + (MAX_INNER_WIDTH / cMax) * tmp->startAt, 10, (MAX_INNER_WIDTH / cMax) * tmp->resource, 130);
        painter.setPen(QColor("#111111"));
        painter.drawText(30 + (MAX_INNER_WIDTH / cMax) * tmp->startAt, 70, (MAX_INNER_WIDTH / cMax) * tmp->resource, 20, Qt::AlignCenter, tmp->name);
    }

    for (int i = 0; i < n; ++i) {
        tmp = tasks[1][i];
        scale[tmp->startAt] = 1;
        scale[tmp->startAt + tmp->resource] = 1;
        painter.setPen(QColor("#d4d4d4"));
        painter.setBrush(colors[i % 6]);
        painter.drawRect(30 + (MAX_INNER_WIDTH / cMax) * tmp->startAt, 150, (MAX_INNER_WIDTH / cMax) * tmp->resource, 130);
        painter.setPen(QColor("#111111"));
        painter.drawText(30 + (MAX_INNER_WIDTH / cMax) * tmp->startAt, 210, (MAX_INNER_WIDTH / cMax) * tmp->resource, 20, Qt::AlignCenter, tmp->name);
    }

    painter.setPen(QColor("#111111"));
    for (int i = 0; i <= cMax; ++i) {
        if (scale[i]) {
            painter.drawText(21 + (MAX_INNER_WIDTH / cMax) * i, 285, 18, 10, Qt::AlignCenter, QString::number(i));
        }
    }

    painter.drawText(30, 300, MAX_INNER_WIDTH, 20, Qt::AlignRight, "Cmax = " + QString::number(cMax));
}

