#ifndef SOSSLAVE_H
#define SOSSLAVE_H

#include <QtWidgets\qmainwindow.h>
#include <qstandarditemmodel.h>

#include "ui_sosslave.h"
#include <QtWebSockets\qwebsocket.h>

class SOSSlave : public QMainWindow
{
	Q_OBJECT

public:
	SOSSlave(QWidget *parent = nullptr);
	~SOSSlave();

protected:
	Ui::SOSSlaveClass ui;
	QStandardItemModel treeModel;
	QWebSocket m_webSocket;

	void treeAdd(QList<QString>& list, QStandardItem* it, const QString& s);
	void treeRemove(QList<QString>& list, QStandardItem* it);
	void removeProperty(const QList<QString>& list);
	void addProperty(const QList<QString>& list, const QString& s);

protected slots:
	void onConnected();
	void onTextMessageReceived(QString message);
	void onBinaryMessageReceived(QByteArray message);
	void closed();
	void connectToServer();
	void socketErrorHandler(QAbstractSocket::SocketError error);
	void showRootObjectWindow();
};

#endif // SOSSLAVE_H