#include <QtGui>
#include <QtNetwork>
#include <QDebug>
#include <QMessageBox>

#include "client.h"

void Client::pressedUnus(){
    sendDataString("1");
}
void Client::pressedDuo(){
    sendDataString("2");
}
void Client::pressedTres(){
    sendDataString("3");
}

Client::Client(QWidget *parent) : QDialog(parent), networkSession(0) {
    hostLabel = new QLabel(tr("&Server name:"));
    QString ipAddress;
    QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
    for (int i = 0; i < ipAddressesList.size(); ++i) {
        if (ipAddressesList.at(i) != QHostAddress::LocalHost &&
            ipAddressesList.at(i).toIPv4Address()) {
            ipAddress = ipAddressesList.at(i).toString();
            break;
        }
    }
    if (ipAddress.isEmpty())
        ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

    hostLineEdit = new QLineEdit(ipAddress);
    hostLabel->setBuddy(hostLineEdit);

    statusLabel = new QLabel(tr(""));

    alarmTypeUnus = new QPushButton(tr("Fire"));
    alarmTypeDuo = new QPushButton(tr("Pain"));
    alarmTypeTres = new QPushButton(tr("Breakin"));

    quitButton = new QPushButton(tr("Quit"));
    sendButton = new QPushButton(tr("Send datastring"));

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);
//    buttonBox->addButton(alarmTypeUnus, QDialogButtonBox::ActionRole);
//    buttonBox->addButton(alarmTypeDuo, QDialogButtonBox::ActionRole);
//    buttonBox->addButton(alarmTypeTres, QDialogButtonBox::ActionRole);


    tcpSocket = new QTcpSocket(this);

    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(alarmTypeUnus, SIGNAL(clicked()), this, SLOT(pressedUnus()));
    connect(alarmTypeDuo, SIGNAL(clicked()), this, SLOT(pressedDuo()));
    connect(alarmTypeTres, SIGNAL(clicked()), this, SLOT(pressedTres()));
    connect(tcpSocket, SIGNAL(readyRead()), this, SLOT(readFortune()));
    connect(tcpSocket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(displayError(QAbstractSocket::SocketError)));

    QGridLayout *mainLayout = new QGridLayout;
    mainLayout->addWidget(hostLabel, 0, 0);
    mainLayout->addWidget(hostLineEdit, 0, 1);
    mainLayout->addWidget(alarmTypeUnus, 3, 0);
    mainLayout->addWidget(alarmTypeDuo, 3, 1);
    mainLayout->addWidget(alarmTypeTres, 3, 2);
    mainLayout->addWidget(buttonBox, 4, 0);
    setLayout(mainLayout);

    setWindowTitle(tr("Alarm Client"));
    QNetworkConfigurationManager manager;
    if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
        QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
        settings.beginGroup(QLatin1String("QtNetwork"));
        const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
        settings.endGroup();

        QNetworkConfiguration config = manager.configurationFromIdentifier(id);
        if ((config.state() & QNetworkConfiguration::Discovered) !=
            QNetworkConfiguration::Discovered) {
            config = manager.defaultConfiguration();
        }

        networkSession = new QNetworkSession(config, this);
        connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));

        statusLabel->setText(tr("Opening network session."));
        networkSession->open();
    }
}


void Client::displayError(QAbstractSocket::SocketError socketError) {
    switch (socketError) {
    case QAbstractSocket::RemoteHostClosedError:
        break;
    case QAbstractSocket::HostNotFoundError:
        QMessageBox::information(this, tr("Fortune Client"), tr("The host was not found. Please check the host name and port settings."));
        break;
    case QAbstractSocket::ConnectionRefusedError:
        QMessageBox::information(this, tr("Fortune Client"), tr("The connection was refused by the peer. Make sure the fortune server is running, and check that the host name and port settings are correct."));
        break;
    default:
        QMessageBox::information(this, tr("Fortune Client"), tr("The following error occurred: %1.").arg(tcpSocket->errorString()));
    }
}


void Client::sessionOpened() {
    QNetworkConfiguration config = networkSession->configuration();
    QString id;
    if (config.type() == QNetworkConfiguration::UserChoice)
        id = networkSession->sessionProperty(QLatin1String("UserChoiceConfiguration")).toString();
    else
        id = config.identifier();

    QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    settings.setValue(QLatin1String("DefaultNetworkConfiguration"), id);
    settings.endGroup();

    statusLabel->setText(tr("<FILLIN>"));
}

void Client::sendDataString(QString type) {
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);
    //############RANDOM!!!#################
    //############RANDOM!!!#################
    QString deviceid = "*********";
    QString coordx = "127323.23";
    QString coordy = "234234.32";
    //############RANDOM!!!#################
    //############RANDOM!!!#################
    QString rolltoserver = "#" + deviceid + "#" + coordx + "#" + coordy + "#" + type + "#";
    out << rolltoserver.toLatin1();
    tcpSocket->abort();
    tcpSocket->connectToHost(hostLineEdit->text(), 1767);
    tcpSocket->write(block);
    tcpSocket->waitForBytesWritten();
}
