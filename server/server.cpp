#include <QtNetwork>
#include <stdlib.h>
#include <QDateTime>
#include <QDebug>
#include <QSettings>
#include <QSqlDriver>
#include <QMYSQLDriver>
#include "server.h"


Server::Server() : _tcpServer(0), _networkSession(0)
{
    QSettings *settings = new QSettings("server.conf",QSettings::NativeFormat);
    _port=settings->value("net/port",5141).toInt();
    _mysqlHost=settings->value("mysql/hostname","localhost").toString();
    _mysqlUser=settings->value("mysql/user","").toString();
    _mysqlPass=settings->value("mysql/password","").toString();
    _mysqlDB=settings->value("mysql/database","").toString();

    sessionOpened();
    connect(_tcpServer, SIGNAL(newConnection()), this, SLOT(sendFortune()));
    _mySqlDataBase=_mySqlDataBase.addDatabase("QMYSQL");
    _mySqlDataBase.setHostName(_mysqlHost);
    _mySqlDataBase.setDatabaseName(_mysqlDB);
    _mySqlDataBase.setUserName(_mysqlUser);
    _mySqlDataBase.setPassword(_mysqlPass);
    qDebug()<<_mySqlDataBase.open();
    settings->setValue("net/port",_port);
    settings->setValue("mysql/hostname",_mysqlHost);
    settings->setValue("mysql/database",_mysqlDB);
    settings->setValue("mysql/user",_mysqlUser);
    settings->setValue("mysql/password",_mysqlPass);
    settings->sync();
}

void Server::sessionOpened()
{
    _tcpServer = new QTcpServer();

    if (!_tcpServer->listen(QHostAddress::Any,_port)) {
        return;
    }
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    // use the first non-localhost IPv4 address
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    // if we did not find one, use IPv4 localhost
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
}


void Server::manageDataBase(QString proceededstr) {
        //PARSING INCOMING DATA
        QString device_id = proceededstr.mid(1,9);
        QString coordx = proceededstr.mid(11,9);
        QString coordy = proceededstr.mid(21,9);
        QString call_id = proceededstr.mid(31,1);
        QDate dateString = QDate::currentDate();
        QTime timeString = QTime::currentTime();
        QString call_time = timeString.toString("hh:mm:ss");
        QString call_date = dateString.toString("yyyy-MM-dd");
        QString endDb ="INSERT INTO `mobi` (`date`,`type`,`x`,`y`,`id_device`) VALUES (\'"+call_date+" "+call_time+"\',\'"+call_id+"\',\'"+coordx+"\',\'"+coordy+"\',\'"+device_id+"\');";
        _mySqlDataBase.transaction();
        QSqlQuery query;
        query.exec(endDb);
        _mySqlDataBase.commit();
  return;
}


void Server::sendFortune() {
    QTcpSocket *socket = _tcpServer->nextPendingConnection();
    QDataStream input(socket);
    char *locstring = new char[100];
    uint reqnumber;
    input.setVersion(QDataStream::Qt_4_0);
    socket->waitForReadyRead();
    input.readBytes(locstring, reqnumber);
    QString proceedtodb(locstring);
    manageDataBase(proceedtodb);
}
