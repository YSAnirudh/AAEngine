#pragma once

#include "Engine/Core/Renderer/Buffer.h"

namespace AAEngine {

	/*
	* OpenGL specific Vertex Buffer class
	*/
	class COpenGLVertexBuffer : public IVertexBuffer
	{
	public:
		/*
		* Constructor that takes in Vertices, Count and the Usage type (Currently useful for OpenGL)
		* 
		* @param Vertices - float pointer of Vertices. Array passed in as a pointer.
		* @param Count - size_t Count of the vertices
		* @param EnumUsage - Usage of the buffer - Ex: OpenGL - GL_STATIC_DRAW
		*/
		COpenGLVertexBuffer(float* Vertices, uint32_t Count, unsigned int GLEnumUsage);

		/*
		* Overriden Virtual destructor to delete Vertex Buffers
		*/
		virtual ~COpenGLVertexBuffer() override;
		
		/*
		* Overriden virtual Bind function to Bind to the GL Vertex Buffer.
		*/
		virtual void Bind() override;
		/*
		* Overriden virtual UnBind function to UnBind from the GL Vertex Buffer.
		*/
		virtual void UnBind() override;

		/*
		* Overriden virtual getter GetVertexCount function to get the number of Vertices.
		*
		* @returns Number for Vertices
		*/
		virtual uint32_t GetVertexCount() const override { return VertexCount; };
	private:
		/*
		* Vertex Buffer Index to index this vertex buffer by for OpenGL
		*/
		uint32_t VertexBuffer;
		/*
		* Vertex Count stores the number of Vertices
		*/
		uint32_t VertexCount;
	};

	/*
	* OpenGL specific Index Buffer class
	*/
	class COpenGLIndexBuffer : public IIndexBuffer
	{
	public:
		/*
		* Constructor that takes in Vertices, Count and the Usage type (Currently useful for OpenGL)
		*
		* @param Indices - float pointer of Indices. Array passed in as a pointer.
		* @param Count - size_t Count of the vertices
		* @param EnumUsage - Usage of the buffer - Ex: OpenGL - GL_STATIC_DRAW
		*/
		COpenGLIndexBuffer(uint32_t* Indices, uint32_t Count, unsigned int GLEnumUsage);

		/*
		* Overriden Virtual destructor to delete Index Buffers
		*/
		virtual ~COpenGLIndexBuffer() override;

		/*
		* Overriden virtual Bind function to Bind to the GL Index Buffer.
		*/
		virtual void Bind() override;
		/*
		* Overriden virtual UnBind function to UnBind from the GL Index Buffer.
		*/
		virtual void UnBind() override;

		/*
		* Overriden virtual getter GetIndexCount function to get the number of Indices.
		*
		* @returns Number for Indices
		*/
		virtual uint32_t GetIndexCount() const override { return IndexCount; };
	private:
		/*
		* Index Buffer Index to index this Index buffer by for OpenGL
		*/
		uint32_t IndexBuffer;
		/*
		* Index Count stores the number of Indices
		*/
		uint32_t IndexCount;
	};


	/*
	* OpenGL specific Index Buffer class
	*/
	class COpenGLFramebuffer : public IFramebuffer
	{
	public:
		/*
		* Constructor that takes in Texture and Framebuffer Attachment type (Currently useful for OpenGL)
		*
		* @param Texture - 2D Texture used by the framebuffer.
		* @param FramebufferAttachmentType - Attachment Type of the frameuffer. Ex: Color Attachment
		*/
		COpenGLFramebuffer(ITexture2D* Texture, EAttachmentType FramebufferAttachmentType, uint32_t ColorAttachmentIndex, EFramebufferMode FramebufferMode);

		/*
		* Overriden Virtual destructor to delete Index Buffers
		*/
		virtual ~COpenGLFramebuffer() override;

		/*
		* Overriden virtual Bind function to Bind to the GL Index Buffer.
		*/
		virtual void Bind() override;
		/*
		* Overriden virtual UnBind function to UnBind from the GL Index Buffer.
		*/
		virtual void UnBind() override;

		uint32_t GetGLFramebufferMode(EFramebufferMode FramebufferMode) const;
		uint32_t GetGLAttachmentType(EAttachmentType FramebufferAttachmentType, uint32_t ColorAttachmentIndex = 0) const;

	private:
		/*
		* Framebuffer Index to index this framebuffer by for OpenGL
		*/
		uint32_t Framebuffer = 0;

		/*
		* Framebuffer Target for OpenGL
		*/
		uint32_t GLFramebufferTarget = 0;
	};
}