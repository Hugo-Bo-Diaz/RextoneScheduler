#include "stdafx.h"
#include "Settings.h"
#include "WindowHandler.h"
#include "WindowClasses/WindowClass.h"
#include "WindowClasses/SettingsWindow.h"

#include "DirectoryPaths.h"

Settings* set = nullptr;

Settings & Settings::Get()
{
	if (set == nullptr)
		set = new Settings();

	return *set;
}

Setting * Settings::GetFromName(const char * name)
{
	std::string temp = name;
	for (Setting* set : settings)
	{
		if (set->name == temp)
		{
			return set;
		}
	}
	return nullptr;
}

void Settings::SetSettingsValue(const char * name, int value)
{
	Setting* set = GetFromName(name);
	
	if (set != nullptr)
	{
		set->value = value;
	}
	else
	{
		set = new Setting();
		set->name = name;
		set->value = value;
		settings.push_back(set);
	}
}


int Settings::GetSettingsValue(const char * setting, int defaultvalue)
{
	Setting* set = GetFromName(setting);

	if(set != nullptr)
		return set->value;
	else
		return defaultvalue;
}

void Settings::ClearSettings()
{
	for (Setting* s : settings)
	{
		if (s != nullptr)
			delete s;
	}
	settings.clear();
}

void Settings::SpawnSettingsWindow(WindowClass * Wclass, Window* parent)
{

	SettingsWindow* SetW = new SettingsWindow(parent);
	WindowHandler::Get().RegisterWindow(SetW);
	SetW->Initialize(Wclass, L"Rextone scheduler settings", CW_USEDEFAULT, CW_USEDEFAULT, 300, 350, WS_VISIBLE | WS_MINIMIZEBOX | WS_SYSMENU);
	SetW->GetSettingsOnWindow();

}

void Settings::SaveSettings(const char * file)
{
	ClearInI(file);

	std::wstring fulldir = DocumentsPath() + s2ws(file);

	int it = 0;
	for (Setting* s : settings)
	{
		std::wstring sec = L"sett " + std::to_wstring(it);

		std::wstring name = s2ws(s->name);
		WritePrivateProfileString(sec.c_str(), L"name", name.c_str(), fulldir.c_str());

		std::wstring value = std::to_wstring(s->value);
		WritePrivateProfileString(sec.c_str(), L"value", value.c_str(), fulldir.c_str());

		++it;
	}

}

void Settings::LoadSettings(const char * file)
{
	ClearSettings();

	//	std::wstring fulldir = ExePath() + L"/" + s2ws(filename);
	std::wstring fulldir = DocumentsPath() + s2ws(file);

	TCHAR buffer[500];

	int iter = 0;
	bool stop = false;

	while (!stop)
	{
		std::wstring temp;
		temp = L"sett " + std::to_wstring(iter);
		int value = GetPrivateProfileInt(temp.c_str(), L"value", -1, fulldir.c_str());

		int namesize = GetPrivateProfileString(temp.c_str(), L"name", L"", buffer, ARRAYSIZE(buffer), fulldir.c_str());
		std::string name = ws2s(buffer);

		if (namesize <= 0)
		{
			stop = true;
			break;
		}

		SetSettingsValue(name.c_str(),value);

		++iter;
	}
}
