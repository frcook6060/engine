#include "sys.h"


// Vertex Shader
void ShaderVertex::init(std::string path)
{
	HRESULT r;
	ID3D10Blob* error;

	r = D3DX11CompileFromFile(
		path.c_str(),
		nullptr,
		nullptr,
		"main",
		"vs_5_0",
		D3D10_SHADER_ENABLE_STRICTNESS,
		0,
		nullptr,
		&this->blob,
		&error,
		nullptr);

	if (FAILED(r))
	{
		if (error)
		{
			MessageBox(nullptr, (char*)error->GetBufferPointer(), "Error", MB_OK);
		}
		else
		{
			MessageBox(nullptr, "File doesn't exist", "Error", MB_OK);
		}

		throw std::runtime_error("");
	}

	r = rend_getDevice()->CreateVertexShader(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		nullptr,
		&this->shader);

	if (FAILED(r))
	{
		throw std::runtime_error("Error: didn't create vertex shader");
	}
}

void ShaderVertex::bind()
{
	rend_getContext()->VSSetShader(this->shader, nullptr, 0);
}

void ShaderVertex::release()
{
	SAFE_RELEASE(shader);
	SAFE_RELEASE(blob);
}

void ShaderVertex::setConstBuffer(int startSlot, ID3D11Buffer* buffer)
{
	rend_getContext()->VSSetConstantBuffers(startSlot, 1, &buffer);
}

// Pixel Shader
void ShaderPixel::init(std::string path)
{
	HRESULT r;
	ID3D10Blob* error;

	r = D3DX11CompileFromFile(
		path.c_str(),
		nullptr,
		nullptr,
		"main",
		"ps_5_0",
		D3D10_SHADER_ENABLE_STRICTNESS,
		0,
		nullptr,
		&this->blob,
		&error,
		nullptr);

	if (FAILED(r))
	{
		if (error)
		{
			MessageBox(nullptr, (char*)error->GetBufferPointer(), "Error", MB_OK);
		}
		else
		{
			MessageBox(nullptr, "File doesn't exist", "Error", MB_OK);
		}

		throw std::runtime_error("");
	}

	r = rend_getDevice()->CreatePixelShader(
		blob->GetBufferPointer(),
		blob->GetBufferSize(),
		nullptr,
		&this->shader);

	if (FAILED(r))
	{
		throw std::runtime_error("Error: didn't create vertex shader");
	}
}

void ShaderPixel::bind()
{
	rend_getContext()->PSSetShader(this->shader, nullptr, 0);
}

void ShaderPixel::release()
{
	SAFE_RELEASE(shader);
	SAFE_RELEASE(blob);
}

void ShaderPixel::setConstBuffer(int startSlot, ID3D11Buffer* buffer)
{
	rend_getContext()->PSGetConstantBuffers(startSlot, 1, &buffer);
}


