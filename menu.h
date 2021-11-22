#ifndef MENU_H
#define MENU_H

class MyMenu : public QMenuBar
{
	public:
		MyMenu(QWidget*);
	
	private:	
    	QAction *newAction, *openAction, *quitAction, *saveAction;
		QMenu *fileMenu, *toolsMenu;

	private:
		Q_SLOT
		void newMenuSlot();
		void openMenuSlot();
		void quitMenuSlot();
		void saveMenuSlot();
};

#endif
