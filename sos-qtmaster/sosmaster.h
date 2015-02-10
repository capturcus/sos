#ifndef SOSMASTER_H
#define SOSMASTER_H

#include <QtWidgets/QMainWindow>
#include "ui_sosmaster.h"
#include "lua-utils.h"
#include <Windows.h>

class SOSMaster : public QMainWindow
{
	Q_OBJECT

public:
	SOSMaster(QWidget *parent = 0);
	~SOSMaster();

	void returnPressed();

	Ui::SOSMasterClass ui;

private:
	lua_State* L = nullptr;

	HANDLE readPipe;
};

#endif // SOSMASTER_H
