#pragma once

#include "RendererAPI.h"

namespace AAEngine {

	class CRenderCommand
	{
	public:
		FORCEINLINE static void Clear()
		{
			RendererAPI->Clear();
		}

		FORCEINLINE static void SetClearColor(const FColor& Color)
		{
			RendererAPI->SetClearColor(Color);
		}

		FORCEINLINE static void DrawIndexed(const TSharedPtr<IVertexArray>& VertexArray)
		{
			RendererAPI->DrawIndexed(VertexArray);
		}

	private:
		static IRendererAPI* RendererAPI;
	};
}