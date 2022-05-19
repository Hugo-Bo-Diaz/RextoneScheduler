#ifndef HELP_WINDOW__H
#define HELP_WINDOW__H

#include "Window.h"
#include "UIClasses/FieldUI.h"

class HelpWindow :
	public Window
{
public:
	HelpWindow(Window* _parent = nullptr) { parent = _parent; };

	//FieldUI weekly;

	bool edit_mode = true;

	void AddElements();
	//void ManageButtonPress(WPARAM wp, LPARAM lp);

	~HelpWindow();

};

#endif