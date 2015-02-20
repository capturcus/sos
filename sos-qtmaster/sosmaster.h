#ifndef SOSMASTER_H
#define SOSMASTER_H

#include <Windows.h>
#undef min
#include <QtWidgets/QMainWindow>
#include "ui_sosmaster.h"
#include "lua-utils.h"
#include <QtWebSockets\qwebsocket.h>

class SOSMaster : public QMainWindow
{
	Q_OBJECT

public:
	SOSMaster(QWidget *parent = 0);
	~SOSMaster();

	void returnPressed();

	Ui::SOSMasterClass ui;

protected:
	bool eventFilter(QObject* obj, QEvent *e);
	void flushLua();

	lua_State* L = nullptr;
	HANDLE readPipe;
	QWebSocket m_socket;
	int historyDepth = 0;
	QVector<QString> history;

protected slots:
	void onConnected();
	void onTextMessageReceived(QString message);
	void closed();
	void connectToServer();
	void socketErrorHandler(QAbstractSocket::SocketError error);
	void appendLineToLuaOutput(const QString&);
	void openLuaFile();
};

#endif // SOSMASTER_H
