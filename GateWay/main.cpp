#include "SerialPort/serialdev.h"
#include "SerialPort/serialprotocal.h"
#include "Network/network.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SerialProtocal s;
    Network::getNet();

    return a.exec();
}
