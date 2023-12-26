#pragma once

#include "Core.h"

#include <string>

namespace AAEngine {

    class CEvent;

    /*
    * The base layer class for the engine.
    */
    class AA_ENGINE_API CLayer {
    public:
        /*
        * Constructor for CLayer.
        * 
        * @param LayerName - Name of the layer.
        */
        CLayer(const std::string& LayerName = "Layer");

        /*
        * Virtual destructor for CLayer.
        */
        virtual ~CLayer() {}

        /*
        * Function called when the layer is attached.
        */
        virtual void OnAttach() {}

        /*
        * Function called when the layer is detached.
        */
        virtual void OnDetach() {}

        /*
        * Function called to update the layer.
        */
        virtual void OnUpdate() {}

        /*
        * Function called to update the ImGui Rendering.
        * TO DO: Add a wrapper for ImGui functions if and when UI stuff is ImGui Independent
        */
        virtual void OnImGuiRender() {}

        /*
        * Function called when an event occurs.
        * @param Event - The event received.
        */
        virtual void OnEvent(CEvent& Event) {}

    protected:
        /*
        * Layer's Name for debugging only.
        */
        std::string DebugName;
    };
}