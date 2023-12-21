#pragma once

#include "Core.h"
#include "LayerSystem/Layer.h"
#include "EventSystem/ApplicationEvents.h"
#include "EventSystem/MouseEvents.h"
#include "EventSystem/KeyEvents.h"

namespace AAEngine {

    /*
    * @brief CImGuiLayer class responsible for ImGui-related functionalities, derived from CLayer.
    *
    * This class handles ImGui user interface operations and inherits from CLayer.
    */
    class AA_ENGINE_API CImGuiLayer : public CLayer
    {
    public:
        /*
        * Constructor for CImGuiLayer.
        */
        CImGuiLayer();

        /*
        * Destructor for CImGuiLayer.
        */
        ~CImGuiLayer();

        /*
        * Called when the layer is attached to the application.
        */
        virtual void OnAttach() override;

        /*
        * Called when the layer is detached from the application.
        */
        virtual void OnDetach() override;

        /*
        * Called every frame for updating ImGui and rendering UI elements.
        */
        virtual void OnUpdate() override;

        /*
        * Called when an event occurs within the layer.
        *
        * @param Event - Reference to the event handled by the layer.
        */
        virtual void OnEvent(CEvent& Event) override;

    private:
        /*
        * Handles the event when a key is pressed.
        *
        * @param Event - Reference to the key pressed event.
        * 
        * @return bool - True if the event is handled, false otherwise.
        */
        bool OnKeyPressed(CKeyPressedEvent& Event);

        /*
        * Handles the event when a key is released.
        *
        * @param Event - Reference to the key released event.
        * 
        * @return bool - True if the event is handled, false otherwise.
        */
        bool OnKeyReleased(CKeyReleasedEvent& Event);

        /*
        * Handles the event when a key is typed.
        *
        * @param Event - Reference to the key typed event.
        * 
        * @return bool - True if the event is handled, false otherwise.
        */
        bool OnKeyTyped(CKeyTypedEvent& Event);

        /*
        * Handles the event when a mouse button is pressed.
        *
        * @param Event - Reference to the mouse button pressed event.
        * @return bool - True if the event is handled, false otherwise.
        */
        bool OnMouseButtonPressed(CMouseButtonPressedEvent& Event);

        /*
        * Handles the event when a mouse button is released.
        *
        * @param Event - Reference to the mouse button released event.
        * @return bool - True if the event is handled, false otherwise.
        */
        bool OnMouseButtonReleased(CMouseButtonReleasedEvent& Event);

        /*
        * Handles the event when the mouse is moved.
        *
        * @param Event - Reference to the mouse moved event.
        * @return bool - True if the event is handled, false otherwise.
        */
        bool OnMouseMoved(CMouseMovedEvent& Event);

        /*
        * Handles the event when the mouse wheel is scrolled.
        *
        * @param Event - Reference to the mouse scroll event.
        * @return bool - True if the event is handled, false otherwise.
        */
        bool OnMouseScrolled(CMouseScrollEvent& Event);

        /*
        * Handles the event when the window is resized.
        *
        * @param Event - Reference to the window resize event.
        * @return bool - True if the event is handled, false otherwise.
        */
        bool OnWindowResized(CWindowResizeEvent& Event);

        /*
        * Track the current time
        * TEMP
        */
		float ImGuiTime{ 0.0f };
	};
}