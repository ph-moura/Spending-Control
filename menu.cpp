#include "includes.hpp"
#include "menu.h"

MyMenu::MyMenu (QWidget *window) : QMenuBar(window)
{

	QPixmap newPix("new.png");
	QPixmap openPix("open.png");
	QPixmap quitPix("images/exit.png");

	newAction  = new QAction(newPix, "&New", this);
	openAction = new QAction(openPix, "&Open", this);
	quitAction = new QAction(quitPix, "&Quit", this);
	saveAction = new QAction("&Save", this);

	fileMenu  = new QMenu("&File");
	toolsMenu = new QMenu("&Tools");

	fileMenu->addAction(newAction);
	fileMenu->addAction(openAction);
	fileMenu->addAction(saveAction);
	fileMenu->addSeparator();
	fileMenu->addAction(quitAction);

	this->addMenu(fileMenu);
	this->addMenu(toolsMenu);
	this->setGeometry(10,5,620,20);
	
	// qApp->setAttribute(Qt::AA_DontShowIconsInMenus, false);

	QObject::connect(newAction,  &QAction::triggered, this, &MyMenu::newMenuSlot);
	QObject::connect(openAction, &QAction::triggered, this, &MyMenu::openMenuSlot);
	QObject::connect(quitAction, &QAction::triggered, this, &QApplication::quit);
	QObject::connect(saveAction, &QAction::triggered, this, &MyMenu::saveMenuSlot);

};

void MyMenu::newMenuSlot(){ std::cout << "New menu slot." << std::endl; }

void MyMenu::openMenuSlot(){ std::cout << "Open menu slot." << std::endl; }

void MyMenu::saveMenuSlot(){ std::cout << "Save menu slot." << std::endl; }
