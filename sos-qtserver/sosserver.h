#ifndef SOSSERVER_H
#define SOSSERVER_H

#include "uithread.h"
#include <QtCore\qobject.h>
#include <QtNetwork\qsslerror.h>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class SOSServer : public QObject
{
	Q_OBJECT

public:
	SOSServer(QObject *parent);
	~SOSServer();

public slots:
	void onNewConnection();
	void processTextMessage(QString message);
	void processBinaryMessage(QByteArray message);
	void socketDisconnected();
	void onSslErrors(const QList<QSslError> &errors);
	void closed();

private:
	QWebSocketServer *m_pWebSocketServer;
	QList<QWebSocket *> m_clients;
	QWebSocket* m_masterSocket;
	UIThread uit;
};

#endif // SOSSERVER_H
