#include "mainwindow.h"
#include "tcpServer.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    tcpServer server;
    if(!server.startServer(3333)){
        qDebug() << "ERROR:" << server.errorString();
        return 1;
    }
    qDebug() << "Server started...";
    return a.exec();
}
