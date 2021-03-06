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
	// Vertex Shader
	ShaderVertex vertexShader;
	// Pixel Shader
	ShaderPixel pixelShader;

	// Input Layout
	InputLayout inputLayout;

	// Buffers
	// Vertices
	VertexBufferStatic<glm::vec3> vertices;

	// Color
	VertexBufferStatic<glm::vec4> colors;
	
	// TexCoords
	VertexBufferStatic<glm::vec2> texCoords;

	// Index Buffer
	IndexBufferStatic indices;

	// Const Buffer VS
	ConstantBuffer<ConstVS> constVS;

	// Texture2D
	Texture2D tex0;

	D3D11_VIEWPORT viewPort;

	float yrot = 0.0f;

public:
	virtual void init();
	virtual void update();
	virtual void fixedUpdate();
	virtual void render();
	virtual void release();
};