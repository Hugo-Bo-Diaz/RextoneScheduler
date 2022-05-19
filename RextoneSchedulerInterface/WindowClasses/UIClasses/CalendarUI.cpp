#include "../../stdafx.h"
#include "../../WindowHandler.h"

#include <CommCtrl.h>
#include <tchar.h>
#include "CalendarUI.h"
#include "../../StringToWstring.h"

date CalendarUI::GetDate() {
	//WS_TABSTOP

	SYSTEMTIME st{};

	DateTime_GetSystemtime(CalendarID, &st);
	
	return {st.wDay,st.wMonth,st.wYear};
}
void CalendarUI::SetDate(time_t date) {

	SYSTEMTIME st{};

	tm* ttime = localtime(&date);
	st.wDay = ttime->tm_mday;
	st.wMonth = ttime->tm_mon+1;
	st.wYear = ttime->tm_year+1900;

	DateTime_SetSystemtime(CalendarID, GDT_VALID, &st);
}

void CalendarUI::Initialize(HWND parent_window, LPCWSTR name, int x, int y, int width, int height, int height_label)
{

	CreateWindowW(L"static", name, WS_VISIBLE | WS_CHILD | SS_CENTER | SS_CENTERIMAGE, x, y, width, height, parent_window, NULL, NULL, NULL);
	CalendarID = CreateWindowEx(0, DATETIMEPICK_CLASS,L"",		WS_VISIBLE | WS_CHILD| WS_TABSTOP , x, y+height_label, width, height,parent_window, NULL, NULL, NULL);
}