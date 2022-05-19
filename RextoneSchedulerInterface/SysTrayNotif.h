#ifndef TRAY_NOTIFICATION
#define TRAY_NOTIFICATION

#include <Windows.h>
#include <queue>
#include <shellapi.h>

LRESULT CALLBACK SysTrayProcedure(HWND, UINT, WPARAM, LPARAM);

class WindowClass;

enum SysTrayMsg {
	ST_NONE,

	ST_SETTINGS,//OPEN SETTINGS WINDOW
	ST_WAKE_UP,//WAKE UP MAIN WINDOW AGAIN

	ST_EXIT//EXIT APPLICATION
};

enum SysTrayButtons {
	STB_EXIT,
	STB_OPEN,
	STB_SETTINGS,
};

class SysTrayNotif
{
public:
	SysTrayNotif();
	~SysTrayNotif();

	HWND CommWindow;
	UINT MYWM_SYSTRAY_NOTIF;

	WindowClass* Wclass;
	NOTIFYICONDATA ndata;

	void Initialize(HINSTANCE);

	static SysTrayNotif&Get();
	void ShutDown();
	SysTrayMsg curr_state;

	std::queue<SysTrayMsg> msgqueue;
	SysTrayMsg GetNextMessage();

	void AddTrayMenu();

	void SendNotification(const wchar_t* title, const wchar_t* text);
};



#endif // !TRAY_NOTIFICATION
