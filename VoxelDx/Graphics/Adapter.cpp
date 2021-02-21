#include "Adapter.h"

std::vector<AdapterData> Adapter::adapters;

std::vector<AdapterData> Adapter::getAdapterData()
{
	if (adapters.size() > 0)
		return adapters;

	Microsoft::WRL::ComPtr<IDXGIFactory> pFactory;
	HRESULT hr = CreateDXGIFactory(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pFactory.GetAddressOf()));
	if (FAILED(hr)) {
		ErrorLogger::Log(hr, "Failed to create DXGIFactory");
		exit(-1);
	}

	IDXGIAdapter* pAdapter;
	UINT index = 0;
	while (SUCCEEDED(pFactory->EnumAdapters(index, &pAdapter))) {
		adapters.push_back(AdapterData(pAdapter));
		index++;
	}

	return adapters;
}

AdapterData::AdapterData(IDXGIAdapter* adapter)
{
	this->pAdapter = adapter;
	HRESULT hr = this->pAdapter->GetDesc(&this->desc);
	if (FAILED(hr)) {
		ErrorLogger::Log(GetLastError(), "Failed to get adapter description.");
	}
}
