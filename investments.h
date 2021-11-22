#ifndef INVESTMENTS_H
#define INVESTMENTS_H

#include "includes.hpp"
#include "window.h"

class InvestmentWidget : public QWidget
{
	// Q_OBJECT

	public:
		InvestmentWidget();

		Window * view() { return investmentWindow; };

		QPushButton *quitButton, *clearButton, *investmentReport, *addInvestment;

		Window *investmentWindow, *secondaryWindow;
	
	public slots:
		void investmentSlot();
		void investmentReportSlot(); 
};

#endif
