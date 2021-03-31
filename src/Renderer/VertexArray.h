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

	std::vector<BufferElement> layoutElements;
	int stride;
	int currentOffset;

	void InsertLayoutElement(int size, bool normalized)
	{
		BufferElement element;
		element.size = size;
		element.type = GL_FLOAT;
		element.normalized = normalized;
		element.offset = (void*)currentOffset;
		currentOffset += size;
		stride += size;
	}
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