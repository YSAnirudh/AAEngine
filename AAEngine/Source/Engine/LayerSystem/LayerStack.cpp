#include "AA_PreCompiledHeaders.h"
#include "LayerStack.h"

namespace AAEngine {
	CLayerStack::CLayerStack()
	{
		LayerInsertPos = LayerStack.begin();
	}

	CLayerStack::~CLayerStack()
	{
		for (CLayer* Layer : LayerStack)
		{
			delete Layer;
		}
	}

	void CLayerStack::PushLayer(CLayer* NewLayer)
	{
		LayerInsertPos = LayerStack.Emplace(LayerInsertPos, NewLayer);
		NewLayer->OnAttach();
	}

	void CLayerStack::PopLayer(CLayer* NewLayer)
	{
		auto it = LayerStack.Find(NewLayer);
		if (it != LayerStack.end())
		{
			LayerStack.RemoveAt(it);
			LayerInsertPos--;
			(*it)->OnDetach();
		}
	}

	void CLayerStack::PushOverlay(CLayer* NewOverlay)
	{
		LayerStack.EmplaceBack(NewOverlay);
		NewOverlay->OnAttach();
	}

	void CLayerStack::PopOverlay(CLayer* NewOverlay)
	{
		auto it = LayerStack.Find(NewOverlay);
		if (it != LayerStack.end())
		{
			LayerStack.RemoveAt(it);
			(*it)->OnDetach();
		}
	}
}