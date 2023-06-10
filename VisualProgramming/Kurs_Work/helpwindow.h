#ifndef HELPWINDOW_H
#define HELPWINDOW_H

#include <QWidget>

namespace Ui {
class helpWindow;
}

class helpWindow : public QWidget
{
    Q_OBJECT

public:
    explicit helpWindow(QString Path, QWidget *parent = 0);
    ~helpWindow();

private:
    Ui::helpWindow *ui;
};

#endif // HELPWINDOW_H
