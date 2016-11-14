#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_MainWindow.h"
#include <QtSerialPort/QSerialPort>
#include <QtWidgets/QLabel>

class Graph;
class SettingsDialog;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = Q_NULLPTR);
	~MainWindow();

private:
    Ui::MainWindow ui;
	Graph *graph;
	SettingsDialog *settings;
	QSerialPort *serial;
	QLabel *status;
	QTableWidgetItem *dataResult;
	int line = 0;

private:
	void initActionsConnections();
	void showStatusMessage(const QString &message);
	void showResult(const int numb, const QString &msg);

private slots:
	void openGraphic();
	void openSerialPort();
	void closeSerialPort();
	void writeData(const QByteArray &data);
	void readData();

	void handleError(QSerialPort::SerialPortError error);
};
