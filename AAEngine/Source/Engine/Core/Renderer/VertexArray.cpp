#include "AA_PreCompiledHeaders.h"
#include "VertexArray.h"
#include "RendererAPI.h"

#include "Platform/OpenGL/OpenGLVertexArray.h"

namespace AAEngine {
    IVertexArray* IVertexArray::Create()
    {
		switch (IRendererAPI::GetAPI())
		{
		case IRendererAPI::EAPI::None:
			AA_CORE_ASSERT(false, "None API Specified!");
			return nullptr;
		case IRendererAPI::EAPI::OpenGL:
			return new COpenGLVertexArray();
		}
		AA_CORE_ASSERT(false, "Unknown API Specified!");
		return nullptr;
    }
}