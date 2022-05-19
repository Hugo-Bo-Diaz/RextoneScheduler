#include "stdafx.h"
#include "DirectoryPaths.h"


std::wstring ExePath() {
	TCHAR buffer[MAX_PATH] = { 0 };
	GetModuleFileName(NULL, buffer, MAX_PATH);
	std::wstring::size_type pos = std::wstring(buffer).find_last_of(L"\\/");
	return std::wstring(buffer).substr(0, pos);
}

std::wstring DocumentsPath() {
	std::wstring userpath = s2ws(getenv("USERPROFILE"));
	userpath += L"\\Documents\\RextoneSchedulerData\\";
	CreateDirectory(userpath.c_str(),NULL);
	return userpath;
}


void ClearInI(const char* filename) {
	//std::wstring fulldir = ExePath() + L"/" + s2ws(filename);
	std::wstring fulldir = DocumentsPath() + s2ws(filename);

	//https://www.codeproject.com/Questions/352159/Reading-all-section-names-from-ini-file-using-GetP
	//SOLUTION 4 FROM HERE

	TCHAR * lpszReturnBuffer;
	lpszReturnBuffer = new TCHAR[200];
	int iCnt = GetPrivateProfileSectionNames(lpszReturnBuffer, 200, fulldir.c_str());

	for (int i = 0; i<iCnt; i++)
	{
		if (lpszReturnBuffer[i] == '\0') //find null char
		{
			lpszReturnBuffer[i] = '^';//and replace it to separator.. whatever you want...
		}
	}
	std::string sections = ws2s(lpszReturnBuffer);
	std::string sec;
	size_t iPosEnd = sections.find('^');//find first separator
	size_t iPosStart = 0;
	while (iPosEnd != std::string::npos)
	{
		sec = sections.substr(iPosStart, iPosEnd - iPosStart);//sub string..
		std::wstring to_del = s2ws(sec);
		WritePrivateProfileString(to_del.c_str(), NULL, NULL, fulldir.c_str());
		iPosStart = iPosEnd + 1;
		iPosEnd = sections.find('^', iPosStart);
	}

}