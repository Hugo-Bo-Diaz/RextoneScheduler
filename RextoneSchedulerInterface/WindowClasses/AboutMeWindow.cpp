#include "../stdafx.h"
#include "../DataHandler.h"
#include "../StringToWstring.h"
#include <shellapi.h>

#include "AboutMeWindow.h"

void AboutMeWindow::AddElements()
{
	CreateWindowW(L"static", L"Hello! This is Hugo (known online as Rextone) and I'm currently looking for a job on the software developing industry.\n\n You can find my linkedIn as well as my portfolio below", WS_VISIBLE | WS_CHILD | SS_LEFT | BS_MULTILINE, 10, 30, 300, 100, Whandler, NULL, NULL, NULL);

	CreateWindowW(L"Button", L"LinkedIn", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | WS_TABSTOP, 10, 170, 100, 30, Whandler, (HMENU)ApplicationButtons::AM_LINKED_IN, NULL, NULL);
	CreateWindowW(L"Button", L"Portfolio", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | WS_TABSTOP, 150, 170, 100, 30, Whandler, (HMENU)ApplicationButtons::AM_PORTFOLIO, NULL, NULL);

}
//
void AboutMeWindow::ManageButtonPress(WPARAM wp, LPARAM lp)
{
	switch (wp)
	{
	case ApplicationButtons::AM_LINKED_IN:
		//retrieve all the info and send to data handler
		ShellExecute(0, 0, L"https://www.linkedin.com/in/hugo-bo-diaz/", 0, 0, SW_SHOW);
		break;
	case ApplicationButtons::AM_PORTFOLIO:
		ShellExecute(0, 0, L"https://hugobodiaz.freecluster.eu/", 0, 0, SW_SHOW);
		break;
	default:
		break;
	}
}

AboutMeWindow::~AboutMeWindow()
{
}
