#include "server.h"

Server::Server(QObject *parent) : QTcpServer(parent)
{

}

void Server::deleteClients(){
    foreach(QTcpSocket *socket, list1){
        socket->close();
    }
    qDeleteAll(list1);
    list1.clear();

    QTcpServer::close();
}

void Server::disconnected(){
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    socket->deleteLater();
}

void Server::incomingConnection(qintptr socketDescriptor){
    QTcpSocket *socket = new QTcpSocket();
    socket->setSocketDescriptor(socketDescriptor);

    if(!socket->waitForConnected(500)){
        delete socket;
        return;
    }
    list1.append(socket);
    connect(socket,SIGNAL(readyRead()),this,SLOT(sockReady()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));

    socket->write(m_message.toLatin1());
}

void Server::sockReady(){
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    QByteArray data = socket->readAll();

    foreach(QTcpSocket *socket, list1){
        socket->write(data);
    }
}

QString Server::message() const{
    return m_message;
}

void Server::setMessage(const QString &message){
    m_message = message;
}
