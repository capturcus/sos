#ifndef SOSSERVER_H
#define SOSSERVER_H

#include <QObject>
#include "networkthread.h"
#include "uithread.h"

class SOSServer : public QObject
{
	Q_OBJECT

public:
	SOSServer(QObject *parent);
	~SOSServer();

private:
	NetworkThread nt;
	UIThread uit;
};

#endif // SOSSERVER_H
