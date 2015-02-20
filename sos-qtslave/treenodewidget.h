#ifndef TREENODEWIDGET_H
#define TREENODEWIDGET_H

#include <QWidget>
#include "qlabel.h"

class TreeNodeWidget : public QWidget
{
	Q_OBJECT

public:
	TreeNodeWidget(QWidget *parent = nullptr);
	~TreeNodeWidget();
	void setKey(const QString& text);
	void setValue(const QString& text);

protected:
	QLabel* key;
	QLabel* value;
	
};

#endif // TREENODEWIDGET_H
