#ifndef DELSUBJECTWINDOW_H
#define DELSUBJECTWINDOW_H

#include <QDialog>

namespace Ui {
class delSubjectWindow;
}

class delSubjectWindow : public QDialog
{
    Q_OBJECT

public:
    explicit delSubjectWindow(QWidget *parent = 0);
    ~delSubjectWindow();

private:
    Ui::delSubjectWindow *ui;
};

#endif // DELSUBJECTWINDOW_H
