#include "Graph.h"

Graph::Graph(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	customPlot = new QCustomPlot(); // �������������� ����������� �������
	ui.gridLayout->addWidget(customPlot, 0, 0, 1, 1);  // ������������� customPlot � ���� ����������

	customPlot->setInteraction(QCP::iRangeZoom, true);   // �������� �������������� ��������/�����������
	customPlot->setInteraction(QCP::iRangeDrag, true);  // �������� �������������� �������������� �������
	customPlot->axisRect()->setRangeDrag(Qt::Horizontal);   // �������� �������������� ������ �� �������������� ���
	customPlot->axisRect()->setRangeZoom(Qt::Horizontal);   // �������� ��������/����������� ������ �� �������������� ���
	customPlot->xAxis->setTickLabelType(QCPAxis::ltDateTime);   // ������� ��������� �� ��� X � �������� ���� � �������
	customPlot->xAxis->setDateTimeFormat("hh:mm");  // ������������� ������ ���� � �������

													// ����������� ����� �� ���� ���������
	customPlot->xAxis->setTickLabelFont(QFont(QFont().family(), 8));
	customPlot->yAxis->setTickLabelFont(QFont(QFont().family(), 8));

	// �������������� ��������������� ����� �� ��� X
	customPlot->xAxis->setAutoTickStep(true);

	/* ������ �������� ��� X � Y �� ������� � ������ �������� �������,
	* �� ��������� �� ��� ���� � ������� ���������
	* */
	customPlot->xAxis2->setVisible(true);
	customPlot->yAxis2->setVisible(true);
	customPlot->xAxis2->setTicks(false);
	customPlot->yAxis2->setTicks(false);
	customPlot->xAxis2->setTickLabels(false);
	customPlot->yAxis2->setTickLabels(false);

	customPlot->yAxis->setTickLabelColor(QColor(Qt::red)); // ������� ���� �������� ����� �� ��� Y
	customPlot->legend->setVisible(true);   //�������� ������� �������
											// ������������� ������� � ����� ������� ���� �������
	customPlot->axisRect()->insetLayout()->setInsetAlignment(0, Qt::AlignLeft | Qt::AlignTop);

	// �������������� ������ � ����������� ��� � ����
	graphic = new QCPGraph(customPlot->xAxis, customPlot->yAxis);
	customPlot->addPlottable(graphic);  // ������������� ������ �� �������
	graphic->setName("�����, �");       // �������������
	graphic->setPen(QPen(QColor(Qt::red))); // ������������� ���� �������
	graphic->setAntialiased(false);         // ��������� �����������, �� ��������� ��������
	graphic->setLineStyle(QCPGraph::lsImpulse); // ������ � ���� ���������� �����

												/* ���������� ������ �� ��� X �� ��������� �������� ��������� ���������
												* � ����� ��� ������������� ������� ������� ���.
												* */
	connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)),
		this, SLOT(slotRangeChanged(QCPRange)));

	// ����� ������� ������ � ������������ ��� � ������� ������� � �������
	double now = QDateTime::currentDateTime().toTime_t();
	// ��������� ������� ������� � �������
	QVector <double> time(400), income(400);

	srand(15); // �������������� ��������� ��������������� �����

			   // ��������� ������ ����������
	for (int i = 0; i<400; ++i)
	{
		time[i] = now + 3600 * i;
		income[i] = qFabs(income[i - 1]) + (i / 50.0 + 1)*(rand() / (double)RAND_MAX - 0.5);
	}

	graphic->setData(time, income); // ������������� ������
	customPlot->rescaleAxes();      // ������������ ������ �� ������
	customPlot->replot();           // ������������ ������
}

Graph::~Graph()
{
}
