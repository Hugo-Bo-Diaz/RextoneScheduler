#include "stdafx.h"
#include "SysTrayNotif.h"
#include "WindowClasses/WindowClass.h"
#include <WinUser.h>

SysTrayNotif* STNotif = nullptr;

SysTrayNotif& SysTrayNotif::Get()
{
	if (STNotif == nullptr)
		STNotif = new SysTrayNotif();

	return *STNotif;
}

void SysTrayNotif::ShutDown()
{
	Shell_NotifyIcon(NIM_DELETE, &ndata);

	//remove sys tray icon
}

SysTrayMsg SysTrayNotif::GetNextMessage()
{
	//RESETTING THE STATE BEFORE EXITING THE FUNCTION
	if (msgqueue.size() > 0)
	{
		SysTrayMsg ret = msgqueue.front();
		msgqueue.pop();
		return ret;
	}
	else
	{
		return ST_NONE;
	}
}

void SysTrayNotif::AddTrayMenu()
{
	POINT pt;
	GetCursorPos(&pt);
	HMENU hmenu = CreatePopupMenu();
	HMENU hSubMenu;

	InsertMenu(hmenu, 0, MF_BYPOSITION | MF_STRING, STB_EXIT, L"Exit");
	InsertMenu(hmenu, 0, MF_BYPOSITION | MF_SEPARATOR,NULL,NULL);
	InsertMenu(hmenu, 0, MF_BYPOSITION | MF_STRING, STB_SETTINGS, L"Settings");
	InsertMenu(hmenu, 0, MF_BYPOSITION | MF_STRING, STB_OPEN, L"Open");



	SetForegroundWindow(CommWindow);
	TrackPopupMenu(hmenu, TPM_LEFTALIGN | TPM_LEFTBUTTON | TPM_BOTTOMALIGN, pt.x, pt.y, 0,CommWindow, NULL);
	PostMessage(CommWindow, WM_NULL, NULL, NULL);

}

void SysTrayNotif::SendNotification(const wchar_t * title, const wchar_t * text)
{
	if (wcslen(title) > 64 || wcslen(text) > 256)
		return;

	memcpy(ndata.szInfoTitle,title,64);
	memcpy(ndata.szInfo, text, 64);

	Shell_NotifyIcon(NIM_MODIFY, &ndata);

}

SysTrayNotif::SysTrayNotif()
{
	MYWM_SYSTRAY_NOTIF = RegisterWindowMessageW(L"RSIsystraynotif");
}


SysTrayNotif::~SysTrayNotif()
{
}

void SysTrayNotif::Initialize(HINSTANCE hinst)
{
	Wclass = new WindowClass(hinst,SysTrayProcedure,L"MessageTrayClass");
	Wclass->RegsiterWClass();

	CommWindow = CreateWindowW(Wclass->ClassName, NULL, NULL, 0, 0, 0, 0,HWND_MESSAGE, NULL, NULL, NULL);

	//create system tray icon

	ndata = { 0 };
	ndata.hWnd = CommWindow;
	ndata.cbSize = sizeof(ndata);
	ndata.uFlags = NIF_ICON | NIF_TIP | NIF_INFO | NIF_MESSAGE;
	ndata.uCallbackMessage = MYWM_SYSTRAY_NOTIF;
	
	memcpy(ndata.szTip, L"Rextone Scheduler",128);

	ndata.hIcon = (HICON)LoadImage(hinst, L"RextoneSchedulerIcon.ico", IMAGE_ICON,0,0,LR_LOADFROMFILE);

	Shell_NotifyIcon(NIM_ADD, &ndata);
}


LRESULT CALLBACK SysTrayProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{

	if (msg == SysTrayNotif::Get().MYWM_SYSTRAY_NOTIF)
	{
		switch (LOWORD(lp))
		{
		case WM_LBUTTONDOWN://left click
			SysTrayNotif::Get().msgqueue.push(ST_WAKE_UP);
			//SysTrayNotif::Get().SendNotification(L"testing", L"help me pls");
			break;
		case WM_RBUTTONDOWN://right click
			SysTrayNotif::Get().AddTrayMenu();
			break;
		case NIN_BALLOONUSERCLICK:
			SysTrayNotif::Get().msgqueue.push(ST_WAKE_UP);
			break;
		default:
			break;
		}
	}

	switch (msg)
	{
	case WM_COMMAND:
		switch (wp)
		{
		case STB_EXIT:
			SysTrayNotif::Get().msgqueue.push(ST_EXIT);
			break;
		case STB_OPEN:
			SysTrayNotif::Get().msgqueue.push(ST_WAKE_UP);
			break;
		case STB_SETTINGS:
			SysTrayNotif::Get().msgqueue.push(ST_SETTINGS);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}

	return DefWindowProc(hWnd, msg, wp, lp);


}