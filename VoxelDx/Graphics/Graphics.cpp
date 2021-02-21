#include "Graphics.h"

bool Graphics::Initialize(HWND hwnd, int width, int height)
{
    if (!InitializeDX(hwnd, width, height))
        return false;

    return true;
}

void Graphics::Render()
{
    const float bgcolor[] = { 0.0f, 0.0f, 0.4f, 1.0f };
    this->deviceContext->ClearRenderTargetView(renderTargetView.Get(), bgcolor);
    this->swapChain->Present(1, NULL);
}

bool Graphics::InitializeDX(HWND hwnd, int width, int height)
{
    std::vector<AdapterData> adapters = Adapter::getAdapterData();

    if (adapters.size() < 1) {
        ErrorLogger::Log("Failed to locate any adapter");
        exit(-1);
    }

    DXGI_SWAP_CHAIN_DESC scd;
    ZeroMemory(&scd, sizeof(scd));
    scd.BufferDesc.Width = width;
    scd.BufferDesc.Height = height;
    scd.BufferDesc.RefreshRate.Denominator = 1;
    scd.BufferDesc.RefreshRate.Numerator = 60;
    scd.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    scd.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
    scd.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;

    scd.SampleDesc.Count = 1;
    scd.SampleDesc.Quality = 0;

    scd.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    scd.BufferCount = 1;
    scd.OutputWindow = hwnd;
    scd.Windowed = TRUE;
    scd.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;
    scd.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

   HRESULT hr = D3D11CreateDeviceAndSwapChain(adapters[0].pAdapter, D3D_DRIVER_TYPE_UNKNOWN,
        NULL, NULL,
        0, NULL,
        D3D11_SDK_VERSION,
        &scd, &swapChain,
        &device, NULL, &deviceContext);

   if (FAILED(hr)) {
       ErrorLogger::Log(hr, "Failed to create device and swap chain.");
       return false;
   }

   Microsoft::WRL::ComPtr<ID3D11Texture2D> backBuffer;
   hr = this->swapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(backBuffer.GetAddressOf()));
   if (FAILED(hr)) {
       ErrorLogger::Log(hr, "Failed to get address of back buffer for swap chain.");
       return false;
   }

   hr = this->device->CreateRenderTargetView(backBuffer.Get(), NULL, this->renderTargetView.GetAddressOf());
   if (FAILED(hr)) {
       ErrorLogger::Log(hr, "Failed to create render target view");
       return false;
   }

   this->deviceContext->OMSetRenderTargets(1, renderTargetView.GetAddressOf(), NULL);

    return true;
}
