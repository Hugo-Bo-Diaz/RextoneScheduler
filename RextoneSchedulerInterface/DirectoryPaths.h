#ifndef DIRECTORY_PATHS__H
#define DIRECTORY_PATHS__H

#include <WinBase.h>
#include <filesystem>
#include <string>
#include "StringToWstring.h"

std::wstring ExePath();

std::wstring DocumentsPath();


void ClearInI(const char* filename);


#endif // !DIRECTORY_PATHS__H