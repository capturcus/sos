#include "sosslave.h"
#include "objectwindow.h"
#include "qmessagebox.h"

SOSSlave::SOSSlave(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	adjustSize();
	ObjectWindow* o = new ObjectWindow(&treeModel);
	o->show();
	QList<QString> list = {"root","child1","child2"};
	addProperty(&list);
	list = { "root", "child1", "sibling1" };
	addProperty(&list);
	list = { "root", "sibling1", "sibling1" };
	addProperty(&list);
	tcpSocket = new QTcpSocket();
	connect(tcpSocket, &QTcpSocket::connected, this, &SOSSlave::readFromSocket);
	connectToServer();
}

SOSSlave::~SOSSlave()
{

}

void treeAdd(QList<QString>* list, QStandardItem* it){
	if (list->isEmpty())
		return;
	QString name = list->front();
	list->pop_front();
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

void SOSSlave::addProperty(QList<QString>* list) {
	treeAdd(list, treeModel.invisibleRootItem());
}

void SOSSlave::connectToServer() {
	tcpSocket->abort();
	tcpSocket->connectToHost("localhost", 56321);
}

void SOSSlave::readFromSocket() {
	QMessageBox box;
	box.setText("reading from socket!");
	box.exec();
	box.setText(QString("bytes available: %1").arg(tcpSocket->bytesAvailable()));
	box.exec();
	QDataStream in(tcpSocket);

	if (blockSize == 0) {
		if (tcpSocket->bytesAvailable() < (int)sizeof(quint16))
			return;

		in >> blockSize;
	}

	if (tcpSocket->bytesAvailable() < blockSize)
		return;

	QString text;
	in >> text;

	box.setText(text);
	box.exec();
}