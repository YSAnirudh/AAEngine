#pragma once

#include "Renderer/Buffer.h"

namespace AAEngine {

	/*
	* Platform and API independent Vertex Array Interface to be implemented per platform/API and in the AAEngine.
	*/
	class IVertexArray
	{
	public:
		/*
		* Virtual Destructor as we know we will have derived classes
		*/
		virtual ~IVertexArray() {}

		/*
		* Pure virtual Bind function to Bind to the Vertex Array.
		*/
		virtual void Bind() = 0;

		/*
		* Pure virtual UnBind function to UnBind from the Vertex Array.
		*/
		virtual void UnBind() = 0;

		/*
		* Pure virtual AddVertexBuffer function to Add a Vertex Buffer to the Vertex Array object.
		* 
		* @param VertexBuffer - Shared Pointer of the Vertex Buffer
		*/
		virtual void AddVertexBuffer(const TSharedPtr<IVertexBuffer>& VertexBuffer) = 0;
		/*
		* Pure virtual SetIndexBuffer function to Set the Index Buffer of the Vertex Array object.
		*
		* @param IndexBuffer - Shared Pointer of the Index Buffer
		*/
		virtual void SetIndexBuffer(const TSharedPtr<IIndexBuffer>& IndexBuffer) = 0;

		/*
		* Const getter GetVertexBuffers function to get the Vertex Buffers attached to this Vertex Array.
		*
		* @returns Array of Vertex Buffers of this Vertex Array
		*/
		const TArray<TSharedPtr<IVertexBuffer>>& GetVertexBuffers() const { return VertexBuffers; }
		/*
		* Const getter GetIndexBuffer function to get the Index Buffer attached to this Vertex Array.
		*
		* @returns Index Buffer of this Vertex Array
		*/
		const TSharedPtr<IIndexBuffer>& GetIndexBuffer() const { return IndexBuffer; }

		/*
		* Static create method as create method doesn't vary based on instances.
		*
		* @param Vertices - float pointer of Vertices. Array passed in as a pointer.
		* @param Count - size_t Count of the vertices
		* @param EnumUsage - Usage of the buffer - Ex: OpenGL - GL_STATIC_DRAW
		* 
		* @returns A Platform indepentent Vertex Array
		*/
		static TSharedPtr<IVertexArray> Create();
	protected:
		/*
		* Pointer to the Index Buffer linked to the vertex Array
		*/
		TSharedPtr<IIndexBuffer> IndexBuffer;
		/*
		* Array of Pointers to the Vertex Buffers linked to the vertex Array
		*/
		TArray<TSharedPtr<IVertexBuffer>> VertexBuffers;
	};
}