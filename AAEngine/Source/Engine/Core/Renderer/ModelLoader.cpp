#include "AA_PreCompiledHeaders.h"
#include "ModelLoader.h"
#include "RendererIncludes.h"

#include "Platform/AssImp/AssImpModelLoader.h"

namespace AAEngine {

	void IModelLoader::LoadModel(const std::string& FileName, TArray<float>& OutVertices, TArray<uint32_t>& OutIndices, const CVertexBufferLayout& BufferLayout)
	{
		switch (IRendererAPI::GetModelLoader())
		{
		case IRendererAPI::EModelLoader::None:
			AA_CORE_ASSERT(false, "None API Specified!");
			return;
		case IRendererAPI::EModelLoader::AssImp:
			CAssImpModelLoader::LoadModel_AssImp(FileName, OutVertices, OutIndices, BufferLayout);
			return;
		}
		AA_CORE_ASSERT(false, "Unknown API Specified!");
	}

}