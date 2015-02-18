#include "uithread.h"
#include <QtCore\qdebug.h>

UIThread::UIThread(QObject *parent)
	: QThread(parent)
{

}

UIThread::~UIThread()
{

}

void UIThread::run() {
	qDebug() << "Server started.";
	QString line;
}