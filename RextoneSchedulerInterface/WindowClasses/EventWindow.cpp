#include "../stdafx.h"
#include <CommCtrl.h>
#include "EventWindow.h"
#include "UIClasses/ListUI.h"
#include "UIClasses/TableUI.h"

#include "../DataHandler.h"
#include "../StringToWstring.h"

#include <ctime>

void EventWindow::AddElements() {

	//TOP TO BOTTOM AND LEFT TO RIGHT ORDER

	CreateWindowW(L"static", L"Event editor: ", WS_VISIBLE | WS_CHILD | SS_LEFT | SS_CENTERIMAGE , 10, 10, 200, 20, Whandler, NULL, NULL, NULL);

	std::wstring mode = L"static";

	if (edit_mode)
		mode = L"Edit";


	name_field.Initialize(Whandler,L"Name:",10,50,100,200,20,false,edit_mode);

	desc_field.Initialize(Whandler, L"Description:", 10, 80, 100, 200, 65, false, edit_mode, true);

	s_min_field.Initialize(Whandler, L"Min start:", 10, 155, 100, 50, 20, true, edit_mode);
	e_min_field.Initialize(Whandler, L"Min end:", 160, 155, 100, 50, 20, true, edit_mode);

	s_hour_field.Initialize(Whandler, L"Hour start:", 10, 185, 100, 50, 20, true, edit_mode);
	e_hour_field.Initialize(Whandler, L"Hour end:", 160, 185, 100, 50, 20, true, edit_mode);

	//s_day_field.Initialize(Whandler, L"Day start:", 20, 215, 100, 50, 20, true,edit_mode);
	//e_day_field.Initialize(Whandler, L"Day end:", 170, 215, 100, 50, 20, true,edit_mode);

	//s_month_field.Initialize(Whandler, L"Month start:", 20, 245, 100, 50, 20, true,edit_mode);
	//e_month_field.Initialize(Whandler, L"Month end:", 170, 245, 100, 50, 20, true, edit_mode);

	//s_year_field.Initialize(Whandler, L"Year start:", 20, 275, 100, 50, 20, true,edit_mode);
	//e_year_field.Initialize(Whandler, L"Year end:", 170, 275, 100, 50, 20, true, edit_mode);

	if (edit_mode)
		CreateWindowW(L"Button", L"Copy->", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | WS_TABSTOP, 140, 215, 100, 30, Whandler, (HMENU)ApplicationButtons::EW_COPY_TO_END, NULL, NULL);

	start_day.Initialize(Whandler, L"day start", 90, 245, 100, 20, 20);
	end_day.Initialize(Whandler, L"day end", 210, 245, 100, 20, 20);

	link_field.Initialize(Whandler, L"link:", 10, 305, 100, 200, 60, false, edit_mode, true);


	CreateWindowW(L"Button", L"Cancel", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | WS_TABSTOP, 60, 400, 100, 30, Whandler, (HMENU)ApplicationButtons::EW_CANCEL, NULL, NULL);
	if(edit_mode)
		CreateWindowW(L"Button", L"Accept", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | WS_TABSTOP, 240, 400, 100, 30, Whandler, (HMENU)ApplicationButtons::EW_OKEY, NULL, NULL);



}

void EventWindow::ManageButtonPress(WPARAM wp,LPARAM lp) {
	switch (wp)
	{
	case ApplicationButtons::EW_OKEY:
		//retrieve all the info and send to data handler
		if (!GenerateEvent())
		{
			MessageBox(NULL, L"Error with the provided data", L"Data error", MB_OK);
		}
		else
		{
			DestroyWindow(Whandler);
		}
		break;
	case ApplicationButtons::EW_CANCEL:
		DestroyWindow(Whandler);
		break;
	case ApplicationButtons::EW_COPY_TO_END:
		
		e_min_field.SetFieldText(s_min_field.GetFieldText().c_str());
		e_hour_field.SetFieldText(s_hour_field.GetFieldText().c_str());
		/*
		e_day_field.SetFieldText(s_day_field.GetFieldText().c_str());
		e_month_field.SetFieldText(s_month_field.GetFieldText().c_str());
		e_year_field.SetFieldText(s_year_field.GetFieldText().c_str());
		*/
		break;
	default:
		break;
	}
}

bool EventWindow::GenerateEvent() {

	std::string name = name_field.GetFieldText();
	std::string desc = desc_field.GetFieldText();
	std::string link = link_field.GetFieldText();

	int s_min = s_min_field.GetFieldNumber();
	int e_min = e_min_field.GetFieldNumber();
	
	int s_hour = s_hour_field.GetFieldNumber();
	int e_hour = e_hour_field.GetFieldNumber();

	date start_d = start_day.GetDate();
	date end_d = end_day.GetDate();

	int s_day = start_d.mday;
	int e_day = end_d.mday;

	int s_month = start_d.month;
	int e_month = end_d.month;

	int s_year = start_d.year;
	int e_year = end_d.year;

	time_t start = 0;
	tm* tstart = localtime(&start);
	tstart->tm_min = s_min;
	tstart->tm_hour = s_hour;
	tstart->tm_mday = s_day;
	tstart->tm_year = s_year - 1900;
	tstart->tm_mon = s_month - 1;
	tstart->tm_isdst = -1;

	start = mktime(tstart);


	time_t end = 0;
	tm* tend = localtime(&end);
	tend->tm_min = e_min;
	tend->tm_hour = e_hour;
	tend->tm_mday = e_day;
	tend->tm_year = e_year - 1900;
	tend->tm_mon = e_month - 1;
	tend->tm_isdst = -1;

	end = mktime(tend);

	if (start != -1 && end != -1)
	{
		//this means that its okey to send it to the data handler
		//if(to_modify == -1)
		//	DataHandler::Get().AddModifyEvent(name.c_str(), desc.c_str(), start, end, link.c_str());
		//else
		//	DataHandler::Get().AddModifyEvent(name.c_str(), desc.c_str(), start, end, link.c_str(),to_modify);

		DataHandler::Get().AddModifyEvent(name.c_str(), desc.c_str(), start, end, link.c_str(), to_modify);
		return true;
	}
	else
	{
		return false;
	}
}

void EventWindow::SetEvent(int id)
{
	to_modify = id;

	if (id == -1)
		return;

	Event* ev = (Event*)DataHandler::Get().GetEntry(to_modify);


	name_field.SetFieldText(ev->name.c_str());
	desc_field.SetFieldText(ev->description.c_str());
	link_field.SetFieldText(ev->link.c_str());


	tm* start = localtime(&ev->time_start);

	s_min_field.SetFieldText(std::to_string(start->tm_min).c_str());
	s_hour_field.SetFieldText(std::to_string(start->tm_hour).c_str());
	start_day.SetDate(ev->time_start);

	tm* end = localtime(&ev->time_end);

	e_min_field.SetFieldText(std::to_string(end->tm_min).c_str());
	e_hour_field.SetFieldText(std::to_string(end->tm_hour).c_str());
	end_day.SetDate(ev->time_end);
}
