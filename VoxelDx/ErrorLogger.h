#pragma once
#include "StringHelper.h"
#include <Windows.h>

class ErrorLogger
{
public:
	static void Log(std::string info);
	static void Log(HRESULT hr, std::string info);
	static void Log(HRESULT hr, std::wstring info);
};

