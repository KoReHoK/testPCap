/********************************************************************************
** Form generated from reading UI file 'MainWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

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
#include <QtWidgets/QTableWidget>

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
	QLabel *portErrLab;
	QLabel *compensLab;
	QLabel *discharLab;
	QComboBox *measureBox;
	QComboBox *compensBox;
	QComboBox *discharBox;
	QTableWidget *resultTable;


    void setupUi(QMainWindow *MainWindowClass)
    {
        if (MainWindowClass->objectName().isEmpty())
            MainWindowClass->setObjectName(QStringLiteral("MainWindowClass"));
        MainWindowClass->resize(600, 400);
        menuBar = new QMenuBar(MainWindowClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        MainWindowClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindowClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindowClass->addToolBar(mainToolBar);
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

		mainLayout->addWidget(groupBox,  0, 0, 5, 0, Qt::AlignLeft);
		mainLayout->addWidget(openGraph, 0, 1, Qt::AlignRight);
		mainLayout->addWidget(startMeas, 1, 1, Qt::AlignRight);
		mainLayout->addWidget(stopMeas,  2, 1, Qt::AlignRight);
		mainLayout->addWidget(writeConf, 3, 1, Qt::AlignRight);
		mainLayout->addWidget(reset,	 4, 1, Qt::AlignRight);

		miniLayout = new QGridLayout(groupBox);
		schemeLab = new QLabel("Measurement Scheme");
		portSelLab = new QLabel("Cap. Port Select");
		portErrLab = new QLabel("Cap. Port Error");
		compensLab = new QLabel("Stray Compensation");
		discharLab = new QLabel("Discharge Resistance");

		miniLayout->addWidget(schemeLab, 0, 0);
		miniLayout->addWidget(portSelLab, 1, 0);
		miniLayout->addWidget(portErrLab, 2, 0);
		miniLayout->addWidget(compensLab, 3, 0);
		miniLayout->addWidget(discharLab, 4, 0);

		measureBox = new QComboBox();
		measureBox->addItem("Grounded | Single");
		measureBox->addItem("Grounded | Differential");
		measureBox->addItem("Floating | Single");
		measureBox->addItem("Floating | Differential");

		compensBox = new QComboBox();
		compensBox->addItem("None");
		compensBox->addItem("Internal");
		compensBox->addItem("Extrernal");
		compensBox->addItem("Both");

		discharBox = new QComboBox();
		discharBox->addItem("10k");
		discharBox->addItem("30k");
		discharBox->addItem("90k");
		discharBox->addItem("180k");

		miniLayout->addWidget(measureBox, 0, 1, Qt::AlignRight);
		miniLayout->addWidget(compensBox, 3, 1, Qt::AlignRight);
		miniLayout->addWidget(discharBox, 4, 1, Qt::AlignRight);

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
		resultTable->setColumnWidth(1, 125);
		resultTable->setColumnWidth(2, 125);
		resultTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
		mainLayout->addWidget(resultTable, 5, 0, 5, 2);

        retranslateUi(MainWindowClass);
        QMetaObject::connectSlotsByName(MainWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindowClass)
    {
        MainWindowClass->setWindowTitle(QApplication::translate("MainWindowClass", "MainWindow", 0));
    } // retranslateUi

};

namespace Ui {
    class MainWindowClass: public Ui_MainWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
