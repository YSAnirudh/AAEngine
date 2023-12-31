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
		* @param VertexShaderSource - Vertex Shader Code
		* @param FragmentShaderSource - Fragment Shader Code
		*/
		COpenGLShader(const std::string& VertexShaderSource, const std::string& FragmentShaderSource);
		
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

		void UploadUniformInt(const std::string& UniformName, int Value);
		void UploadUniformVec3(const std::string& UniformName, const FVector3f& Value);
		void UploadUniformVec4(const std::string& UniformName, const FVector4f& Value);
		void UploadUniformMat4(const std::string& UniformName, const FMatrix44f& Value);
	private:
		/*
		* Shader Program for OpenGL
		*/
		uint32_t ShaderProgram{ 0 };
	};
}