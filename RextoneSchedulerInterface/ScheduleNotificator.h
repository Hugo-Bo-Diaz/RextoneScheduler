#ifndef SCHEDULE_NOTIFICATOR__H
#define SCHEDULE_NOTIFICATOR__H

#define TIME_THRESHHOLD 3600

#include <list>

struct Data;
class WindowClass;

struct DataToNotify {
	DataToNotify(int _id, time_t happening, time_t end = 0) {
		id = _id;
		time_happening = happening;

		time_ending = end;
		if (time_ending == 0)
			time_ending = happening;
	}

	int id;
	time_t time_happening;
	time_t time_ending;
};

class ScheduleNotificator
{
public:
	ScheduleNotificator();
	~ScheduleNotificator();

	HWND CommWindow;
	WindowClass* Wclass;

	UINT IDTIMER_CHECK;
	std::list<DataToNotify> DataToHappen;

	void GetEvents();
	bool IsDataOnNotifyList(Data* d);

	void Initialize(HINSTANCE);

	static ScheduleNotificator& Get();

};


LRESULT CALLBACK TimerFuncCheckTimes(HWND, UINT, WPARAM, LPARAM);



#endif // !SCHEDULE_NOTIFICATOR__H