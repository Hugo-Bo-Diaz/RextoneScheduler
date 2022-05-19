#ifndef MAIN_WINDOW__H
#define MAIN_WINDOW__H

#include "Window.h"
#include <vector>

class TableUI;

class ListUI;

struct Data;
struct Event;
struct ToDo;
struct Note;

class MainWindow : public Window {
public:
	MainWindow(Window* parent = nullptr) {};

	HMENU hMenu;

	TableUI* events_t;
	TableUI* todo_t;
	ListUI* notes_t;

	std::vector<int>ev_list;
	std::vector<int>todo_list;
	std::vector<int>note_list;

	void AddMenu();
	void AddElements();
	void ManageButtonPress(WPARAM wp,LPARAM lp);
	void ManageWindowNotifications(WPARAM wp, LPARAM id);

	void AddEventWindow(int id,bool edit);
	void AddNoteWindow(int id, bool edit);
	void AddToDoWindow(int id, bool edit);
	void DataAdded(int id);
	void DataUpdate(int id);
	void DataCreated();
	void DataDestroyed(int id);
	void DataCleared();

	void AddDataToTable(Data*d);
	
	void ModifyEventTable(Event*ev, int row = -1);
	void ModifyToDoTable(ToDo*td, int row = -1);
	void ModifyNoteTable(Note*nt);

	void AddHelpWindow();
	void AddAboutMeWindow();

};
#endif // !MAIN_WINDOW__H
