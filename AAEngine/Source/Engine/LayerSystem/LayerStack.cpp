#include "AA_PreCompiledHeaders.h"
#include "LayerStack.h"

namespace AAEngine {
	CLayerStack::CLayerStack()
	{
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
		LayerStack.Emplace(LayerStack.begin() + LayerInsertIndex, NewLayer);
		LayerInsertIndex++;
		NewLayer->OnAttach();
	}

	void CLayerStack::PopLayer(CLayer* NewLayer)
	{
		auto it = LayerStack.Find(NewLayer);
		if (it != LayerStack.end())
		{
			LayerStack.RemoveAt(it);
			LayerInsertIndex--;
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