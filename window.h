#ifndef WINDOW_H
#define WINDOW_H

#include "includes.hpp"

class Window: public QWidget 
{
	public:
		Window(QWidget *parent=0);
		void addWidgetWindow(QWidget *widget, int x, int y, int dx=0, int dy=0);

	private:	
		QGridLayout *grid;	 

	public slots:
		void clearSlot();

};

#endif
