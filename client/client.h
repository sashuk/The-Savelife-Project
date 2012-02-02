#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QTcpSocket>

#ifdef Q_OS_SYMBIAN 
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include  <QSystemDeviceInfo>
#include <QMessage>
#include <QMessageAddress>
#include <QMessageService>

QTM_USE_NAMESPACE
#endif
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

#ifdef Q_OS_SYMBIAN
public slots:
    void positonUpdated(const QGeoPositionInfo &info);
#endif

private slots:
    void displayError(QAbstractSocket::SocketError socketError);
    void sessionOpened();
    void sendDataString(QString);
    void pressedUnus();
    void pressedDuo();
    void pressedTres();
private:
    void readSettings(); //читай настройка
    void writeSettings(); //пиши настройка
protected:
    void closeEvent(QCloseEvent *);

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
#ifdef Q_OS_SYMBIAN
    QSystemDeviceInfo *sysInfo;
    QMessage msg;
    QMessageAddress addr;
    QMessageService service;
#endif
    int info_code;
    QString sIpAddress_; //адрес сервера
    QString sTelephone_; //номер человека
};

#endif
