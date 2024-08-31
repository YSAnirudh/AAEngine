#pragma once

namespace AAEngine {

	class CVertexBufferLayout;
	class IModelLoader
	{
	public:
		static void LoadModel(const std::string& FileName, TArray<float>& OutVertices, TArray<uint32_t>& OutIndices, const CVertexBufferLayout& BufferLayout);
	};
}