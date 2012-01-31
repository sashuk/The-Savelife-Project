#ifndef SERVER_H
#define SERVER_H
class QTcpServer;
class QNetworkSession;
#include <QObject>
#include <QtSql>
#include <QSqlDatabase>
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
    QSqlDatabase _mySqlDataBase;
    QNetworkSession *_networkSession;
    int _port;
    QString _mysqlHost;
    QString _mysqlDB;
    QString _mysqlUser;
    QString _mysqlPass;

    void manageDataBase(QString);

};

#endif
