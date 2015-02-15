#ifndef OBJECTWINDOW_H
#define OBJECTWINDOW_H

#include <QMainWindow>
#include <qstandarditemmodel.h>
#include "ui_objectwindow.h"

class ObjectWindow : public QMainWindow
{
	Q_OBJECT

public:
	ObjectWindow(QStandardItemModel*, QWidget *parent = 0);
	~ObjectWindow();

private:
	Ui::ObjectWindow ui;
};

#endif // OBJECTWINDOW_H
