#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QTcpSocket>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include  <QSystemDeviceInfo>
#include <QMessage>
#include <QMessageAddress>
#include <QMessageService>

QTM_USE_NAMESPACE

QT_BEGIN_NAMESPACE
class QDialogButtonBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QTcpSocket;
class QNetworkSession;
QT_END_NAMESPACE

//! [0]
class Client : public QDialog
{
    Q_OBJECT

public:
    Client(QWidget *parent = 0);

public slots:
    void positonUpdated(const QGeoPositionInfo &info);


private slots:
    void displayError(QAbstractSocket::SocketError socketError);
    void sessionOpened();
    void sendDataString(QString);
    void pressedUnus();
    void pressedDuo();
    void pressedTres();


private:
    //Geoposition
    QString deviceid;
    QString coordx;
    QString coordy;
    QLabel *hostLabel;
    QLineEdit *hostLineEdit;
    QLabel *statusLabel;
    QPushButton *quitButton;
    QPushButton *alarmTypeUnus;
    QPushButton *alarmTypeDuo;
    QPushButton *alarmTypeTres;
    QDialogButtonBox *buttonBox;
    QPushButton *sendButton;
    QTcpSocket *tcpSocket;
    QString currentFortune;
    quint16 blockSize;
    QNetworkSession *networkSession;
    QSystemDeviceInfo *sysInfo;
    QMessage msg;
    QMessageAddress addr;
    QMessageService service;
    int info_code;
};

#endif
