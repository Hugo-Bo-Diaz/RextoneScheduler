#ifndef TABLE__H
#define TABLE__H
#include <Windows.h>
#include <CommCtrl.h>
#include <string>
#include <vector>
class TableUI
{
public:

	HWND listViewID;
	int number_of_columns = 0;
	bool has_checkboxes;

	void AddColumn(LPWSTR name, int width, int align = LVCFMT_LEFT);
	void AddItem(int args,int row = -1,bool checked = false,...);
	void ClearItems();
	void RemoveItem(int id);

	int GetTableLenght() {};
	int GetSelectedIndex();

	bool GetCheckbox(int index);
	void SetCheckbox(int index,bool sel);

	TableUI(HWND parent_window,LPCWSTR name, int x, int y, int width, int height,bool checkboxes = false);
	~TableUI() {};

private:

};

#endif