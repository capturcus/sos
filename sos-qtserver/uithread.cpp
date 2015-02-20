#include "uithread.h"
#include <QtCore\qdebug.h>
#include <string>
#include <iostream>
#include <QtWidgets\qapplication.h>
#include "sosserver.h"
#include <QtWebSockets\QWebSocket>

UIThread::UIThread(QObject *parent)
	: QThread(parent)
{

}

UIThread::~UIThread()
{

}

void UIThread::run() {
	qDebug() << "Server started.";
	std::string line;
	while (true)
	{
		std::getline(std::cin, line);
		if (line == "exit")
		{
			qApp->exit();
		}
		if (line == "status"){
			SOSServer* server = dynamic_cast<SOSServer*>(parent());
			if (!server)
				qDebug() << "Something went wrong.";
			else
			{
				if (server->getMaster())
					qDebug() << "MASTER: " << server->getMaster()->peerAddress() << server->getMaster()->peerPort() << server->getMaster()->peerName();
				else
					qDebug() << "MASTER: not set";
				qDebug() << "SLAVES:";
				for (QWebSocket* slave : server->getSlaves())
				{
					qDebug() << slave->peerAddress() << slave->peerPort() << slave->peerName();
				}
			}
		}
		else {
			std::cout << "Unknown command: " << line << "\n";
		}
	}
}