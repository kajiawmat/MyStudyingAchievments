#ifndef SERVER_H
#define SERVER_H

#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QList>

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = nullptr);
    void deleteClients();
    QString message() const;
    void setMessage(const QString &message);
signals:
    void changed();
public slots:
    void disconnected();
    void sockReady();
protected:
    void incomingConnection(qintptr socketDescriptor) override;
private:
    QString m_message;
    QList<QTcpSocket*> list1;
};

#endif // SERVER_H
