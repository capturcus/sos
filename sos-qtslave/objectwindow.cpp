#include "objectwindow.h"
#include "qmessagebox.h"
#include "qlineedit.h"

ObjectWindow::ObjectWindow(QStandardItemModel* tm, QPersistentModelIndex root, QWidget *parent)
	: QMainWindow(parent), rootIndex(root)
{
	ui.setupUi(this);
	ui.treeView->setModel(tm);
	ui.treeView->setHeaderHidden(true);
	ui.treeView->setRootIndex(root);

	connect(ui.treeView, &QTreeView::doubleClicked, this, &ObjectWindow::doubleClicked);

	adjustSize();
}

ObjectWindow::~ObjectWindow()
{
}

void ObjectWindow::setRootIndex(const QModelIndex& i){
	ui.treeView->setRootIndex(i);
}

void ObjectWindow::doubleClicked(const QModelIndex & index) {
	auto treeModel = (QStandardItemModel*)ui.treeView->model();
	ObjectWindow* o = new ObjectWindow(treeModel, index);
	o->show();
	o->setWindowTitle(treeModel->itemFromIndex(index)->text());
}