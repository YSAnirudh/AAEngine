#include "AA_PreCompiledHeaders.h"
#include "OpenGLVertexArray.h"
#include "OpenGLBuffer.h"

#include <glad/glad.h>

namespace AAEngine {

	COpenGLVertexArray::COpenGLVertexArray()
	{
		glCreateVertexArrays(1, &VertexArray);
	}

	COpenGLVertexArray::~COpenGLVertexArray()
	{
		glDeleteVertexArrays(1, &VertexArray);
	}

	void COpenGLVertexArray::Bind()
	{
		glBindVertexArray(VertexArray);
	}

	void COpenGLVertexArray::UnBind()
	{
		glBindVertexArray(0);
	}

	void COpenGLVertexArray::AddVertexBuffer(const TSharedPtr<IVertexBuffer>& VertexBuffer)
	{
		Bind();
		VertexBuffer->Bind();

		const CVertexBufferLayout& Layout = VertexBuffer->GetLayout();

		uint32_t Index = 0;
		for (const FVertexBufferElement& Elem : Layout)
		{
			glEnableVertexAttribArray(Index);
			glVertexAttribPointer(
				Index,
				Elem.GetComponentCount(),
				GL_FLOAT,
				Elem.bShouldNormalize ? GL_TRUE : GL_FALSE,
				Layout.GetStride(),
				reinterpret_cast<const void*>(Elem.Offset)
			);
			Index++;
		}

		VertexBuffers.EmplaceBack(VertexBuffer);
	}

	void COpenGLVertexArray::SetIndexBuffer(const TSharedPtr<IIndexBuffer>& InIndexBuffer)
	{
		glBindVertexArray(VertexArray);
		InIndexBuffer->Bind();

		IndexBuffer = InIndexBuffer;
	}
}