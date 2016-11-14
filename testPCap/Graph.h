#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Graph.h"

class Graph : public QMainWindow
{
	Q_OBJECT

public:
	Graph(QWidget *parent = Q_NULLPTR);
	~Graph();

	void addPoint(const int);

private:
	Ui::Graph ui;

	QVector<double> x, y;
	long long int count = 0;
};
