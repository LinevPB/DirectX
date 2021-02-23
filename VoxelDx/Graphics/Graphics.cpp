#include "Graphics.h"

bool Graphics::Initialize(HWND hwnd, int width, int height)
{
    if (!InitializeDX(hwnd, width, height))
        return false;

    if (!InitializeShaders())
        return false;

    if (!InitializeScene())
        return false;

    return true;
}

void Graphics::Render()
{
    const float bgcolor[] = { 0.0f, 0.0f, 0.4f, 1.0f };
    this->deviceContext->ClearRenderTargetView(renderTargetView.Get(), bgcolor);

    this->deviceContext->IASetInputLayout(this->vshader.getInputLayout());
    this->deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D10_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

    this->deviceContext->VSSetShader(vshader.getShader(), NULL, 0);
    this->deviceContext->PSSetShader(pshader.getShader(), NULL, 0);

    UINT stride = sizeof(Vertex);
    UINT offset = 0;
    this->deviceContext->IASetVertexBuffers(0, 1, vertexBuffer.GetAddressOf(), &stride, &offset);

    this->deviceContext->Draw(3, 0);

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
        NULL, 0,
        D3D11_SDK_VERSION,
        &scd, swapChain.GetAddressOf(),
        device.GetAddressOf(), NULL, deviceContext.GetAddressOf());

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

   D3D11_VIEWPORT viewport;
   ZeroMemory(&viewport, sizeof(D3D11_VIEWPORT));

   viewport.TopLeftX = 0;
   viewport.TopLeftY = 0;
   viewport.Width = width;
   viewport.Height = height;

   this->deviceContext->RSSetViewports(1, &viewport);

   return true;
}

bool Graphics::InitializeShaders()
{
    std::wstring shaderFolder;
#pragma region locateShaderFolder
    if (IsDebuggerPresent()) {
#ifdef _DEBUG
    #ifdef _WIN64
        shaderFolder = L"..\\x64\\Debug\\";
    #else
        shaderFolder = L"..\\Debug\\";
    #endif
#else
    #ifdef _WIN64
        shaderFolder = L"..\\x64\\Release\\";
    #else
        shaderFolder = L"..\\Release\\";
    #endif
#endif
    }

    D3D11_INPUT_ELEMENT_DESC layout[] = {
        {"POSITION", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT, 0, 0, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0 },
        {"COLOR", 0, DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT, 0, D3D11_APPEND_ALIGNED_ELEMENT, D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA, 0}
    };

    UINT numElements = ARRAYSIZE(layout);
    if (!vshader.Initialize(device, shaderFolder + L"vertexShader.cso", layout, numElements))
        return false;

    if (!pshader.Initialize(device, shaderFolder + L"pixelShader.cso"))
        return false;

    return true;
}

bool Graphics::InitializeScene()
{
    Vertex v[] = {
        Vertex(-0.5f, -0.5f, 0.0f, 0.0f, 1.0f),
        Vertex(0.0f, 0.5f, 0.0f, 1.0f, 0.0f ),
        Vertex(0.5f, -0.5f, 1.0f, 0.0f, 0.0f )
    };

    D3D11_BUFFER_DESC desc;
    ZeroMemory(&desc, sizeof(desc));

    desc.Usage = D3D11_USAGE_DEFAULT;
    desc.ByteWidth = sizeof(Vertex) * ARRAYSIZE(v);
    desc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
    desc.CPUAccessFlags = 0;
    desc.MiscFlags = 0;

    D3D11_SUBRESOURCE_DATA data;
    ZeroMemory(&data, sizeof(data));

    data.pSysMem = v;

    HRESULT hr = device->CreateBuffer(&desc, &data, vertexBuffer.GetAddressOf());
    if (FAILED(hr)) {
        ErrorLogger::Log(hr, "Failed to create vertex buffer");
        return false;
    }

    return true;
}
