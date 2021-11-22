#include "includes.hpp"
#include "window.h"
#include "insert_data.h"
#include "show_data.h"

Window::Window(QWidget *parent): QWidget(parent=0)//
{
	grid = new QGridLayout(this);	 
	grid->setOriginCorner(Qt::TopLeftCorner);
	setLayout(grid);
}

void Window::addWidgetWindow(QWidget *widget, int x, int y, int dx, int dy){
	if (dx != 0 && dy != 0){
		grid->addWidget(widget,x,y,dx,dy);
	}else{
		grid->addWidget(widget,x,y);
	}
}

void Window::clearSlot() {
	if ( this->layout() != nullptr )
	{
		QLayoutItem* item;
		while ( ( item = this->layout()->takeAt( 0 ) ) != nullptr )
		{
			delete item->widget();
			delete item;
		}
	}
}
