#include "includes.hpp"
#include "insert_data.h"
#include "show_data.h"
#include "investments.h"
#include "window.h"

InvestmentWidget::InvestmentWidget(){

	investmentWindow = new Window();	
	// investmentWindow->setStyleSheet("background-color:rgb(75,175,75)");

	secondaryWindow = new Window();	
	secondaryWindow->setStyleSheet("background-color: rgb(75, 175, 75)");

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

	addInvestment = new QPushButton("&Add");
	addInvestment->setStyleSheet("background-color:gray");
	addInvestment->setFixedSize(75,30);

	investmentReport = new QPushButton("&Plot");
	investmentReport->setStyleSheet("background-color:gray");
	investmentReport->setFixedSize(75,30);

	investmentWindow->addWidgetWindow(addInvestment,0,0);
	investmentWindow->addWidgetWindow(investmentReport,0,1);
	investmentWindow->addWidgetWindow(clearButton,0,2);
	investmentWindow->addWidgetWindow(quitButton,0,3);
	investmentWindow->addWidgetWindow(secondaryWindow,1,0,1,5);

	QObject::connect(addInvestment, &QPushButton::clicked, this, &InvestmentWidget::investmentSlot);
	QObject::connect(investmentReport, &QPushButton::clicked, this, &InvestmentWidget::investmentReportSlot);
	QObject::connect(clearButton, &QPushButton::clicked, secondaryWindow, &Window::clearSlot);
	QObject::connect(quitButton, &QPushButton::clicked, QCoreApplication::quit);
}

void InvestmentWidget::investmentSlot() {
	InsertData *investimentos = new InsertData(this);	
	investimentos->setCategoryFileName("investimentos.txt");
	investimentos->setDataFileName("investimentos.csv");
	investimentos->setObjectName("investimentos");
	investimentos->setStyleSheet("background-color:rgb(175,250,175); border-color:green; selection-background-color:darkgreen; selection-color:white");
	investimentos->dataInput();
	secondaryWindow->addWidgetWindow(investimentos, 1,0);
}

void InvestmentWidget::investmentReportSlot() { 
	ShowData *plot = new ShowData();
	plot->setPlotTitle("Relatório de Investimentos");
	plot->setDataFileName("investimentos.csv");
	secondaryWindow->addWidgetWindow(plot->plot(), 0,0);
}
