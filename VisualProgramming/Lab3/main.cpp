#include "sdiprogram.h"
#include <QApplication>
#include <QSplashScreen>
#include <QtWidgets>

void loadModules(QSplashScreen *psplash)
{
    QTime time;
    time.start();

    for(int i=0;i<100;)
    {
        if(time.elapsed()>40)
        {
            time.start();
            ++i;
        }
        psplash->showMessage("Loading Modules: "+QString::number(i)+"%",Qt::AlignCenter|Qt::AlignCenter,Qt::blue);
        qApp->processEvents();
    }

}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    QPixmap pixmap("my.jpeg");
    //qDebug() << pixmap.load("C:/Users/Alex/Documents/Lab3/s.jpg");
    QSplashScreen splash(pixmap);
    splash.show();
    loadModules(&splash);
    SDIProgram w;
    splash.finish(&w);
    w.show();

    return a.exec();
}

