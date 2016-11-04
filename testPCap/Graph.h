#pragma once

#include <QMainWindow>
#include "qcustomplot.h"
#include "ui_Graph.h"

class Graph : public QMainWindow
{
	Q_OBJECT

public:
	Graph(QWidget *parent = Q_NULLPTR);
	~Graph();

private:
	Ui::Graph ui;
	QCustomPlot *customPlot;    // ��������� ����������� �������
	QCPGraph *graphic;          // ��������� ������

private slots:
	void slotRangeChanged(const QCPRange &newRange);
};
