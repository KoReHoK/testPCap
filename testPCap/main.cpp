#include "MainWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
	w.setFixedSize(405, 495);
    w.show();

    return a.exec();
}
