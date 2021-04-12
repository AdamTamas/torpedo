/*#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}*/
#include <QCoreApplication>
#include "tcpServer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ATcpServer server;
    if(!server.startServer(3333)){
        qDebug() << "ERROR:" << server.errorString();
        return 1;
    }
    qDebug() << "Server started...";
    return a.exec();
}
