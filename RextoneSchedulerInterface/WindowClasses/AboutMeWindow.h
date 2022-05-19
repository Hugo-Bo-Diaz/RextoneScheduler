#ifndef ABOUT_ME_WINDOW__H
#define ABOUT_ME_WINDOW__H

#include "Window.h"
#include "UIClasses/FieldUI.h"

class HyperLinkUI;

class AboutMeWindow :
	public Window
{
public:
	AboutMeWindow(Window* _parent = nullptr) { parent = _parent; };

	//FieldUI weekly;


	void AddElements();
	void ManageButtonPress(WPARAM wp, LPARAM lp);

	~AboutMeWindow();

};

#endif