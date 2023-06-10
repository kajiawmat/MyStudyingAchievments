#include "mainwindow.h"
#include <QApplication>
#include "startdialog.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    StartDialog startDialog;
    startDialog.setMinimumWidth(192);
    startDialog.setMinimumHeight(108);
    startDialog.show();
    return a.exec();
}
