#ifndef RESWINDOW_H
#define RESWINDOW_H

#include <QDialog>

namespace Ui {
class resWindow;
}

class resWindow : public QDialog
{
    Q_OBJECT

public:
    explicit resWindow(QWidget *parent = 0);
    ~resWindow();

private:
    Ui::resWindow *ui;
};

#endif // RESWINDOW_H
