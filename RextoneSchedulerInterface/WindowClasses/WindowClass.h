#ifndef WINDOW_CLASS__H
#define WINDOW_CLASS__H

#include "../stdafx.h"
#include "../resource.h"


class WindowClass
{
public:
	WNDCLASSW wc = { 0 };
	WindowClass() {};
	WindowClass(HINSTANCE, WNDPROC, LPCWSTR class_name = L"BasicWindow", HBRUSH background = (HBRUSH)COLOR_WINDOW, HCURSOR cursor = LoadCursor(NULL, IDC_ARROW));

	HBRUSH Background;
	HCURSOR Cursor;
	HINSTANCE AppInstance;
	LPCWSTR ClassName;
	WNDPROC Handler;//DON'T MAKE THE FUNCTION CLASS SPECIFIC!!!!

	WNDCLASSW GetWindowClass() { return wc; };

	bool RegsiterWClass();
};


#endif // !WINDOW_CLASS__H

