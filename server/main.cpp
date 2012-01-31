#include <QCoreApplication>
#include <QtCore>
#include <QDebug>
#include <stdlib.h>
#include "server.h"

int main(int argc, char *argv[])
{
QCoreApplication app(argc, argv);
Server server;
while(true) {
       QString string = "";
       int ch;
   //   while ((ch = getchar()) != '\n')
    //      string += ch;
       QCoreApplication::processEvents();
    }
}
