#include "sosslave.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	SOSSlave w;
	w.show();
	return a.exec();
}