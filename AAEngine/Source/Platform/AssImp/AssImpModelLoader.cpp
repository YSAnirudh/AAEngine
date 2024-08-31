#include "AA_PreCompiledHeaders.h"
#include "AssImpModelLoader.h"

#include "Renderer/Buffer.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

namespace AAEngine {

	void CAssImpModelLoader::LoadModel_AssImp(const std::string& FileName, TArray<float>& OutVertices, TArray<uint32_t>& OutIndices, const CVertexBufferLayout& BufferLayout)
	{
		Assimp::Importer Importer;
		const aiScene* Scene = Importer.ReadFile(FileName, aiProcess_Triangulate | aiProcess_FlipUVs | aiProcess_CalcTangentSpace);

		if (Scene == nullptr || Scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || Scene->mRootNode == nullptr)
		{
			AA_CORE_LOG(Error, "Cannot load model from %s (AssImp)", FileName.c_str());
			return;
		}
		//Directory = Path.substr(0, Path.find_last_of('/'));

		ProcessNode(Scene->mRootNode, Scene, OutVertices, OutIndices, BufferLayout);
	}

	void CAssImpModelLoader::ProcessNode(aiNode* Node, const aiScene* Scene, TArray<float>& OutVertices, TArray<uint32_t>& OutIndices, const CVertexBufferLayout& BufferLayout)
	{
		for (unsigned int i = 0; i < Node->mNumMeshes; i++)
		{
			aiMesh* Mesh = Scene->mMeshes[Node->mMeshes[i]];
			ProcessMesh(Mesh, Scene, OutVertices, OutIndices, BufferLayout);
		}

		for (unsigned int i = 0; i < Node->mNumChildren; i++)
		{
			ProcessNode(Node->mChildren[i], Scene, OutVertices, OutIndices, BufferLayout);
		}
	}

	void CAssImpModelLoader::ProcessMesh(aiMesh* Mesh, const aiScene* Scene, TArray<float>& OutVertices, TArray<uint32_t>& OutIndices, const CVertexBufferLayout& BufferLayout)
	{
		OutVertices.Reserve(Mesh->mNumVertices * BufferLayout.GetStride());

		for (unsigned int i = 0; i < Mesh->mNumVertices; i++)
		{
			for (const FVertexBufferElement& Elem : BufferLayout)
			{
				switch (Elem.VertexInputType)
				{
				case EVertexInputType::VI_Position:
					for (uint32_t j = 0; j < Elem.GetComponentCount(); j++)
					{
						OutVertices.PushBack(Mesh->mVertices[i][j]);
					}
					break;
				case EVertexInputType::VI_Normal:
					if (Mesh->HasNormals())
					{
						for (uint32_t j = 0; j < Elem.GetComponentCount(); j++)
						{
							OutVertices.PushBack(Mesh->mNormals[i][j]);
						}
						break;
					}
					OutVertices.PushBack(0.0f);
					OutVertices.PushBack(0.0f);
					OutVertices.PushBack(0.0f);
					break;
				case EVertexInputType::VI_TexCoords:
					if (Mesh->mTextureCoords[0])
					{
						for (uint32_t j = 0; j < Elem.GetComponentCount(); j++)
						{
							OutVertices.PushBack(Mesh->mTextureCoords[0][i][j]);
						}
						break;
					}
					OutVertices.PushBack(0.0f);
					OutVertices.PushBack(0.0f);
					break;
				case EVertexInputType::VI_Tangent:
					if (Mesh->mTextureCoords[0] && Mesh->mTangents)
					{
						for (uint32_t j = 0; j < Elem.GetComponentCount(); j++)
						{
							OutVertices.PushBack(Mesh->mTangents[i][j]);
						}
						break;
					}
					OutVertices.PushBack(0.0f);
					OutVertices.PushBack(0.0f);
					OutVertices.PushBack(0.0f);
					break;
				case EVertexInputType::VI_BiTangent:
					if (Mesh->mTextureCoords[0] && Mesh->mBitangents)
					{
						for (uint32_t j = 0; j < Elem.GetComponentCount(); j++)
						{
							OutVertices.PushBack(Mesh->mBitangents[i][j]);
						}
						break;
					}
					OutVertices.PushBack(0.0f);
					OutVertices.PushBack(0.0f);
					OutVertices.PushBack(0.0f);
					break;
				default:
					AA_CORE_LOG(Error, "Invalid Input Type.");
					break;
				}
			}
		}

		for (unsigned int i = 0; i < Mesh->mNumFaces; i++)
		{
			aiFace Face = Mesh->mFaces[i];
			for (unsigned int j = 0; j < Face.mNumIndices; j++)
			{
				OutIndices.PushBack(Face.mIndices[j]);
			}
		}
	}

	void CAssImpModelLoader::LoadMaterialTextures(aiMaterial* Material)
	{
	}

}