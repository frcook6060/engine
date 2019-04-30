#pragma once



#define SAFE_RELEASE(d) if(d) { d->Release(); } 

void rend_init();

void rend_release();


void rend_clear(const glm::vec4& color, float depth);

void rend_clearColor(const glm::vec4& color);
void rend_clearDepth(float depth);

void rend_present();

IDXGISwapChain* rend_getSwapChain();
ID3D11Device* rend_getDevice();
ID3D11DeviceContext* rend_getContext();

// Shaders
class Shader
{
protected:
	ID3D10Blob* blob = nullptr;
public:

	virtual void init(std::string path) = 0;

	virtual void bind() = 0;

	virtual void release() = 0;

	ID3D10Blob* getBlob() { return this->blob;  }
};

template<typename T>
class ShaderBase : public Shader
{
protected:
	T* shader;
public:

	T* getShader() { return this->shader; }
};

class ShaderVertex : public ShaderBase<ID3D11VertexShader>
{
public:
	virtual void init(std::string path);

	virtual void bind();

	virtual void release();
};

class ShaderPixel : public ShaderBase<ID3D11PixelShader>
{
public:
	virtual void init(std::string path);

	virtual void bind();

	virtual void release();
};

// Input Layout
class InputLayout
{
private:
	std::vector<D3D11_INPUT_ELEMENT_DESC> elements;
	ID3D11InputLayout* inputLayout = nullptr;
public:

	void add(D3D11_INPUT_ELEMENT_DESC desc);

	void clear();

	void init(Shader* shader);

	void bind();

	void release();

	
};

// Buffers
class Buffer
{
public:
	virtual void init(
		D3D11_BIND_FLAG bindFlags = D3D11_BIND_VERTEX_BUFFER) = 0;

	virtual void init(
		void* data, 
		size_t size, 
		D3D11_BIND_FLAG bindFlags = D3D11_BIND_VERTEX_BUFFER) = 0;

	virtual void release() = 0;

	virtual void addData(void* data, size_t size) = 0;

	virtual ID3D11Buffer* getBuffer() = 0;
};

// Static Buffer

// Dynamic Buffer

// Vertex Buffers

// Constant Buffer
