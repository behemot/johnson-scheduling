/**
 * 
 * @author Michał Białas <michal.bialas@mbialas.pl>
 *
 */

#include <QHBoxLayout>
#include <QWidget>
#include <QSlider>
#include <QLabel>
#include <QLineEdit>

#include "choose.h"

ChooseWidget::ChooseWidget()
{
    QHBoxLayout *topLayout = new QHBoxLayout();
    leftLabel = new QLabel(QString::fromUtf8("Rozmiar zadania"));

    slider = new QSlider(Qt::Horizontal);
    slider->setRange(3, 100);
    slider->setSingleStep(1);
    slider->setValue(3);

    input = new QLineEdit();
    input->setText("3");
    input->setFixedWidth(30);

    topLayout->addWidget(leftLabel);
    topLayout->addWidget(slider);
    topLayout->addWidget(input);

    connect(slider, SIGNAL(valueChanged(int)), this, SLOT(valueChanged(int)));
    connect(this, SIGNAL(setChanged(const QString&)), input, SLOT(setText(const QString&)));

    connect(input, SIGNAL(textChanged(const QString&)), this, SLOT(valueChanged(const QString&)));
    connect(this, SIGNAL(setChanged(int)), slider, SLOT(setValue(int)));
    
    setLayout(topLayout);
    setFixedHeight(50);
}

void ChooseWidget::valueChanged(int val)
{
    const QString *value = new QString(QString::number(val));
    emit setChanged(*value);
}

void ChooseWidget::valueChanged(const QString& val)
{
    int value = val.toInt();
    emit setChanged(value);
}

