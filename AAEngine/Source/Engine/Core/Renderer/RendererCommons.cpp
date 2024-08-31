#include "AA_PreCompiledHeaders.h"
#include "RendererCommons.h"
#include "RendererIncludes.h"

namespace AAEngine {
    
	TSharedPtr<IVertexArray> CRendererUtils::MakeVertexArray(const TArray<float>& Vertices, const TArray<uint32_t>& Indices, const CVertexBufferLayout& BufferLayout)
    {
		TSharedPtr<IVertexArray> VertexArray = IVertexArray::Create();

		TSharedPtr<IVertexBuffer> VertexBuffer = IVertexBuffer::Create(const_cast<float*>(Vertices.Data()), static_cast<uint32_t>(Vertices.Num()), 0);
		TSharedPtr<IIndexBuffer> IndexBuffer = IIndexBuffer::Create(const_cast<uint32_t*>(Indices.Data()), static_cast<uint32_t>(Indices.Num()), 0);

		VertexBuffer->SetLayout(BufferLayout);
		VertexArray->AddVertexBuffer(VertexBuffer);
		VertexArray->SetIndexBuffer(IndexBuffer);

		return VertexArray;
    }

	char* CRendererUtils::GetVertexInputName(EVertexInputType VertexInput)
	{
		switch (VertexInput)
		{
		case EVertexInputType::VI_Position:
			return "Position";
		case EVertexInputType::VI_Normal:
			return "Normal";
		case EVertexInputType::VI_TexCoords:
			return "TexCoords";
		case EVertexInputType::VI_Tangent:
			return "Tangent";
		case EVertexInputType::VI_BiTangent:
			return "BiTangent";
		default:
			AA_CORE_LOG(Error, "Invalid Vertex Input passed in. No Vertex Input Name.");
		}

		return "";
	}

}