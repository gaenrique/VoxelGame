#pragma once

#include <vector>

#include <GL/glew.h>

enum BufferType
{
	VERTEX,
	INDEX
};

struct BufferLayout
{
	struct BufferElement
	{
		int size;
		GLenum type;
		bool normalized;
		const void* offset;
	};

	void InsertLayoutElement(int size, bool normalized)
	{
		BufferElement element;
		element.size = size;
		element.type = GL_FLOAT;
		element.normalized = normalized;
		element.offset = (void*)currentOffset;
		currentOffset += (size * sizeof(float));
		stride += (size * sizeof(float));
		layoutElements.push_back(element);
	}

	std::vector<BufferElement> layoutElements;
	int stride = 0;
	int currentOffset = 0;
};

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddBuffer(BufferType type, const void* data, unsigned int size, BufferLayout& layout);

private:
	unsigned int m_RendererID;
	unsigned int m_VertexBufferID;
	unsigned int m_IndexBufferID;

	void AddBufferAttributes(BufferLayout& layout);
};