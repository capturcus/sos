#include "sosmaster.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SOSMaster w;
	w.show();
	return a.exec();
}
