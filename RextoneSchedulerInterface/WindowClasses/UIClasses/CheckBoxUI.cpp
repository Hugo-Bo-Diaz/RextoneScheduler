#include "../../stdafx.h"
#include "CheckBoxUI.h"

#include <Windows.h>
#include <CommCtrl.h>
#include <tchar.h>

CheckBoxUI::CheckBoxUI()
{
}

void CheckBoxUI::Initialize(HWND _parent, LPCWSTR text, int x, int y, int w, int h)
{
	checkboxID = CreateWindowW(L"button", text ,WS_VISIBLE|WS_CHILD | BS_AUTOCHECKBOX | WS_TABSTOP,x,y,w,h,_parent,NULL,NULL,NULL);

}


CheckBoxUI::~CheckBoxUI()
{
}

bool CheckBoxUI::isChecked()
{
	UINT state = SendMessage(checkboxID, BM_GETCHECK, 0, 0);

	if (state == BST_CHECKED)
		return true;
	else
		return false;
}

void CheckBoxUI::SetCheck(bool on)
{
	if (on)
		SendMessage(checkboxID, BM_SETCHECK, BST_CHECKED, 0);
	else
		SendMessage(checkboxID, BM_SETCHECK, BST_UNCHECKED, 0);

}
