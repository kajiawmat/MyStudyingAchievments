#ifndef AUTH_H
#define AUTH_H

#include <QMainWindow>

namespace Ui {
class Auth;
}

class Auth : public QMainWindow
{
    Q_OBJECT

public:
    explicit Auth(QWidget *parent = 0);
    ~Auth();

private:
    Ui::Auth *ui;
};

#endif // AUTH_H
