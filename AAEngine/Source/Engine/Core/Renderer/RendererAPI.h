#pragma once

#include "Renderer/VertexArray.h"

namespace AAEngine {

	/*
	* Platform and API independent Renderer API Interface to be implemented per platform/API and in the AAEngine.
	*/
	class IRendererAPI
	{
	public:
		/*
		* Enum to track what Graphics API we are using.
		*/
		enum class EAPI
		{
			None = 0,
			OpenGL = 1,
		};
		/*
		* Enum to track what Model Loader we are using.
		*/
		enum class EModelLoader
		{
			None = 0,
			AssImp = 1,
		};
	public:
		/*
		* Pure Virtual Init method to initialize the renderer
		*/
		virtual void Init() = 0;
		/*
		* Pure Virtual Clear method to clear Buffers before starting a frame
		*/
		virtual void Clear() = 0;
		/*
		* Pure Virtual SetClearColor method to Set the color that buffer needs to be cleared to.
		* 
		* @param Color - The Color that buffer needs to be cleared to.
		*/
		virtual void SetClearColor(const FColor& Color) = 0;
		/*
		* Pure Virtual DrawIndexed method to Draw Vertices using an Indexed way (Indices).
		* 
		* @param VertexArray - Vertex Array used to draw stuff
		*/
		virtual void DrawIndexed(const TSharedPtr<IVertexArray>& VertexArray) = 0;

		/*
		* Static GetAPI method to get the Currently used Graphics API
		* 
		* @returns Currently used Graphics API
		*/
		static EAPI GetAPI() { return RenderingAPI; }
		/*
		* Static GetModelLoader method to get the Currently used Model Loader
		*
		* @returns Currently used Model Loader
		*/
		static EModelLoader GetModelLoader() { return ModelLoader; }

	protected:
		/*
		* Static EAPI variable to track the Currently used Graphics API
		*/
		static EAPI RenderingAPI;
		/*
		* Static EModelLoader variable to track the Currently used Model Loader
		*/
		static EModelLoader ModelLoader;
	};
}