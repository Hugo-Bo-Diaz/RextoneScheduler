#ifndef NOTE_WINDOW__H
#define NOTE_WINDOW__H

#include "Window.h"
#include "UIClasses/FieldUI.h"

class NoteWindow :
	public Window
{
public:
	NoteWindow(Window* _parent = nullptr) { parent = _parent; };

	FieldUI title_field;
	HWND note_edit;

	bool edit_mode = true;

	void AddElements();
	void ManageButtonPress(WPARAM wp, LPARAM lp);

	~NoteWindow();


	bool GenerateNote();

	int to_modify = -1;
	void SetNote(int id);
};

#endif