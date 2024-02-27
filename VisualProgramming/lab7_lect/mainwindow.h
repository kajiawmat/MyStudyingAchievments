#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPaintDevice>
#include <QPainter>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

protected:
    virtual void paintEvent(QPaintEvent* e)
    {
        QMainWindow::paintEvent(e);

        QPainter p(this);
        p.setRenderHint(QPainter::Antialiasing,true);
        p.setPen(QPen(Qt::red,2,Qt::DashDotDotLine));
        p.drawLine(0,0,100,100);
        p.setBrush(QBrush(Qt::green,Qt::BDiagPattern));
        p.drawEllipse(0,0,150,200);
        QImage Img("Car.png");
        Img=Img.scaled(25,25,Qt::KeepAspectRatioByExpanding);
        p.drawImage(10,10,Img);
    }
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
