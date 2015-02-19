#include "sosserver.h"
#include <QtCore/QDebug>
#include <QtCore/QFile>
#include <QtNetwork/QSslCertificate>
#include <QtNetwork/QSslKey>
#include <QtWebSockets\qwebsocket.h>
#include <QtWebSockets\qwebsocketserver.h>
#include <QtWidgets\qapplication.h>

SOSServer::SOSServer(QObject *parent)
	: QObject(parent), uit(this),
	m_pWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),
	QWebSocketServer::NonSecureMode, this))
{
	uit.start();
	if (m_pWebSocketServer->listen(QHostAddress::Any, 56321)) {
		qDebug() << "Echoserver listening on port" << 56321;
		connect(m_pWebSocketServer, &QWebSocketServer::newConnection,
			this, &SOSServer::onNewConnection);
		connect(m_pWebSocketServer, &QWebSocketServer::closed, this, &SOSServer::closed);
	}
	else {
		qDebug() << "Failed to initiate server." << m_pWebSocketServer->errorString();
		qApp->exit();
	}
}

SOSServer::~SOSServer()
{

}

void SOSServer::onNewConnection()
{
	QWebSocket *pSocket = m_pWebSocketServer->nextPendingConnection();

	qDebug() << "Client connected!";

	connect(pSocket, &QWebSocket::textMessageReceived, this, &SOSServer::processTextMessage);
	connect(pSocket, &QWebSocket::binaryMessageReceived,
		this, &SOSServer::processBinaryMessage);
	connect(pSocket, &QWebSocket::disconnected, this, &SOSServer::socketDisconnected);

	undecidedRole.insert(pSocket);
}

void SOSServer::processTextMessage(QString message)
{
	QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	if (pClient)
	{
		if (undecidedRole.contains(pClient)){
			if (message == "master"){
				master = pClient;
				master->sendTextMessage("master");
				qDebug() << "Master set.";
			}
			else if (message == "slave"){
				slaves.insert(pClient);
				pClient->sendTextMessage("slave");
				qDebug() << "Slave added.";
			}
			undecidedRole.remove(pClient);
		}
		else
		{
			qDebug() << "Received a text message out of context: " << message;
		}
	}
	else {
		qDebug() << "Failed to cast sender to QWebSocket.";
	}
}

void SOSServer::processBinaryMessage(QByteArray message)
{
	QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	if (pClient)
	{
		if (pClient == master){
			for (QWebSocket* s : slaves)
			{
				s->sendBinaryMessage(message);
			}
		}
		else if (slaves.contains(pClient)){
			master->sendBinaryMessage(message);
		}
		else
		{
			qDebug() << "Received binary message from unknown sender.";
		}
	}
}

void SOSServer::socketDisconnected()
{
	qDebug() << "Client disconnected";
	QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	if (pClient)
	{
		if (pClient == master)
		{
			qDebug() << "Master disconnected!";
			master = nullptr;
		}
		else if (slaves.contains(pClient))
		{
			qDebug() << "A slave disconnected!";
			slaves.remove(pClient);
		}
		else {
			undecidedRole.remove(pClient);
		}
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

QWebSocket* SOSServer::getMaster(){
	return master;
}
const QSet<QWebSocket*>& SOSServer::getUndecidedRole(){
	return undecidedRole;
}
const QSet<QWebSocket*>& SOSServer::getSlaves(){
	return slaves;
}