#include <QCoreApplication>
#include "metadata.h"
#include "metadatamaker.h"
#include "server.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    Server* server = Server::GetServerInst();

    return a.exec();
}
