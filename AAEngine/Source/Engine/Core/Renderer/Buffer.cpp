#include "AA_PreCompiledHeaders.h"
#include "Buffer.h"
#include "Texture.h"
#include "Renderer.h"
#include "RendererCommons.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace AAEngine {

	CVertexBufferLayout CVertexBufferLayout::PhongLayout = {
		{ EShaderVarType::SVT_Float3, EVertexInputType::VI_Position },
		{ EShaderVarType::SVT_Float3, EVertexInputType::VI_Normal },
		{ EShaderVarType::SVT_Float2, EVertexInputType::VI_TexCoords },
	};

	TSharedPtr<IVertexBuffer> IVertexBuffer::Create(float* Vertices, uint32_t Count, uint32_t EnumUsage)
	{
		switch (IRendererAPI::GetAPI())
		{
		case IRendererAPI::EAPI::None:
			AA_CORE_ASSERT(false, "None API Specified!");
			return nullptr;
		case IRendererAPI::EAPI::OpenGL:
			return MakeShared<COpenGLVertexBuffer>(Vertices, Count, EnumUsage);
		}
		AA_CORE_ASSERT(false, "Unknown API Specified!");
		return nullptr;
	}

	TSharedPtr<IIndexBuffer> IIndexBuffer::Create(uint32_t* Indices, uint32_t Count, uint32_t EnumUsage)
	{
		switch (IRendererAPI::GetAPI())
		{
		case IRendererAPI::EAPI::None:
			AA_CORE_ASSERT(false, "None API Specified!");
			return nullptr;
		case IRendererAPI::EAPI::OpenGL:
			return MakeShared<COpenGLIndexBuffer>(Indices, Count, EnumUsage);
		}
		AA_CORE_ASSERT(false, "Unknown API Specified!");
		return nullptr;
	}

	TSharedPtr<IFramebuffer> IFramebuffer::Create(ITexture2D* Texture, EAttachmentType FramebufferAttachmentType, uint32_t ColorAttachmentIndex, EFramebufferMode FramebufferMode)
	{
		switch (IRendererAPI::GetAPI())
		{
		case IRendererAPI::EAPI::None:
			AA_CORE_ASSERT(false, "None API Specified!");
			return nullptr;
		case IRendererAPI::EAPI::OpenGL:
			return MakeShared<COpenGLFramebuffer>(Texture, FramebufferAttachmentType, ColorAttachmentIndex, FramebufferMode);
		}
		AA_CORE_ASSERT(false, "Unknown API Specified!");
		return nullptr;
	}
}