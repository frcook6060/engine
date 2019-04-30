#pragma once


#include "sys.h"



struct ConstVS
{
	glm::mat4 proj;
	glm::mat4 view;
	glm::mat4 model;
};

class AppTest : public IApp
{
private:
	// Draw a triangle for now...
	// Shader
	ID3D10Blob* vertexBlob;
	ID3D11VertexShader* vertexShader;
	ID3D11PixelShader* pixelShader;
	// Input Layout
	ID3D11InputLayout* inputLayout = nullptr;
	// Buffers
	// Vertices
	std::vector<glm::vec3> vertices = {
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(-1.0f, -1.0f, 0.0f),
		glm::vec3(1.0f, -1.0f, 0.0f)
	};

	// Vertices Buffer
	ID3D11Buffer* verticesBuffer;

	// Color
	std::vector<glm::vec4> colors = {
		glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 1.0f, 0.0f, 1.0f),
		glm::vec4(0.0f, 0.0f, 1.0f, 1.0f)
	};

	ID3D11Buffer* colorsBuffer;

	// Const Buffer VS
	ID3D11Buffer* constBuffer;

	D3D11_VIEWPORT viewPort;

	float yrot = 0.0f;

	void initShaders();
	void initInputLayout();
	void initVertexBuffer();
	void initConstBuffer();

public:
	virtual void init();
	virtual void update();
	virtual void fixedUpdate();
	virtual void render();
	virtual void release();
};