#include "../stdafx.h"
#include "../DataHandler.h"
#include "../StringToWstring.h"

#include "HelpWindow.h"

void HelpWindow::AddElements()
{
	CreateWindowW(L"static", L"Welcome to the Rextone Scheduler!\n\nThis is an application that helps with organization: you can set up your own events,notes and tasks and the application will remember you about them. You can even set up windows notifications for them!\n\nIf you close the main window the application will stay in the background waiting for events to happen, to close it use the icon on the task bar", WS_VISIBLE | WS_CHILD | SS_LEFT | BS_MULTILINE, 10, 30, 300, 200, Whandler, NULL, NULL, NULL);


}
//
//void HelpWindow::ManageButtonPress(WPARAM wp, LPARAM lp)
//{
//	switch (wp)
//	{
//	case ApplicationButtons::TW_OKEY:
//		//retrieve all the info and send to data handler
//		if (!GenerateToDo())
//		{
//			MessageBox(NULL, L"Error with the provided data", L"Data error", MB_OK);
//		}
//		else
//		{
//			DestroyWindow(Whandler);
//		}
//		break;
//	case ApplicationButtons::TW_CANCEL:
//		DestroyWindow(Whandler);
//		break;
//	default:
//		break;
//	}
//}

HelpWindow::~HelpWindow()
{
}
