#include "stdafx.h"
#include "resource.h"
#include "WindowClasses/WindowClass.h"

#include "WindowClasses/MainWindow.h"
#include "WindowHandler.h"
#include "DataHandler.h"
#include "SysTrayNotif.h"
#include "ScheduleNotificator.h"
#include "Settings.h"
#include <shellapi.h>
#include <strsafe.h>
#include <chrono>

#include <ctime>

enum APPSTATE {
	STARTING,
	RUNNING,
	MINIMIZED,
	STOP,
	EXIT
}appstate;

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void WakeUp(WindowClass* wclass);
void AddWindowToApplication(HWND handler, LPARAM lp);

int WINAPI WinMain(HINSTANCE hInst, HINSTANCE hInstPrev, LPSTR args, int ncmdshow)
{
	appstate = STARTING;
	


	//SetTimer(NULL, 0, 5000, TimerFuncCheckTimes);


	SysTrayNotif::Get().Initialize(hInst);
	ScheduleNotificator::Get().Initialize(hInst);
	WindowClass* class_1 = new WindowClass(hInst,WindowProcedure);
	class_1->RegsiterWClass();
	//DataHandler::Get().AddEvent("name", "description", t, t, "help");
	//DataHandler::Get().AddToDo("take the trash out", "take it", t);
	//DataHandler::Get().AddEvent("first", "descriion", t, t, "help");
	//DataHandler::Get().AddToDo("take the out", "take it", t);
	//DataHandler::Get().AddEvent("second", "desiption", t, t, "help");
	//DataHandler::Get().AddNote("noted", "notingnotincehbjs");
	//DataHandler::Get().AddNote("noted2", "notingnotincehbjs");
	//DataHandler::Get().AddEvent("third", "descrip", t, t, "help");
	//DataHandler::Get().SaveToInI("data.ini");
	//DataHandler::Get().RemoveElement(DataHandler::Get().data[2]);
	//DataHandler::Get().LoadFromInI("data.ini");
	//time_t t = time(0);
	//tm* t1 = gmtime(&t);
	//t1.

	 
	while (appstate != EXIT)
	{

		switch (appstate)
		{
		case STARTING:
			//load things and init
			WakeUp(class_1); //PROCESS ALL WINDOW WAKING UP MSGS

			for (Window* win : WindowHandler::Get().windows)
			{
				MSG msg = { 0 };

				while (PeekMessage(&msg, win->Whandler, NULL, NULL, PM_REMOVE))
				{
					//if (!IsDialogMessage(NULL, &msg))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
				}
			}

			DataHandler::Get().LoadFromInI("data.ini");
			Settings::Get().LoadSettings("settings.ini");
			appstate = RUNNING;
			break;
		case RUNNING:
			//MAIN LOOP WITH WINDOWS
			for (Window* win : WindowHandler::Get().windows)
			{
				MSG msg = { 0 };

				while (PeekMessage(&msg,win->Whandler, NULL, NULL, PM_REMOVE))
				{
					//if (!IsDialogMessage(NULL, &msg))
					{
						TranslateMessage(&msg);
						DispatchMessage(&msg);
					}
				}
			}

			//clears windows that have been erased
			WindowHandler::Get().RemoveWindowFromArray();

			if (WindowHandler::Get().windows.size() <= 0)
				appstate = MINIMIZED;

			break;
		case STOP:
			Settings::Get().SaveSettings("settings.ini");
			DataHandler::Get().SaveToInI("data.ini");
			DataHandler::Get().ClearElements();
			WindowHandler::Get().ClearWindows();
			SysTrayNotif::Get().ShutDown();

			delete class_1;
			appstate = EXIT;
			break;
		default:
			break;
		}

		if (appstate == RUNNING || appstate == MINIMIZED)
		{
			Sleep(100);
			MSG msg = { 0 };

			while (PeekMessage(&msg, SysTrayNotif::Get().CommWindow, NULL, NULL, PM_REMOVE))
			{
				TranslateMessage(&msg);
				DispatchMessage(&msg);
				
			}

			//query the system tray icon
			SysTrayMsg Nmsg = SysTrayNotif::Get().GetNextMessage();
			while (Nmsg != ST_NONE)
			{
				switch (Nmsg)
				{
				case ST_WAKE_UP:
					WakeUp(class_1);
					break;
				case ST_SETTINGS:
					if (appstate == MINIMIZED) {
						Settings::Get().SpawnSettingsWindow(class_1);
						appstate = RUNNING;
					}
						
					break;
				case ST_EXIT:
					appstate = STOP;
					break;
				default:
					break;
				}
				Nmsg = SysTrayNotif::Get().GetNextMessage();
			}
			MSG msg1 = { 0 };

			while (PeekMessage(&msg1, ScheduleNotificator::Get().CommWindow, NULL, NULL, PM_REMOVE))
			{
				TranslateMessage(&msg1);
				DispatchMessage(&msg1);

			}

		}


	}


	return 0;
}




LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp) {
	

	Window* to_operate = WindowHandler::Get().GetWindowFromHandler(hWnd);

	if (msg == DataHandler::Get().MYWM_DATAUPDATED)
	{
		to_operate->DataUpdate(lp);
		ScheduleNotificator::Get().GetEvents();
	}
	else if (msg == DataHandler::Get().MYWM_DATACREATED)
	{
		to_operate->DataCreated();
		ScheduleNotificator::Get().GetEvents();
	}
	else if (msg == DataHandler::Get().MYWM_DATADELETED)
	{
		to_operate->DataDestroyed(lp);
		ScheduleNotificator::Get().GetEvents();
	}
	else if (msg == DataHandler::Get().MYWM_DATA_ADDED)
	{
		to_operate->DataAdded(lp);
		ScheduleNotificator::Get().GetEvents();
	}
	else if (msg == DataHandler::Get().MYWM_DATACLEARED)
	{
		to_operate->DataCleared();
		ScheduleNotificator::Get().GetEvents();
	}

	switch (msg)
	{
	case WM_CREATE:
		AddWindowToApplication(hWnd, lp);
		break;
	case WM_COMMAND:
		to_operate->ManageButtonPress(wp,lp);
		break;
	case WM_DESTROY:
		WindowHandler::Get().SetupRemoveWindow(to_operate);
		WindowHandler::Get().EnableParent(to_operate);
		break;
	case WM_NOTIFY:
		if(appstate!=STARTING)
			to_operate->ManageWindowNotifications(wp, lp);
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wp, lp);

}


void AddWindowToApplication(HWND handler, LPARAM lp) {
	CREATESTRUCT * pCreate = reinterpret_cast<CREATESTRUCT*>(lp);
	Window* w = reinterpret_cast<Window*>(pCreate->lpCreateParams);
	w->Whandler = handler;
	SetClassLongPtr(w->Whandler,GCLP_HICON,(LONG_PTR)LoadIcon(w->WClass->AppInstance, MAKEINTRESOURCE(IDI_ICON1)));

	if (w->parent != nullptr)
		EnableWindow(w->parent->Whandler, false);

	w->AddElements();
	w->AddMenu();
}


void WakeUp(WindowClass* wclass) {
	if (WindowHandler::Get().windows.size() == 0)
	{
		MainWindow* MainW = new MainWindow();
		WindowHandler::Get().RegisterWindow(MainW);
		MainW->Initialize(wclass, L"Rextone scheduler", CW_USEDEFAULT, CW_USEDEFAULT, 650, 700, WS_VISIBLE | WS_MINIMIZEBOX | WS_SYSMENU);
	
		if (appstate != STARTING)
		{
			PostMessage(HWND_BROADCAST, DataHandler::Get().MYWM_DATACREATED, NULL, NULL);
		}
		
		appstate = RUNNING;

	}

}
