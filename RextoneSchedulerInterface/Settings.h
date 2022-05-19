#ifndef SETTINGS__H
#define SETTINGS__H

#include <string>
#include <vector>
#include <Windows.h>

class WindowClass;
class Window;

struct Setting {
	std::string name;
	int value;
};

class Settings
{
private:
	Settings() {};
	std::vector<Setting*> settings;

	Setting* GetFromName(const char*);
public:
	~Settings() {};
	void SetSettingsValue(const char* name, int value);
	int GetSettingsValue(const char* setting,int defaultvalue =-1);
	void ClearSettings();

	void SpawnSettingsWindow(WindowClass* Wclass, Window* parent = nullptr);

	void SaveSettings(const char* file);
	void LoadSettings(const char* file);

	static Settings& Get();
};
#endif // !SETTINGS__H