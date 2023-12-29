#include "AA_PreCompiledHeaders.h"
#include "ImGuiLayer.h"

#include "Input/KeyCodes.h"
#include "Input/MouseCodes.h"

#include "EngineApplication.h"

#include "ImGuiCodes.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_opengl3_loader.h"

// Temp
#include <GLFW/glfw3.h>

namespace AAEngine {
	CImGuiLayer::CImGuiLayer()
		: CLayer("ImGuiLayer")
	{
	}

	CImGuiLayer::~CImGuiLayer()
	{
	}

	void CImGuiLayer::OnAttach()
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;     // Enable Keyboard Controls
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;         // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;       // Enable Multi-Viewport / Platform Windows
		//io.ConfigViewportsNoAutoMerge = true;
		//io.ConfigViewportsNoTaskBarIcon = true;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsLight();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		// Setup Platform/Renderer backends
		GLFWwindow* Window = static_cast<GLFWwindow*>(CEngineApplication::Get().GetWindow().GetNativeWindow());

		ImGui_ImplGlfw_InitForOpenGL(Window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void CImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void CImGuiLayer::OnImGuiRender()
	{
		//static bool bShowDemoWindow = false;
		//ImGui::ShowDemoWindow(&bShowDemoWindow);
	}

	void CImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void CImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		CEngineApplication& Application = CEngineApplication::Get();
		io.DisplaySize = ImVec2((float)Application.GetWindow().GetWindowWidth(), (float)Application.GetWindow().GetWindowHeight());

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		// Update and Render additional Platform Windows
		// (Platform functions may change the current OpenGL context, so we save/restore it to make it easier to paste this code elsewhere.
		//  For this specific demo app we could also call glfwMakeContextCurrent(window) directly)
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void CImGuiLayer::OnEvent(CEvent& Event)
	{
		/*CEventHandler EventHandler(Event);

		EventHandler.HandleEvent<CMouseButtonPressedEvent>(BIND_EVENT_FUNCTION(this, &CImGuiLayer::OnMouseButtonPressed));
		EventHandler.HandleEvent<CMouseButtonReleasedEvent>(BIND_EVENT_FUNCTION(this, &CImGuiLayer::OnMouseButtonReleased));
		EventHandler.HandleEvent<CMouseMovedEvent>(BIND_EVENT_FUNCTION(this, &CImGuiLayer::OnMouseMoved));
		EventHandler.HandleEvent<CMouseScrollEvent>(BIND_EVENT_FUNCTION(this, &CImGuiLayer::OnMouseScrolled));

		EventHandler.HandleEvent<CKeyPressedEvent>(BIND_EVENT_FUNCTION(this, &CImGuiLayer::OnKeyPressed));
		EventHandler.HandleEvent<CKeyReleasedEvent>(BIND_EVENT_FUNCTION(this, &CImGuiLayer::OnKeyReleased));
		EventHandler.HandleEvent<CKeyTypedEvent>(BIND_EVENT_FUNCTION(this, &CImGuiLayer::OnKeyTyped));

		EventHandler.HandleEvent<CWindowResizeEvent>(BIND_EVENT_FUNCTION(this, &CImGuiLayer::OnWindowResized));*/
	}

	bool CImGuiLayer::OnKeyPressed(CKeyPressedEvent& Event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddKeyEvent(FEngineToImGuiCodes::GetKey(Event.GetKeyCode()), true);
		
		// Ctrl, Alt, Shift, Super bindings

		return false;
	}

	bool CImGuiLayer::OnKeyReleased(CKeyReleasedEvent& Event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddKeyEvent(FEngineToImGuiCodes::GetKey(Event.GetKeyCode()), false);

		return false;
	}
	bool CImGuiLayer::OnKeyTyped(CKeyTypedEvent& Event)
	{
		ImGuiIO& io = ImGui::GetIO();
		
		auto KeyCode = Event.GetKeyCode();
		if (KeyCode > 0 && KeyCode < 0x10000)
		{
			io.AddInputCharacter(KeyCode);
		}

		return false;
	}
	bool CImGuiLayer::OnMouseButtonPressed(CMouseButtonPressedEvent& Event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(Event.GetMouseCode(), true);

		return false;
	}
	bool CImGuiLayer::OnMouseButtonReleased(CMouseButtonReleasedEvent& Event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseButtonEvent(Event.GetMouseCode(), false);

		return false;
	}
	bool CImGuiLayer::OnMouseMoved(CMouseMovedEvent& Event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMousePosEvent((float)Event.GetXPos(), (float)Event.GetYPos());

		return false;
	}
	bool CImGuiLayer::OnMouseScrolled(CMouseScrollEvent& Event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.AddMouseWheelEvent((float)Event.GetXOffset(), (float)Event.GetYOffset());

		return false;
	}
	bool CImGuiLayer::OnWindowResized(CWindowResizeEvent& Event)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)Event.GetWindowWidth(), (float)Event.GetWindowHeight());

		return false;
	}
}