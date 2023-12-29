#pragma once

namespace AAEngine {

	/*
	* Platform and API independent Shader Interface to be implemented per platform/API and in the AAEngine.
	*/
	class IShader
	{
	public:
		/*
		* Virtual Destructor as we know we will have derived classes
		*/
		virtual ~IShader() {}

		/*
		* Pure virtual Bind function to Bind the shader to the program.
		*/
		virtual void Bind() = 0;

		/*
		* Pure virtual UnBind function to UnBind the shader from the program.
		*/
		virtual void UnBind() = 0;

		/*
		* Static create method as create method doesn't vary based on instances.
		*
		* @param VertexShaderSource - std::string of the Vertex Shader Code.
		* @param FragmentShaderSource - std::string of the Fragment Shader Code.
		*/
		static IShader* Create(const std::string& VertexShaderSource, const std::string& FragmentShaderSource);
	};
}