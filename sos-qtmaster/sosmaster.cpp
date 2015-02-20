#include "sosmaster.h"
#include "lua-utils.h"
#include <QtWidgets\qlineedit.h>
#include <QtCore/QCoreApplication>
#include "QtCore/qdebug.h"

#include <stdio.h>
#include <fcntl.h>
#include <io.h>
#include <fstream>

#include "QtWidgets\qmessagebox.h"
#include "QtGui\QKeyEvent"
#include "QtWidgets\qfiledialog.h"
#include "..\sos-qtserver\Common.h"

const int MAX_LEN = 40;
const int MAX_LINE_COUNT = 40;

const QString LABEL_CONNECTED = "\n<style>\nhuehue{ \ncolor:green; }\n</style>\n<body>Server Status : <huehue>CONNECTED</huehue></body>";
const QString LABEL_DISCONNECTED = "<style>\nhuehue{\ncolor:red; }\n</style>\n<body>Server Status: <huehue>DISCONNECTED</huehue></body>";
const QString LABEL_TRYING = "\n<style>\nhuehue{ \ncolor:blue; }\n</style>\n<body>Server Status: <huehue>Connecting...</huehue></body>";

HANDLE redirectStdout() {
	HANDLE readPipe;
	HANDLE writePipe;

	CreatePipe(&readPipe, &writePipe, 0, 0);

	int pipeHandle = _open_osfhandle((intptr_t)writePipe, _O_TEXT);

	FILE * stdoutfile = _fdopen(pipeHandle, "wt");

	*stdout = *stdoutfile;

	setvbuf(stdout, NULL, _IONBF, 0);

	return readPipe;
}

SOSMaster::SOSMaster(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.label->setTextFormat(Qt::TextFormat::RichText);

	ui.luaInput->installEventFilter(this);

	L = luaL_newstate();
	luaL_openlibs(L);
	lua_register(L, "printRec", [](lua_State * L) -> int{
		printLuaValue(L, -1);
		lua_pop(L, 1);
		return 0;
	});

	readPipe = redirectStdout();

	connect(ui.luaInput, &QLineEdit::returnPressed, this, &SOSMaster::returnPressed);
	connect(ui.serverAddress, &QLineEdit::returnPressed, this, &SOSMaster::connectToServer);

	connect(&m_socket, &QWebSocket::connected, this, &SOSMaster::onConnected);
	connect(&m_socket, &QWebSocket::disconnected, this, &SOSMaster::closed);
	connect(&m_socket, static_cast<void (QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error),
		this, static_cast<void (SOSMaster::*)(QAbstractSocket::SocketError)>(&SOSMaster::socketErrorHandler));

	connect(ui.actionLoadLua, &QAction::triggered, this, &SOSMaster::openLuaFile);

	luaL_dostring(L, "WORLD = {}");
}

SOSMaster::~SOSMaster()
{
	lua_close(L);
}

QList<QString> recursion;
QMap<QString, QString> world;

bool isWeirdType(int n){
	if (n == LUA_TTHREAD || 
		n == LUA_TUSERDATA || 
		n == LUA_TLIGHTUSERDATA ||
		n == LUA_TFUNCTION ||
		n == LUA_TNIL)
		return true;
	return false;
}

void serializeWorld(lua_State* L){
	int valueType = lua_type(L, -1);
	int keyType = lua_type(L, -2);
	if (isWeirdType(keyType) || keyType == LUA_TTABLE)
		return;
	if (isWeirdType(valueType))
		return;
	if (valueType == LUA_TTABLE){
		recursion.append(luaValueToString(L, -2));
		traverseLuaTable(L, serializeWorld);
		recursion.pop_back();
	}
	QString key;
	for (const QString& s : recursion)
	{
		key += (s + ".");
	}
	key += luaValueToString(L, -2);
	if (valueType != LUA_TTABLE)
		world[key] = luaValueToString(L, -1);
	else
		world[key] = "";	// HAXXX
}

void SOSMaster::returnPressed() {
	historyDepth = 0;

	QString text = ui.luaInput->text();

	history.push_front(text);

	if (text == "exit")
		qApp->exit();

	ui.luaInput->clear();

	int res = luaL_dostring(L, text.toStdString().c_str());
	appendLineToLuaOutput(QString(">") + text);

	printf("#");
	flushLua();

	if (res != 0){
		const char* err = lua_tostring(L, -1);
		appendLineToLuaOutput(QString(err));
		lua_pop(L, 1);
	}
	else if (m_socket.state() == QAbstractSocket::SocketState::ConnectedState){
		auto oldWorld = world;
		world.clear();

		traverseGlobalLuaTable(L, "WORLD", serializeWorld);

		QByteArray buffer;
		QDataStream *stream = new QDataStream(&buffer, QIODevice::WriteOnly);
		*stream << (int)MESSAGE_TYPE::WORLD;
		//*stream << world;

		auto oldIt = oldWorld.begin();
		auto it = world.begin();

		auto compareIterators = [&]() -> int {
			if (oldIt == oldWorld.end())
				return -1;
			if (it == world.end())
				return 1;

			return QString::compare(it.key(), oldIt.key());
		};

		while (oldIt != oldWorld.end() || it != world.end())
		{
			int cmp = compareIterators();

			if (cmp < 0)
			{
				// Dodajemy coœ
				*stream << (qint8)1 << it.key() << it.value();
				it++;
			}
			else if (cmp > 0)
			{
				// Kasujemy coœ
				*stream << (qint8)-1 << oldIt.key();
				oldIt++;
			}
			else
			{
				// Bez zmian
				it++;
				oldIt++;
			}
		}

		*stream << (qint8)0;

		delete stream;
		m_socket.sendBinaryMessage(buffer);
		recursion.clear();
		
	}
}

void SOSMaster::onConnected(){
	connect(&m_socket, &QWebSocket::textMessageReceived,
		this, &SOSMaster::onTextMessageReceived);
	m_socket.sendTextMessage(QStringLiteral("master"));
}
void SOSMaster::onTextMessageReceived(QString message){
	if (message == "master"){
		ui.label->setText(LABEL_CONNECTED);
	}
	else {
		QMessageBox::information(this, "Message from the server", QString("Message from the server: ") + message);
	}
}

void SOSMaster::closed(){
	ui.label->setText(LABEL_DISCONNECTED);
}

void SOSMaster::connectToServer(){
	ui.label->setText(LABEL_TRYING);
	m_socket.open(QUrl(QString("ws://") + ui.serverAddress->text() + ":56321"));
}

void SOSMaster::socketErrorHandler(QAbstractSocket::SocketError error){
	ui.label->setText(LABEL_DISCONNECTED);
	QMessageBox::information(this, "Error!", QString("ERROR OCCURED!\n") + m_socket.errorString());
}

void SOSMaster::appendLineToLuaOutput(const QString& text) {
	QString oldText = ui.luaOutput->text();
	oldText += (text + "\n");
	while (oldText.count("\n") > MAX_LINE_COUNT){
		oldText.remove(0, 1);
	}
	ui.luaOutput->setText(oldText);
}

bool SOSMaster::eventFilter(QObject* obj, QEvent *event)
{
	if (obj == ui.luaInput)
	{
		if (event->type() == QEvent::KeyPress)
		{
			QKeyEvent* keyEvent = static_cast<QKeyEvent*>(event);
			if (keyEvent->key() == Qt::Key_Up)
			{
				if (history.empty())
					return true;
				ui.luaInput->setText(history[historyDepth]);
				if (historyDepth < history.size() - 1)
					historyDepth++;
				return true;
			}
			else if (keyEvent->key() == Qt::Key_Down)
			{
				if (history.empty())
					return true;
				if (historyDepth > 0)
					historyDepth--;
				ui.luaInput->setText(history[historyDepth]);
				return true;
			}
		}
		return false;
	}
	return QMainWindow::eventFilter(obj, event);
}

void SOSMaster::openLuaFile() {
	QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Lua files (*.lua)"));
	int res = luaL_dofile(L, fileName.toStdString().c_str());
	if (res != 0){
		const char* err = lua_tostring(L, -1);
		printf(err);
		lua_pop(L, 1);
	}
	printf("#");
	flushLua();
}

void SOSMaster::flushLua(){
	char buffer[1024] = { 0 };
	ReadFile(readPipe, buffer, 1024, 0, 0);
	appendLineToLuaOutput(QString(buffer));
}