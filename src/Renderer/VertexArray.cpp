#include "VertexArray.h"

#include "GLError.h"

VertexArray::VertexArray()
{
	GLCall(glCreateVertexArrays(1, &m_RendererID));
}

VertexArray::~VertexArray()
{
	GLCall(glDeleteVertexArrays(1, &m_RendererID));
}

void VertexArray::AddBuffer(BufferType type, const void* data, unsigned int size,
	BufferLayout* layout)
{
	GLenum bufferType;
	unsigned int* bufferID;
	// Uses BufferType enum passed as an argument to determine what the type of 
	// buffer is
	switch (type)
	{
		case VERTEX:
			bufferType = GL_ARRAY_BUFFER;
			bufferID = &m_VertexBufferID;
			break;
		case INDEX:
			bufferType = GL_ELEMENT_ARRAY_BUFFER;
			bufferID = &m_IndexBufferID;
			break;
		default:
			return;
	}
	// Use information gathered from BufferType to create an OpenGL buffer
	// of the correct type and link it to VertexArray
	Bind();
	GLCall(glCreateBuffers(1, bufferID));
	GLCall(glBindBuffer(bufferType, *bufferID));
	GLCall(glBufferData(bufferType, size, data, GL_STATIC_DRAW));
	// Index buffers do not have attribute pointers
	if (bufferType != GL_ELEMENT_ARRAY_BUFFER)
	{
		AddBufferAttributes(layout);
	}
}

void VertexArray::AddBufferAttributes(BufferLayout* layout)
{
	for (unsigned int i = 0; i < (*layout).layoutElements.size(); i++)
	{
		auto element = (*layout).layoutElements[i];
		GLCall(glEnableVertexAttribArray(i));
		GLCall(glVertexAttribPointer(i, element.size, element.type, element.normalized,
			(*layout).stride, element.offset));
	}
}

void VertexArray::Bind() const
{
	GLCall(glBindVertexArray(m_RendererID));
}

void VertexArray::Unbind() const
{
	GLCall(glBindVertexArray(0));
}



