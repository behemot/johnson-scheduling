/**
 * 
 * @author Michał Białas <michal.bialas@mbialas.pl>
 *
 */

#ifndef _GANT_H
#define _GANT_H

#include <QDialog>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QVBoxLayout>
#include <QPainter>
#include <QPushButton>
#include <QBrush>

#include "johnson.h"

class GantDialog : public QDialog
{
    Q_OBJECT
    public:
        GantDialog(Task*** tasks, int n);
    private:
        QGraphicsScene *scene;
        QGraphicsView *view;
        QVBoxLayout* layout;
};

class GantPainter : public QWidget
{
    Q_OBJECT
    public:
        int n;
        Task*** tasks;
        GantPainter(QWidget *parent = 0);
    protected:
        void paintEvent(QPaintEvent *event);
};

#endif //_GANT_H

