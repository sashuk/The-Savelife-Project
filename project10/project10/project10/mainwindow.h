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
    MainWindow(QWidget *parent = 0);
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
    void pressedUnus();
    void pressedDuo();
    void pressedTres();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();

private:
    Ui::MainWindow *ui;
    QString deviceid;
    QString coordx;
    QString coordy;
    QTcpSocket *tcpSocket;
    QString currentFortune;
    quint16 blockSize;
    QNetworkSession *networkSession;
    QSystemDeviceInfo *sysInfo;
    QMessage msg;
    QMessageAddress addr;
    QMessageService service;
    int info_code;
    QString globIpAdress;
    quint16 globPort;
    QString phone1;
    QString phone2;
    QString phone3;
    QSettings *settings;
};
