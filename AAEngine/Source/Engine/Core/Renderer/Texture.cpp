#include "AA_PreCompiledHeaders.h"
#include "Texture.h"

#include "Renderer/Renderer.h"

#include "Platform/OpenGL/OpenGLTexture.h"

namespace AAEngine {
	
	TSharedPtr<ITexture2D> ITexture2D::Create(const std::string& FilePath)
	{
		switch (IRendererAPI::GetAPI())
		{
		case IRendererAPI::EAPI::None:
			AA_CORE_ASSERT(false, "None API Specified!");
			return nullptr;
		case IRendererAPI::EAPI::OpenGL:
			return MakeShared<COpenGLTexture2D>(FilePath);
		}
		AA_CORE_ASSERT(false, "Unknown API Specified!");
		return nullptr;
	}
}