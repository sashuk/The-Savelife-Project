#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include <QDialog>
#include <QTcpSocket>
#include <QMainWindow>

#include <QGeoPositionInfo>
#include <QGeoPositionInfoSource>
#include <QSystemDeviceInfo>
#include <QMessage>
#include <QMessageAddress>
#include <QSettings>
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

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QString path,QWidget *parent = 0);
    enum ScreenOrientation {
        ScreenOrientationLockPortrait,
        ScreenOrientationLockLandscape,
        ScreenOrientationAuto
    };

    virtual ~MainWindow();
    void setOrientation(ScreenOrientation orientation);
    void showExpanded();

public slots:
    void positonUpdated(const QGeoPositionInfo &info);

private slots:
    void sessionOpened();
    void sendDataString(QString);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void send2Sms();
    void send3Sms();

private:
    Ui::MainWindow *ui;
    QString deviceid;
    QString globtype;
    QString coordx;
    QString coordy;
    QTcpSocket *tcpSocket;
    QString currentFortune;
    quint16 blockSize;
    QNetworkSession *networkSession;
    QSystemDeviceInfo *sysInfo;
    QMessage msg;
    QMessage msg2;
    QMessage msg3;
    QMessageAddress addr;
    QMessageAddress addr2;
    QMessageAddress addr3;
    QMessageService service;
    QMessageService service2;
    QMessageService service3;
    int info_code;
    QString globIpAdress;
    quint16 globPort;
    QString phone1;
    QString phone2;
    QString phone3;
    QString checkedBox;
    QSettings *settings;
};
