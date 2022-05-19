#include "../stdafx.h"
#include <CommCtrl.h>
#include "MainWindow.h"
#include "UIClasses/ListUI.h"
#include "UIClasses/TableUI.h"

#include <vector>
#include "EventWindow.h"
#include "NoteWindow.h"
#include "ToDoWindow.h"
#include "HelpWindow.h"
#include "AboutMeWindow.h"

#include "../Settings.h"
#include "../WindowHandler.h"
#include "../DataHandler.h"

void MainWindow::AddMenu() {
	hMenu = CreateMenu();

	HMENU hFileMenu = CreateMenu();
	
	HMENU new_menu = CreateMenu();
		AppendMenu(new_menu, MF_STRING, ApplicationButtons::AB_ADD_EVENT, L"Event");
		AppendMenu(new_menu, MF_STRING, ApplicationButtons::AB_ADD_NOTE, L"Note");
		AppendMenu(new_menu, MF_STRING, ApplicationButtons::AB_ADD_TODO, L"To Do");
	
	//FILE
	AppendMenu(hFileMenu, MF_POPUP, (UINT_PTR)new_menu, L"Add");
	//V
	AppendMenu(hFileMenu, MF_STRING, ApplicationButtons::AB_SAVE, L"Save");
	//V
	AppendMenu(hFileMenu, MF_SEPARATOR, NULL, NULL);
	//V
	AppendMenu(hFileMenu, MF_STRING, ApplicationButtons::AB_QUIT, L"Quit");

	//HMENU hSettingsMenu = CreateMenu();

	//AppendMenu(hSettingsMenu, MF_STRING, ApplicationButtons::AB_RESET, L"Erase data");

	AppendMenu(hMenu, MF_POPUP, (UINT_PTR)hFileMenu, L"File");
	AppendMenu(hMenu, MF_STRING, ApplicationButtons::AB_SETTINGS, L"Settings");
	AppendMenu(hMenu, MF_STRING, ApplicationButtons::AB_HELP, L"Help");
	AppendMenu(hMenu, MF_STRING, ApplicationButtons::AB_ABOUTME, L"About Me");



	SetMenu(Whandler, hMenu);
}
void MainWindow::AddElements() {

	//TOP TO BOTTOM AND LEFT TO RIGHT ORDER

	CreateWindowW(L"static", L"Events: ", WS_VISIBLE | WS_CHILD | SS_LEFT | SS_CENTERIMAGE , 40, 20, 54, 20, Whandler, NULL, NULL, NULL);

	//HWND list = CreateWindow(WC_LISTVIEW, L"list name", WS_VISIBLE | WS_CHILD | WS_BORDER|LVS_REPORT | LVS_EDITLABELS,100,50,300,200,Whandler,(HMENU)NULL,NULL,NULL);
	
	events_t = new TableUI(Whandler, L"EventList", 40, 40, 570, 200);
	std::wstring col_name = L"Name";
	events_t->AddColumn((LPWSTR)col_name.c_str(), 170, LVCFMT_LEFT);
	col_name = L"Day";
	events_t->AddColumn((LPWSTR)col_name.c_str(), 130, LVCFMT_LEFT);
	col_name = L"Hour";
	events_t->AddColumn((LPWSTR)col_name.c_str(), 110, LVCFMT_LEFT);
	col_name = L"Link";
	events_t->AddColumn((LPWSTR)col_name.c_str(), 160, LVCFMT_LEFT);


	CreateWindowW(L"Button", L"Add ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | WS_TABSTOP, 40, 250, 100, 30, Whandler, (HMENU)ApplicationButtons::AB_ADD_EVENT, NULL, NULL);
	CreateWindowW(L"Button", L"Modify ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | WS_TABSTOP, 196, 250, 100, 30, Whandler, (HMENU)ApplicationButtons::AB_MODIFY_EVENT, NULL, NULL);
	CreateWindowW(L"Button", L"Delete ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | WS_TABSTOP, 352, 250, 100, 30, Whandler, (HMENU)ApplicationButtons::AB_REMOVE_EVENT, NULL, NULL);
	CreateWindowW(L"Button", L"View ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | WS_TABSTOP, 510, 250, 100, 30, Whandler, (HMENU)ApplicationButtons::AB_VIEW_EVENT, NULL, NULL);

	CreateWindowW(L"static", L"Notes: ", WS_VISIBLE | WS_CHILD | SS_LEFT | SS_CENTERIMAGE, 40, 310, 54, 20, Whandler, NULL, NULL, NULL);
	notes_t = new ListUI(Whandler,L"NoteList",40,330,250,210);

	CreateWindowW(L"Button", L"Add ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | WS_TABSTOP, 40, 550, 70, 30, Whandler, (HMENU)ApplicationButtons::AB_ADD_NOTE, NULL, NULL);
	CreateWindowW(L"Button", L"Modify ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | WS_TABSTOP, 130, 550, 70, 30, Whandler, (HMENU)ApplicationButtons::AB_MODIFY_NOTE, NULL, NULL);
	CreateWindowW(L"Button", L"Delete ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | WS_TABSTOP, 220, 550, 70, 30, Whandler, (HMENU)ApplicationButtons::AB_REMOVE_NOTE, NULL, NULL);


	CreateWindowW(L"static", L"To Do's: ", WS_VISIBLE | WS_CHILD | SS_LEFT | SS_CENTERIMAGE, 310, 310, 54, 20, Whandler, NULL, NULL, NULL);
	todo_t = new TableUI(Whandler, L"ToDoList", 310, 330, 300, 210,true);
	col_name = L"Done";
	todo_t->AddColumn((LPWSTR)col_name.c_str(), 40, LVCFMT_LEFT);
	col_name = L"Task";
	todo_t->AddColumn((LPWSTR)col_name.c_str(), 140, LVCFMT_LEFT);
	col_name = L"Expiration";
	todo_t->AddColumn((LPWSTR)col_name.c_str(), 120, LVCFMT_LEFT);

	CreateWindowW(L"Button", L"Add ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | WS_TABSTOP, 310, 550, 80, 30, Whandler, (HMENU)ApplicationButtons::AB_ADD_TODO, NULL, NULL);
	CreateWindowW(L"Button", L"Modify ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | WS_TABSTOP, 420, 550, 80, 30, Whandler, (HMENU)ApplicationButtons::AB_MODIFY_TODO, NULL, NULL);
	CreateWindowW(L"Button", L"Delete ", WS_VISIBLE | WS_CHILD | WS_BORDER | SS_CENTER | WS_TABSTOP, 530, 550, 80, 30, Whandler, (HMENU)ApplicationButtons::AB_REMOVE_TODO, NULL, NULL);


}

void MainWindow::ManageButtonPress(WPARAM wp, LPARAM lp) {

	int wmId = LOWORD(wp);
	int wmEvent = HIWORD(wp);

	if (wmEvent == LBN_DBLCLK && (HWND)lp == notes_t->listBoxID)
	{
		//this counts the same as view
		AddNoteWindow(note_list[notes_t->GetSelectedIndex()], false);
	}
	

	switch (wp)
	{
	//EVENT WINDOW INSTRUCTIONS
	case ApplicationButtons::AB_ADD_EVENT:
		AddEventWindow(-1,true);
		break;
	case ApplicationButtons::AB_MODIFY_EVENT:
		//get selected event here
		if(events_t->GetSelectedIndex() != -1)
			AddEventWindow(ev_list[events_t->GetSelectedIndex()],true);
		else
			MessageBox(NULL, L"Select an event first", L"Event", MB_OK);
		break;
	case ApplicationButtons::AB_VIEW_EVENT:
		//get selected event here
		if (events_t->GetSelectedIndex() != -1)
			AddEventWindow(ev_list[events_t->GetSelectedIndex()],false);
		else
			MessageBox(NULL, L"Select an event first", L"Event", MB_OK);
		break;
	case ApplicationButtons::AB_REMOVE_EVENT:
		if(events_t->GetSelectedIndex() != -1)
			DataHandler::Get().RemoveElement(ev_list[events_t->GetSelectedIndex()]);
		else
			MessageBox(NULL, L"Select an event first", L"Event", MB_OK);
		break;

	//NOTE WINDOW INSTRUCTIONS
	case ApplicationButtons::AB_ADD_NOTE:
		AddNoteWindow(-1, true);
		break;
	case ApplicationButtons::AB_MODIFY_NOTE:
		if (notes_t->GetSelectedIndex() != -1)
			AddNoteWindow(note_list[notes_t->GetSelectedIndex()], true);
		else
			MessageBox(NULL, L"Select a note first", L"Note", MB_OK);
		break;
	case ApplicationButtons::AB_VIEW_NOTE:
		if (notes_t->GetSelectedIndex() != -1)
			AddNoteWindow(note_list[notes_t->GetSelectedIndex()], false);
		else
			MessageBox(NULL, L"Select a note first", L"Note", MB_OK);
		break;
	case ApplicationButtons::AB_REMOVE_NOTE:
		if (notes_t->GetSelectedIndex() != -1)
			DataHandler::Get().RemoveElement(note_list[notes_t->GetSelectedIndex()]);
		else
			MessageBox(NULL, L"Select a note first", L"Note", MB_OK);
		break;


		//TODO WINDOW INSTRUCTIONS
	case ApplicationButtons::AB_ADD_TODO:
		AddToDoWindow(-1, true);
		break;
	case ApplicationButtons::AB_MODIFY_TODO:
		if (todo_t->GetSelectedIndex() != -1)
			AddToDoWindow(todo_list[todo_t->GetSelectedIndex()], true);
		else
			MessageBox(NULL, L"Select a note first", L"Note", MB_OK);
		break;
	case ApplicationButtons::AB_VIEW_TODO:
		if (todo_t->GetSelectedIndex() != -1)
			AddToDoWindow(todo_list[todo_t->GetSelectedIndex()], false);
		else
			MessageBox(NULL, L"Select a note first", L"Note", MB_OK);
		break;
	case ApplicationButtons::AB_REMOVE_TODO:
		if (todo_t->GetSelectedIndex() != -1)
			DataHandler::Get().RemoveElement(todo_list[todo_t->GetSelectedIndex()]);
		else
			MessageBox(NULL, L"Select a note first", L"Note", MB_OK);
		break;

	case ApplicationButtons::AB_ABOUTME:
		//SHOW WINDOW THAT TELLS THEM ABOUT ME :)
		AddAboutMeWindow();
		break;
	case ApplicationButtons::AB_HELP:
		//SHOW WINDOW THAT TELLS THEM ABOUT ME :)
		AddHelpWindow();
		break;

	case ApplicationButtons::AB_SETTINGS:
		Settings::Get().SpawnSettingsWindow(this->WClass,this);
		break;

	case ApplicationButtons::AB_RESET:
		DataHandler::Get().ClearElements();
		break;
	case ApplicationButtons::AB_SAVE:
		DataHandler::Get().SaveToInI("data.ini");
		break;
	case ApplicationButtons::AB_QUIT:
		DestroyWindow(Whandler);
		break;
	case NM_DBLCLK:
		MessageBox(NULL, L"Error with the provided data", L"Data error", MB_OK);
		break;
	default:
		break;
	}
}

void MainWindow::ManageWindowNotifications(WPARAM wp, LPARAM id)
{

	//IMPROVEMENT: ONLY ENTER IF ITEM IS SELECTED
	if((((LPNMHDR)id)->hwndFrom)== events_t->listViewID)
	{

			switch (((LPNMHDR)id)->code)
			{
			case NM_DBLCLK:
			{
				int index = events_t->GetSelectedIndex();
				if (index != -1)
				{
					AddEventWindow(ev_list[index], false);
					return;
				}
			}
			break;
			default:
				int index;
				break;
			}
		
	}

	if ((((LPNMHDR)id)->hwndFrom) == todo_t->listViewID)
	{
		LPNMLISTVIEW pnmv = (LPNMLISTVIEW)id;
		int index = 0;

			switch (((LPNMHDR)id)->code)
			{
			case NM_DBLCLK:
				index = todo_t->GetSelectedIndex();
				if (index != -1)
				{
					AddToDoWindow(todo_list[index], false);
				}
				return;
			break;
			case LVN_ITEMCHANGED:
				if (pnmv->uChanged & LVIF_STATE)
				{
					ToDo* to_mod = (ToDo*)DataHandler::Get().GetEntry(todo_list[pnmv->iItem]);
					bool is_completed = todo_t->GetCheckbox(pnmv->iItem);
					DataHandler::Get().SetToDoValue(is_completed, to_mod->id);
				}
			break;
			default:
				break;
			}
		

	}


	//else {
	//	DefWindowProc(Whandler, WM_NOTIFY, wp, id);
	//}

}

void MainWindow::AddEventWindow(int id,bool edit)
{
	EventWindow* ev = new EventWindow(this);

	WindowHandler::Get().RegisterWindow(ev);
	ev->edit_mode = edit;

	ev->Initialize(this->WClass,L"Event modify", CW_USEDEFAULT, CW_USEDEFAULT, 400,500, WS_VISIBLE | WS_MINIMIZEBOX | WS_SYSMENU);
	ev->SetEvent(id);

}

void MainWindow::AddNoteWindow(int id, bool edit)
{
	NoteWindow* nt = new NoteWindow(this);

	WindowHandler::Get().RegisterWindow(nt);
	nt->edit_mode = edit;

	nt->Initialize(this->WClass, L"Note modify", CW_USEDEFAULT, CW_USEDEFAULT, 400, 350, WS_VISIBLE | WS_MINIMIZEBOX | WS_SYSMENU);
	nt->SetNote(id);

}

void MainWindow::AddToDoWindow(int id, bool edit)
{
	ToDoWindow* td = new ToDoWindow(this);

	WindowHandler::Get().RegisterWindow(td);
	td->edit_mode = edit;

	td->Initialize(this->WClass, L"Note modify", CW_USEDEFAULT, CW_USEDEFAULT, 400, 350, WS_VISIBLE | WS_MINIMIZEBOX | WS_SYSMENU);
	td->SetToDo(id);

}

void MainWindow::DataAdded(int id)
{
	//add new data into the window interface
	Data* d = DataHandler::Get().GetEntry(id);

	if (d == nullptr)
		return;

	AddDataToTable(d);

}

void MainWindow::DataUpdate(int id)
{
	for (unsigned int i =0;i<ev_list.size();++i)
	{
		if (ev_list[i] == id)
		{
			Event* e = (Event*)DataHandler::Get().GetEntry(id);
			ModifyEventTable(e, i);
		}
	}

}

void MainWindow::DataCreated()
{

	ev_list.clear();
	DataHandler::Get().GetAllEvents(ev_list);
	todo_list.clear();
	DataHandler::Get().GetAllToDos(todo_list);
	note_list.clear();
	DataHandler::Get().GetAllNotes(note_list);

	for (int i : ev_list)
	{
		//IMPROVEMENT: CHECK DATA TYPE BEFORE CASTING as a safety net
		Event* e = (Event*)DataHandler::Get().GetEntry(i);

		ModifyEventTable(e);
	}

	for (int i : todo_list)
	{
		//FILL THE EVENT TABLE
		ToDo* t = (ToDo*)DataHandler::Get().GetEntry(i);

		ModifyToDoTable(t);

	}

	for (int i : note_list)
	{
		Note* n = (Note*)DataHandler::Get().GetEntry(i);

		ModifyNoteTable(n);
	}
}

void MainWindow::DataDestroyed(int id)
{
	//https://stackoverflow.com/questions/4713131/removing-item-from-vector-while-iterating
	//still using an iterator because i need to access the part of the list
	int iterator = 0;
	std::vector<int>::iterator it;
	
	it = ev_list.begin();
	while (it != ev_list.end()) 
	{
		if ((*it)==id) {
			events_t->RemoveItem(iterator);
			it = ev_list.erase(it);
		}
		else ++it;

		++iterator;
	}

	iterator = 0;
	it = todo_list.begin();
	while (it != todo_list.end())
	{
		if ((*it) == id) {
			todo_t->RemoveItem(iterator);
			it = todo_list.erase(it);
		}
		else ++it;

		++iterator;
	}


	iterator = 0;
	it = note_list.begin();
	while (it != note_list.end())
	{
		if ((*it) == id) {
			notes_t->RemoveItem(iterator);
			it = note_list.erase(it);
		}
		else ++it;

		++iterator;
	}

	//int items_erased = 0;
	//for (int i = 0 ;i<ev_list.size()- items_erased;++i)
	//{
	//	if (ev_list[i] == id)
	//	{
	//		events_t->RemoveItem(i);
	//		ev_list.erase(ev_list.begin() + i);
	//		++items_erased;
	//	}
	//}
	//for (int i = 0; i<todo_list.size(); ++i)
	//{
	//	if (todo_list[i] == id)
	//	{
	//		todo_t->RemoveItem(i);
	//		todo_list.erase(todo_list.begin() + i);
	//		++items_erased;
	//	}
	//}
	//items_erased = 0;
	//for (int i = 0; i<note_list.size(); ++i)
	//{
	//	if (note_list[i] == id)
	//		notes_t->RemoveItem(i);
	//}
}

void MainWindow::DataCleared()
{
	ev_list.clear();
	todo_list.clear();
	note_list.clear();

	events_t->ClearItems();
	todo_t->ClearItems();
	notes_t->ClearItems();

}

void MainWindow::AddDataToTable(Data * d)
{

	if (d->type == DataType::DT_event)
	{
		ev_list.push_back(d->id);
		Event * e = (Event*)d;
		ModifyEventTable(e);
	}
	else if (d->type == DataType::DT_ToDo) 
	{
		todo_list.push_back(d->id);
		ToDo * t = (ToDo*)d;
		ModifyToDoTable(t);
	}
	else if (d->type == DataType::DT_note)
	{
		note_list.push_back(d->id);
		Note * n = (Note*)d;
		ModifyNoteTable(n);
	}
}

void MainWindow::ModifyEventTable(Event * e,int row)
{

	tm* t1 = localtime(&e->time_start);
	t1->tm_mday;

	std::string day = std::to_string(t1->tm_mday) + " / " + std::to_string(t1->tm_mon+1) + " / " + std::to_string(t1->tm_year + 1900);
	std::string hour = std::to_string(t1->tm_hour) + ":" + std::to_string(t1->tm_min);
	events_t->AddItem(4,row,false, e->name.c_str(), day.c_str(), hour.c_str(), e->link.c_str());
}

void MainWindow::ModifyToDoTable(ToDo * t, int row)
{
	tm* t1 = localtime(&t->expiration);
	t1->tm_mday;

	std::string exp = std::to_string(t1->tm_mday) + " / " + std::to_string(t1->tm_mon);

	todo_t->AddItem(3,row,t->completed, "", t->name.c_str(), exp.c_str());
}

void MainWindow::ModifyNoteTable(Note * n)
{
	notes_t->AddItem(n->name.c_str());

}

void MainWindow::AddAboutMeWindow()
{
	AboutMeWindow* aw = new AboutMeWindow(this);

	WindowHandler::Get().RegisterWindow(aw);

	aw->Initialize(this->WClass, L"About Me", CW_USEDEFAULT, CW_USEDEFAULT, 350, 250, WS_VISIBLE | WS_MINIMIZEBOX | WS_SYSMENU);

}

void MainWindow::AddHelpWindow()
{
	HelpWindow* hw = new HelpWindow(this);

	WindowHandler::Get().RegisterWindow(hw);

	hw->Initialize(this->WClass, L"Help", CW_USEDEFAULT, CW_USEDEFAULT, 350, 300, WS_VISIBLE | WS_MINIMIZEBOX | WS_SYSMENU);

}
