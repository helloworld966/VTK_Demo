#include "VTK_OCC_Qt.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	VTK_OCC_Qt w;
	w.show();
	return a.exec();
}
