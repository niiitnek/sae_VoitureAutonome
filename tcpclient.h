#ifndef TCPCLIENT_H
#define TCPCLIENT_H
#include <QTcpSocket>

#include <QDataStream>


class TCPclient :public QObject

{
    Q_OBJECT
public:
    TCPclient(QString _Host, int _port);
    void sendDatas(QString datas);
    void onReadyRead();

private:
    QString Host;
    QTcpSocket clientSocket;
    int port;
    void connectTCP();
    void ReconnectConnectOrWait();
signals:
    void newDatas(QString datas);

};

#endif // TCPCLIENT_H
