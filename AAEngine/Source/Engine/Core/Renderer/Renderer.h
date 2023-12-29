#pragma once

#include "RenderCommand.h"

namespace AAEngine {

	/*
	* Platform Independent Renderer Class
	*/
	class CRenderer
	{
	public:
		/*
		* Before we begin a scene render
		*/
		static void BeginScene() {}
		/*
		* After we begin a scene render
		*/
		static void EndScene() {}

		/*
		* Submit a vertex array to be drawn to the Render Command Queue
		* 
		* @param Vertex Array
		*/
		static void Submit(const TSharedPtr<IVertexArray>& VertexArray)
		{
			CRenderCommand::DrawIndexed(VertexArray);
		}

		/*
		* Static getter for the currently used Graphics API
		*/
		static IRendererAPI::EAPI GetAPI() { return IRendererAPI::GetAPI(); }
	};
}