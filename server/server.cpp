#include <QtNetwork>
#include <stdlib.h>
#include <QDateTime>
#include <QDebug>
#include <QSettings>
#include <QSqlDriver>
#include <QMYSQLDriver>
#include "server.h"


Server::Server() : _tcpServer(0)
{
    QSettings *settings = new QSettings("server.conf",QSettings::NativeFormat);
    _port=settings->value("net/port",51413).toInt();
    _mysqlHost=settings->value("mysql/hostname","localhost").toString();
    _mysqlUser=settings->value("mysql/user","").toString();
    _mysqlPass=settings->value("mysql/password","").toString();
    _mysqlDB=settings->value("mysql/database","").toString();
    _tcpServer = new QTcpServer();
    if(_tcpServer->listen(QHostAddress::Any,_port))
        qDebug()<<"Listening "<<_port<<" port [OK]";
    else
        qDebug()<<"Listening "<<_port<<" port [FAIL]";
    connect(_tcpServer, SIGNAL(newConnection()), this, SLOT(sendFortune()));
    _mySqlDataBase=_mySqlDataBase.addDatabase("QMYSQL");
    _mySqlDataBase.setHostName(_mysqlHost);
    _mySqlDataBase.setDatabaseName(_mysqlDB);
    _mySqlDataBase.setUserName(_mysqlUser);
    _mySqlDataBase.setPassword(_mysqlPass);
    if(_mySqlDataBase.open())
    {
        qDebug()<<"Connectting to Data Base [OK]";
    }
    else
    {
        qDebug()<<"Connectting to Data Base [FAIL]";
        qDebug()<<"     "+_mySqlDataBase.lastError().databaseText();
    }
    settings->setValue("net/port",_port);
    settings->setValue("mysql/hostname",_mysqlHost);
    settings->setValue("mysql/database",_mysqlDB);
    settings->setValue("mysql/user",_mysqlUser);
    settings->setValue("mysql/password",_mysqlPass);
    settings->sync();
}

void Server::manageDataBase(QString proceededstr)
{
        //PARSING INCOMING DATA
    QRegExp rxlen("#(\\S*)#(\\S*)#(\\S*)#(\\S*)#");
     int pos = rxlen.indexIn(proceededstr);
     QStringList list = rxlen.capturedTexts();

     QString device_id = list[1];
        QString coordx = list[2];
        QString coordy = list[3];
        QString call_id = list[4];
        QDate dateString = QDate::currentDate();
        QTime timeString = QTime::currentTime();
        QString call_time = timeString.toString("hh:mm:ss");
        QString call_date = dateString.toString("yyyy-MM-dd");
        QString endDb ="INSERT INTO `mobi` (`date`,`type`,`x`,`y`,`id_device`) VALUES (\'"+call_date+" "+call_time+"\',\'"+call_id+"\',\'"+coordx+"\',\'"+coordy+"\',\'"+device_id+"\');";
        _mySqlDataBase.transaction();
        qDebug()<<endDb;
        QSqlQuery query;
        query.exec(endDb);
        _mySqlDataBase.commit();
}

void Server::sendFortune()
{
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
