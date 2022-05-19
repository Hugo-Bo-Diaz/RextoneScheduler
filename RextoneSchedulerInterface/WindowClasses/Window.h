#ifndef WINDOW__H
#define WINDOW__H

#include "../stdafx.h"
#include "../resource.h"
#include "WindowClass.h"
enum ApplicationButtons {
	//MAIN WINDOW
	AB_QUIT = 10000,

	AB_ADD_EVENT,
	AB_MODIFY_EVENT,
	AB_REMOVE_EVENT,
	AB_VIEW_EVENT,

	AB_ADD_NOTE,
	AB_MODIFY_NOTE,
	AB_REMOVE_NOTE,
	AB_VIEW_NOTE,

	AB_ADD_TODO,
	AB_MODIFY_TODO,
	AB_REMOVE_TODO,
	AB_VIEW_TODO,

	AB_SAVE,

	AB_RESET,
	//AB_NOTIFICATIONS_TOGGLE,

	AB_SETTINGS,

	AB_HELP,
	AB_ABOUTME,

	//SETTINGS WINDOW
	SW_APPLY,
	SW_CLOSE,
	SW_CLEAR_DATA,

	//ABOUT ME WINDOW
	AM_LINKED_IN,
	AM_PORTFOLIO,


	//ADD EVENT WINDOW
	EW_OKEY,
	EW_CANCEL,
	EW_COPY_TO_END,

	//ADD NOTE WINDOW
	NW_OKEY,
	NW_CANCEL,

	//ADD TODO WINDOW
	TW_OKEY,
	TW_CANCEL,

	AB_MAX
};


struct Data;

class Window {
public:
	HWND Whandler;
	Window*parent = nullptr;
	WindowClass* WClass;

	Window(Window* _parent = nullptr) { parent = _parent; };

	bool Initialize(WindowClass* _Wclass, LPCWSTR window_name, int x = 100, int y = 100, int w = 500, int h = 500, DWORD args = WS_OVERLAPPEDWINDOW | WS_VISIBLE)
	{


		WClass = _Wclass;
		CreateWindowW(WClass->ClassName, window_name, args, x, y, w, h, NULL, NULL, NULL,this);

		return true;
	}

	virtual void AddMenu() {};
	virtual void AddElements() {};
	virtual void ManageButtonPress(WPARAM wp, LPARAM lp) {};
	virtual void ManageWindowNotifications(WPARAM wp, LPARAM id) {};//useful when having listUI and tableUI as it recieves WM_NOTIFY

	//ADD THIS METHOD TO CHILDREN CLASSES AND REFER TO IT TO HANDLE STUFF :D
	//LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

	virtual void DataUpdate(int id) {};
	virtual void DataCreated() {};
	virtual void DataAdded(int id) {};
	virtual void DataDestroyed(int id) {};
	virtual void DataCleared() {};


};

#endif // !WINDOW__H

