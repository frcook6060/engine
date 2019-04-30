#include "sys.h"

void InputLayout::add(D3D11_INPUT_ELEMENT_DESC desc)
{
	this->elements.push_back(desc);
}

void InputLayout::clear()
{
	elements.clear();
}

void InputLayout::init(Shader* shader)
{
	if (elements.size() > 0)
	{
		HRESULT r;
		r = rend_getDevice()->CreateInputLayout(
			elements.data(),
			elements.size(),
			shader->getBlob()->GetBufferPointer(),
			shader->getBlob()->GetBufferSize(),
			&this->inputLayout);

		if (FAILED(r))
		{
			throw std::runtime_error("");
		}
	}
}

void InputLayout::bind()
{
	rend_getContext()->IASetInputLayout(this->inputLayout);
}

void InputLayout::release()
{
	SAFE_RELEASE(inputLayout);
	this->clear();
}