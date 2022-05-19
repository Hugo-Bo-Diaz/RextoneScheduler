#ifndef CALENDAR__H
#define CALENDAR__H
#include <Windows.h>
#include <CommCtrl.h>
#include <string>
#include <vector>
#include <time.h>

struct date {
	int mday;
	int month;
	int year;
};

class CalendarUI
{
public:
	CalendarUI() {};
	~CalendarUI() {};

	HWND CalendarID;

	void Initialize(HWND parent_window, LPCWSTR name, int x, int y, int width, int height, int height_label);
	date GetDate();
	void SetDate(time_t date);
;

private:

};

#endif