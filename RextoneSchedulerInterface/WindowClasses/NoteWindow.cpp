#include "../stdafx.h"
#include "../DataHandler.h"
#include "../StringToWstring.h"

#include "NoteWindow.h"

void NoteWindow::AddElements()
{
	title_field.Initialize(Whandler,L"Note:",10,10,35,200,20,false,edit_mode);

	CreateWindowW(L"static", L"content: (1000 char max)", WS_VISIBLE | WS_CHILD | SS_LEFT | SS_CENTERIMAGE, 10, 30, 300, 20, Whandler, NULL, NULL, NULL);

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


	note_edit = CreateWindowW(mode.c_str(), L"", style, 10, 60, 380, 200, Whandler, NULL, NULL, NULL);

	CreateWindowW(L"Button", L"Cancel ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 60, 270, 100, 30, Whandler, (HMENU)ApplicationButtons::NW_CANCEL, NULL, NULL);
	if (edit_mode)
		CreateWindowW(L"Button", L"Accept ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER, 240, 270, 100, 30, Whandler, (HMENU)ApplicationButtons::NW_OKEY, NULL, NULL);


}

void NoteWindow::ManageButtonPress(WPARAM wp, LPARAM lp)
{
	switch (wp)
	{
	case ApplicationButtons::NW_OKEY:
		//retrieve all the info and send to data handler
		if (!GenerateNote())
		{
			MessageBox(NULL, L"Error with the provided data", L"Data error", MB_OK);
		}
		else
		{
			DestroyWindow(Whandler);
		}
		break;
	case ApplicationButtons::NW_CANCEL:
		DestroyWindow(Whandler);
		break;
	default:
		break;
	}
}

NoteWindow::~NoteWindow()
{
}

bool NoteWindow::GenerateNote()
{

	std::string name = title_field.GetFieldText();

	wchar_t buffer[1000];
	GetWindowText(note_edit, buffer, 1000);
	std::string desc = ws2s(buffer);

	//if (to_modify == -1)
	//	DataHandler::Get().AddNote(name.c_str(), desc.c_str());
	//else
	//	DataHandler::Get().ModifyNote(to_modify, name.c_str(), desc.c_str());

	DataHandler::Get().AddModifyNote(name.c_str(), desc.c_str(),to_modify);

	return true;
}

void NoteWindow::SetNote(int id)
{
	to_modify = id; 
	
	if (id == -1)
		return;

	Note* nt = (Note*)DataHandler::Get().GetEntry(to_modify);


	title_field.SetFieldText(nt->name.c_str());

	std::wstring wstr = s2ws(nt->description);
	SetWindowText(note_edit, wstr.c_str());


}
