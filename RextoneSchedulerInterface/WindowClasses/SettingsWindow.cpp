#include "../stdafx.h"
#include "../DataHandler.h"
#include "../StringToWstring.h"

#include "SettingsWindow.h"
#include "../Settings.h"

void SettingsWindow::AddElements()
{
	notify_events.Initialize(Whandler, L"Notifications for events", 20, 20, 150, 20);

	ev_min_notif.Initialize(Whandler,L"mins", 20, 50, 50, 30, 20, true);
	ev_hr_notif.Initialize(Whandler, L"hours", 150, 50, 50, 30, 20, true);

	notify_todos.Initialize(Whandler, L"Notifications for To Dos", 20, 90, 150, 20);

	td_min_notif.Initialize(Whandler, L"mins", 20, 120, 50, 30, 20, true);
	td_hr_notif.Initialize(Whandler, L"hours", 150, 120, 50, 30, 20, true);



	CreateWindowW(L"Button", L"Clear data", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | WS_TABSTOP, 20, 160, 100, 30, Whandler, (HMENU)ApplicationButtons::SW_CLEAR_DATA, NULL, NULL);
	CreateWindowW(L"Button", L"Cancel", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | WS_TABSTOP, 20, 240, 100, 30, Whandler, (HMENU)ApplicationButtons::SW_CLOSE, NULL, NULL);
	CreateWindowW(L"Button", L"Apply", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | WS_TABSTOP, 150, 240, 100, 30, Whandler, (HMENU)ApplicationButtons::SW_APPLY, NULL, NULL);


}

void SettingsWindow::ManageButtonPress(WPARAM wp, LPARAM lp)
{
	switch (wp)
	{
	case ApplicationButtons::SW_APPLY:
		//retrieve all the info and send to data handler
		if (!ApplySettings())
		{
			MessageBox(NULL, L"Could not apply settings", L"Settings", MB_OK);
		}
		else
		{
			DestroyWindow(Whandler);
		}
		break;
	case ApplicationButtons::SW_CLEAR_DATA:
		DataHandler::Get().ClearElements();
		break;
	case ApplicationButtons::SW_CLOSE:
		DestroyWindow(Whandler);
		break;
	default:
		break;
	}
}

SettingsWindow::~SettingsWindow()
{
}

bool SettingsWindow::ApplySettings()
{
	int min_ev = ev_min_notif.GetFieldNumber();
	int hr_ev = ev_hr_notif.GetFieldNumber();

	int min_td = td_min_notif.GetFieldNumber();
	int hr_td = td_hr_notif.GetFieldNumber();

	if (min_ev < 60 && min_ev >= 0 && min_td < 60 && min_td >= 0)
	{
		Settings::Get().SetSettingsValue("ActiveEventNotif", notify_events.isChecked());
		int secondsToEventNotification = hr_ev * 3600 + min_ev * 60;
		Settings::Get().SetSettingsValue("TimeToEventNotif", secondsToEventNotification);

		Settings::Get().SetSettingsValue("ActiveToDoNotif", notify_todos.isChecked());
		int secondsToToDoNotification = hr_td * 3600 + min_td * 60;
		Settings::Get().SetSettingsValue("TimeToToDoNotif", secondsToToDoNotification);
		return true;
	}
	else
	{
		return false;
	}
}

void SettingsWindow::GetSettingsOnWindow()
{
	int time_to_ev_notif = Settings::Get().GetSettingsValue("TimeToEventNotif", 3600);
	//separate this number into hours and minutes
	int totalmins = time_to_ev_notif / 60;
	int hr_ev = totalmins / 60;
	int min_ev = totalmins % 60;

	int time_to_td_notif = Settings::Get().GetSettingsValue("TimeToToDoNotif", 3600);
	//separate this number into hours and minutes
	totalmins = time_to_td_notif / 60;
	int hr_td = totalmins / 60;
	int min_td = totalmins % 60;


	ev_min_notif.SetFieldText(std::to_string(min_ev).c_str());
	ev_hr_notif.SetFieldText(std::to_string(hr_ev).c_str());

	td_min_notif.SetFieldText(std::to_string(min_td).c_str());
	td_hr_notif.SetFieldText(std::to_string(hr_td).c_str());

	//notify_events.setchecked()
	bool active = Settings::Get().GetSettingsValue("ActiveEventNotif",true);
	notify_events.SetCheck(active);

	active = Settings::Get().GetSettingsValue("ActiveToDoNotif",true);
	notify_todos.SetCheck(active);
}
