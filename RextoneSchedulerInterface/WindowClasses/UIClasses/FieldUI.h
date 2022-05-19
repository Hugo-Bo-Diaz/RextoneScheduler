#ifndef FIELD__H
#define FIELD__H
#include <Windows.h>
#include <CommCtrl.h>
#include <string>
#include <vector>
class FieldUI
{
public:

	HWND FieldID;
	bool only_numbers = false;
	
	FieldUI() {};
	void Initialize(HWND parent_window,LPCWSTR name, int x, int y, int w_label, int w_field,int height,bool only_numbers = false,bool editable = true, bool multiline = false);
	~FieldUI() {};

	std::string GetFieldText();//MAX 300 CHAR
	int GetFieldNumber();//RETURNS -1 IF IT ALLOWS STRINGS
	void SetFieldText(const char*);
private:

};

#endif