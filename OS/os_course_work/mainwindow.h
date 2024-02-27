#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMessageBox>
#include <QTcpSocket>
#include <QStringList>
#include <QStringListModel>
#include <QAbstractSocket>
#include <QShortcut>
#include <QNetworkReply>

#include <typeinfo>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButtonConnect_clicked();

    void on_disconnectButton_clicked();

    void on_sendButton_clicked();

    void connected();

    void disconnected();

    void sockReady();

    void on_lineEditSend_returnPressed();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket1;
    QStringList list1;
    QStringListModel model1;
    QString name1;
};
#endif // MAINWINDOW_H
