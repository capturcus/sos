#include "sosmaster.h"
#include <QtWidgets\qlineedit.h>
#include <QtCore/QCoreApplication>
#include <QDebug>

#include <stdio.h>

#include <fcntl.h>

#include <io.h>

#include <fstream>

const int MAX_LEN = 40;

HANDLE redirectStdout() {
	HANDLE readPipe;
	HANDLE writePipe;

	CreatePipe(&readPipe, &writePipe, 0, 0);

	int pipeHandle = _open_osfhandle((intptr_t)writePipe, _O_TEXT);

	FILE * stdoutfile = _fdopen(pipeHandle, "wt");

	*stdout = *stdoutfile;

	setvbuf(stdout, NULL, _IONBF, 0);

	return readPipe;
}

SOSMaster::SOSMaster(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	L = luaL_newstate();
	luaL_openlibs(L);

	readPipe = redirectStdout();

	connect(ui.lineEdit, &QLineEdit::returnPressed, this, &SOSMaster::returnPressed);
}

SOSMaster::~SOSMaster()
{
	lua_close(L);
}

void SOSMaster::returnPressed() {
	QString text = ui.lineEdit->text();

	if (text == "exit")
		qApp->exit();

	ui.lineEdit->clear();

	int res = luaL_dostring(L, text.toStdString().c_str());
	ui.luaOutput->setText(ui.luaOutput->text() + ">" + text + "\n");

	char buffer[1024] = { 0 };
	
	printf("#");

	ReadFile(readPipe, buffer, 128, 0, 0);
	//ReadFileEx(readPipe, buffer, 128, 0, 0);

	ui.luaOutput->setText(ui.luaOutput->text() + buffer + "\n");

	if (res != 0){
		const char* err = lua_tostring(L, -1);
		ui.luaOutput->setText(ui.luaOutput->text() + "ERROR: " + err + "\n");
		lua_pop(L, 1);
	}
}