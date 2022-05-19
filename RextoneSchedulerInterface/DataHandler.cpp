#include "stdafx.h"
#include "DataHandler.h"
#include "StringToWstring.h"

#include "DirectoryPaths.h"

DataHandler* Dhand = nullptr;


DataHandler& DataHandler::Get()
{
	if (Dhand == nullptr)
		Dhand = new DataHandler();

	return *Dhand;
}

void DataHandler::SaveToInI(const char * filename)
{
	ClearInI(filename);

	std::wstring fulldir =ExePath()+ L"/" + s2ws(filename);
	//std::wstring fulldir = DocumentsPath() + s2ws(filename);

	int it = 0;

	for (Data* d : data)
	{
		std::wstring sec = L"s" + std::to_wstring(it++);

		std::wstring temp;

		temp = s2ws(d->name);
		WritePrivateProfileString(sec.c_str(), L"Name", temp.c_str(), fulldir.c_str());
		temp = s2ws(d->description);
		WritePrivateProfileString(sec.c_str(), L"Desc", temp.c_str(), fulldir.c_str());
		temp = std::to_wstring(d->id);
		WritePrivateProfileString(sec.c_str(), L"ID", temp.c_str(), fulldir.c_str());

		d->SaveToIni(fulldir.c_str(), sec.c_str());

	}

}



void Event::SaveToIni(const wchar_t* filename, const wchar_t* section)
{
	std::wstring temp;
	temp = std::to_wstring((int)type);
	WritePrivateProfileString(section, L"Type",temp.c_str() , filename);

	temp = std::to_wstring(time_start);
	WritePrivateProfileString(section, L"Start", temp.c_str(), filename);

	temp = std::to_wstring(time_end);
	WritePrivateProfileString(section, L"End", temp.c_str(), filename);

	temp = s2ws(link);
	WritePrivateProfileString(section, L"Link", temp.c_str(), filename);
}

void ToDo::SaveToIni(const wchar_t* filename, const wchar_t* section)
{
	std::wstring temp;
	temp = std::to_wstring((int)type);
	WritePrivateProfileString(section, L"Type", temp.c_str(), filename);

	temp = std::to_wstring(completed);
	WritePrivateProfileString(section, L"Compl", temp.c_str(), filename);

	temp = std::to_wstring(expiration);
	WritePrivateProfileString(section, L"Expir", temp.c_str(), filename);
}

void Note::SaveToIni(const wchar_t* filename, const wchar_t* section)
{
	std::wstring temp;
	temp = std::to_wstring((int)type);
	WritePrivateProfileString(section, L"Type", temp.c_str(), filename);
}




void DataHandler::LoadFromInI(const char * filename)
{
	ClearElements();

	std::wstring fulldir = ExePath() + L"/" + s2ws(filename);
	//std::wstring fulldir = DocumentsPath() + s2ws(filename);


	TCHAR buffer[500];
	
	int iter = 0;
	bool stop = false;

	while (!stop)
	{
		std::wstring temp;
		temp = L"s"+ std::to_wstring(iter);
		int type = GetPrivateProfileInt(temp.c_str(), L"Type", -1, fulldir.c_str());

		Data* entry = nullptr;

		switch ((DataType)type)
		{
		case DataType::DT_event:
			entry = new Event();

			((Event*)entry)->time_start = GetPrivateProfileInt(temp.c_str(), L"Start", -1, fulldir.c_str());
			((Event*)entry)->time_end = GetPrivateProfileInt(temp.c_str(), L"End", -1, fulldir.c_str());
			GetPrivateProfileString(temp.c_str(), L"Link", L"", buffer, ARRAYSIZE(buffer), fulldir.c_str());
			((Event*)entry)->link = ws2s(buffer);

			break;
		case DataType::DT_ToDo:
			entry = new ToDo();

			((ToDo*)entry)->completed = GetPrivateProfileInt(temp.c_str(), L"Compl", 0, fulldir.c_str());
			((ToDo*)entry)->expiration = GetPrivateProfileInt(temp.c_str(), L"Expir", -1, fulldir.c_str());

			break;
		case DataType::DT_note:
			entry = new Note();
			
			break;
		default:
			stop = true;
			break;
		}

		if (entry != nullptr)
		{
			GetPrivateProfileString(temp.c_str(), L"Name", L"", buffer, ARRAYSIZE(buffer), fulldir.c_str());
			entry->name = ws2s(buffer);
			GetPrivateProfileString(temp.c_str(), L"Desc", L"", buffer, ARRAYSIZE(buffer), fulldir.c_str());
			entry->description = ws2s(buffer);
			entry->id= GetPrivateProfileInt(temp.c_str(), L"ID", 0, fulldir.c_str());

			data.push_back(entry);
		}

		iter += 1;
	}

	PostMessage(HWND_BROADCAST, MYWM_DATACREATED, NULL, NULL);

}


void DataHandler::AddModifyEvent(const char * name, const char * description, time_t start, time_t end, const char * link, int id)
{
	Event* ev;
	if (id!=-1)
	{
		ev = (Event*)GetEntry(id);
		if (ev == nullptr)
			return;
	}
	else
	{
		ev = new Event();
		ev->id = GetNextID();
	}
	ev->name = name;
	ev->description = description;
	ev->link = link;
	ev->time_start = start;
	ev->time_end = end;

	if (id != -1)
	{
		SendMessage(HWND_BROADCAST, MYWM_DATAUPDATED, NULL, ev->id);
	}
	else
	{
		data.push_back(ev);
		SendMessage(HWND_BROADCAST, MYWM_DATA_ADDED, NULL, ev->id);
	}


}

//void DataHandler::ModifyEvent(int id, const char * name, const char * description, time_t start, time_t end, const char * link)
//{
//	//IMPROVEMENT ADD SECURITY TO MAKE SURE ITS CASTABLE
//	Event* ev = (Event*)GetEntry(id);
//
//	if (ev == nullptr)
//		return;
//
//	ev->name = name;
//	ev->description = description;
//	ev->link = link;
//	ev->time_start = start;
//	ev->time_end = end;
//
//	SendMessage(HWND_BROADCAST, MYWM_DATAUPDATED, NULL, ev->id);
//}

void DataHandler::AddModifyToDo(const char * name, const char * description, time_t expiration,bool completed,int id)
{
	ToDo* td;
	if (id != -1)
	{
		td = (ToDo*)GetEntry(id);
		if (td == nullptr)
			return;
	}
	else
	{
		td = new ToDo();
		td->id = GetNextID();
	}

	td->name = name;
	td->description = description;
	td->expiration = expiration;
	td->completed = completed;
	
	if (id != -1)
	{
		SendMessage(HWND_BROADCAST, MYWM_DATAUPDATED, NULL, td->id);
	}
	else
	{
		data.push_back(td);
		SendMessage(HWND_BROADCAST, MYWM_DATA_ADDED, NULL, td->id);
	}


}

void DataHandler::SetToDoValue(bool val, int id)
{
	ToDo* td;
	if (id != -1)
	{
		td = (ToDo*)GetEntry(id);
		if (td == nullptr)
			return;
	}
	else
	{
		return;
	}
	td->completed = val;
}

//void DataHandler::ModifyToDo(int id, const char * name, const char * description, time_t expiration)
//{
//	ToDo* td = (ToDo*)GetEntry(id);
//
//	if (td == nullptr)
//		return;
//
//	td->name = name;
//	td->description = description;
//	td->expiration = expiration;
//	td->completed = false;
//
//	SendMessage(HWND_BROADCAST, MYWM_DATAUPDATED, NULL, td->id);
//}

void DataHandler::AddModifyNote(const char * name, const char * description, int id)
{
	Note* nt;
	if (id != -1)
	{
		nt = (Note*)GetEntry(id);
		if (nt == nullptr)
			return;
	}
	else
	{
		nt = new Note();
		nt->id = GetNextID();
	}

	nt->name = name;
	nt->description = description;


	if (id != -1)
	{
		SendMessage(HWND_BROADCAST, MYWM_DATAUPDATED, NULL, nt->id);
	}
	else
	{
		data.push_back(nt);
		SendMessage(HWND_BROADCAST, MYWM_DATA_ADDED, NULL, nt->id);
	}

}

//void DataHandler::ModifyNote(int id, const char * name, const char * description)
//{
//	Note* nt = (Note*)GetEntry(id);
//	nt->name = name;
//	nt->description = description;
//
//	SendMessage(HWND_BROADCAST, MYWM_DATAUPDATED, NULL, nt->id);
//}

Data * DataHandler::GetEntry(int id)
{
	for (Data* d : data)
	{
		if (d->id == id)
			return d;
	}

	return nullptr;
}

UINT DataHandler::GetNextID()
{
	int highestID = 0;
	for (Data* d :data)
	{
		if (d->id > highestID)
			highestID = d->id;
	}

	return highestID+1;
}

void DataHandler::GetAllEvents(std::vector<int>& to_fill)
{
	for (Data* d : data)
	{
		if (d->type == DataType::DT_event)
			to_fill.push_back(d->id);
	}
}

void DataHandler::GetAllToDos(std::vector<int>& to_fill)
{
	for (Data* d : data)
	{
		if (d->type == DataType::DT_ToDo)
			to_fill.push_back(d->id);
	}
}

void DataHandler::GetAllNotes(std::vector<int>& to_fill)
{
	for (Data* d : data)
	{
		if (d->type == DataType::DT_note)
			to_fill.push_back(d->id);
	}
}


void DataHandler::RemoveElement(int id)
{
	Data* to_del = nullptr;
	for (Data* d : data)
	{
		if (d->id == id)
			to_del = d;
	}

	RemoveElement(to_del);

}

void DataHandler::RemoveElement(Data * to_del)
{
	if (to_del != nullptr)
	{
		SendMessage(HWND_BROADCAST, MYWM_DATADELETED, NULL, to_del->id);
		delete to_del;
	}
	data.erase(std::remove(data.begin(), data.end(), to_del),data.end());

}

void DataHandler::ClearElements()
{
	for (Data* d : data)
	{
		if(d != nullptr)
			delete d;
	}

	data.clear();

	PostMessage(HWND_BROADCAST, MYWM_DATACLEARED, NULL, NULL);

}
