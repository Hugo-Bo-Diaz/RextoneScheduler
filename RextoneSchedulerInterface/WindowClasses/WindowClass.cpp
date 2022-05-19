#include "../stdafx.h"

#include "WindowClass.h"

WindowClass::WindowClass(HINSTANCE hInst, WNDPROC procedure, LPCWSTR name, HBRUSH background, HCURSOR cursor)
{
	Background = wc.hbrBackground = background;
	Cursor = wc.hCursor = cursor;
	AppInstance = wc.hInstance = hInst;
	ClassName = wc.lpszClassName = name;
	Handler =  wc.lpfnWndProc = procedure;
}


bool WindowClass::RegsiterWClass()
{
	if (!RegisterClassW(&wc))
	{
		return false;
	};
	return true;
}
