#ifndef CHECKBOX__H
#define CHECKBOX__H

#include <Windows.h>

class CheckBoxUI
{
public:

	HWND checkboxID;

	CheckBoxUI();
	void Initialize(HWND parent,LPCWSTR text,int x, int y, int w, int h );
	~CheckBoxUI();

	bool isChecked();
	void SetCheck(bool);
};


#endif // !CHECKBOX__UI