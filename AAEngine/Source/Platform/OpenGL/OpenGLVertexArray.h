#pragma once

#include "Engine/Core/Renderer/VertexArray.h"

namespace AAEngine {

	/*
	* OpenGL specific Vertex Array class
	*/
	class COpenGLVertexArray : public IVertexArray
	{
	public:
		/*
		* Constructor that takes in Vertices, Count and the Usage type (Currently useful for OpenGL)
		*/
		COpenGLVertexArray();

		/*
		* Overriden Virtual destructor to delete Vertex Array
		*/
		virtual ~COpenGLVertexArray() override;

		/*
		* Overriden virtual Bind function to Bind to the GL Vertex Array.
		*/
		virtual void Bind() override;
		/*
		* Overriden virtual UnBind function to UnBind from the GL Vertex Array.
		*/
		virtual void UnBind() override;

		/*
		* Overriden virtual AddVertexBuffer function to Add a Vertex Buffer to the Vertex Array object.
		*
		* @param VertexBuffer - Shared Pointer of the Vertex Buffer
		*/
		virtual void AddVertexBuffer(const TSharedPtr<IVertexBuffer>& VertexBuffer) override;
		/*
		* Overriden virtual SetIndexBuffer function to Set the Index Buffer of the Vertex Array object.
		*
		* @param IndexBuffer - Shared Pointer of the Index Buffer
		*/
		virtual void SetIndexBuffer(const TSharedPtr<IIndexBuffer>& IndexBuffer) override;
	private:
		uint32_t VertexArray;
	};
}