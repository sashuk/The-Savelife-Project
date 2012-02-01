#include <QCoreApplication>
#include <QtCore>
#include <QDebug>
#include <stdlib.h>
#include "server.h"

int main(int argc, char *argv[])
{
QCoreApplication app(argc, argv);
Server server;
QCoreApplication::processEvents();
daemon(0,0);
return app.exec();
}
