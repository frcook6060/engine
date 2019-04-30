#include "app_test.h"

void AppTest::init()
{
	vertexShader.init("data/shaders/main_vs.hlsl");
	pixelShader.init("data/shaders/main_ps.hlsl");

	/*
	std::vector<D3D11_INPUT_ELEMENT_DESC> elements = {
		{
			"POSITION",
			0,
			DXGI_FORMAT_R32G32B32_FLOAT,
			0,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		},
		*/
	inputLayout.add({ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
		/*
		{
			"COLOR",
			0,
			DXGI_FORMAT_R32G32B32A32_FLOAT,
			1,
			0,
			D3D11_INPUT_PER_VERTEX_DATA,
			0
		}
	};
	*/
	inputLayout.add({ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 });
	inputLayout.init(&this->vertexShader);

	//this->initInputLayout();
	this->initVertexBuffer();
	this->initConstBuffer();

	viewPort = {};
	viewPort.TopLeftX = 0.0f;
	viewPort.TopLeftY = 0.0f;
	viewPort.Width = app_getConfig()->width;
	viewPort.Height = app_getConfig()->height;
	viewPort.MaxDepth = 1.0f;
	viewPort.MinDepth = 0.0f;


}

void AppTest::update()
{
	yrot += 64.0f * app_getConfig()->timer.delta;
	if (yrot > 360.0f)
	{
		yrot -= 360.0f;
	}
}

void AppTest::fixedUpdate()
{
}

void AppTest::render()
{
	ConstVS constVS = {};
	constVS.proj =
		glm::perspective(
			glm::radians(45.0f),
			(float)app_getConfig()->width / (float)app_getConfig()->height,
			1.0f,
			1024.0f);
	constVS.view =
		glm::mat4(1.0f);
	constVS.model =
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(yrot), glm::vec3(0.0f, 1.0f, 0.0f));


	D3D11_MAPPED_SUBRESOURCE mapped = {};
	rend_getContext()->Map(constBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mapped);
	memcpy(mapped.pData, &constVS, sizeof(ConstVS));
	rend_getContext()->Unmap(constBuffer, 0);

	rend_clear(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 1.0f);


	rend_getContext()->RSSetViewports(1, &this->viewPort);

	//rend_getContext()->VSSetShader(this->vertexShader, nullptr, 0);
	vertexShader.bind();
	rend_getContext()->VSSetConstantBuffers(0, 1, &this->constBuffer);
	//rend_getContext()->PSSetShader(this->pixelShader, nullptr, 0);
	pixelShader.bind();


	uint32_t stride = sizeof(glm::vec3);
	uint32_t offset = 0;

	inputLayout.bind();
	rend_getContext()->IASetVertexBuffers(0, 1, &this->verticesBuffer, &stride, &offset);
	stride = sizeof(glm::vec4);
	rend_getContext()->IASetVertexBuffers(1, 1, &this->colorsBuffer, &stride, &offset);

	rend_getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	
	rend_getContext()->Draw(vertices.size(), 0);

	rend_present();
}

void AppTest::release()
{
	SAFE_RELEASE(constBuffer);
	SAFE_RELEASE(colorsBuffer);
	SAFE_RELEASE(verticesBuffer);
	//SAFE_RELEASE(inputLayout);

	inputLayout.release();
	pixelShader.release();
	vertexShader.release();
}

void AppTest::initVertexBuffer()
{
	HRESULT r;

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DEFAULT;
	bufferDesc.ByteWidth = sizeof(glm::vec3) * vertices.size();
	bufferDesc.CPUAccessFlags = 0;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	D3D11_SUBRESOURCE_DATA data = {};
	data.pSysMem = vertices.data();
	data.SysMemPitch = 0;
	data.SysMemSlicePitch = 0;

	r = rend_getDevice()->CreateBuffer(
		&bufferDesc,
		&data,
		&this->verticesBuffer);

	if (FAILED(r))
	{
		throw std::runtime_error("");
	}

	// Color
	bufferDesc.ByteWidth = sizeof(glm::vec4) * colors.size();

	data.pSysMem = colors.data();

	r = rend_getDevice()->CreateBuffer(
		&bufferDesc,
		&data,
		&this->colorsBuffer);

	if (FAILED(r))
	{
		throw std::runtime_error("");
	}

}

void AppTest::initConstBuffer()
{
	HRESULT r;

	D3D11_BUFFER_DESC bufferDesc = {};
	bufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bufferDesc.ByteWidth = sizeof(ConstVS);
	bufferDesc.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	bufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bufferDesc.MiscFlags = 0;
	bufferDesc.StructureByteStride = 0;

	r = rend_getDevice()->CreateBuffer(
		&bufferDesc,
		nullptr,
		&this->constBuffer);


}