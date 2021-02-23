#include "Shaders.h"

bool VertexShader::Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring filePath, D3D11_INPUT_ELEMENT_DESC* desc, UINT numElements)
{
	HRESULT hr = D3DReadFileToBlob(filePath.c_str(), buffer.GetAddressOf());
	if (FAILED(hr)) {
		ErrorLogger::Log(hr, "Failed to read file to blob");
		return false;
	}

	hr = device->CreateVertexShader(this->buffer->GetBufferPointer(), this->buffer->GetBufferSize(),
		NULL, shader.GetAddressOf());
	if (FAILED(hr)) {
		ErrorLogger::Log(hr, "Failed to create vertex shader");
		return false;
	}

	hr = device->CreateInputLayout(desc, numElements, buffer->GetBufferPointer(),
		buffer->GetBufferSize(), inputLayout.GetAddressOf());
	if (FAILED(hr)) {
		ErrorLogger::Log(hr, "Failed to create input layout");
		return false;
	}

	return true;
}

ID3D11VertexShader* VertexShader::getShader()
{
	return this->shader.Get();
}

ID3D10Blob* VertexShader::getBuffer()
{
	return this->buffer.Get();
}

ID3D11InputLayout* VertexShader::getInputLayout()
{
	return this->inputLayout.Get();
}


// PIXEL SHADER

bool PixelShader::Initialize(Microsoft::WRL::ComPtr<ID3D11Device>& device, std::wstring filePath)
{
	HRESULT hr = D3DReadFileToBlob(filePath.c_str(), buffer.GetAddressOf());
	if (FAILED(hr)) {
		ErrorLogger::Log(hr, "Failed to read file to blob");
		return false;
	}

	hr = device->CreatePixelShader(this->buffer.Get()->GetBufferPointer(), this->buffer.Get()->GetBufferSize(),
		NULL, shader.GetAddressOf());
	if (FAILED(hr)) {
		ErrorLogger::Log(hr, "Failed to create vertex shader");
		return false;
	}

	return true;
}

ID3D11PixelShader* PixelShader::getShader()
{
	return this->shader.Get();
}

ID3D10Blob* PixelShader::getBuffer()
{
	return this->buffer.Get();
}
