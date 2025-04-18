#pragma once

#include "Engine/Core/Renderer/Shader.h"

namespace AAEngine {

	/*
	* OpenGL specific Shader Class.
	*/
	class COpenGLShader : public IShader
	{
	public:
		/*
		* Contructor that takes in Vertex Shader code and Fragment Shader code as String.
		* 
		* @param ShaderName - Name of the Shader
		* @param VertexShaderSource - Vertex Shader Code
		* @param FragmentShaderSource - Fragment Shader Code
		*/
		COpenGLShader(const std::string& ShaderName, const std::string& VertexShaderSource, const std::string& FragmentShaderSource);
		COpenGLShader(std::string&& ShaderName, const std::string& VertexShaderSource, const std::string& FragmentShaderSource);
		
		/*
		* Contructor that takes in Vertex Shader code and Fragment Shader code as String.
		*
		* @param ShaderFilePath - Path to the shader file
		*/
		COpenGLShader(const std::string& ShaderFilePath);

		/*
		* Contructor that takes in Vertex Shader code and Fragment Shader code as String.
		*
		* @param ShaderName - Name of the Shader
		* @param ShaderFilePath - Path to the shader file
		*/
		COpenGLShader(const std::string& ShaderName, const std::string& ShaderFilePath);
		COpenGLShader(std::string&& ShaderName, const std::string& ShaderFilePath);
		
		/*
		* Virtual Destructor as we know we will have derived classes
		*/
		virtual ~COpenGLShader() override;

		/*
		* Overriden virtual Bind function to Bind the shader to the program.
		*/
		virtual void Bind() override;

		/*
		* Overriden virtual UnBind function to UnBind the shader from the program.
		*/
		virtual void UnBind() override;

		/*
		* Overriden virtual GetName function to get the name of the Shader.
		*
		* @returns Name of the Shader.
		*/
		virtual std::string GetName() override
		{
			return ShaderName;
		}

		/*
		* Upload uniform functions with params as uniform name and specified data to the shader.
		* 
		* @param UniformName - name of the uniform variable.
		* @param DataType - varying from Int to Vec4 to Mat4 - data to be uploaded to the uniform variable
		*/
		virtual void UploadUniformInt(const char* UniformName, int Value) override;
		virtual void UploadUniformVec3(const char* UniformName, const FVector3f& Value) override;
		virtual void UploadUniformVec4(const char* UniformName, const FVector4f& Value) override;
		virtual void UploadUniformMat4(const char* UniformName, const FMatrix44f& Value) override;
	private:
		/*
		* Function to read shader code from a file.
		* 
		* @param ShaderFilePath - FilePath to the Shader File
		* 
		* @returns Contents of the Shader file as a String.
		*/
		std::string ReadShaderSourceFromFile(const std::string& ShaderFilePath);
		/*
		* Function to parse the shader code into array of shader data.
		*
		* @param ShaderSource - Contents of the Shader file.
		* 
		* @returns Map of Shader Data (Type of Shader, Shader Source).
		* 
		* TO DO: Replace Array of shader data with HashMap
		*/
		TMap<EShaderType, std::string> ParseShaderSourceIntoShaderData(const std::string& ShaderSource);
		/*
		* Function to compile the Shaders in the ShaderData Array.
		*
		* @param ShaderDataArray - Array of Shader Data (Type of Shader, Shader Source).
		*
		* TO DO: Replace Array of shader data with HashMap
		*/
		void CompileShaders(const TMap<EShaderType, std::string>& ShaderDataArray);

		/*
		* Shader Enum to OpenGL enum function
		* 
		* @param ShaderType - EShaderType specifying the AA Enum for Shaders
		* 
		* @returns OpenGL unsigned int for Shaders (Ex: GL_VERTEX_SHADER)
		*/
		FORCEINLINE virtual unsigned int AAShaderEnumToAPIEnum(EShaderType ShaderType) override;
		


	private:
		/*
		* Shader Program for OpenGL
		*/
		uint32_t ShaderProgram{ 0 };
		/*
		* Name of the Shader
		*/
		std::string ShaderName;
	};
}