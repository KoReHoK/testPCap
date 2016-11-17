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
	x.push_back(0);
	y.push_back(0);
	ui.plot->axisRect()->setupFullAxesBox(true);
	ui.plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom);

	ui.plot->xAxis->setRange(0, 100, Qt::AlignLeft);
	ui.plot->yAxis->setRange(0, 100, Qt::AlignLeft);
}

Graph::~Graph()
{
}

void Graph::addPoint(const uint32_t _y){
	// TODO: ƒобавить обработку при переполнении count
	y.push_back(_y);
	x.push_back(++count);
	ui.plot->graph(0)->setData(x, y);
	ui.plot->replot();
}
