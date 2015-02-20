#ifndef NODEDELEGATE_H
#define NODEDELEGATE_H

#include <QStyledItemDelegate>
#include "treenodewidget.h"

class NodeDelegate : public QStyledItemDelegate
{
	Q_OBJECT

public:
	NodeDelegate(QWidget *parent);
	~NodeDelegate();

	void NodeDelegate::paint(QPainter *painter,
		const QStyleOptionViewItem &option,
		const QModelIndex &index) const override;

	QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

protected:
	TreeNodeWidget* treeNodeWidget;
	
	void setNodeWidget(const QModelIndex&) const;

};

#endif // NODEDELEGATE_H
