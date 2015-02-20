#include "nodedelegate.h"
#include "qspinbox.h"
#include "qlabel.h"
#include "qpainter.h"
#include "QtCore\QModelIndex"
#include "qstandarditemmodel.h"
#include "treenodewidget.h"

NodeDelegate::NodeDelegate(QWidget *parent)
	: QStyledItemDelegate(parent), treeNodeWidget(new TreeNodeWidget())
{

}

NodeDelegate::~NodeDelegate()
{

}
void NodeDelegate::paint(QPainter *painter,
	const QStyleOptionViewItem &option,
	const QModelIndex &index) const {
	painter->save();
	setNodeWidget(index);
	treeNodeWidget->resize(option.rect.size());
	painter->translate(option.rect.topLeft());
	treeNodeWidget->render(painter, QPoint(), QRegion(), QWidget::DrawChildren);
	painter->restore();
}

QSize NodeDelegate::sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const {
	setNodeWidget(index);
	return treeNodeWidget->sizeHint();
}

void NodeDelegate::setNodeWidget(const QModelIndex& index) const {
	QStandardItemModel* model = (QStandardItemModel*)index.model();
	treeNodeWidget->setKey(model->itemFromIndex(index)->text());
	treeNodeWidget->setValue("value");
}