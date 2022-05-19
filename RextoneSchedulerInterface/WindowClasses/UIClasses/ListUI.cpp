#include "../../stdafx.h"

#include "ListUI.h"

#include "../../StringToWstring.h"


void ListUI::AddItem(const char * text)
{
	std::wstring ws = s2ws(text);

	SendMessage(listBoxID, LB_ADDSTRING, 0, (LPARAM)ws.c_str());
}

void ListUI::ClearItems()
{
	int length = GetTableLenght();
	for (size_t i = 0; i < length; i++)
	{
		SendMessage(listBoxID, LB_DELETESTRING, 0, NULL);
	}
}

void ListUI::RemoveItem(int id)
{
	SendMessage(listBoxID, LB_DELETESTRING, id, NULL);

}

int ListUI::GetTableLenght()
{
	return SendMessage(listBoxID, LB_GETCOUNT, NULL, NULL);
}

int ListUI::GetSelectedIndex()
{
	return SendMessage(listBoxID,LB_GETCURSEL,NULL,NULL);
}

ListUI::ListUI(HWND parent_window, LPCWSTR name, int x, int y, int width, int height)
{
	listBoxID = CreateWindowW(WC_LISTBOX, name, WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | WS_HSCROLL , x, y, width, height, parent_window, (HMENU)NULL, NULL, NULL);

	SendMessage(listBoxID, LB_SETCOLUMNWIDTH, width, NULL);
}
