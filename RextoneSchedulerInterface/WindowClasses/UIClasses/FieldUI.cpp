#include "../../stdafx.h"

#include <CommCtrl.h>
#include <tchar.h>
#include "../../StringToWstring.h"
#include "FieldUI.h"


void FieldUI::Initialize(HWND parent_window, LPCWSTR name, int x, int y, int w_label, int w_field, int height, bool _only_numbers, bool editable, bool multiline)
{
	CreateWindowW(L"static", name, WS_VISIBLE | WS_CHILD | SS_RIGHT | SS_CENTERIMAGE, x, y, w_label, height, parent_window, NULL, NULL, NULL);
	only_numbers = _only_numbers;

	std::wstring mode = L"Edit";


	if (editable == false)
		mode = L"static";


	DWORD style = WS_VISIBLE | WS_CHILD | SS_LEFT | WS_TABSTOP;
	
	
	if (multiline)
	{
		if (editable)
		{
			style += ES_MULTILINE | ES_WANTRETURN;
		}
		else
		{
			style += BS_MULTILINE;
		}
	}
	else
	{
		style += SS_CENTERIMAGE;
	}

	if (only_numbers)
		style += ES_NUMBER;


	FieldID = CreateWindowW(mode.c_str(), L"", style, x+w_label, y, w_field, height, parent_window, NULL, NULL, NULL);

}

std::string FieldUI::GetFieldText()
{
	wchar_t buffer[300];
	GetWindowText(FieldID, buffer, 300);
	return ws2s(buffer);
}

int FieldUI::GetFieldNumber()
{
	if(only_numbers==false)
		return -1;

	wchar_t buffer[20];//20 figure number
	GetWindowText(FieldID, buffer, 20);
	std::string ret = ws2s(buffer);

	if (ret.length() == 0)
		return -1;

	return std::stoi(ret);
	
}

void FieldUI::SetFieldText(const char * newtext)
{
	std::wstring wstr = s2ws(newtext);
	SetWindowText(FieldID, wstr.c_str());

}
