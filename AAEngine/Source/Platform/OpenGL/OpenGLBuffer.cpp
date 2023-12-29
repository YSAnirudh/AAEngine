#include "AA_PreCompiledHeaders.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace AAEngine {

	COpenGLVertexBuffer::COpenGLVertexBuffer(float* Vertices, uint32_t Count, unsigned int GLEnumUsage)
	{
		VertexCount = Count;

		glCreateBuffers(1, &VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
		glBufferData(GL_ARRAY_BUFFER, Count * sizeof(float), Vertices, GL_STATIC_DRAW);
	}

	COpenGLVertexBuffer::~COpenGLVertexBuffer()
	{
		glDeleteBuffers(1, &VertexBuffer);
	}

	void COpenGLVertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer);
	}

	void COpenGLVertexBuffer::UnBind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}


	COpenGLIndexBuffer::COpenGLIndexBuffer(uint32_t* Indices, uint32_t Count, unsigned int GLEnumUsage)
	{
		IndexCount = Count;

		glCreateBuffers(1, &IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, Count * sizeof(uint32_t), Indices, GL_STATIC_DRAW);
	}

	COpenGLIndexBuffer::~COpenGLIndexBuffer()
	{
		glDeleteBuffers(1, &IndexBuffer);
	}

	void COpenGLIndexBuffer::Bind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer);
	}

	void COpenGLIndexBuffer::UnBind()
	{
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	}
}