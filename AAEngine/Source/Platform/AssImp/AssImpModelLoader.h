#pragma once
#include "Renderer/ModelLoader.h"

struct aiNode;
struct aiMesh;
struct aiScene;
struct aiMaterial;

namespace AAEngine {

	class CVertexBufferLayout;
	class CAssImpModelLoader : public IModelLoader
	{
	public:
		static void LoadModel_AssImp(const std::string& FileName, TArray<float>& OutVertices, TArray<uint32_t>& OutIndices, const CVertexBufferLayout& BufferLayout);

	private:

		static void ProcessNode(aiNode* Node, const aiScene* Scene, TArray<float>& OutVertices, TArray<uint32_t>& OutIndices, const CVertexBufferLayout& BufferLayout);
		static void ProcessMesh(aiMesh* Mesh, const aiScene* Scene, TArray<float>& OutVertices, TArray<uint32_t>& OutIndices, const CVertexBufferLayout& BufferLayout);
		static void LoadMaterialTextures(aiMaterial* Material);
	};
}