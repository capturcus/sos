#include "uithread.h"
#include <QtCore\qdebug.h>
#include <string>
#include <iostream>
#include <QtWidgets\qapplication.h>

UIThread::UIThread(QObject *parent)
	: QThread(parent)
{

}

UIThread::~UIThread()
{

}

void UIThread::run() {
	qDebug() << "Server started.";
	std::string line;
	while (true)
	{
		std::getline(std::cin, line);
		if (line == "exit")
		{
			qApp->exit();
		}
		else {
			std::cout << "Unknown command: " << line << "\n";
		}
	}
}