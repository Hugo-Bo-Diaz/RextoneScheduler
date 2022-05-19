#ifndef LIST_UI__H
#define LIST_UI__H
#include <Windows.h>
#include <CommCtrl.h>
#include <string>
#include <vector>

class ListUI
{
public:
	HWND listBoxID;

	void AddItem(const char*);
	void ClearItems();
	void RemoveItem(int id);

	int GetTableLenght();
	int GetSelectedIndex();

	ListUI(HWND parent_window, LPCWSTR name, int x, int y, int width, int height);
	~ListUI() {};

};

#endif // !LIST_UI__H
