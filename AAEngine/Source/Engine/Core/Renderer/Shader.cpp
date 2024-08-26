#include "AA_PreCompiledHeaders.h"
#include "Shader.h"

#include "Renderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

namespace AAEngine {

	// ---------- SHADER ---------------------------

	TSharedPtr<IShader> IShader::Create(const std::string& ShaderName, const std::string& VertexShaderSource, const std::string& FragmentShaderSource)
	{
		switch (IRendererAPI::GetAPI())
		{
		case IRendererAPI::EAPI::None:
			AA_CORE_ASSERT(false, "None API Specified!");
			return nullptr;
		case IRendererAPI::EAPI::OpenGL:
			return MakeShared<COpenGLShader>(ShaderName, VertexShaderSource, FragmentShaderSource);
		}
		AA_CORE_ASSERT(false, "Unknown API Specified!");
		return nullptr;
	}

	TSharedPtr<IShader> IShader::Create(const std::string& ShaderFilePath)
	{
		switch (IRendererAPI::GetAPI())
		{
		case IRendererAPI::EAPI::None:
			AA_CORE_ASSERT(false, "None API Specified!");
			return nullptr;
		case IRendererAPI::EAPI::OpenGL:
			return MakeShared<COpenGLShader>(ShaderFilePath);
		}
		AA_CORE_ASSERT(false, "Unknown API Specified!");
		return nullptr;
	}

	TSharedPtr<IShader> IShader::Create(const std::string& ShaderName, const std::string& ShaderFilePath)
	{
		switch (IRendererAPI::GetAPI())
		{
		case IRendererAPI::EAPI::None:
			AA_CORE_ASSERT(false, "None API Specified!");
			return nullptr;
		case IRendererAPI::EAPI::OpenGL:
			return MakeShared<COpenGLShader>(ShaderName, ShaderFilePath);
		}
		AA_CORE_ASSERT(false, "Unknown API Specified!");
		return nullptr;
	}

	TSharedPtr<IShader> IShader::Create(std::string&& ShaderName, const std::string& ShaderFilePath)
	{
		switch (IRendererAPI::GetAPI())
		{
		case IRendererAPI::EAPI::None:
			AA_CORE_ASSERT(false, "None API Specified!");
			return nullptr;
		case IRendererAPI::EAPI::OpenGL:
			return MakeShared<COpenGLShader>(Move(ShaderName), ShaderFilePath);
		}
		AA_CORE_ASSERT(false, "Unknown API Specified!");
		return nullptr;
	}

	// ---------- SHADER LIBRARY -------------------
	
	void CShaderLibrary::AddShader(const std::string& ShaderName, const TSharedPtr<IShader>& NewShader)
	{
		AA_CORE_ASSERT(!Exists(ShaderName), "Shader already exists!");
		ShaderLibrary[ShaderName] = NewShader;
	}

	void CShaderLibrary::AddShader(const TSharedPtr<IShader>& NewShader)
	{
		const std::string& ShaderName = NewShader->GetName();
		AddShader(ShaderName, NewShader);
	}

	TSharedPtr<IShader> CShaderLibrary::LoadShader(const std::string& ShaderName, const std::string& VertexSource, const std::string& FragmentSource)
	{
		TSharedPtr<IShader> Shader = IShader::Create(ShaderName, VertexSource, FragmentSource);
		AddShader(ShaderName, Shader);
		return Shader;
	}

	TSharedPtr<IShader> CShaderLibrary::LoadShader(const std::string& ShaderName, const std::string& FilePath)
	{
		TSharedPtr<IShader> Shader = IShader::Create(ShaderName, FilePath);
		AddShader(ShaderName, Shader);
		return Shader;
	}

	TSharedPtr<IShader> CShaderLibrary::LoadShader(const std::string& FilePath)
	{
		TSharedPtr<IShader> Shader = IShader::Create(FilePath);
		std::string ShaderName = Shader->GetName();
		AddShader(ShaderName, Shader);
		return Shader;
	}
	TSharedPtr<IShader> CShaderLibrary::GetShader(const std::string& ShaderName)
	{
		AA_CORE_ASSERT(Exists(ShaderName), "Shader doesn't exist!");
		return ShaderLibrary[ShaderName];
	}
	bool CShaderLibrary::Exists(const std::string& ShaderName)
	{
		return ShaderLibrary.find(ShaderName) != ShaderLibrary.end();
	}
}