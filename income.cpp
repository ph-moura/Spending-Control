#include "includes.hpp"
#include "income.h"
#include "insert_data.h"
#include "show_data.h"
#include "window.h"

IncomeWidget::IncomeWidget(){

	incomeWindow = new Window();	
	// incomeWindow->setStyleSheet("background-color:rgb(50,50,150)");

	secondaryWindow = new Window();	
	secondaryWindow->setStyleSheet("background-color:rgb(75,75,150)");

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

	addIncome = new QPushButton("&Add");
	addIncome->setStyleSheet("background-color:gray");
	addIncome->setFixedSize(75,30);

	incomeReport = new QPushButton("&Plot");
	incomeReport->setStyleSheet("background-color:gray");
	incomeReport->setFixedSize(75,30);

	incomeWindow->addWidgetWindow(addIncome,0,0);
	incomeWindow->addWidgetWindow(incomeReport,0,1);
	incomeWindow->addWidgetWindow(clearButton,0,2);
	incomeWindow->addWidgetWindow(quitButton,0,3);
	incomeWindow->addWidgetWindow(secondaryWindow,1,0,1,5);

	QObject::connect(addIncome, &QPushButton::clicked, this, &IncomeWidget::incomeSlot);
	QObject::connect(incomeReport, &QPushButton::clicked, this, &IncomeWidget::incomeReportSlot);
	QObject::connect(clearButton, &QPushButton::clicked, secondaryWindow, &Window::clearSlot);
	QObject::connect(quitButton, &QPushButton::clicked, QCoreApplication::quit);
}

void IncomeWidget::incomeReportSlot() { 
	ShowData *plot = new ShowData();
	plot->setPlotTitle("Relatório de Receitas");
	plot->setDataFileName("receitas.csv");
	secondaryWindow->addWidgetWindow(plot->plot(), 0,0);
}

void IncomeWidget::incomeSlot() {
	InsertData *receitas = new InsertData(this);	
	receitas->setCategoryFileName("receitas.txt");
	receitas->setDataFileName("receitas.csv");
	receitas->setStyleSheet("background-color:rgb(175,175,250); border-color:blue; selection-background-color:darkblue; selection-color:white");
	receitas->dataInput();
	secondaryWindow->addWidgetWindow(receitas, 1,0);
}

