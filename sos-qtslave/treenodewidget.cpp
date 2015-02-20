#include "treenodewidget.h"
#include <QtWidgets\qhboxlayout>
#include "qlabel.h"

TreeNodeWidget::TreeNodeWidget(QWidget *parent)
	: QWidget(parent), key(new QLabel), value(new QLabel)
{
	QHBoxLayout* mainLayout = new QHBoxLayout(this);
	setLayout(mainLayout);
	mainLayout->addWidget(key);
	mainLayout->addStretch();
	mainLayout->addWidget(value);
	mainLayout->setContentsMargins(0, 2, 5, 2);
	adjustSize();
}

TreeNodeWidget::~TreeNodeWidget()
{

}

void TreeNodeWidget::setKey(const QString& text) {
	key->setText(text);
}
void TreeNodeWidget::setValue(const QString& text){
	value->setText(text);
}