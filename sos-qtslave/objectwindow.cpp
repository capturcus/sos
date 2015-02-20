#include "objectwindow.h"
#include "qmessagebox.h"
#include "qlineedit.h"
#include "qlabel.h"
#include "nodedelegate.h"

ObjectWindow::ObjectWindow(QStandardItemModel* tm, QPersistentModelIndex root, QWidget *parent)
	: QMainWindow(parent), rootIndex(root)
{
	ui.setupUi(this);
	ui.treeView->setModel(tm);
	ui.treeView->setHeaderHidden(true);
	ui.treeView->setRootIndex(root);

	//setIndexWidgets(tm->invisibleRootItem());
	ui.treeView->setItemDelegate(new NodeDelegate(this));

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

void ObjectWindow::setIndexWidgets(QStandardItem* it) {
	auto model = (QStandardItemModel*)ui.treeView->model();
	QModelIndex i = model->indexFromItem(it);
	ui.treeView->setIndexWidget(i, new QLineEdit);
	for (int i = 0; i < it->rowCount(); i++)
	{
		setIndexWidgets(it->child(i));
	}
}