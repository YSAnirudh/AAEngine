#include "AA_PreCompiledHeaders.h"
#include "Shader.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace AAEngine {

	IShader* IShader::Create(const std::string& VertexShaderSource, const std::string& FragmentShaderSource)
	{
		switch (IRendererAPI::GetAPI())
		{
		case IRendererAPI::EAPI::None:
			AA_CORE_ASSERT(false, "None API Specified!");
			return nullptr;
		case IRendererAPI::EAPI::OpenGL:
			return new COpenGLShader(VertexShaderSource, FragmentShaderSource);
		}
		AA_CORE_ASSERT(false, "Unknown API Specified!");
		return nullptr;
	}
	IShader* IShader::Create(const std::string& ShaderFilePath)
	{
		switch (IRendererAPI::GetAPI())
		{
		case IRendererAPI::EAPI::None:
			AA_CORE_ASSERT(false, "None API Specified!");
			return nullptr;
		case IRendererAPI::EAPI::OpenGL:
			return new COpenGLShader(ShaderFilePath);
		}
		AA_CORE_ASSERT(false, "Unknown API Specified!");
		return nullptr;
	}
}