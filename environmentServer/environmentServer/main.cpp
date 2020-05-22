#include <QCoreApplication>
#include "gatewayserver.h"
#include "clientserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    GatewayServer::getGateServer();
    ClientServer::getClientServer();

    return a.exec();
}
