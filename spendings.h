#ifndef SPENDINGS_H
#define SPENDINGS_H

#include "includes.hpp"
#include "window.h"

class SpendingWidget : public QWidget
{
	// Q_OBJECT

	public:
		SpendingWidget();

		Window * view() { return spendingWindow; };

		QPushButton *quitButton, *clearButton, *spendingReport, *addSpending;

		Window *spendingWindow, *secondaryWindow;

	public slots:
		void spendingSlot();
		void spendingReportSlot();
};

#endif
