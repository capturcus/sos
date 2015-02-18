#include <iostream>
#include <QtCore/QCoreApplication>
#include "sosserver.h"

int main(int argc, char *argv[])
{
	QCoreApplication a(argc, argv);
	SOSServer s(nullptr);
	return a.exec();
}
