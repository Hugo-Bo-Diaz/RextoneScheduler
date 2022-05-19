#ifndef TODO_WINDOW__H
#define TODO_WINDOW__H

#include "Window.h"
#include "UIClasses/FieldUI.h"
#include "UIClasses/CalendarUI.h"

class ToDoWindow :
	public Window
{
public:
	ToDoWindow(Window* _parent = nullptr) { parent = _parent; };

	FieldUI title_field;
	HWND note_edit;

	FieldUI min_exp;
	FieldUI hour_exp;
	CalendarUI cal_exp;

	//FieldUI weekly;

	bool edit_mode = true;

	void AddElements();
	void ManageButtonPress(WPARAM wp, LPARAM lp);

	~ToDoWindow();


	bool GenerateToDo();

	int to_modify = -1;
	void SetToDo(int id);
};

#endif