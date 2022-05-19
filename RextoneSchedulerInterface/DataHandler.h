#ifndef DATA_HANDLER__H
#define DATA_HANDLER__H

#include <string>
#include <ctime>
#include <vector>
#include "DataStructures.h"

class DataHandler
{
private:
	DataHandler() {
		MYWM_DATAUPDATED = RegisterWindowMessage(L"Data updated");
		MYWM_DATACREATED = RegisterWindowMessage(L"Data created");
		MYWM_DATADELETED = RegisterWindowMessage(L"Data deleted");
		MYWM_DATA_ADDED = RegisterWindowMessage(L"Data added");
		MYWM_DATACLEARED = RegisterWindowMessage(L"Data cleared");
	};

public:
	UINT MYWM_DATAUPDATED = 0;
	UINT MYWM_DATACREATED = 0;
	UINT MYWM_DATADELETED = 0;
	UINT MYWM_DATA_ADDED = 0;
	UINT MYWM_DATACLEARED = 0;
	~DataHandler() {
	//REGISTER HANDLER_MESSAGES
	};


	std::vector<Data*>data;

	int amnt_events = 0;
	int amnt_todos = 0;
	int amnt_notes = 0;
	
	void AddModifyEvent(const char* name ,const char*description, time_t start, time_t end, const char* link, int id = -1);
	void AddModifyToDo(const char* name, const char*description, time_t expiration,bool completed = false, int id = -1);
	void SetToDoValue(bool val, int id);
	void AddModifyNote(const char* name, const char* description, int id = -1);

	Event* GetEvent(int id) {};
	ToDo* GetToDo(int id) {};
	Note* GetNote(int id) {};

	std::vector<Data*>* GetData() { return &data; };

	Data* GetEntry(int id);

	UINT GetNextID();

	//due to how the project is structured and the fact that whoever asks this has their own vector i feel like its better not to return the vector but fill it out
	//can't return all the data as that may result in data duplication or more than one pointer pointing the same place
	void GetAllEvents(std::vector<int>&);
	void GetAllToDos(std::vector<int>&);
	void GetAllNotes(std::vector<int>&);

	void RemoveElement(Data* data);
	void RemoveElement(int id);
	void ClearElements();

	void SaveToInI(const char* filename);
	void LoadFromInI(const char* filename);

	static DataHandler& Get();

};


#endif // !DATA_HANDLER__H

