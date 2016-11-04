#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"

class Graph;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);

private:
    Ui::MainWindowClass ui;
	Graph *graph;

private slots:
	void openGraphic();
};
