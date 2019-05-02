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

	virtual void setConstBuffer(int startSlot, ID3D11Buffer* buffer) = 0;
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

	virtual void setConstBuffer(int startSlot, ID3D11Buffer* buffer);
};

class ShaderPixel : public ShaderBase<ID3D11PixelShader>
{
public:
	virtual void init(std::string path);

	virtual void bind();

	virtual void release();

	virtual void setConstBuffer(int startSlot, ID3D11Buffer* buffer);
};

// Input Layout
class InputLayout
{
private:
	std::vector<D3D11_INPUT_ELEMENT_DESC> elements;
	ID3D11InputLayout* inputLayout = nullptr;
public:

	void add(D3D11_INPUT_ELEMENT_DESC desc);
	void addAll(std::vector<D3D11_INPUT_ELEMENT_DESC>& descs);

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
		void* data, 
		size_t size, 
		D3D11_BIND_FLAG bindFlags = D3D11_BIND_VERTEX_BUFFER) = 0;

	virtual void bind(int inputSlot, size_t stride, size_t offset = 0) = 0;

	virtual void release() = 0;

	virtual void addData(void* data, size_t size) = 0;

	virtual ID3D11Buffer* getBuffer() = 0;
};

// Static Buffer
class BufferStatic : public Buffer
{
private:
	ID3D11Buffer* buffer = nullptr;
	D3D11_BIND_FLAG bindFlags;

public:
	virtual void init(
		void* data,
		size_t size,
		D3D11_BIND_FLAG bindFlags = D3D11_BIND_VERTEX_BUFFER);

	virtual void bind(int inputSlot, size_t stride, size_t offset = 0);

	virtual void release();

	virtual void addData(void* data, size_t size);

	virtual ID3D11Buffer* getBuffer();
};

// Dynamic Buffer
class BufferDynamic : public Buffer
{
private:
	ID3D11Buffer* buffer = nullptr;
	D3D11_BIND_FLAG bindFlags;

public:
	virtual void init(
		void* data,
		size_t size,
		D3D11_BIND_FLAG bindFlags = D3D11_BIND_VERTEX_BUFFER);

	virtual void bind(int inputSlot, size_t stride, size_t offset = 0);

	virtual void release();

	virtual void addData(void* data, size_t size);

	virtual ID3D11Buffer* getBuffer();
};

// Vertex Buffers

// Static Vertex Buffers
template<typename T>
class VertexBufferStatic
{
private:
	std::vector<T> list;
	BufferStatic buffer;
public:

	void add(T t) 
	{
		list.push_back(t);
	}

	void addAll(std::vector<T>& list)
	{
		std::for_each(list.begin(), list.end(), [&](T& t) {
			this->list.push_back(t);
		});
	}

	void clear()
	{
		list.clear();
	}

	void init()
	{
		buffer.init(list.data(), size());
	}

	void bind(int startSlot)
	{
		buffer.bind(startSlot, sizeof(T));
	}

	void release()
	{
		buffer.release();
	}

	ID3D11Buffer* getBuffer()
	{
		return buffer.getBuffer();
	}

	size_t typeSize()
	{
		return sizeof(T);
	}

	size_t count()
	{
		return list.size();
	}

	size_t size()
	{
		return typeSize() * count();
	}
};

// Dynamic Vertex Buffer
template<typename T>
class VertexBufferDynamic
{
private:
	std::vector<T> list;
	BufferDynamic buffer;
public:

	void add(T t)
	{
		list.push_back(t);
	}

	void addAll(std::vector<T>& list)
	{
		std::for_each(list.begin(), list.end(), [&](T& t) {
			this->list.push_back(t);
		});
	}

	void clear()
	{
		list.clear();
	}

	void init()
	{
		buffer.init(nullptr, size());
	}

	void update()
	{
		buffer.addData(list.data(), size());
	}

	void bind(int startSlot)
	{
		buffer.bind(startSlot, sizeof(T));
	}

	void release()
	{
		buffer.release();
	}

	ID3D11Buffer* getBuffer()
	{
		return buffer.getBuffer();
	}

	size_t typeSize()
	{
		return sizeof(T);
	}

	size_t count()
	{
		return list.size();
	}

	size_t size()
	{
		return typeSize() * count();
	}

};

// Index Buffer

// Static Index Buffer
class IndexBufferStatic
{
private:
	std::vector<uint32_t> list;
	BufferStatic buffers;
public:

	void add(uint32_t index)
	{
		list.push_back(index);
	}

	void addAll(std::vector<uint32_t>& list)
	{
		std::for_each(list.begin(), list.end(), [&](uint32_t t) {
			this->list.push_back(t);
		});
	}

	void clear()
	{
		list.clear();
	}

	void init()
	{
		buffers.init(list.data(), size(), D3D11_BIND_INDEX_BUFFER);
	}

	void bind()
	{
		buffers.bind(0, 0);
	}

	void release()
	{
		buffers.release();
	}

	ID3D11Buffer* getBuffer()
	{
		return this->buffers.getBuffer();
	}

	size_t typeSize()
	{
		return sizeof(uint32_t);
	}

	size_t count()
	{
		return list.size();
	}

	size_t size()
	{
		return typeSize() * count();
	}

};

// Dynamic Index Buffer
class IndexBufferDynamic
{
private:
	std::vector<uint32_t> list;
	BufferDynamic buffers;
public:
	void add(uint32_t t)
	{
		list.push_back(t);
	}

	void addAll(const std::vector<uint32_t>& list)
	{
		std::for_each(list.begin(), list.end(), [&](uint32_t t) {
			this->list.push_back(t);
		});
	}

	void clear()
	{
		list.clear();
	}

	void init()
	{
		buffers.init(nullptr, size(), D3D11_BIND_INDEX_BUFFER);
	}

	void update()
	{
		buffers.addData(list.data(), size());
	}

	void bind(int startSlot)
	{
		buffers.bind(startSlot, sizeof(uint32_t));
	}

	void release()
	{
		buffers.release();
	}

	ID3D11Buffer* getBuffer()
	{
		return buffers.getBuffer();
	}

	size_t typeSize()
	{
		return sizeof(uint32_t);
	}

	size_t count()
	{
		return list.size();
	}

	size_t size()
	{
		return typeSize() * count();
	}
};

// Constant Buffer
template<typename T>
class ConstantBuffer
{
private:
	T value;
	BufferDynamic buffer;
public:

	T* get()
	{
		return &value;
	}

	ID3D11Buffer* getBuffer()
	{
		return buffer.getBuffer();
	}

	void init()
	{
		buffer.init(nullptr, this->typeSize(), D3D11_BIND_CONSTANT_BUFFER);
	}

	void update()
	{
		buffer.addData(&this->value, this->typeSize());
	}

	void release()
	{
		buffer.release();
	}

	size_t typeSize()
	{
		return sizeof(T);
	}
};


class Texture2D
{
private:
	Image image;
	ID3D11Texture2D* tex = nullptr;
	ID3D11ShaderResourceView* shaderResourceView = nullptr;
	ID3D11SamplerState* samplerState = nullptr;
public:

	void init(std::string path);

	void bind(int inputSlot);

	void release();

	uint32_t getWidth();

	uint32_t getHeight();

};