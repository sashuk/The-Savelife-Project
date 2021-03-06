#include <QtGui>
#include <QtNetwork>
#include <QDebug>
#include <QMessageBox>
#include <fstream>

#include "client.h"

void Client::pressedUnus(){
    info_code = 1;
    sendDataString(QString(info_code));
}
void Client::pressedDuo(){
    info_code = 2;
    sendDataString(QString(info_code));
}
void Client::pressedTres(){
    info_code = 3;
    sendDataString(QString(info_code));
}

Client::Client(QWidget *parent) : QDialog(parent), networkSession(0) {
    readSettings();
#ifdef Q_OS_SYMBIAN
    sysInfo = new QSystemDeviceInfo(this);
  //  QGeoPositionInfo::QGeoPositionInfo(info);

    QGeoPositionInfoSource *source = QGeoPositionInfoSource::createDefaultSource(this);

    if(source)
    {
        positonUpdated(source->lastKnownPosition());
        source->setUpdateInterval(10000);
        connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(positonUpdated(QGeoPositionInfo)));
        source->startUpdates();
    }
    else
    {
        //����
        QMessageBox::warning(this,"GPS is not available","sory");
    }
#else
     coordx=QString::number(999);
     coordy=QString::number(999);
#endif

    hostLabel = new QLabel(tr("&Server name:"));
    
    hostLineEdit = new QLineEdit(sIpAddress_);
    hostLabel->setBuddy(hostLineEdit);

    statusLabel = new QLabel(tr(""));

    alarmTypeUnus = new QPushButton(tr("Fire"));
    alarmTypeDuo = new QPushButton(tr("Pain"));
    alarmTypeTres = new QPushButton(tr("Breakin"));

    quitButton = new QPushButton(tr("Quit"));
    sendButton = new QPushButton(tr("Send datastring"));

    buttonBox = new QDialogButtonBox;
    buttonBox->addButton(quitButton, QDialogButtonBox::RejectRole);

    tcpSocket = new QTcpSocket(this);

    connect(quitButton, SIGNAL(clicked()), this, SLOT(close()));
    connect(alarmTypeUnus, SIGNAL(clicked()), this, SLOT(pressedUnus()));
    connect(alarmTypeDuo, SIGNAL(clicked()), this, SLOT(pressedDuo()));
    connect(alarmTypeTres, SIGNAL(clicked()), this, SLOT(pressedTres()));
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
    if (socketError) {
//    case QAbstractSocket::RemoteHostClosedError:
//        break;
//    case QAbstractSocket::HostNotFoundError:
//        QMessageBox::information(this, tr("Fortune Client"), tr("The host was not found. Please check the host name and port settings."));
//        break;
//    case QAbstractSocket::ConnectionRefusedError:
//        QMessageBox::information(this, tr("Fortune Client"), tr("The connection was refused by the peer. Make sure the fortune server is running, and check that the host name and port settings are correct."));
//        break;
//    default:
//        //QMessageBox::information(this, tr("Fortune Client"), tr("The following error occurred: %1.").arg(tcpSocket->errorString()));        qDebug() << service.state();
#ifdef Q_OS_SYMBIAN
        addr.setType(QMessageAddress::Phone);
        addr.setAddressee(QString(""));
        msg.setTo(addr);
        ///����� �������
        switch(info_code){
          case  1:
                msg.setBody("Fire!!!");
                msg.setType(QMessage::Sms);
                service.send(msg);
                qDebug() << service.state();
                break;
           case 2:
                msg.setBody("Pain!!!");
                msg.setType(QMessage::Sms);
                service.send(msg);
                qDebug() << service.state();
                break;
           case 3:
                msg.setBody("Breaking!!!");
                msg.setType(QMessage::Sms);
                service.send(msg);
                qDebug() << service.state();
                break;
        }
#endif
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

#ifdef Q_OS_SYMBIAN
    deviceid = QString(sysInfo->imei());
#else
    deviceid=QString("desktop");
#endif
    QString rolltoserver = "#" + deviceid + "#" + coordx + "#" + coordy + "#" + "1" + "#";
    qDebug() << rolltoserver;

    #ifdef Q_OS_SYMBIAN
        addr.setType(QMessageAddress::Phone);
            //#############KOSTIL'##################
        addr.setAddressee(sTelephone_);
        msg.setTo(addr);
        msg.setBody("Hello, this is a EmergencyNotifier. You have been asked for a help in " + coordx + " ; " + coordy +
                    " , Call id: " + type + ", IMEI: " + deviceid);
        msg.setType(QMessage::Sms);
        service.send(msg);
        qDebug() << service.state();
#endif

    out << rolltoserver.toLatin1();
    tcpSocket->abort();
    tcpSocket->connectToHost(hostLineEdit->text(), 51413);
    tcpSocket->write(block);
    tcpSocket->waitForBytesWritten();
}

#ifdef Q_OS_SYMBIAN
void Client::positonUpdated(const QGeoPositionInfo &info)
{
    coordx = QString::number(info.coordinate().latitude());
    coordy = QString::number(info.coordinate().longitude());
}
#endif

void Client::readSettings() //�����
{
    //��������� �������� ��������
    QSettings settings("Matan inc gmbh", "Savelife"); 
    
    sIpAddress_ = settings.value("ip","91.221.60.166").toString();
    sTelephone_ = settings.value("telephone","+79204023482").toString();
}

void Client::writeSettings() //����
{
    QSettings settings("Matan inc gmbh", "Savelife"); 
    
    sIpAddress_ = hostLineEdit->text();

    settings.setValue("ip", sIpAddress_);
    settings.setValue("telephone", sTelephone_);
}

void Client::closeEvent(QCloseEvent *e)
{
    writeSettings();
    e->accept();
}
