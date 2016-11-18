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

private:
	QByteArray scheme;
	QByteArray portSel;
	QByteArray averCount;
	QByteArray compensat;
	QByteArray dischRes;

	QByteArray cmd;

private:
	void initConnections();
	void showStatusMessage(const QString &message);
	void showResult(const int &numb, const QString &msg);
	void makeCommand();
	void beginCommand();

private slots:
	void openGraphic();
	void startMeas();
	void stopMeas();
	void writeConfig();
	void reset();
	void openSerialPort();
	void closeSerialPort();
	void writeData(const QByteArray &data);
	void readData();

	void handleError(QSerialPort::SerialPortError error);

private slots:
	void setCapPort0();
	void setCapPort1();
	void setCapPort2();
	void setCapPort3();
	void setCapPort4();
	void setCapPort5();
	void setCapPort6();
	void setCapPort7();
	void setScheme();
	void setAverCount();
	void setCompensat();
	void setDischRes();

private:
	QByteArray getScheme();
	QByteArray getPortSel();
	QByteArray getAverCount();
	QByteArray getCompensat();
	QByteArray getDischRes();
};
