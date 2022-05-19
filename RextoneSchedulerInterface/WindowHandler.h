#ifndef WINDOW_HANDLER__H
#define WINDOW_HADNLER__H

#include "WindowClasses/Window.h"
#include <vector>

class WindowHandler {
private:
	WindowHandler() {};

public:

	~WindowHandler() {};
	std::vector<Window*> windows;
	std::vector<Window*> to_remove;

	void RegisterWindow(Window* to_reg);
	void ClearWindows();
	void SetupRemoveWindow(Window* w);
	void RemoveWindowFromArray();
	Window* GetWindowFromHandler(HWND handler);

	void EnableParent(Window* child);

	static WindowHandler& Get();

};


#endif // !WINDOW_HANDLER__H
