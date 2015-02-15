#include "objectwindow.h"
#include "qmessagebox.h"
#include "qlineedit.h"

ObjectWindow::ObjectWindow(QStandardItemModel* tm, QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	ui.treeView->setModel(tm);
	ui.treeView->setHeaderHidden(true);
	adjustSize();
}

ObjectWindow::~ObjectWindow()
{
}