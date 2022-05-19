#include "../../stdafx.h"

#include <CommCtrl.h>
#include <tchar.h>
#include "TableUI.h"
#include "../../StringToWstring.h"


void TableUI::AddColumn(LPWSTR name, int width, int align)
{
	LVCOLUMN lvc;
	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	LPWSTR szText = name;
	lvc.pszText = szText;
	lvc.cx = width;
	lvc.fmt = align;

	ListView_InsertColumn(listViewID, number_of_columns, &lvc);

	number_of_columns++;

}

void TableUI::AddItem(int args,int _row,bool set,...)//RETURN ITEM ID IN TABLE
{
	va_list cols;
	va_start(cols,set);

		LVITEMA itm;
		unsigned row;
		if (_row == -1)
		{
			row = ListView_GetItemCount(listViewID);

			PSTR empty = PSTR("");
			itm.mask = LVIF_TEXT | LVIF_PARAM;
			itm.iItem = row;
			itm.iSubItem = 0;
			itm.pszText = empty;
			itm.cchTextMax = 100;

			ListView_InsertItem(listViewID, &itm);
		}
		else
		{
			row = _row;
		}
		
		if (has_checkboxes)
		{
			ListView_SetCheckState(listViewID, row, set);
		}

	for (unsigned i = 0; i < args; i++)
	{
		std::string text_c =  va_arg(cols, char*);
		std::wstring str = s2ws(text_c);
		LPWSTR txt = (LPWSTR)str.c_str();
		ListView_SetItemText(listViewID, row, i,txt);
	}

	va_end(cols);
}

void TableUI::ClearItems()//ADD SPECIFIC ITEM DELETE
{
	ListView_DeleteAllItems(listViewID);

	//int iNumItems = ListView_GetItemCount(listViewID);
	//for (int iIndex = 0; iIndex < iNumItems; ++iIndex)
	//{
	//	ListView_DeleteItem(listViewID, 1);
	//	// update this item
	//}
}

void TableUI::RemoveItem(int id)
{
	ListView_DeleteItem(listViewID, id);
}

int TableUI::GetSelectedIndex()
{

	return ListView_GetNextItem(listViewID, -1, LVNI_SELECTED);

}

bool TableUI::GetCheckbox(int index)
{
	return ListView_GetCheckState(listViewID, index);
}

void TableUI::SetCheckbox(int index,bool sel)
{
	ListView_SetCheckState(listViewID, index, sel);
}

TableUI::TableUI(HWND parent_window, LPCWSTR name, int x, int y, int width, int height,bool checkboxes)
{
	listViewID = CreateWindowW(WC_LISTVIEW, name, WS_VISIBLE | WS_CHILD | WS_BORDER | LVS_REPORT | LVS_EDITLABELS, x, y, width, height, parent_window, (HMENU)NULL, NULL, NULL);

	if (checkboxes)
	{
		has_checkboxes = true;
		ListView_SetExtendedListViewStyle(listViewID, LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);
	}
	else
	{
		has_checkboxes = false;
		ListView_SetExtendedListViewStyle(listViewID, LVS_EX_FULLROWSELECT);
	}

}
