#include "sys.h"

// Static Buffer
void BufferStatic::init(
	void* data,
	size_t size,
	D3D11_BIND_FLAG bindFlags)
{
	HRESULT r;

	this->bindFlags = bindFlags;

	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DEFAULT;
	desc.ByteWidth = size;
	desc.BindFlags = bindFlags;
	desc.CPUAccessFlags = 0;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA sdata = {};
	sdata.pSysMem = data;
	sdata.SysMemPitch = 0;
	sdata.SysMemSlicePitch = 0;

	r = rend_getDevice()->CreateBuffer(
		&desc,
		&sdata,
		&this->buffer);

	if (FAILED(r))
	{
		throw std::runtime_error("");
	}
}

void BufferStatic::bind(int inputSlot, size_t stride, size_t offset)
{
	switch (this->bindFlags)
	{
	case D3D11_BIND_VERTEX_BUFFER:
		rend_getContext()->IASetVertexBuffers(inputSlot, 1, &this->buffer, &stride, &offset);
		break;
	case D3D11_BIND_INDEX_BUFFER:
		rend_getContext()->IASetIndexBuffer(this->buffer, DXGI_FORMAT_R32_UINT, offset);
		break;
	default:
		break;
	}
}

void BufferStatic::release()
{
	SAFE_RELEASE(buffer);
}

void BufferStatic::addData(void* data, size_t size) {}

ID3D11Buffer* BufferStatic::getBuffer()
{
	return buffer;
}



// Dynamic Buffer
void BufferDynamic::init(
	void* data,
	size_t size,
	D3D11_BIND_FLAG bindFlags)
{
	HRESULT r;

	this->bindFlags = bindFlags;

	D3D11_BUFFER_DESC desc = {};
	desc.Usage = D3D11_USAGE_DYNAMIC;
	desc.ByteWidth = size;
	desc.BindFlags = bindFlags;
	desc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	desc.MiscFlags = 0;
	desc.StructureByteStride = 0;

	r = rend_getDevice()->CreateBuffer(
		&desc,
		nullptr,
		&this->buffer
	);

	if (FAILED(r))
	{
		throw std::runtime_error("");
	}
}

void BufferDynamic::bind(int inputSlot, size_t stride, size_t offset)
{
	switch (this->bindFlags)
	{
	case D3D11_BIND_VERTEX_BUFFER:
		rend_getContext()->IASetVertexBuffers(inputSlot, 1, &this->buffer, &stride, &offset);
		break;
	case D3D11_BIND_INDEX_BUFFER:
		rend_getContext()->IASetIndexBuffer(this->buffer, DXGI_FORMAT_R32_UINT, offset);
		break;
	default:
		break;
	}
}

void BufferDynamic::release()
{
	SAFE_RELEASE(buffer);
}

void BufferDynamic::addData(void* data, size_t size)
{
	D3D11_MAPPED_SUBRESOURCE mapped = {};
	rend_getContext()->Map(this->buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	memcpy(mapped.pData, data, size);
	rend_getContext()->Unmap(this->buffer, 0);
}

ID3D11Buffer* BufferDynamic::getBuffer()
{
	return this->buffer;
}
