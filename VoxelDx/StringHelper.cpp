#include "StringHelper.h"

std::wstring StringHelper::StringToWide(std::string text)
{
	std::wstring wstr(text.begin(), text.end());

	return wstr;
}