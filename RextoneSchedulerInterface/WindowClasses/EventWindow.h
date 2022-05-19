#ifndef EVENT_WINDOW__H
#define EVENT_WINDOW__H

#include "Window.h"
#include "UIClasses/FieldUI.h"
#include "UIClasses/CalendarUI.h"

class EventWindow : public Window {
public:
	EventWindow(Window* _parent = nullptr) { parent = _parent; };

	FieldUI name_field;
	FieldUI desc_field;

	FieldUI s_min_field;
	FieldUI e_min_field;

	FieldUI s_hour_field;
	FieldUI e_hour_field;

	FieldUI link_field;

	CalendarUI start_day;
	CalendarUI end_day;

	bool edit_mode = true;

	void AddElements();
	void ManageButtonPress(WPARAM wp,LPARAM lp);

	bool GenerateEvent();

	int to_modify = -1;
	void SetEvent(int id);

};
#endif // !EVENT_WINDOW__H
