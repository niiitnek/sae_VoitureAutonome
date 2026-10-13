#ifndef TCPSERVEUR_H
#define TCPSERVEUR_H


#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>

#include <QObject>

class TcpServeur : public QObject
{
    Q_OBJECT
public:
    explicit TcpServeur(int port);
    void sendDatas(QString datas );
private slots:
    void onReadyRead();
    void newConnection();


private:
    QTcpServer monServeur;
    QTcpSocket* serveurSocket  = nullptr;
    QDataStream dataIn;




signals:
    void newDatas(QString datas);
};

#endif // TCPSERVEUR_H
