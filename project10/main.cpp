#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    //Variable for keeping the path
    QApplication app(argc, argv);
    QString glob_filepath = app.applicationDirPath();
    MainWindow *mainWindow;
    mainWindow = new MainWindow(glob_filepath);
    mainWindow->setOrientation(MainWindow::ScreenOrientationAuto);
    mainWindow->showExpanded();
    return app.exec();
}
