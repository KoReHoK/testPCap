#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QTableWidget>
#include <QtSerialPort/QSerialPort>

QT_BEGIN_NAMESPACE

class Ui_MainWindowClass
{
public:
	QMenuBar *menuBar;
	QToolBar *mainToolBar;
	QWidget *centralWidget;
	QStatusBar *statusBar;
	QGridLayout *mainLayout;
	QGridLayout *miniLayout;
	QGroupBox *groupBox;
	QPushButton *openGraph;
	QPushButton *startMeas;
	QPushButton *stopMeas;
	QPushButton *writeConf;
	QPushButton *reset;
	QLabel *schemeLab;
	QLabel *portSelLab;
	QLabel *averCountLab;
	QLabel *compensLab;
	QLabel *discharLab;
	QComboBox *measureBox;
	QLineEdit *averCountEdit;
	QCheckBox *checkPort0;
	QCheckBox *checkPort1;
	QCheckBox *checkPort2;
	QCheckBox *checkPort3;
	QCheckBox *checkPort4;
	QCheckBox *checkPort5;
	QCheckBox *checkPort6;
	QCheckBox *checkPort7;
	QComboBox *compensBox;
	QComboBox *discharBox;
	QTableWidget *resultTable;
	QAction *actionConnect;
	QAction *actionDisconnect;
	QAction *actionConfigure;
	QAction *actionQuit;


	void setupUi(QMainWindow *MainWindowClass)
	{
		actionConnect = new QAction(MainWindowClass);
		actionConnect->setObjectName("actionConnect");
		QIcon icon;
		icon.addFile(QStringLiteral(":/MainWindow/images/connect.png"), QSize(), QIcon::Normal, QIcon::Off);
		actionConnect->setIcon(icon);

		actionDisconnect = new QAction(MainWindowClass);
		actionDisconnect->setObjectName("actionDisconnect");
		QIcon icon1;
		icon1.addFile(QStringLiteral(":/MainWindow/images/disconnect.png"), QSize(), QIcon::Normal, QIcon::Off);
		actionDisconnect->setIcon(icon1);

		actionConfigure = new QAction(MainWindowClass);
		actionConfigure->setObjectName("actionConfigure");
		QIcon icon2;
		icon2.addFile(QStringLiteral(":/MainWindow/images/settings.png"), QSize(), QIcon::Normal, QIcon::Off);
		actionConfigure->setIcon(icon2);

		actionQuit = new QAction(MainWindowClass);
		actionQuit->setObjectName("actionQuit");
		QIcon icon3;
		icon3.addFile(QStringLiteral(":/MainWindow/images/application-exit.png"), QSize(), QIcon::Normal, QIcon::Off);
		actionQuit->setIcon(icon3);

		if (MainWindowClass->objectName().isEmpty())
			MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
		MainWindowClass->resize(600, 400);
		menuBar = new QMenuBar(MainWindowClass);
		menuBar->setObjectName(QStringLiteral("menuBar"));
		MainWindowClass->setMenuBar(menuBar);
		mainToolBar = new QToolBar(MainWindowClass);
		mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
		mainToolBar->addAction(actionConnect);
		mainToolBar->addAction(actionDisconnect);
		mainToolBar->addAction(actionConfigure);
		mainToolBar->addAction(actionQuit);
		MainWindowClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
		centralWidget = new QWidget(MainWindowClass);
		centralWidget->setObjectName(QStringLiteral("centralWidget"));
		MainWindowClass->setCentralWidget(centralWidget);
		statusBar = new QStatusBar(MainWindowClass);
		statusBar->setObjectName(QStringLiteral("statusBar"));
		MainWindowClass->setStatusBar(statusBar);

		mainLayout = new QGridLayout(centralWidget);
		mainLayout->setContentsMargins(10, 10, 10, 10);
		mainLayout->setSpacing(6);
		groupBox = new QGroupBox("Capacitance to Digital Conversion Frontend");
		openGraph = new QPushButton("Open Graph");
		startMeas = new QPushButton("Start Measurement");
		stopMeas = new QPushButton("Stop Measurement");
		writeConf = new QPushButton("Write Config");
		reset = new QPushButton("Reset");

		openGraph->setFixedWidth(100);
		startMeas->setFixedWidth(100);
		stopMeas->setFixedWidth(100);
		writeConf->setFixedWidth(100);
		reset->setFixedWidth(100);

		mainLayout->addWidget(groupBox, 0, 0, 5, 0, Qt::AlignLeft);
		mainLayout->addWidget(openGraph, 0, 1, Qt::AlignRight);
		mainLayout->addWidget(startMeas, 1, 1, Qt::AlignRight);
		mainLayout->addWidget(stopMeas, 2, 1, Qt::AlignRight);
		mainLayout->addWidget(writeConf, 3, 1, Qt::AlignRight);
		mainLayout->addWidget(reset, 4, 1, Qt::AlignRight);

		miniLayout = new QGridLayout(groupBox);
		schemeLab = new QLabel("Measurement Scheme");
		portSelLab = new QLabel("Cap. Port Select");
		averCountLab = new QLabel("Average Count");
		compensLab = new QLabel("Stray Compensation");
		discharLab = new QLabel("Discharge Resistance");

		miniLayout->addWidget(schemeLab, 0, 0);
		miniLayout->addWidget(portSelLab, 1, 0);
		miniLayout->addWidget(averCountLab, 2, 0);
		miniLayout->addWidget(compensLab, 3, 0);
		miniLayout->addWidget(discharLab, 4, 0);

		measureBox = new QComboBox();
		measureBox->setFixedWidth(150);
		measureBox->addItem("Grounded | Single");
		measureBox->addItem("Grounded | Differential");
		measureBox->addItem("Floating | Single");
		measureBox->addItem("Floating | Differential");

		averCountEdit = new QLineEdit();
		averCountEdit->setFixedWidth(150);
		//TODO: Добавить проверку ввода данных

		compensBox = new QComboBox();
		compensBox->setFixedWidth(150);
		compensBox->addItem("None");
		compensBox->addItem("Internal");
		compensBox->addItem("Extrernal");
		compensBox->addItem("Both");

		discharBox = new QComboBox();
		discharBox->setFixedWidth(150);
		discharBox->addItem("10k");
		discharBox->addItem("30k");
		discharBox->addItem("90k");
		discharBox->addItem("180k");

		checkPort0 = new QCheckBox();
		checkPort1 = new QCheckBox();
		checkPort2 = new QCheckBox();
		checkPort3 = new QCheckBox();
		checkPort4 = new QCheckBox();
		checkPort5 = new QCheckBox();
		checkPort6 = new QCheckBox();
		checkPort7 = new QCheckBox();

		miniLayout->addWidget(checkPort0, 1, 1, Qt::AlignRight);
		miniLayout->addWidget(checkPort1, 1, 2, Qt::AlignRight);
		miniLayout->addWidget(checkPort2, 1, 3, Qt::AlignRight);
		miniLayout->addWidget(checkPort3, 1, 4, Qt::AlignRight);
		miniLayout->addWidget(checkPort4, 1, 5, Qt::AlignRight);
		miniLayout->addWidget(checkPort5, 1, 6, Qt::AlignRight);
		miniLayout->addWidget(checkPort6, 1, 7, Qt::AlignRight);
		miniLayout->addWidget(checkPort7, 1, 8, Qt::AlignRight);

		miniLayout->addWidget(measureBox,	 0, 1, 1, 8, Qt::AlignRight);
		miniLayout->addWidget(averCountEdit, 2, 1, 1, 8, Qt::AlignRight);
		miniLayout->addWidget(compensBox,	 3, 1, 1, 8, Qt::AlignRight);
		miniLayout->addWidget(discharBox,	 4, 1, 1, 8, Qt::AlignRight);

		resultTable = new QTableWidget(8, 3);
		resultTable->setHorizontalHeaderItem(0, new QTableWidgetItem("Name"));
		resultTable->setHorizontalHeaderItem(1, new QTableWidgetItem("Digital, hex"));
		resultTable->setHorizontalHeaderItem(2, new QTableWidgetItem("Results, pF"));
		resultTable->setItem(0, 0, new QTableWidgetItem("C0/Cref"));
		resultTable->setItem(1, 0, new QTableWidgetItem("C1/Cref"));
		resultTable->setItem(2, 0, new QTableWidgetItem("C2/Cref"));
		resultTable->setItem(3, 0, new QTableWidgetItem("C3/Cref"));
		resultTable->setItem(4, 0, new QTableWidgetItem("C4/Cref"));
		resultTable->setItem(5, 0, new QTableWidgetItem("C5/Cref"));
		resultTable->setItem(6, 0, new QTableWidgetItem("C6/Cref"));
		resultTable->setItem(7, 0, new QTableWidgetItem("C7/Cref"));
		resultTable->setColumnWidth(0, 105);
		resultTable->setColumnWidth(1, 130);
		resultTable->setColumnWidth(2, 130);
		resultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
		mainLayout->addWidget(resultTable, 5, 0, 5, 2);
		//TODO: Добавить скрытие определенных кнопок

		retranslateUi(MainWindowClass);
		QMetaObject::connectSlotsByName(MainWindowClass);
	} // setupUi

	void retranslateUi(QMainWindow *MainWindowClass)
	{
		MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", 0));
		actionConnect->setText(QApplication::translate("MainWindow", "C&onnect", 0));
#ifndef QT_NO_TOOLTIP
		actionConnect->setToolTip(QApplication::translate("MainWindow", "Connect to serial port", 0));
#endif // QT_NO_TOOLTIP
		actionConnect->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0));
		actionDisconnect->setText(QApplication::translate("MainWindow", "&Disconnect", 0));
#ifndef QT_NO_TOOLTIP
		actionDisconnect->setToolTip(QApplication::translate("MainWindow", "Disconnect from serial port", 0));
#endif // QT_NO_TOOLTIP
		actionDisconnect->setShortcut(QApplication::translate("MainWindow", "Ctrl+D", 0));
		actionConfigure->setText(QApplication::translate("MainWindow", "&Configure", 0));
#ifndef QT_NO_TOOLTIP
		actionConfigure->setToolTip(QApplication::translate("MainWindow", "Configure serial port", 0));
#endif // QT_NO_TOOLTIP
		actionConfigure->setShortcut(QApplication::translate("MainWindow", "Alt+C", 0));
		actionQuit->setText(QApplication::translate("MainWindow", "&Quit", 0));
		actionQuit->setShortcut(QApplication::translate("MainWindow", "Ctrl+Q", 0));
	} // retranslateUi

};

namespace Ui {
	class MainWindow : public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H