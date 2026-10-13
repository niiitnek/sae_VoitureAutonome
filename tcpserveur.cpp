#include "tcpserveur.h"
#include <QCoreApplication>
#include <QDebug>
#include <QTcpSocket>

TcpServeur::TcpServeur(int port)
{
    monServeur.listen(QHostAddress::AnyIPv4, port);
    connect(&monServeur, &QTcpServer::newConnection,
            this, &TcpServeur::newConnection);
}

void TcpServeur::newConnection()
{
    serveurSocket = monServeur.nextPendingConnection();
    dataIn.setDevice(serveurSocket);

    connect(serveurSocket, &QTcpSocket::readyRead,
            this, &TcpServeur::onReadyRead);

    qDebug() << "Nouvelle connection !";
}

void TcpServeur::sendDatas(QString datas)
{
    if (!serveurSocket) {
        qDebug() << "Aucun client connecté, envoi impossible";
        return;
    }

    QByteArray block;
    QDataStream dataIn(&block, QIODevice::WriteOnly);
    dataIn.setVersion(QDataStream::Qt_5_0);
    dataIn << datas;
    qDebug()<<"message envoyé :"<<datas;
    serveurSocket->write(block);
}

void TcpServeur::onReadyRead()
{
    dataIn.startTransaction();

    QString data;
    dataIn >> data;

    if (!dataIn.commitTransaction())
        return;

    qDebug() << data;
    emit newDatas(data);
}


