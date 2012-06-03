/**
 * 
 * @author Michał Białas <michal.bialas@mbialas.pl>
 *
 */

#ifndef _CHOOSE_H
#define _CHOOSE_H

#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QLineEdit>

class ChooseWidget: public QWidget
{
    Q_OBJECT
    private:
        QSlider *slider;
        QLabel *leftLabel;
        QLineEdit *input;
    public:
        ChooseWidget();
    public slots:
        void valueChanged(int);
        void valueChanged(const QString&);
    signals:
        void setChanged(const QString&);
        void setChanged(int);
};

#endif //_CHOOSE_H
