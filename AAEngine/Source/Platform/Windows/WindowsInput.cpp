#include "AA_PreCompiledHeaders.h"
#include "WindowsInput.h"

#include "EngineApplication.h"
#include <GLFW/glfw3.h>

namespace AAEngine {

    // Initializing the Static Reference to Windows Input.
    CInput* CInput::InputInstance = new CWindowsInput();

    bool CWindowsInput::IsKeyPressed_Implementation(EKeyCode KeyCode)
    {
        GLFWwindow* Window = static_cast<GLFWwindow*>(CEngineApplication::Get().GetWindow().GetNativeWindow());
        int KeyState = glfwGetKey(Window, KeyCode);

        return KeyState == GLFW_PRESS || KeyState == GLFW_REPEAT;
    }

    bool CWindowsInput::IsMouseButtonPressed_Implementation(EMouseCode MouseCode)
    {
        GLFWwindow* Window = static_cast<GLFWwindow*>(CEngineApplication::Get().GetWindow().GetNativeWindow());
        int ButtonState = glfwGetMouseButton(Window, MouseCode);

        return ButtonState == GLFW_PRESS;
    }

    float CWindowsInput::GetMouseX_Implementation() const
    {
        GLFWwindow* Window = static_cast<GLFWwindow*>(CEngineApplication::Get().GetWindow().GetNativeWindow());

        double XPos, YPos;
        glfwGetCursorPos(Window, &XPos, &YPos);

        return (float)XPos;
    }

    float CWindowsInput::GetMouseY_Implementation() const
    {
        GLFWwindow* Window = static_cast<GLFWwindow*>(CEngineApplication::Get().GetWindow().GetNativeWindow());

        double XPos, YPos;
        glfwGetCursorPos(Window, &XPos, &YPos);

        return (float)YPos;
    }
}