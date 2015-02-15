#ifndef NETWORKTHREAD_H
#define NETWORKTHREAD_H

#include <QThread>
#include "qtcpserver.h"

class NetworkThread : public QThread
{
	Q_OBJECT

public:
	NetworkThread(QObject *parent);
	~NetworkThread();
	void run();
public slots:
	void newConnection();
private:
	QTcpServer* tcpServer;
};

#endif // NETWORKTHREAD_H
