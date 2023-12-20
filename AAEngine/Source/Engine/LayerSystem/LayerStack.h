#pragma once

#include "Core.h"

#include "Layer.h"
#include "Containers/Array.h"

namespace AAEngine {

    /*
    * Class representing a LayerStack to store layers in the Application
    */
    class AA_ENGINE_API CLayerStack
    {
    public:
        /*
        * Constructor for the CLayerStack class
        */
        CLayerStack();

        /*
        * Destructor for the CLayerStack class
        */
        ~CLayerStack();

        /*
        * Adds a new layer to the layer stack
        * 
        * @param NewLayer - Pointer to the layer to be added
        */
        void PushLayer(CLayer* NewLayer);

        /*
        * Removes a layer from the layer stack
        * 
        * @param LayerToRemove - Pointer to the layer to be removed
        */
        void PopLayer(CLayer* LayerToRemove);

        /*
        * Adds a new overlay to the layer stack
        * 
        * @param NewOverlay - Pointer to the overlay to be added
        */
        void PushOverlay(CLayer* NewOverlay);

        /*
        * Removes an overlay from the layer stack
        * 
        * @param OverlayToRemove - Pointer to the overlay to be removed
        */
        void PopOverlay(CLayer* OverlayToRemove);

        /*
        * Iterator pointing to the beginning of the layer stack
        * 
        * @returns An iterator pointing to the start of the layer stack
        */
        TArray<CLayer*>::Iterator begin() { return LayerStack.begin(); }

        /*
         * Iterator pointing to the end of the layer stack
         * 
         * @returns An iterator pointing to the end of the layer stack
         */
        TArray<CLayer*>::Iterator end() { return LayerStack.end(); }
    private:
        /*
         * Array to store layers in the stack
         */
        TArray<CLayer*> LayerStack;

        /*
         * Iterator pointing to the position where the next layer will be inserted
         */
        TArray<CLayer*>::Iterator LayerInsertPos;
    };
}