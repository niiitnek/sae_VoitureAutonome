#include "tcpclient.h"
#include <QIODevice>
#include <QDataStream>
#include <QDebug>
#include <unistd.h>

TCPclient::TCPclient(QString _Host, int _port)
{
    // Important : il faut lier le signal du socket au slot !
    connect(&clientSocket, &QTcpSocket::readyRead, this, &TCPclient::onReadyRead);
    Host = _Host;
    port = _port;
    connectTCP();

}

void TCPclient::connectTCP()
{
    qDebug() << "Lancement de la connexion vers" << Host << "...";
    clientSocket.connectToHost(Host, port);

    qDebug() << "Attente de la connexion (max 3s)...";
    if (clientSocket.waitForConnected(3000)) {
        qDebug() << "Connexion réussie ! État :" << clientSocket.state();
    } else {
        qDebug() << "Erreur de connexion ->" << clientSocket.errorString();
        ReconnectConnectOrWait();
    }

}

void TCPclient::sendDatas(QString datas)
{
    if (clientSocket.state() != QAbstractSocket::ConnectedState) {
        qDebug() << "Impossible d'envoyer : le socket n'est pas connecté.";
        return;
        ReconnectConnectOrWait();
    }

    QByteArray block;

    QDataStream dataIn(&block, QIODevice::WriteOnly);


    // Avec les transactions, on envoie directement la donnée
    // Qt s'occupe d'encapsuler le type et la taille sous le capot.
    dataIn << datas;

    //Une fois le message encapsulé il est envoyé via le socket vers le serveur
    clientSocket.write(block);
    qDebug() << "Client :" << datas;

}

void TCPclient::onReadyRead()
{
    QDataStream in(&clientSocket);
    in.setVersion(QDataStream::Qt_5_0); // Doit correspondre à la version de sendDatas

    // On boucle pour traiter tous les messages si plusieurs paquets sont arrivés ensemble
    while (true) {
        in.startTransaction();

        QString messageRecu;
        in >> messageRecu; // Tente d'extraire le QString complet

        if (in.commitTransaction()) {
            // La transaction a réussi, le message est complet
            qDebug() << "Serveur :" << messageRecu;
            emit newDatas(messageRecu);
        } else {
            // on sort et on attend le prochain OnreadyRead
            break;
        }
    }
}

void TCPclient::ReconnectConnectOrWait()
{
    while(clientSocket.state() != QAbstractSocket::ConnectedState)
    {
        clientSocket.connectToHost(Host, port);
        clientSocket.waitForConnected(3000);
        sleep(1);
    }
}
