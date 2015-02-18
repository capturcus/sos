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

private:
	lua_State* L = nullptr;
	HANDLE readPipe;
	QWebSocket m_socket;

private slots:
	void onConnected();
	void onTextMessageReceived(QString message);
	void closed();
	void connectToServer();
	void socketErrorHandler(QAbstractSocket::SocketError error);
};

#endif // SOSMASTER_H
