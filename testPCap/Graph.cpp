#include "Graph.h"

Graph::Graph(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	
	ui.plot->addGraph();
	ui.plot->graph()->setPen(QPen(Qt::blue));
	ui.plot->graph()->setBrush(QBrush(QColor(0, 0, 255, 20)));
	ui.plot->addGraph();
	ui.plot->graph()->setPen(QPen(Qt::red));
	QVector<double> x(500), y0(500), y1(500);
	for (int i = 0; i<500; ++i)
	{
		x[i] = (i / 499.0 - 0.5) * 10;
		y0[i] = qExp(-x[i] * x[i] * 0.25)*qSin(x[i] * 5) * 5;
		y1[i] = qExp(-x[i] * x[i] * 0.25) * 5;
	}
	ui.plot->graph(0)->setData(x, y0);
	ui.plot->graph(1)->setData(x, y1);
	ui.plot->axisRect()->setupFullAxesBox(true);
	ui.plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

	ui.plot->xAxis->setRange(0, 6, Qt::AlignCenter);
	ui.plot->yAxis->setRange(0, 10, Qt::AlignCenter);
}

Graph::~Graph()
{
}
