#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "settingsdialog.h"
#include "Graph.h"

#include <QtSerialPort/QSerialPort>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QLabel>

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	graph = new Graph();
	settings = new SettingsDialog();
	serial = new QSerialPort(this);

	ui.actionConnect->setEnabled(true);
	ui.actionDisconnect->setEnabled(false);
	ui.actionQuit->setEnabled(true);
	ui.actionConfigure->setEnabled(true);

	status = new QLabel;
	ui.statusBar->addWidget(status);

	initActionsConnections();

	connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
		this, &MainWindow::handleError);

	connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);

	connect(ui.openGraph, SIGNAL(clicked()), this, SLOT(openGraphic()));
}

MainWindow::~MainWindow() {
	delete settings;
	delete graph;
}

void MainWindow::openSerialPort()
{
	SettingsDialog::Settings p = settings->settings();
	serial->setPortName(p.name);
	serial->setBaudRate(p.baudRate);
	serial->setDataBits(p.dataBits);
	serial->setParity(p.parity);
	serial->setStopBits(p.stopBits);
	serial->setFlowControl(p.flowControl);
	if (serial->open(QIODevice::ReadWrite)) {
		ui.actionConnect->setEnabled(false);
		ui.actionDisconnect->setEnabled(true);
		ui.actionConfigure->setEnabled(false);
		showStatusMessage(tr("Connected to %1 : %2, %3, %4, %5, %6")
			.arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
			.arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl));
	}
	else {
		QMessageBox::critical(this, tr("Error"), serial->errorString());

		showStatusMessage(tr("Open error"));
	}
}

void MainWindow::closeSerialPort()
{
	if (serial->isOpen())
		serial->close();
	ui.actionConnect->setEnabled(true);
	ui.actionDisconnect->setEnabled(false);
	ui.actionConfigure->setEnabled(true);
	showStatusMessage(tr("Disconnected"));
}

void MainWindow::writeData(const QByteArray &data)
{
	serial->write(data);
}

void MainWindow::readData()
{
	QByteArray data = serial->readAll();
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
	if (error == QSerialPort::ResourceError) {
		QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
		closeSerialPort();
	}
}

void MainWindow::initActionsConnections()
{
	connect(ui.actionConnect, &QAction::triggered, this, &MainWindow::openSerialPort);
	connect(ui.actionDisconnect, &QAction::triggered, this, &MainWindow::closeSerialPort);
	connect(ui.actionQuit, &QAction::triggered, this, &MainWindow::close);
	connect(ui.actionConfigure, &QAction::triggered, settings, &MainWindow::show);
}

void MainWindow::showStatusMessage(const QString &message)
{
	status->setText(message);
}

void MainWindow::openGraphic() {
	graph->show();
}
