#ifndef STRING__TO__WSTRING__H
#define STRING__TO__WSTRING__H

#include <string>
#include <stringapiset.h>

std::wstring s2ws(const std::string& str);
std::string ws2s(const std::wstring& wstr);

#endif // !STRING__TO__WSTRING__H



