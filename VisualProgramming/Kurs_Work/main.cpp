#include "mainwindow.h"
#include <QApplication>
#include <QtWidgets>

void loadModules(QSplashScreen* psplash)
{
    QTime time;
    time.start();
    for(int i=0;i<100;)
    {
        if(time.elapsed()>40)
        {
            time.start();
            i++;
        }
        psplash->showMessage("Loading modules: " + QString::number(i)+"%",Qt::AlignTop|Qt::AlignHCenter,Qt::black);
        qApp->processEvents();
    }
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QFile f("://StyleSheet/Style.qss");
    if (!f.exists())
    {
        qDebug("Unable to set stylesheet, file not found\n");
    }
    else   {
        f.open(QFile::ReadOnly | QFile::Text);
        QTextStream ts(&f);
        qApp->setStyleSheet(ts.readAll());
    }
    QSplashScreen splash(QPixmap("://Images/EkranZagruzki.png"));
    splash.show();
    loadModules(&splash);
    MainWindow w;
    w.show();
    return a.exec();
}
