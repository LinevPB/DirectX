#pragma once
#include "../ErrorLogger.h"
#include <wrl/client.h>
#include <d3d11.h>
#include <vector>

class AdapterData
{
public:
	AdapterData(IDXGIAdapter* adapter);
	IDXGIAdapter* pAdapter = nullptr;
	DXGI_ADAPTER_DESC desc;
};

class Adapter
{
public:
	static std::vector<AdapterData> getAdapterData();

private:
	static std::vector<AdapterData> adapters;
};