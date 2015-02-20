#ifndef OBJECTWINDOW_H
#define OBJECTWINDOW_H

#include <QMainWindow>
#include <qstandarditemmodel.h>
#include "ui_objectwindow.h"

class ObjectWindow : public QMainWindow
{
	Q_OBJECT

public:
	ObjectWindow(QStandardItemModel*, QPersistentModelIndex root, QWidget *parent = 0);
	~ObjectWindow();
	void setRootIndex(const QModelIndex&);
	void setIndexWidgets(QStandardItem* it);

public slots:
	void doubleClicked(const QModelIndex & index);

protected:
	Ui::ObjectWindow ui;
	QPersistentModelIndex rootIndex;
};

#endif // OBJECTWINDOW_H
