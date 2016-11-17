#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "settingsdialog.h"
#include "Graph.h"

#include <QtSerialPort/QSerialPort>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QLabel>
#include <QDebug>
#include <QRegExp>

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

	dataResult = new QTableWidgetItem();

	initConnections();

	beginCommand();
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
	QString data;
	//data.truncate();
	if (serial->canReadLine()) {
		//data = serial->readLine();
		data.append(serial->readLine());
		QRegExp rx("[:]");
		QStringList list = data.split(rx, QString::SkipEmptyParts);
		showResult(list.at(0).toInt(), list.at(1));
		graph->addPoint(list.at(1).toUInt());
		//uint32_t testVal = list.at(1).toUInt();
		//graph->addPoint(testVal);
	}
}

void MainWindow::handleError(QSerialPort::SerialPortError error)
{
	if (error == QSerialPort::ResourceError) {
		QMessageBox::critical(this, tr("Critical Error"), serial->errorString());
		closeSerialPort();
	}
}

void MainWindow::initConnections()
{
	connect(ui.actionConnect, &QAction::triggered, this, &MainWindow::openSerialPort);
	connect(ui.actionDisconnect, &QAction::triggered, this, &MainWindow::closeSerialPort);
	connect(ui.actionQuit, &QAction::triggered, this, &MainWindow::close);
	connect(ui.actionConfigure, &QAction::triggered, settings, &MainWindow::show);

	connect(serial, static_cast<void (QSerialPort::*)(QSerialPort::SerialPortError)>(&QSerialPort::error),
		this, &MainWindow::handleError);

	connect(serial, &QSerialPort::readyRead, this, &MainWindow::readData);

	connect(ui.openGraph, SIGNAL(clicked()), this, SLOT(openGraphic()));

	connect(ui.startMeas, SIGNAL(clicked()), this, SLOT(startMeas()));

	connect(ui.stopMeas, SIGNAL(clicked()), this, SLOT(stopMeas()));

	connect(ui.writeConf, SIGNAL(clicked()), this, SLOT(writeConfig()));

	connect(ui.reset, SIGNAL(clicked()), this, SLOT(reset()));

	connect(ui.measureBox, SIGNAL(currentIndexChanged(int)),
		this, SLOT(setScheme()));

	connect(ui.averCountEdit, SIGNAL(textChanged(QString)),
		this, SLOT(setAverCount()));

	connect(ui.compensBox, SIGNAL(currentIndexChanged(int)),
		this, SLOT(setCompensat()));

	connect(ui.discharBox, SIGNAL(currentIndexChanged(int)),
		this, SLOT(setDischRes()));
}

void MainWindow::beginCommand() {
	scheme = "2";
	portSel = "255";
	averCount = "50";
	compensat = "3";
	dischRes = "2";
}

void MainWindow::showStatusMessage(const QString &message)
{
	status->setText(message);
}

void MainWindow::showResult(const int &numb, const QString &msg) {
	dataResult->setText(msg);
	ui.resultTable->setItem(numb, 1, dataResult);
}

void MainWindow::openGraphic() {
	graph->show();
}

void MainWindow::startMeas() {
	writeData("4:");
}

void MainWindow::stopMeas() {
	writeData("5:");
}

void MainWindow::writeConfig() {
	makeCommand();
	writeData(cmd);
}

void MainWindow::reset() {
	emit ui.stopMeas->clicked();
	emit ui.startMeas->clicked();
}

void MainWindow::setScheme() {
	switch (ui.measureBox->currentIndex()) {
		case 0: scheme = "0"; break;
		case 1: scheme = "1"; break;
		case 2: scheme = "2"; break;
		case 3: scheme = "3"; break;
	}
}

void MainWindow::setPortSel(){
	portSel = "";
	//TODO: Добавить обработку выбора порта
	portSel.append("255");
}

void MainWindow::setAverCount() {
	averCount = "";
	averCount.append(ui.averCountEdit->text());
}

void MainWindow::setCompensat() {
	switch (ui.compensBox->currentIndex()) {
		case 0: compensat = "0"; break;
		case 1: compensat = "1"; break;
		case 2: compensat = "2"; break;
		case 3: compensat = "3"; break;
	}
}

void MainWindow::setDischRes() {
	switch (ui.discharBox->currentIndex()) {
		case 0: dischRes = "0"; break;
		case 1: dischRes = "1"; break;
		case 2: dischRes = "2"; break;
		case 3: dischRes = "3"; break;
	}
}

QByteArray MainWindow::getScheme() {
	return scheme;
}

QByteArray MainWindow::getPortSel() {
	return portSel;
}

QByteArray MainWindow::getAverCount() {
	return averCount;
}

QByteArray MainWindow::getCompensat() {
	return compensat;
}

QByteArray MainWindow::getDischRes() {
	return dischRes;
}

void MainWindow::makeCommand() {
	cmd = "";
	cmd += getScheme() + ':';
	cmd += getPortSel() + ':';
	cmd += getAverCount() + ':';
	cmd += getCompensat() + ':';
	cmd += getDischRes();
}