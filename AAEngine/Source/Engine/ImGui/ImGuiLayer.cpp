#include "AA_PreCompiledHeaders.h"
#include "ImGuiLayer.h"

#include "Input/KeyCodes.h"
#include "Input/MouseCodes.h"

#include "EngineApplication.h"

#include "ImGuiCodes.h"

#include "imgui.h"
#include "Platform/OpenGL/ImGuiOpenGLRenderer.h"

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
		ImGui::CreateContext();
		ImGui::StyleColorsDark();

		ImGuiIO& io = ImGui::GetIO();

		io.BackendFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.BackendFlags |= ImGuiBackendFlags_HasSetMousePos;

		//io.AddKeyEvent((ImGuiKey)Key::A, )

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void CImGuiLayer::OnDetach()
	{
	}

	void CImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		CEngineApplication& Application = CEngineApplication::Get();
		io.DisplaySize = ImVec2((float)Application.GetWindow().GetWindowWidth(), (float)Application.GetWindow().GetWindowHeight());

		float Time = (float)glfwGetTime();
		io.DeltaTime = ImGuiTime > 0.0f ? (Time - ImGuiTime) : 1.0f / 60.0f;
		ImGuiTime = Time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		static bool bShowDemoWindow = true;
		ImGui::ShowDemoWindow(&bShowDemoWindow);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void CImGuiLayer::OnEvent(CEvent& Event)
	{
		CEventHandler EventHandler(Event);

		EventHandler.HandleEvent<CMouseButtonPressedEvent>(BIND_EVENT_FUNCTION(this, &CImGuiLayer::OnMouseButtonPressed));
		EventHandler.HandleEvent<CMouseButtonReleasedEvent>(BIND_EVENT_FUNCTION(this, &CImGuiLayer::OnMouseButtonReleased));
		EventHandler.HandleEvent<CMouseMovedEvent>(BIND_EVENT_FUNCTION(this, &CImGuiLayer::OnMouseMoved));
		EventHandler.HandleEvent<CMouseScrollEvent>(BIND_EVENT_FUNCTION(this, &CImGuiLayer::OnMouseScrolled));

		EventHandler.HandleEvent<CKeyPressedEvent>(BIND_EVENT_FUNCTION(this, &CImGuiLayer::OnKeyPressed));
		EventHandler.HandleEvent<CKeyReleasedEvent>(BIND_EVENT_FUNCTION(this, &CImGuiLayer::OnKeyReleased));
		EventHandler.HandleEvent<CKeyTypedEvent>(BIND_EVENT_FUNCTION(this, &CImGuiLayer::OnKeyTyped));

		EventHandler.HandleEvent<CWindowResizeEvent>(BIND_EVENT_FUNCTION(this, &CImGuiLayer::OnWindowResized));
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