#ifndef SETTINGS_WINDOW__H
#define SETTINGS_WINDOW__H

#include "Window.h"
#include "UIClasses/FieldUI.h"
#include "UIClasses/CheckBoxUI.h"

class SettingsWindow :
	public Window
{
public:
	SettingsWindow(Window* _parent = nullptr) { parent = _parent; };

	CheckBoxUI notify_events;

	FieldUI ev_min_notif;
	FieldUI ev_hr_notif;

	CheckBoxUI notify_todos;

	FieldUI td_min_notif;
	FieldUI td_hr_notif;



	void AddElements();
	void ManageButtonPress(WPARAM wp, LPARAM lp);

	~SettingsWindow();


	bool ApplySettings();
	void GetSettingsOnWindow();
};

#endif