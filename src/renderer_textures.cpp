#include "sys.h"


void Texture2D::init(std::string path)
{
	HRESULT r;

	image.init(path);

	// Create Texuture 2D
	D3D11_TEXTURE2D_DESC texDesc = {};
	texDesc.Width = image.getWidth();
	texDesc.Height = image.getHeight();
	texDesc.MipLevels = 0;
	texDesc.ArraySize = 1;
	texDesc.CPUAccessFlags = 0;
	texDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	texDesc.SampleDesc.Count = 1;
	texDesc.SampleDesc.Quality = 0;
	texDesc.Usage = D3D11_USAGE_DEFAULT;
	texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE | D3D11_BIND_RENDER_TARGET;
	texDesc.MiscFlags = D3D11_RESOURCE_MISC_GENERATE_MIPS;

	r = rend_getDevice()->CreateTexture2D(
		&texDesc,
		nullptr,
		&this->tex);

	if (FAILED(r))
	{
		throw std::runtime_error("");
	}

	uint32_t rowPitch = (image.getWidth() * 4) * sizeof(uint8_t);

	rend_getContext()->UpdateSubresource(tex, 0, nullptr, image.getPixels(), rowPitch, 0);

	// Create Shader Resource
	D3D11_SHADER_RESOURCE_VIEW_DESC shaderViewDesc = {};
	shaderViewDesc.Format = texDesc.Format;
	shaderViewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2D;
	shaderViewDesc.Texture2D.MipLevels = -1;
	shaderViewDesc.Texture2D.MostDetailedMip = 0;

	r = rend_getDevice()->CreateShaderResourceView(
		this->tex,
		&shaderViewDesc,
		&this->shaderResourceView);

	if (FAILED(r))
	{
		throw std::runtime_error("");
	}

	rend_getContext()->GenerateMips(this->shaderResourceView);

	// Create Sampler
	D3D11_SAMPLER_DESC sampDesc = {};
	sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
	sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
	sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
	sampDesc.MinLOD = 0;
	sampDesc.MaxLOD = D3D11_FLOAT32_MAX;

	r = rend_getDevice()->CreateSamplerState(&sampDesc, &this->samplerState);

	if (FAILED(r))
	{
		throw std::runtime_error("");
	}

}

void Texture2D::bind(int inputSlot)
{
	rend_getContext()->PSSetShaderResources(inputSlot, 1, &this->shaderResourceView);
	rend_getContext()->PSSetSamplers(inputSlot, 1, &this->samplerState);
}

void Texture2D::release()
{
	SAFE_RELEASE(this->samplerState);
	SAFE_RELEASE(this->shaderResourceView);
	SAFE_RELEASE(this->tex);
	image.release();
}

uint32_t Texture2D::getWidth()
{
	return image.getWidth();
}

uint32_t Texture2D::getHeight()
{
	return image.getHeight();
}
