#include "app_test.h"

void AppTest::init()
{
	vertexShader.init("data/shaders/main_vs.hlsl");
	pixelShader.init("data/shaders/main_ps.hlsl");

	std::vector<D3D11_INPUT_ELEMENT_DESC> elements = {
		{ "POSITION", 0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "COLOR", 0, DXGI_FORMAT_R32G32B32A32_FLOAT, 1, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 },
		{ "TEXCOORD", 0, DXGI_FORMAT_R32G32_FLOAT, 2, 0, D3D11_INPUT_PER_VERTEX_DATA, 0 }
	};
	inputLayout.addAll(elements);
	inputLayout.init(&this->vertexShader);

	// Vertex
	std::vector<glm::vec3> v = {
		glm::vec3(-1.0f, 1.0f, 0.0f),
		glm::vec3(1.0f, 1.0f, 0.0f),
		glm::vec3(-1.0f, -1.0f, 0.0f),
		glm::vec3(1.0f, -1.0f, 0.0f)
	};
	vertices.addAll(v);
	vertices.init();

	// Colors
	std::vector<glm::vec4> c = {
		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f),
		glm::vec4(1.0f, 1.0f, 0.0f, 1.0f)
	};
	colors.addAll(c);
	colors.init();

	// TexCoords
	std::vector<glm::vec2> tc = {
		glm::vec2(0.0f, 0.0f),
		glm::vec2(1.0f, 0.0f),
		glm::vec2(0.0f, 1.0f),
		glm::vec2(1.0f, 1.0f)
	};
	texCoords.addAll(tc);
	texCoords.init();

	// Index
	std::vector<uint32_t> i = {
		0, 1, 2,
		2, 1, 3
	};
	indices.addAll(i);
	indices.init();

	constVS.init();

	tex0.init("data/textures/angry.png");

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
	constVS.get()->proj =
		glm::perspective(
			glm::radians(45.0f),
			(float)app_getConfig()->width / (float)app_getConfig()->height,
			1.0f,
			1024.0f);

	constVS.get()->view =
		glm::mat4(1.0f);

	constVS.get()->model =
		glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -5.0f)) *
		glm::rotate(glm::mat4(1.0f), glm::radians(yrot), glm::vec3(0.0f, 1.0f, 0.0f));

	constVS.update();

	rend_clear(glm::vec4(0.0f, 0.0f, 0.0f, 1.0f), 1.0f);

	rend_getContext()->RSSetViewports(1, &this->viewPort);

	vertexShader.bind();
	vertexShader.setConstBuffer(0, constVS.getBuffer());

	pixelShader.bind();

	tex0.bind(0);

	inputLayout.bind();
	vertices.bind(0);
	colors.bind(1);
	texCoords.bind(2);

	indices.bind();
	rend_getContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
	rend_getContext()->DrawIndexed(indices.count(), 0, 0);

	rend_present();
}

void AppTest::release()
{
	tex0.release();
	constVS.release();
	indices.release();
	texCoords.release();
	colors.release();
	vertices.release();
	inputLayout.release();
	pixelShader.release();
	vertexShader.release();
}