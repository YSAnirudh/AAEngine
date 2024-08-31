#pragma once
#include "Core/Math/MathIncludes.h"

namespace AAEngine {

	struct FPerFrameShaderData
	{
		FMatrix44f ViewMatrix;
		FMatrix44f ProjectionMatrix;
	};

	struct FPerObjectShaderData
	{
		FMatrix44f ModelMatrix;
	};

	enum class EVertexInputType
	{
		VI_Position,
		VI_Normal,
		VI_TexCoords,
		VI_Tangent,
		VI_BiTangent,
	};

	class IVertexArray;
	class CVertexBufferLayout;
	class CRendererUtils
	{
	public:

		static TSharedPtr<IVertexArray> MakeVertexArray(const TArray<float>& Vertices, const TArray<uint32_t>& Indices, const CVertexBufferLayout& BufferLayout);

		static char* GetVertexInputName(EVertexInputType VertexInput);

		// Variables
	public:

	};

}