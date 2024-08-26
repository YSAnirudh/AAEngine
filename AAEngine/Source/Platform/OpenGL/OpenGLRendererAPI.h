#pragma once

#include "Engine/Core/Renderer/RendererAPI.h"

namespace AAEngine {

	/*
	* OpenGL specific Renderer API class
	*/
	class COpenGLRendererAPI : public IRendererAPI
	{
	public:
		/*
		* Overriden Virtual Clear method to initialize the renderer
		*/
		virtual void Init() override;
		/*
		* Overriden Virtual Clear method to clear Buffers before starting a frame
		*/
		virtual void Clear() override;
		/*
		* Overriden Virtual SetClearColor method to Set the color that buffer needs to be cleared to.
		*
		* @param Color - The Color that buffer needs to be cleared to.
		*/
		virtual void SetClearColor(const FColor& Color) override;
		/*
		* Overriden Virtual DrawIndexed method to Draw Vertices using an Indexed way (Indices).
		*
		* @param VertexArray - Vertex Array used to draw stuff
		*/
		virtual void DrawIndexed(const TSharedPtr<IVertexArray>& VertexArray) override;
	};
}