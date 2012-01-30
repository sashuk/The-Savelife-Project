#include <QtNetwork>
#include <stdlib.h>
#include <QDateTime>
#include <QDebug>
#include <QtSql>
#include "server.h"


Server::Server() : _tcpServer(0), _networkSession(0) {

    QNetworkConfigurationManager manager;
    /*if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        // Get saved network configuration
        QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        // If the saved network configuration is not currently discovered use the system default
        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        _networkSession = new QNetworkSession(config);
        connect(_networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));
        _networkSession->open();
        } else {
        sessionOpened();
        }*/

        connect(_tcpServer, SIGNAL(newConnection()), this, SLOT(sendFortune()));

}

void Server::sessionOpened()
{
    // Save the used configuration
    if (_networkSession) {
        QNetworkConfiguration config = _networkSession->configuration();
        QString id;
        if (config.type() == QNetworkConfiguration::UserChoice)
            id = _networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
        else
            id = config.identifier();

        QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
        settings.endGroup();
    }

    _tcpServer = new QTcpServer();

    if (!_tcpServer->listen(QHostAddress::Any, 51413)) {
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
    //QMessageBox::warning(this, "", proceededstr);
    QSqlDatabase dbase = QSqlDatabase::addDatabase("QSQLITE");
    dbase.setDatabaseName("appbase");
    if (!dbase.open()) {
        qDebug() << "works baaaad";
        return;
    } else {
        //PARSING INCOMING DATA
        QString device_id = proceededstr.mid(1,9);
        QString coordx = proceededstr.mid(11,9);
        QString coordy = proceededstr.mid(21,9);
        QString call_id = proceededstr.mid(31,1);
        QDate dateString = QDate::currentDate();
        qDebug()<<dateString;
        QString call_date = dateString.toString("yyyy-MM-dd");
        QTime timeString = QTime::currentTime();
        QString call_time = timeString.toString("hh:mm:ss");
        QString query_string = "insert into apptable values('" + device_id
                + "', '" + coordx + "', '" + coordy + "', '" + call_id + "', '" +
                call_date + "', '" + call_time + "');";
        QSqlQuery mainquery;
        mainquery.prepare(query_string);
        if (!mainquery.exec()) {
            //QMessageBox::warning(this, "Connection error","Error while executing the SQL query");
        }
        dbase.close();
    }
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
