#ifndef DELWINDOW_H
#define DELWINDOW_H

#include <QDialog>

namespace Ui {
class delWindow;
}

class delWindow : public QDialog
{
    Q_OBJECT

public slots:
    void GetData();

signals:
    void sentData(QVector<int>);

public:
    explicit delWindow(int sw=0, QVector<QString> *list=NULL, QWidget *parent = 0);
    ~delWindow();

private:
    Ui::delWindow *ui;
};

#endif // DELWINDOW_H
