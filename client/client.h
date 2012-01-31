#ifndef CLIENT_H
#define CLIENT_H

#include <QDialog>
#include <QTcpSocket>
#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>

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
    Client(QWidget *parent = 0){
        QGeoPositionInfoSource *source =
                QGeoPositionInfoSource::createDefaultSource(this);
        if(source){
            connect(source, SIGNAL(positionUpdated(QGeoPositionInfo)),
                    this, SLOT(positionUpdated(QGeoPositionInfo)));
            source->startUpdates();
        }
    }

private slots:
    void displayError(QAbstractSocket::SocketError socketError);
    void sessionOpened();
    void sendDataString(QString);
    void pressedUnus();
    void pressedDuo();
    void pressedTres();
    void positionUpdated(const QGeoPositionInfo &info);


private:
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
    QGeoPositionInfo info;
};

#endif
