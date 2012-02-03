#include <QtCore/QCoreApplication>
#include <QtNetwork>
#include <QtNetwork>
#include <QDebug>
#include <QSettings>
#include <QDesktopWidget>
#include <QMessageBox>
#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::pressedUnus() {
    sendDataString("1");
}
void MainWindow::pressedDuo() {
    sendDataString("2");
}
void MainWindow::pressedTres() {
    sendDataString("3");
}

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), networkSession(0)
{
    //Setting up user interface
    ui->setupUi(this);

    //Example styling for UI element
    ui->tabWidget->setStyleSheet("QTabBar::tab { height: 50px; width: 160px; }");

    //Uploading settings at the initialization of the application
    settings = new QSettings("settings.conf",QSettings::NativeFormat);

    globIpAdress = settings->value("settings/serv_ip", "91.221.60.166").toString();
    globPort = settings->value("settings/serv_port", "51413").toInt();
    phone2 = settings->value("settings/phone2", "").toString();
    phone3 = settings->value("settings/phone3", "").toString();

    //Updating the UI
    ui->lineEdit->setText(globIpAdress);
    ui->lineEdit_2->setText(QString::number(globPort));
    qDebug() << globIpAdress << "@" << globPort;

    sysInfo = new QSystemDeviceInfo(this);
    QGeoPositionInfo::QGeoPositionInfo(info);
    QGeoPositionInfoSource *source = QGeoPositionInfoSource::createDefaultSource(this);
    if(source)
    {
        connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)), this, SLOT(positonUpdated(QGeoPositionInfo)));
        source->requestUpdate();
    }

QString ipAddress;
QList<QHostAddress> ipAddressesList = QNetworkInterface::allAddresses();
for (int i = 0; i < ipAddressesList.size(); ++i)
{
    if (ipAddressesList.at(i) != QHostAddress::LocalHost && ipAddressesList.at(i).toIPv4Address())
    {
        ipAddress = ipAddressesList.at(i).toString();
        //ipAddress = "91.221.60.166";
        break;
    }
}
if (ipAddress.isEmpty()) ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

tcpSocket = new QTcpSocket(this);
QNetworkConfigurationManager manager;
if (manager.capabilities() & QNetworkConfigurationManager::NetworkSessionRequired) {
    QSettings settings(QSettings::UserScope, QLatin1String("Trolltech"));
    settings.beginGroup(QLatin1String("QtNetwork"));
    const QString id = settings.value(QLatin1String("DefaultNetworkConfiguration")).toString();
    settings.endGroup();

    QNetworkConfiguration config = manager.configurationFromIdentifier(id);
    if ((config.state() & QNetworkConfiguration::Discovered) !=
        QNetworkConfiguration::Discovered)
    {
        config = manager.defaultConfiguration();
    }

    networkSession = new QNetworkSession(config, this);
    connect(networkSession, SIGNAL(opened()), this, SLOT(sessionOpened()));
    networkSession->open();
    }
}


void MainWindow::sessionOpened() {
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
}

void MainWindow::sendDataString(QString type)
{
    QByteArray block;
    QDataStream out(&block, QIODevice::WriteOnly);
    out.setVersion(QDataStream::Qt_4_0);

    deviceid = QString(sysInfo->imei());
    qDebug()<<type;
    QString rolltoserver = "#" + deviceid + "#" + coordx + "#" + coordy + "#" + type + "#";
    qDebug() << rolltoserver;

    addr.setType(QMessageAddress::Phone);
    //#############KOSTIL'##################
    addr.setAddressee(phone1);
    msg.setTo(addr);
    msg.setBody("Hello, this is a EmergencyNotifier. You have been asked for a help in " + coordx + " ; " + coordy +
                    " , Call id: " + type + ", IMEI: " + deviceid);
    msg.setType(QMessage::Sms);
    service.send(msg);
    //qDebug() << service.state();

       out<<rolltoserver.toLatin1();
        tcpSocket->abort();

        qDebug() << globIpAdress << "@" << globPort;
        tcpSocket->connectToHost(globIpAdress, globPort);
        tcpSocket->write(block);
        tcpSocket->waitForBytesWritten();

}


void MainWindow::positonUpdated(const QGeoPositionInfo &info)
{
    coordx = QString::number(info.coordinate().latitude());
    coordy = QString::number(info.coordinate().longitude());
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setOrientation(ScreenOrientation orientation)
{
#if defined(Q_OS_SYMBIAN)
    // If the version of Qt on the device is < 4.7.2, that attribute won't work
    if (orientation != ScreenOrientationAuto) {
        const QStringList v = QString::fromAscii(qVersion()).split(QLatin1Char('.'));
        if (v.count() == 3 && (v.at(0).toInt() << 16 | v.at(1).toInt() << 8 | v.at(2).toInt()) < 0x040702) {
            qWarning("Screen orientation locking only supported with Qt 4.7.2 and above");
            return;
        }
    }
#endif // Q_OS_SYMBIAN

    Qt::WidgetAttribute attribute;
    switch (orientation) {
#if QT_VERSION < 0x040702
    // Qt < 4.7.2 does not yet have the Qt::WA_*Orientation attributes
    case ScreenOrientationLockPortrait:
        attribute = static_cast<Qt::WidgetAttribute>(128);
        break;
    case ScreenOrientationLockLandscape:
        attribute = static_cast<Qt::WidgetAttribute>(129);
        break;
    default:
    case ScreenOrientationAuto:
        attribute = static_cast<Qt::WidgetAttribute>(130);
        break;
#else // QT_VERSION < 0x040702
    case ScreenOrientationLockPortrait:
        attribute = Qt::WA_LockPortraitOrientation;
        break;
    case ScreenOrientationLockLandscape:
        attribute = Qt::WA_LockLandscapeOrientation;
        break;
    default:
    case ScreenOrientationAuto:
        attribute = Qt::WA_AutoOrientation;
        break;
#endif // QT_VERSION < 0x040702
    };
    setAttribute(attribute, true);
}

void MainWindow::showExpanded()
{
#if defined(Q_OS_SYMBIAN) || defined(Q_WS_SIMULATOR)
    showFullScreen();
#elif defined(Q_WS_MAEMO_5)
    showMaximized();
#else
    show();
#endif
}



void MainWindow::on_pushButton_clicked()
{
    pressedUnus();
}

void MainWindow::on_pushButton_2_clicked()
{
    pressedDuo();
}

void MainWindow::on_pushButton_3_clicked()
{
    pressedTres();
}

void MainWindow::on_pushButton_4_clicked()
{
    globIpAdress = ui->lineEdit->text().toLatin1();
    globPort = ui->lineEdit_2->text().toInt();
    phone2 = ui->lineEdit_4->text().toLatin1();
    phone3 = ui->lineEdit_5->text().toLatin1();
    settings->setValue("settings/serv_ip", globIpAdress);
    settings->setValue("settings/serv_port", globPort);
    settings->setValue("settings/phone2", phone2);
    settings->setValue("settings/phone3", phone3);
    settings->sync();
    qDebug() << "File was updated - " <<  globIpAdress << globPort;
}
