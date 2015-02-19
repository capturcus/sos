#include "sosslave.h"
#include "objectwindow.h"
#include "qmessagebox.h"

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
	ObjectWindow* o = new ObjectWindow(&treeModel);
	o->show();
	QList<QString> list = {"root","child1","child2"};
	addProperty(list);
	list = { "root", "child1", "sibling1" };
	addProperty(list);
	list = { "root", "sibling1", "sibling1" };
	addProperty(list);
	ui.connectionLabel->setTextFormat(Qt::TextFormat::RichText);
	ui.connectionLabel->setText(LABEL_HEADER + LABEL_DISCONNECTED);

	ui.connectButton->setText(CONNECT_STRING);
	connect(ui.connectButton, &QPushButton::clicked, this, &SOSSlave::connectToServer);

	connect(&m_webSocket, &QWebSocket::connected, this, &SOSSlave::onConnected);
	connect(&m_webSocket, &QWebSocket::disconnected, this, &SOSSlave::closed);
	connect(&m_webSocket, static_cast<void (QWebSocket::*)(QAbstractSocket::SocketError)>(&QWebSocket::error),
		this, static_cast<void (SOSSlave::*)(QAbstractSocket::SocketError)>(&SOSSlave::socketErrorHandler));

	connect(ui.lineEdit, &QLineEdit::returnPressed, this, &SOSSlave::connectToServer);
}

SOSSlave::~SOSSlave()
{

}

void treeAdd(QList<QString>& list, QStandardItem* it){
	if (list.isEmpty())
		return;
	QString name = list.front();
	list.pop_front();
	bool added = false;
	for (int i = 0; i < it->rowCount(); i++)
	{
		if (name == it->child(i)->text()){
			treeAdd(list, it->child(i));
			added = true;
			break;
		}
	}
	if (!added){
		auto newit = new QStandardItem(name);
		it->appendRow(newit);
		treeAdd(list, newit);
	}
}

void SOSSlave::addProperty(const QList<QString>& list) {
	treeAdd(QList<QString>(list), treeModel.invisibleRootItem());
}

void SOSSlave::onConnected(){
	ui.connectionLabel->setText(LABEL_HEADER + LABEL_CONNECTED);
	connect(&m_webSocket, &QWebSocket::textMessageReceived,
		this, &SOSSlave::onTextMessageReceived);
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