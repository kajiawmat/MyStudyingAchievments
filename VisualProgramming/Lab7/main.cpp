#include "mainwindow.h"
#include "nikolaevgame.h"
#include "infowidget.h"
#include <QApplication>
#include <QGraphicsView>
#include <QtWidgets>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    NikolaevGame sc;
    QGraphicsView view(&sc);
    view.show();
    return a.exec();
}
