#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_Graph.h"

class Graph : public QMainWindow
{
	Q_OBJECT

public:
	Graph(QWidget *parent = Q_NULLPTR);
	~Graph();

private:
	Ui::Graph ui;
};
