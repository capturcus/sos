#include "sosmaster.h"
#include <QtWidgets/QApplication>

#include <QtCore\QtPlugin>
Q_IMPORT_PLUGIN(QWindowsIntegrationPlugin)

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SOSMaster w;
	w.show();
	return a.exec();
}