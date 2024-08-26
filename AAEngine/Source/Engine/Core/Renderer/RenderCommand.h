#pragma once

#include "RendererAPI.h"

namespace AAEngine {

	/*
	* Platform Independent Renderer Class
	*/
	class CRenderCommand
	{
	public:
		/*
		* Static Renderer API Call
		* Static Init method to Initialize the Renederer
		*/
		FORCEINLINE static void Init()
		{
			RendererAPI->Init();
		}
		/*
		* Static Renderer API Call
		* Static Clear method to clear Buffers before starting a frame
		*/
		FORCEINLINE static void Clear()
		{
			RendererAPI->Clear();
		}
		/*
		* Static Renderer API
		* Static SetClearColor method to Set the color that buffer needs to be cleared to.
		*
		* @param Color - The Color that buffer needs to be cleared to.
		*/
		FORCEINLINE static void SetClearColor(const FColor& Color)
		{
			RendererAPI->SetClearColor(Color);
		}

		/*
		* Static Renderer API Call
		* Static DrawIndexed method to Draw Vertices using an Indexed way (Indices).
		*
		* @param VertexArray - Vertex Array used to draw stuff
		*/
		FORCEINLINE static void DrawIndexed(const TSharedPtr<IVertexArray>& VertexArray)
		{
			RendererAPI->DrawIndexed(VertexArray);
		}

	private:
		/*
		* Static Renderer API object to make API calls
		*/
		static IRendererAPI* RendererAPI;
	};
}