#include "includes.hpp"
#include "menu.h"
#include "window.h"
#include "spendings.h"
#include "investments.h"
#include "income.h"
#include "settings.h"

int main (int argc, char* argv[])
{
	QApplication app(argc,argv);

/*
	QFile styleFile("application.qss");
	styleFile.open( QFile::ReadOnly);
	app.setStyleSheet(QString::fromLatin1(styleFile.readAll()));
	styleFile.close();
*/
	Window *mainWindow = new Window();
	// mainWindow->setFixedSize(1080,720);
	// mainWindow->setStyleSheet("background-color: rgb(75, 75, 75)");

	SpendingWidget *firstWindow = new SpendingWidget();
	IncomeWidget *secondWindow = new IncomeWidget();
	InvestmentWidget *thirdWindow = new InvestmentWidget();
	SettingWidget *fourthWindow = new SettingWidget();

	QTabWidget *tabWidget = new QTabWidget();
	tabWidget->setTabShape(QTabWidget::Rounded);
	
	tabWidget->addTab(firstWindow->view(),"Despesas");
	tabWidget->addTab(secondWindow->view(), "Receitas");
	tabWidget->addTab(thirdWindow->view(), "Investimentos");
	tabWidget->addTab(fourthWindow->view(), "Configurações");
	
	mainWindow->addWidgetWindow(tabWidget,0,0);	

	mainWindow->show();

	return app.exec();
}
