#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "Graph.h"

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	graph = new Graph();
	connect(ui.openGraph, SIGNAL(clicked()), this, SLOT(openGraphic()));
}

void MainWindow::openGraphic() {
	graph->show();
}
