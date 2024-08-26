#include "AA_PreCompiledHeaders.h"
#include "Buffer.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLBuffer.h"

namespace AAEngine {

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
}