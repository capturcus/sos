#include "sosslave.h"
#include "objectwindow.h"
#include "qmessagebox.h"
#include "..\sos-qtserver\Common.h"
#include "treenodewidget.h"
#include "qpushbutton.h"
#include "qlineedit.h"

const QString CONNECT_STRING = "Connect to server!";

const QString LABEL_HEADER = "<style>\ntittle{ font-family:comic sans ms;\nfont-size:30pt;\n }\nbody {\nfont-family:comic sans ms;\nfont-size:20pt;\n}\n</style>\n"
"<center><tittle>SOS Slave</tittle></center><hr>";
const QString LABEL_DISCONNECTED = "<style>\nhuehue{\ncolor:red; }\n</style>\n<body>Server Status: <huehue>DISCONNECTED</huehue></body>";
const QString LABEL_CONNECTED = "\n<style>\nhuehue{ \ncolor:green; }\n</style>\n<body>Server Status: <huehue>CONNECTED</huehue></body>";
const QString LABEL_TRYING = "\n<style>\nhuehue{ \ncolor:blue; }\n</style>\n<body>Server Status: <huehue>Connecting...</huehue></body>";

SOSSlave::SOSSlave(QWidget *p)
	: QMainWindow(p)
{
	ui.setupUi(this);
	adjustSize();

	/*QList<QString> list = { "root", "child1", "child2" };
	addProperty(list, "v1");
	list = { "root", "child1", "sibling1" };
	addProperty(list, "v2");
	list = { "root", "sibling1", "sibling1" };
	addProperty(list, "v3");
	list = { "root", "sibling1" };
	removeProperty(list);*/

	ui.connectionLabel->setTextFormat(Qt::TextFormat::RichText);
	ui.connectionLabel->setText(LABEL_HEADER + LABEL_DISCONNECTED);

	ui.connectButton->setText(CONNECT_STRING);
	connect(ui.connectButton, &QPushButton::clicked, this, &SOSSlave::connectToServer);

	connect(&m_webSocket, &QWebSocket::connected, this, &SOSSlave::onConnected);
	connect(&m_webSocket, &QWebSocket::disconnected, this, &SOSSlave::closed);
	connect(&m_webSocket, static_cast<void (QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error),
		this, static_cast<void (SOSSlave::*)(QAbstractSocket::SocketError)>(&SOSSlave::socketErrorHandler));

	connect(ui.lineEdit, &QLineEdit::returnPressed, this, &SOSSlave::connectToServer);

	connect(ui.showObjectWindowButton, &QPushButton::clicked, this, &SOSSlave::showRootObjectWindow);
}

SOSSlave::~SOSSlave()
{

}

void SOSSlave::treeAdd(QList<QString>& list, QStandardItem* it, const QString& value){
	if (list.isEmpty()){
		it->setData(value, 42);
		return;
	}
	QString name = list.front();
	list.pop_front();
	bool added = false;
	for (int i = 0; i < it->rowCount(); i++)
	{
		if (name == it->child(i)->text()){
			treeAdd(list, it->child(i), value);
			added = true;
			break;
		}
	}
	if (!added){
		auto newit = new QStandardItem(name);
		it->appendRow(newit);
		treeAdd(list, newit, value);
	}
}

void SOSSlave::treeRemove(QList<QString> & list, QStandardItem* it){
	if (list.isEmpty()) {
		auto parent = it->parent() ? it->parent() : treeModel.invisibleRootItem();
		parent->removeRow(it->index().row());
		return;
	}

	QString name = list.front();
	list.pop_front();

	for (int i = 0; i < it->rowCount(); i++) {
		if (name == it->child(i)->text()) {
			treeRemove(list, it->child(i));
			return;
		}
	}
}

void SOSSlave::addProperty(const QList<QString>& list, const QString& s) {
	treeAdd(QList<QString>(list), treeModel.invisibleRootItem(), s);
}

void SOSSlave::removeProperty(const QList<QString>& list) {
	treeRemove(QList<QString>(list), treeModel.invisibleRootItem());
}

void SOSSlave::onConnected(){
	ui.connectionLabel->setText(LABEL_HEADER + LABEL_CONNECTED);
	connect(&m_webSocket, &QWebSocket::textMessageReceived, this, &SOSSlave::onTextMessageReceived);
	connect(&m_webSocket, &QWebSocket::binaryMessageReceived, this, &SOSSlave::onBinaryMessageReceived);
	m_webSocket.sendTextMessage(QStringLiteral("slave"));
}
void SOSSlave::onTextMessageReceived(QString message){
	if (message == "slave"){
		ui.connectionLabel->setText(LABEL_HEADER + LABEL_CONNECTED);
	}
	else {
		QMessageBox::information(this, "Message from the server", QString("Message from the server: ") + message);
	}
}

void SOSSlave::closed() {
	ui.connectionLabel->setText(LABEL_HEADER + LABEL_DISCONNECTED);
}

void SOSSlave::connectToServer() {
	ui.connectionLabel->setText(LABEL_HEADER + LABEL_TRYING);
	m_webSocket.open(QUrl(QString("ws://") + ui.lineEdit->text() + ":56321"));
}

void SOSSlave::socketErrorHandler(QAbstractSocket::SocketError error) {
	ui.connectionLabel->setText(LABEL_HEADER + LABEL_DISCONNECTED);
	QMessageBox::information(this, "Error!", QString("ERROR OCCURED!\n") + m_webSocket.errorString());
}

void SOSSlave::onBinaryMessageReceived(QByteArray message){
	QDataStream s(&message, QIODevice::ReadOnly);
	QMap<QString, QString> map;
	int type;
	s >> type;
	if ((MESSAGE_TYPE)type == MESSAGE_TYPE::WORLD){
		/*s >> map;
		treeModel.clear();
		auto it = map.begin();
		while (it != map.end()){
			QStringList list = it.key().split(QString("."));
			addProperty(list, it.value());
			it++;
		}*/

		qint8 cmd;

		while (true)
		{
			s >> cmd;
			if (cmd == 0)
				break;	// Koniec

			if (cmd == 1)
			{
				// Dodanie wartoœci
				QString key, value;
				s >> key >> value;
				addProperty(key.split('.'), value);
			}
			else if (cmd == -1)
			{
				// Wywalenie wartoœci
				QString key;
				s >> key;
				removeProperty(key.split('.'));
			}
		}
	}
	else {
		QMessageBox::critical(this, "Error", "Unknown message type.");
	}
}

void SOSSlave::showRootObjectWindow() {
	ObjectWindow* o = new ObjectWindow(&treeModel, treeModel.indexFromItem(treeModel.invisibleRootItem()));
	o->show();
	o->setWindowTitle("WORLD");
}