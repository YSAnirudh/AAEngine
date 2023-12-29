#pragma once

#include "Engine/Core/Renderer/RenderingContext.h"

struct GLFWwindow;

namespace AAEngine {

	/*
	* OpenGL Rendering Context class
	*/
	class AA_ENGINE_API COpenGLRenderingContext : public IRenderingContext
	{
	public:
		/*
		* Constructor that takes in a GLFWwindow to Initialize OpenGL Rendering Context
		* 
		* @param WindowHandle - OpenGL Window that is bound to this Rendering context.
		*/
		COpenGLRenderingContext(GLFWwindow* WindowHandle);

		/*
		* Overriden virtual function Used to Initialize a Rendering Context;
		*/
		virtual void InitializeContext() override;

		/*
		* Overriden virtual function Used to Swap Buffers;
		*/
		virtual void SwapBuffers() override;
	private:
		/*
		* GLFW Window for the Rendering context
		*/
		GLFWwindow* WindowHandle;
	};
}