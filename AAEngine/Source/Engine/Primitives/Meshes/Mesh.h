#pragma once
#include "Renderer/Renderable.h"

namespace AAEngine {

	class IVertexArray;
	class CVertexBufferLayout;
	/*
	* Mesh class that takes in vertices, indices and a vertex layout to create a mesh.
	*/
	class CMesh : public IRenderable
	{
	public:
		CMesh(const TArray<float>& Vertices, const TArray<uint32_t>& Indices, const CVertexBufferLayout& BufferLayout);
		CMesh(const std::string& FileName, const CVertexBufferLayout& BufferLayout);
		~CMesh();

		virtual void Render() override;

	private:
		TArray<float> Vertices;
		TArray<uint32_t> Indices;

		TSharedPtr<IVertexArray> VertexArray = nullptr;
	};
}