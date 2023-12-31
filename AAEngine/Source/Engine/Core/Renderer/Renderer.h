#pragma once

#include "RenderCommand.h"

#include "Camera.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace AAEngine {

	/*
	* Platform Independent Renderer Class
	*/
	class CRenderer
	{
	public:
		/*
		* Before we begin a scene render
		*/
		static void BeginScene(CCamera& Camera)
		{
			SceneData->ViewProjectionMatrix = Camera.GetCameraViewProjectionMatrix();
		}
		/*
		* After we begin a scene render
		*/
		static void EndScene() {}

		/*
		* Submit a vertex array to be drawn to the Render Command Queue
		* 
		* @param Vertex Array
		*/
		static void Submit(const TSharedPtr<IShader>& Shader, const TSharedPtr<IVertexArray>& VertexArray, const FMatrix44f& Transform)
		{
			Shader->Bind();
			std::dynamic_pointer_cast<COpenGLShader>(Shader)->UploadUniformMat4("MVPMatrix", Transform * SceneData->ViewProjectionMatrix);
			CRenderCommand::DrawIndexed(VertexArray);
		}

		/*
		* Static getter for the currently used Graphics API
		*/
		static IRendererAPI::EAPI GetAPI() { return IRendererAPI::GetAPI(); }
	private:
		struct FSceneData
		{
			FMatrix44f ViewProjectionMatrix;
		};

		static FSceneData* SceneData;
	};
}