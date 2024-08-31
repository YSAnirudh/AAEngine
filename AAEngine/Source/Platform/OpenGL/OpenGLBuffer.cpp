#include "AA_PreCompiledHeaders.h"
#include "OpenGLBuffer.h"
#include "OpenGLTexture.h"

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

	COpenGLFramebuffer::COpenGLFramebuffer(ITexture2D* Texture, EAttachmentType FramebufferAttachmentType, uint32_t ColorAttachmentIndex, EFramebufferMode FramebufferMode)
	{
		COpenGLTexture2D* GLTexture = dynamic_cast<COpenGLTexture2D*>(Texture);
		if (GLTexture == nullptr)
		{
			AA_LOG(Error, "Cannot create Framebuffer, OpenGLTexture2D is null");
			return;
		}
		glCreateFramebuffers(1, &Framebuffer);
		GLFramebufferTarget = 0;

		glBindFramebuffer(GLFramebufferTarget, Framebuffer);
		glFramebufferTexture2D(GLFramebufferTarget, GetGLAttachmentType(FramebufferAttachmentType, ColorAttachmentIndex), GL_TEXTURE_2D, GLTexture->GetTextureID(), 0);
	}

	COpenGLFramebuffer::~COpenGLFramebuffer()
	{
	}

	void COpenGLFramebuffer::Bind()
	{
		glBindFramebuffer(GLFramebufferTarget, Framebuffer);
	}

	void COpenGLFramebuffer::UnBind()
	{
		glBindFramebuffer(GLFramebufferTarget, 0);
	}

	uint32_t COpenGLFramebuffer::GetGLFramebufferMode(EFramebufferMode FramebufferMode) const
	{
		switch (FramebufferMode)
		{
		case EFramebufferMode::FM_None:
			return GL_FRAMEBUFFER;
			break;
		case EFramebufferMode::FM_Write:
			return GL_DRAW_FRAMEBUFFER;
			break;
		case EFramebufferMode::FM_Read:
			return GL_READ_FRAMEBUFFER;
			break;
		default:
			break;
		}
		return 0;
	}

	uint32_t COpenGLFramebuffer::GetGLAttachmentType(EAttachmentType FramebufferAttachmentType, uint32_t ColorAttachmentIndex) const
	{
		switch (FramebufferAttachmentType)
		{
		case EAttachmentType::AT_None:
			return GL_COLOR_ATTACHMENT0 + ColorAttachmentIndex;
			break;
		case EAttachmentType::AT_Color:
			return GL_COLOR_ATTACHMENT0 + ColorAttachmentIndex;
			break;
		case EAttachmentType::AT_Depth:
			return GL_DEPTH_ATTACHMENT;
			break;
		case EAttachmentType::AT_DepthStencil:
			return GL_DEPTH_STENCIL_ATTACHMENT;
			break;
		default:
			break;
		}
		return 0;
	}
}