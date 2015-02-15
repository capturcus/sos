#ifndef SOSSLAVE_H
#define SOSSLAVE_H

#include <QtWidgets/QMainWindow>
#include <qstandarditemmodel.h>
#include "qtcpsocket.h"

#include "ui_sosslave.h"

class SOSSlave : public QMainWindow
{
	Q_OBJECT

public:
	SOSSlave(QWidget *parent = 0);
	~SOSSlave();
	void addProperty(QList<QString>*);

private:
	Ui::SOSSlaveClass ui;
	QStandardItemModel treeModel;
	QTcpSocket* tcpSocket;

	void connectToServer();
	void readFromSocket();
	int blockSize = 0;
};

#endif // SOSSLAVE_H