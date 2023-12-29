#pragma once

#include "RenderCommand.h"

namespace AAEngine {

	class CRenderer
	{
	public:
		static void BeginScene() {}
		static void EndScene() {}

		static void Submit(const TSharedPtr<IVertexArray>& VertexArray)
		{
			CRenderCommand::DrawIndexed(VertexArray);
		}

		static IRendererAPI::EAPI GetAPI() { return IRendererAPI::GetAPI(); }
	};
}