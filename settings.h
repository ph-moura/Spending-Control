#ifndef SETTINGS_H
#define SETTINGS_H

#include "includes.hpp"
#include "window.h"

class SettingWidget : public QWidget
{
	// Q_OBJECT

	public:
		SettingWidget();

		Window * view() { return settingWindow; };

		QPushButton *quitButton, *clearButton, *addSetting;

		Window *settingWindow, *secondaryWindow;

	public slots:
		void settingSlot();
};

#endif
