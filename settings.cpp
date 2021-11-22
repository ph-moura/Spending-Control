#include "includes.hpp"
#include "insert_data.h"
#include "settings.h"
#include "show_data.h"
#include "window.h"

SettingWidget::SettingWidget(){

	settingWindow = new Window();	
	// settingWindow->setStyleSheet("background-color:rgb(75,75,75)");

	secondaryWindow = new Window();	
	secondaryWindow->setStyleSheet("background-color:rgb(75,75,75)");

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

	addSetting = new QPushButton("&Add");
	addSetting->setStyleSheet("background-color:gray");
	addSetting->setFixedSize(75,30);

	settingWindow->addWidgetWindow(addSetting,0,0);
	settingWindow->addWidgetWindow(clearButton,0,1);
	settingWindow->addWidgetWindow(quitButton,0,2);
	settingWindow->addWidgetWindow(secondaryWindow,1,0,1,5);

	QObject::connect(addSetting, &QPushButton::clicked, this, &SettingWidget::settingSlot);
	QObject::connect(clearButton, &QPushButton::clicked, secondaryWindow, &Window::clearSlot);
	QObject::connect(quitButton, &QPushButton::clicked, QCoreApplication::quit);
}

void SettingWidget::settingSlot() { 
	InsertData *insCategory = new InsertData(this);	
	insCategory->setStyleSheet("background-color: rgb(250,250,250); border-color: rgb(100,100,100);\
									 border color: black; selection-background-color: rgb(50,50,50); selection-color:white");
	insCategory->insertCategory();
	secondaryWindow->addWidgetWindow(insCategory, 1,1);
}
