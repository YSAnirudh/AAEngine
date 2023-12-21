#include "AA_PreCompiledHeaders.h"
#include "WindowsWindow.h"
#include "EventSystem/ApplicationEvents.h"
#include "EventSystem/MouseEvents.h"
#include "EventSystem/KeyEvents.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace AAEngine {

	static bool bIsGLFWInitialized = false;

	static void GLFWErrorCallback(int ErrorCode, const char* Description)
	{
		AA_CORE_LOG(Error, "GLFW Error (%d): %s", ErrorCode, Description);
	}

	CWindowsWindow::CWindowsWindow(const FWindowProps& WindowProps)
	{
		Initialize(WindowProps);
	}

	CWindowsWindow::~CWindowsWindow()
	{
		Shutdown();
	}

	void CWindowsWindow::Tick()
	{
		glfwPollEvents();
		glfwSwapBuffers(Window);
	}

	IWindow* IWindow::Create(const FWindowProps& WindowProps)
	{
		return new CWindowsWindow(WindowProps);
	}

	void CWindowsWindow::Initialize(const FWindowProps& WindowProps)
	{
		WindowData.WindowWidth = WindowProps.WindowWidth;
		WindowData.WindowHeight = WindowProps.WindowHeight;
		WindowData.WindowTitle = WindowProps.WindowTitle;

		AA_CORE_LOG(Info, "Creating Window %s for AAEngine : Width (%d) | Height (%d)", WindowData.WindowTitle.c_str(), WindowData.WindowWidth, WindowData.WindowHeight);

		if (!bIsGLFWInitialized)
		{
			// Initialize GLFW if not already intialized by any other windows.
			int GLFWInitSuccess = glfwInit();
			AA_CORE_ASSERT(GLFWInitSuccess, "Could not Initializee GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);

			glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
			glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
			glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

			bIsGLFWInitialized = true;
		}

		// Create the GLFW window
		Window = glfwCreateWindow(WindowData.WindowWidth, WindowData.WindowHeight, WindowData.WindowTitle.c_str(), nullptr, nullptr);

		if (Window == nullptr)
		{
			AA_CORE_LOG(Error, "GLFW Window could not be created!");
			glfwTerminate();
			return;
		}

		glfwMakeContextCurrent(Window);

		int GLADInitSuccess = gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
		AA_CORE_ASSERT(GLADInitSuccess, "Could not Initializee GLAD!");

		glfwSetWindowUserPointer(Window, &WindowData);
		SetVSync(true);

		// Add Event callbacks
		SetGLFWEventCallbacks();
	}

	void CWindowsWindow::Shutdown()
	{
		glfwDestroyWindow(Window);
	}

	void CWindowsWindow::SetGLFWEventCallbacks()
	{
		// WINDOW Callbacks

		// Window Resize
		glfwSetWindowSizeCallback(Window, 
			[](GLFWwindow* Window, int Width, int Height)
			{
				FWindowData& UserPointerWindowData = *(FWindowData*)glfwGetWindowUserPointer(Window);
				UserPointerWindowData.WindowWidth = Width;
				UserPointerWindowData.WindowHeight = Height;

				CWindowResizeEvent Event(Width, Height);
				UserPointerWindowData.EventCallback(Event);
			});

		// Window Close
		glfwSetWindowCloseCallback(Window, 
			[](GLFWwindow* Window)
			{
				FWindowData& UserPointerWindowData = *(FWindowData*)glfwGetWindowUserPointer(Window);

				CWindowCloseEvent Event;
				UserPointerWindowData.EventCallback(Event);
			});

		// Window Focus / Lost Focus
		glfwSetWindowFocusCallback(Window, 
			[](GLFWwindow* Window, int Focused)
			{
				FWindowData& UserPointerWindowData = *(FWindowData*)glfwGetWindowUserPointer(Window);

				switch (Focused)
				{
				case GL_TRUE:
				{
					CWindowFocusEvent Event;
					UserPointerWindowData.EventCallback(Event);
					break;
				}
				case GL_FALSE:
				{
					CWindowLostFocusEvent Event;
					UserPointerWindowData.EventCallback(Event);
					break;
				}
				}
			});

		// Window Move
		glfwSetWindowPosCallback(Window, 
			[](GLFWwindow* Window, int XPos, int YPos)
			{
				FWindowData& UserPointerWindowData = *(FWindowData*)glfwGetWindowUserPointer(Window);

				CWindowMovedEvent Event(XPos, YPos);
				UserPointerWindowData.EventCallback(Event);
			});

		// KEY Callback Press / Release / Repeat
		glfwSetKeyCallback(Window,
			[](GLFWwindow* Window, int KeyCode, int ScanCode, int Action, int Mods) {
				FWindowData& UserPointerWindowData = *(FWindowData*)glfwGetWindowUserPointer(Window);

				switch (Action)
				{
				case GLFW_PRESS:
				{
					CKeyPressedEvent Event(KeyCode, false);
					UserPointerWindowData.EventCallback(Event);
					break;
				}
				case GLFW_RELEASE:
				{
					CKeyReleasedEvent Event(KeyCode);
					UserPointerWindowData.EventCallback(Event);
					break;
				}
				case GLFW_REPEAT:
				{
					CKeyPressedEvent Event(KeyCode, true);
					UserPointerWindowData.EventCallback(Event);
					break;
				}
				}
			});

		glfwSetCharCallback(Window,
			[](GLFWwindow* Window, unsigned int KeyCode)
			{
				FWindowData& UserPointerWindowData = *(FWindowData*)glfwGetWindowUserPointer(Window);

				CKeyTypedEvent Event(KeyCode);
				UserPointerWindowData.EventCallback(Event);
			});

		// MOUSE Callbacks

		// Mouse Move
		glfwSetCursorPosCallback(Window,
			[](GLFWwindow* Window, double XPos, double YPos)
			{
				FWindowData& UserPointerWindowData = *(FWindowData*)glfwGetWindowUserPointer(Window);

				CMouseMovedEvent Event(XPos, YPos);
				UserPointerWindowData.EventCallback(Event);
			});

		// Mouse Scroll
		glfwSetScrollCallback(Window,
			[](GLFWwindow* Window, double XOffset, double YOffset)
			{
				FWindowData& UserPointerWindowData = *(FWindowData*)glfwGetWindowUserPointer(Window);

				CMouseScrollEvent Event(XOffset, YOffset);
				UserPointerWindowData.EventCallback(Event);
			});

		// Mouse Button Press / Release
		glfwSetMouseButtonCallback(Window,
			[](GLFWwindow* Window, int MouseCode, int Action, int Mods)
			{
				FWindowData& UserPointerWindowData = *(FWindowData*)glfwGetWindowUserPointer(Window);

				switch (Action)
				{
				case GLFW_PRESS:
				{
					CMouseButtonPressedEvent Event(MouseCode);
					UserPointerWindowData.EventCallback(Event);
					break;
				}
				case GLFW_RELEASE:
				{
					CMouseButtonReleasedEvent Event(MouseCode);
					UserPointerWindowData.EventCallback(Event);
					break;
				}
				}
			});
	}

	void CWindowsWindow::SetVSync(bool bEnabled)
	{
		if (bEnabled)
		{
			glfwSwapInterval(1);
		}
		else
		{
			glfwSwapInterval(0);
		}

		WindowData.VSync = bEnabled;
	}

	bool CWindowsWindow::IsVSync() const
	{
		return WindowData.VSync;
	}
}