#include "sosserver.h"
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtNetwork/QSslCertificate>
#include <QtNetwork/QSslKey>
#include <QtWebSockets\qwebsocket.h>
#include <QtWebSockets\qwebsocketserver.h>

SOSServer::SOSServer(QObject *parent)
	: QObject(parent), uit(nullptr),
	m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),
	QWebSocketServer::NonSecureMode, this)),
	m_clients()
{
	uit.start();
	if (m_pWebSocketServer->listen(QHostAddress::Any, 56321)) {
		qDebug() << "Echoserver listening on port" << 56321;
		connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
			this, &SOSServer::onNewConnection);
		connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &SOSServer::closed);
	}
}

SOSServer::~SOSServer()
{

}

void SOSServer::onNewConnection()
{
	QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

	qDebug() << "Client connected:" << pSocket->peerName() << pSocket->origin() << pSocket->peerAddress();

	connect(pSocket, &QWebSocket::textMessageReceived, this, &SOSServer::processTextMessage);
	connect(pSocket, &QWebSocket::binaryMessageReceived,
		this, &SOSServer::processBinaryMessage);
	connect(pSocket, &QWebSocket::disconnected, this, &SOSServer::socketDisconnected);
	//connect(pSocket, &QWebSocket::pong, this, &SslEchoServer::processPong);

	m_clients << pSocket;
}

void SOSServer::processTextMessage(QString message)
{
	QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	if (pClient)
	{
		pClient->sendTextMessage(message);
	}
}

void SOSServer::processBinaryMessage(QByteArray message)
{
	QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	if (pClient)
	{
		pClient->sendBinaryMessage(message);
	}
}

void SOSServer::socketDisconnected()
{
	qDebug() << "Client disconnected";
	QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	if (pClient)
	{
		m_clients.removeAll(pClient);
		pClient->deleteLater();
	}
}

void SOSServer::onSslErrors(const QList<QSslError> &)
{
	qDebug() << "Ssl errors occurred";
}

void SOSServer::closed() {
	qDebug() << "closed";
}