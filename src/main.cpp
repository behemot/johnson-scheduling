/**
 * 
 * @author Michał Białas <michal.bialas@mbialas.pl>
 *
 */

#include <QtGui>
#include "gui.h"
#include "johnson.h"

int main(int argc, char* argv[])
{
    QApplication app(argc, argv);
    TopWindow window;

    QTime midnight(0, 0, 0);
    qsrand(midnight.secsTo(QTime::currentTime()));

    window.setAlgorithm(new Johnson());
    window.setWindowTitle(QString::fromUtf8("MPD - projekt 1"));
    window.setMinimumSize(640, 400);
    window.show();
    return app.exec();
}

