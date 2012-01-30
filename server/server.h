#ifndef SERVER_H
#define SERVER_H
class QTcpServer;
class QNetworkSession;
#include <QObject>
#include <QStringList>

class Server : public QObject
{
     Q_OBJECT
public:
    Server();

public slots:
    void sendFortune();
    void sessionOpened();
private:
    QTcpServer *_tcpServer;
    QStringList _notification;
    QNetworkSession *_networkSession;
    void manageDataBase(QString);

};

#endif
