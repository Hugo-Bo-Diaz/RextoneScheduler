#include "../stdafx.h"
#include "../DataHandler.h"
#include "../StringToWstring.h"

#include "ToDoWindow.h"

void ToDoWindow::AddElements()
{
	title_field.Initialize(Whandler,L"Name:",10,10,40,200,20,false,edit_mode);

	CreateWindowW(L"static", L"Description: (200 char max)", WS_VISIBLE | WS_CHILD | SS_LEFT | SS_CENTERIMAGE, 10, 30, 300, 20, Whandler, NULL, NULL, NULL);

	std::wstring mode = L"Edit";

	if (edit_mode == false)
		mode = L"static";

	DWORD style = WS_VISIBLE | WS_CHILD | SS_LEFT;

	if (edit_mode)
	{
		style += ES_MULTILINE;
	}
	else
	{
		style += BS_MULTILINE;
	}
	note_edit = CreateWindowW(mode.c_str(), L"", style, 10, 60, 380, 100, Whandler, NULL, NULL, NULL);

	min_exp.Initialize(Whandler,L"Expiration min:",10,170,100,35,20,true,edit_mode);
	hour_exp.Initialize(Whandler, L"Expiration hr:", 150, 170, 100, 35, 20, true, edit_mode);

	cal_exp.Initialize(Whandler, L"Expiration day", 10, 200, 100, 20, 20);

	

	CreateWindowW(L"Button", L"Cancel ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 60, 250, 100, 30, Whandler, (HMENU)ApplicationButtons::TW_CANCEL, NULL, NULL);
	if (edit_mode)
		CreateWindowW(L"Button", L"Accept ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 240, 250, 100, 30, Whandler, (HMENU)ApplicationButtons::TW_OKEY, NULL, NULL);


}

void ToDoWindow::ManageButtonPress(WPARAM wp, LPARAM lp)
{
	switch (wp)
	{
	case ApplicationButtons::TW_OKEY:
		//retrieve all the info and send to data handler
		if (!GenerateToDo())
		{
			MessageBox(NULL, L"Error with the provided data", L"Data error", MB_OK);
		}
		else
		{
			DestroyWindow(Whandler);
		}
		break;
	case ApplicationButtons::TW_CANCEL:
		DestroyWindow(Whandler);
		break;
	default:
		break;
	}
}

ToDoWindow::~ToDoWindow()
{
}

bool ToDoWindow::GenerateToDo()
{

	std::string name = title_field.GetFieldText();

	wchar_t buffer[500];
	GetWindowText(note_edit, buffer, 500);
	std::string desc = ws2s(buffer);


	time_t start = 0;
	tm* tstart = gmtime(&start);
	tstart->tm_min = min_exp.GetFieldNumber() - 1;
	tstart->tm_hour = hour_exp.GetFieldNumber();

	date exp = cal_exp.GetDate();

	tstart->tm_mday = exp.mday;
	tstart->tm_year = exp.year;
	tstart->tm_mon = exp.month;
	tstart->tm_isdst = -1;

	start = mktime(tstart);
	if (start != -1)
	{
		//if (to_modify == -1)
		//	DataHandler::Get().AddToDo(name.c_str(), desc.c_str(), start);
		//else
		//	DataHandler::Get().ModifyToDo(to_modify, name.c_str(), desc.c_str(),start);

		DataHandler::Get().AddModifyToDo(name.c_str(), desc.c_str(), start,false,to_modify);


		return true;
	}


	return false;
}

void ToDoWindow::SetToDo(int id)
{
	to_modify = id;

	if (id == -1)
		return;

	ToDo* td = (ToDo*)DataHandler::Get().GetEntry(to_modify);


	title_field.SetFieldText(td->name.c_str());

	std::wstring wstr = s2ws(td->description);
	SetWindowText(note_edit, wstr.c_str());

	tm* texp = gmtime(&td->expiration);

	min_exp.SetFieldText(std::to_string(texp->tm_min+1).c_str());
	hour_exp.SetFieldText(std::to_string(texp->tm_hour).c_str());

	cal_exp.SetDate(td->expiration);

}