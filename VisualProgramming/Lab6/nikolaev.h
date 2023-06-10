#ifndef NIKOLAEV_H
#define NIKOLAEV_H

#include <QWidget>
#include <QAbstractButton>

namespace Ui {
class Nikolaev;
}

class Nikolaev : public QWidget
{
    Q_OBJECT

public:
    explicit Nikolaev(QWidget *parent = 0);
    ~Nikolaev();

private:
    Ui::Nikolaev *ui;

public slots:
    void receiveData(QString str);
private slots:
    void on_buttonBox_clicked(QAbstractButton *button);
};

#endif // NIKOLAEV_H
