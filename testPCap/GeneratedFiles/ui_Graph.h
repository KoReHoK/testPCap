#ifndef UI_GRAPH_H
#define UI_GRAPH_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include "qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_Graph
{
public:
	QMenuBar *menuBar;
	QToolBar *mainToolBar;
	QWidget *centralWidget;
	QStatusBar *statusBar;
	QCustomPlot *plot;

	void setupUi(QMainWindow *Graph)
	{
		if (Graph->objectName().isEmpty())
			Graph->setObjectName(QStringLiteral("Graph"));
		Graph->resize(400, 300);
		menuBar = new QMenuBar(Graph);
		menuBar->setObjectName(QStringLiteral("menuBar"));
		Graph->setMenuBar(menuBar);
		mainToolBar = new QToolBar(Graph);
		mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
		Graph->addToolBar(mainToolBar);
		centralWidget = new QWidget(Graph);
		centralWidget->setObjectName(QStringLiteral("centralWidget"));
		statusBar = new QStatusBar(Graph);
		statusBar->setObjectName(QStringLiteral("statusBar"));
		Graph->setStatusBar(statusBar);

		plot = new QCustomPlot();
		Graph->setCentralWidget(plot);
		retranslateUi(Graph);

		QMetaObject::connectSlotsByName(Graph);
	} // setupUi

	void retranslateUi(QMainWindow *Graph)
	{
		Graph->setWindowTitle(QApplication::translate("Graph", "Graph", 0));
	} // retranslateUi

};

namespace Ui {
	class Graph : public Ui_Graph {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GRAPH_H