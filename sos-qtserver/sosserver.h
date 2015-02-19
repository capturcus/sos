#ifndef SOSSERVER_H
#define SOSSERVER_H

#include "uithread.h"
#include <QtCore\qobject.h>
#include <QtNetwork\qsslerror.h>
#include <QtCore\qset.h>

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

class SOSServer : public QObject
{
	Q_OBJECT

public:
	SOSServer(QObject *parent);
	~SOSServer();
	QWebSocket* getMaster();
	const QSet<QWebSocket*>& getUndecidedRole();
	const QSet<QWebSocket*>& getSlaves();

public slots:
	void onNewConnection();
	void processTextMessage(QString message);
	void processBinaryMessage(QByteArray message);
	void socketDisconnected();
	void onSslErrors(const QList<QSslError> &errors);
	void closed();

protected:
	QWebSocketServer *m_pWebSocketServer;
	UIThread uit;
	QSet<QWebSocket*> undecidedRole;
	QSet<QWebSocket*> slaves;
	QWebSocket* master = nullptr;
};

#endif // SOSSERVER_H
