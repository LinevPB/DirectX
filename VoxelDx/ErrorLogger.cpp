#include "ErrorLogger.h"
#include <comdef.h>

void ErrorLogger::Log(std::string info)
{
	MessageBoxA(NULL, info.c_str(), "Error", MB_ICONERROR);
}

void ErrorLogger::Log(HRESULT hr, std::string info)
{
	_com_error error(hr);

	std::wstring error_msg = L"Error: " + StringHelper::StringToWide(info) + L"\n" + error.ErrorMessage() + L"\n";
	MessageBoxW(NULL, error_msg.c_str(), L"Error", MB_ICONERROR);
}