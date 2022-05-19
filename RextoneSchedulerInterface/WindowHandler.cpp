#include "stdafx.h"
#include "WindowHandler.h"

WindowHandler* Whand = nullptr;

WindowHandler& WindowHandler::Get()
{
	if (Whand == nullptr)
		Whand = new WindowHandler();

	return *Whand;

}

void WindowHandler::RegisterWindow(Window* to_reg)
{
	windows.push_back(to_reg);
};

void WindowHandler::ClearWindows()
{
	for (Window* var : windows)
	{
		if (var != nullptr)
		{
			delete var;
		}
	}
	windows.clear();
};


void WindowHandler::SetupRemoveWindow(Window*w)
{
	to_remove.push_back(w);
};


void WindowHandler::RemoveWindowFromArray()
{
	for (Window* i : to_remove)
	{
		auto it = std::find(windows.begin(), windows.end(), i);
		if (it != windows.end() && i != nullptr)
		{
			delete i;
			windows.erase(it);
		}
	}
	to_remove.clear();
}

Window* WindowHandler::GetWindowFromHandler(HWND handler) {

	for (Window* var : windows)
	{
		if (var->Whandler == handler)
		{
			return var;
		}
	}
	return nullptr;
};

void WindowHandler::EnableParent(Window* child)
{
	Window* parent = child->parent;
	if (parent == nullptr)
		return;

	//checking if the parent should be enable because of more windows having the same parent, which is rare case but wanted to take it into account
	int number_of_windows_with_children_parent = 0;
	for (Window* w : windows) {
		if (w->parent == parent)
			number_of_windows_with_children_parent++;
	}

	if (number_of_windows_with_children_parent == 1) {
		EnableWindow(parent->Whandler, true);
		BringWindowToTop(parent->Whandler);
	}
}