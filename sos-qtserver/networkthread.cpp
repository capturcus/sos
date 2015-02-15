#include "networkthread.h"
#include "qdebug.h"
#include "qtcpserver.h"
#include "qnetworkinterface.h"
#include "qtcpsocket.h"

NetworkThread::NetworkThread(QObject *parent)
	: QThread(parent)
{

}

NetworkThread::~NetworkThread()
{

}

void NetworkThread::run() {
	tcpServer = new QTcpServer();
	if (!tcpServer->listen(QHostAddress::Any, 56321)) {
		qDebug() << tr("Unable to start the server: %1.").arg(tcpServer->errorString());
		return;
	}
	QString ipAddress;
	ipAddress = QHostAddress(QHostAddress::LocalHost).toString();

	connect(tcpServer, &QTcpServer::newConnection, this, &NetworkThread::newConnection);

	qDebug() << (tr("The server is running on\n\nIP: %1\nport: %2\n\n"
		"Run the Fortune Client example now.")
		.arg(ipAddress).arg(tcpServer->serverPort()));
	tcpServer->waitForNewConnection(-1);
}

void NetworkThread::newConnection() {
	qDebug() << "new connection!";
	QByteArray block;
	QDataStream out(&block, QIODevice::WriteOnly);
	out << (quint16)0;
	out << "DUPA QRWA";
	out.device()->seek(0);
	out << (quint16)(block.size() - sizeof(quint16));

	QTcpSocket *clientConnection = tcpServer->nextPendingConnection();
	connect(clientConnection, &QTcpSocket::disconnected, clientConnection, &QTcpSocket::deleteLater);

	clientConnection->write(block);
	clientConnection->disconnectFromHost();
	qDebug() << "disconnected";
}