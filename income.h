#ifndef INCOME_H
#define INCOME_H

#include "includes.hpp"
#include "window.h"

class IncomeWidget : public QWidget
{
	public:
		IncomeWidget();

		Window * view() { return incomeWindow; };

		QPushButton *quitButton, *clearButton, *incomeReport, *addIncome;

		Window *incomeWindow, *secondaryWindow;

	public slots:
		void incomeReportSlot();
		void incomeSlot();
};

#endif
