#include "includes.hpp"
#include "insert_data.h"
#include "show_data.h"
#include "spendings.h"
#include "window.h"

SpendingWidget::SpendingWidget(){

	spendingWindow = new Window();	
	// spendingWindow->setStyleSheet("background-color:rgb(175,75,75)");

	secondaryWindow = new Window();	
	secondaryWindow->setStyleSheet("background-color:rgb(175,75,75)");

	quitButton = new QPushButton("&Quit");
	QIcon quitIcon("images/exit.png");
	quitButton->setObjectName("quitButton");
	quitButton->setIcon(quitIcon);
	quitButton->setStyleSheet("background-color:gray");
	quitButton->setFixedSize(75,30);
	
	clearButton = new QPushButton("&Clear");
	QIcon clearIcon("images/clear.png");
	clearButton->setStyleSheet("background-color:gray");
	clearButton->setIcon(clearIcon);
	clearButton->setFixedSize(75,30);

	addSpending = new QPushButton("&Add");
	addSpending->setStyleSheet("background-color:gray");
	addSpending->setFixedSize(75,30);

	spendingReport = new QPushButton("&Plot");
	spendingReport->setStyleSheet("background-color:gray");
	spendingReport->setFixedSize(75,30);

	spendingWindow->addWidgetWindow(addSpending,0,0);
	spendingWindow->addWidgetWindow(spendingReport,0,1);
	spendingWindow->addWidgetWindow(clearButton,0,2);
	spendingWindow->addWidgetWindow(quitButton,0,3);
	spendingWindow->addWidgetWindow(secondaryWindow,1,0,1,5);

	QObject::connect(addSpending, &QPushButton::clicked, this, &SpendingWidget::spendingSlot);
	QObject::connect(spendingReport, &QPushButton::clicked, this, &SpendingWidget::spendingReportSlot);
	QObject::connect(clearButton, &QPushButton::clicked, secondaryWindow, &Window::clearSlot);
	QObject::connect(quitButton, &QPushButton::clicked, QCoreApplication::quit);
}

void SpendingWidget::spendingReportSlot() { 
	ShowData *plot = new ShowData();
	plot->setPlotTitle("Relatório de Despesas");
	plot->setDataFileName("despesas.csv");
	secondaryWindow->addWidgetWindow(plot->plot(), 0,0);
}

void SpendingWidget::spendingSlot(){ 
	InsertData *despesas = new InsertData(this);	
	despesas->setCategoryFileName("despesas.txt");
	despesas->setDataFileName("despesas.csv");
	despesas->setStyleSheet("background-color:rgb(250,175,175); border-color:red; selection-background-color:darkred; selection-color:white");
	despesas->dataInput();
	secondaryWindow->addWidgetWindow(despesas, 1,0);
}

