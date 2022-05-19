#ifndef DATA_STRUCTURES__H
#define DATA_STRUCTURES__H

enum DataType{
	DT_event,
	DT_ToDo,
	DT_note
};

struct Data
{
	int id;
	DataType type;
	std::string name;
	std::string description;

	virtual void SaveToIni(const wchar_t* filename, const wchar_t* section) {};
};


struct Event : public Data {

	time_t time_start;
	time_t time_end;
	std::string link;

	Event() { type = DT_event; }

	void SaveToIni(const wchar_t* filename, const wchar_t* section);

};

struct ToDo : public Data {

	bool completed;
	time_t expiration;

	ToDo() { type = DT_ToDo; }

	void SaveToIni(const wchar_t* filename, const wchar_t* section);

};

struct Note : public Data {

	Note() { type = DT_note; }

	void SaveToIni(const wchar_t* filename, const wchar_t* section);
};

#endif // !DATA_STRUCTURES__H
