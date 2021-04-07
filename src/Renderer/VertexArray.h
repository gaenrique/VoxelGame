#pragma once

#include <vector>

#include <GL/glew.h>

enum BufferType
{
	VERTEX,
	INDEX
};

// BufferLayout struct is used to specify the layout of
// attribute pointers for vertex buffers
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
		// All buffers must use floats
		element.type = GL_FLOAT;
		element.normalized = normalized;
		// The element's offset will simply be its current offset.
		// This current offset is incremented by the size of
		// the attribute pointer multipled by the size of float
		element.offset = (void*)currentOffset;
		currentOffset += (size * sizeof(float));
		// The buffer's overall stride is incremented each time a new
		// element is inserted
		stride += (size * sizeof(float));

		layoutElements.push_back(element);
	}

	// Keeps track of all layout elements
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

	// I made the decision that BufferLayout must be passed as a pointer
	// so that I can make nullptr the default value. This allows me
	// to not have to pass a BufferLayout for index buffers
	void AddBuffer(BufferType type, const void* data, unsigned int size, 
		BufferLayout* layout = nullptr);

private:
	unsigned int m_RendererID;
	unsigned int m_VertexBufferID;
	unsigned int m_IndexBufferID;

	void AddBufferAttributes(BufferLayout* layout);
};