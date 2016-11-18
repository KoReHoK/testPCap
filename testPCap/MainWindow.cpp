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
	if (serial->canReadLine()) {
		//TODO: проверить передачу и прием данных
		//QByteArray temp = serial->readLine();
		data.append(serial->readLine());
		QRegExp rx("[:]");
		QStringList list = data.split(rx, QString::SkipEmptyParts);
		showResult(list.at(0).toInt(), list.at(1));
		graph->addPoint(list.at(1).toUInt());
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

	connect(ui.checkPort0, SIGNAL(clicked()),
		this, SLOT(setCapPort0()));

	connect(ui.checkPort1, SIGNAL(clicked()),
		this, SLOT(setCapPort1()));

	connect(ui.checkPort2, SIGNAL(clicked()),
		this, SLOT(setCapPort2()));

	connect(ui.checkPort3, SIGNAL(clicked()),
		this, SLOT(setCapPort3()));

	connect(ui.checkPort4, SIGNAL(clicked()),
		this, SLOT(setCapPort4()));

	connect(ui.checkPort5, SIGNAL(clicked()),
		this, SLOT(setCapPort5()));

	connect(ui.checkPort6, SIGNAL(clicked()),
		this, SLOT(setCapPort6()));

	connect(ui.checkPort7, SIGNAL(clicked()),
		this, SLOT(setCapPort7()));
}

void MainWindow::beginCommand() {
	scheme = "0";
	portSel = "0";
	averCount = "1";
	compensat = "0";
	dischRes = "0";
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
	scheme = "";
	scheme.append(QString::number(ui.measureBox->currentIndex()));
}

void MainWindow::setCapPort0(){
	int temp = portSel.toInt();

	if(ui.checkPort0->isChecked()) temp |= 0x1;
	else temp &= 0xFE;

	portSel = "";
	portSel.append(QString::number(temp));
}

void MainWindow::setCapPort1() {
	int temp = portSel.toInt();

	if (ui.checkPort0->isChecked()) temp |= 0x2;
	else temp &= 0xFD;

	portSel = "";
	portSel.append(QString::number(temp));
}

void MainWindow::setCapPort2() {
	int temp = portSel.toInt();

	if (ui.checkPort0->isChecked()) temp |= 0x4;
	else temp &= 0xFB;

	portSel = "";
	portSel.append(QString::number(temp));
}

void MainWindow::setCapPort3() {
	int temp = portSel.toInt();

	if (ui.checkPort0->isChecked()) temp |= 0x8;
	else temp &= 0xF7;

	portSel = "";
	portSel.append(QString::number(temp));
}

void MainWindow::setCapPort4() {
	int temp = portSel.toInt();

	if (ui.checkPort0->isChecked()) temp |= 0x10;
	else temp &= 0xEF;

	portSel = "";
	portSel.append(QString::number(temp));
}

void MainWindow::setCapPort5() {
	int temp = portSel.toInt();

	if (ui.checkPort0->isChecked()) temp |= 0x20;
	else temp &= 0xDF;

	portSel = "";
	portSel.append(QString::number(temp));
}

void MainWindow::setCapPort6() {
	int temp = portSel.toInt();

	if (ui.checkPort0->isChecked()) temp |= 0x40;
	else temp &= 0xBF;

	portSel = "";
	portSel.append(QString::number(temp));
}

void MainWindow::setCapPort7() {
	int temp = portSel.toInt();

	if (ui.checkPort0->isChecked()) temp |= 0x80;
	else temp &= 0x7F;

	portSel = "";
	portSel.append(QString::number(temp));
}

void MainWindow::setAverCount() {
	averCount = "";
	averCount.append(ui.averCountEdit->text());
}

void MainWindow::setCompensat() {
	compensat = "";
	compensat.append(QString::number(ui.compensBox->currentIndex()));
}

void MainWindow::setDischRes() {
	dischRes = "";
	dischRes.append(QString::number(ui.discharBox->currentIndex()));
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