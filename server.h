#ifndef SERVER_H
#define SERVER_H

#include <QtNetwork>
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <map>

class Server: public QObject
{
    Q_OBJECT
    public:
        static Server* GetServerInst();
        ~Server();
    public slots:
        void acceptConnection();
        void read();
    private:
        QTcpServer server;
        QTcpSocket* client;

        Server(QObject * parent = 0);
        static Server* _inst;
};

#endif // SERVER_H
