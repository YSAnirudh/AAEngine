#include "AA_PreCompiledHeaders.h"
#include "Mesh.h"
#include "Renderer/Buffer.h"
#include "Renderer/VertexArray.h"
#include "Renderer/RenderCommand.h"
#include "Renderer/RendererCommons.h"
#include "Renderer/ModelLoader.h"

namespace AAEngine {

	CMesh::CMesh(const TArray<float>& Vertices, const TArray<uint32_t>& Indices, const CVertexBufferLayout& BufferLayout)
		: Vertices(Vertices), Indices(Indices)
	{
		VertexArray = CRendererUtils::MakeVertexArray(Vertices, Indices, BufferLayout);
	}

	CMesh::CMesh(const std::string& FileName, const CVertexBufferLayout& BufferLayout)
		: Vertices({}), Indices({})
	{
		IModelLoader::LoadModel(FileName, Vertices, Indices, BufferLayout);
		VertexArray = CRendererUtils::MakeVertexArray(Vertices, Indices, BufferLayout);
	}

	CMesh::~CMesh()
	{
	}

	void CMesh::Render()
	{
		CRenderCommand::DrawIndexed(VertexArray);
	}

}