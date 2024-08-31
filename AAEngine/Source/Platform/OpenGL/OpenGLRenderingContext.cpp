#include "AA_PreCompiledHeaders.h"
#include "OpenGLRenderingContext.h"

// Only if Windowing library is GLFW
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace AAEngine {
	COpenGLRenderingContext::COpenGLRenderingContext(GLFWwindow* WindowHandle)
		: WindowHandle(WindowHandle)
	{
		AA_CORE_ASSERT(WindowHandle, "WindowHandle is Null!");
	}

	void COpenGLRenderingContext::InitializeContext()
	{
		// Use Window Handle to make context current for the specific window in GLFW
		glfwMakeContextCurrent(WindowHandle);

		// Initialize GLAD
		int GLADInitSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AA_CORE_ASSERT(GLADInitSuccess, "Could not Initializee GLAD!");

		// Log OpenGL specific Info
		AA_CORE_LOG(Info, "Open GL Graphics");
		AA_CORE_LOG(Info, "	Graphics Vendor:  %s", glGetString(GL_VENDOR));
		AA_CORE_LOG(Info, "	Graphics Driver:  %s", glGetString(GL_RENDERER));
		AA_CORE_LOG(Info, "	OpenGL Version:	  %s", glGetString(GL_VERSION));

		glEnable(GL_DEPTH_TEST);
	}

	void COpenGLRenderingContext::SwapBuffers()
	{
		glfwSwapBuffers(WindowHandle);
	}
}