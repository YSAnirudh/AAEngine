#pragma once

#include "RenderCommand.h"
#include "RendererCommons.h"
#include "Renderable.h"
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
		* Initialization of Renderer
		*/
		static void Init()
		{
			CRenderCommand::Init();
		}

		/*
		* Before we begin a scene render
		*/
		static void BeginScene(CCamera& Camera)
		{
			SceneData->FrameShaderData.ViewMatrix = Camera.GetCameraViewMatrix();
			SceneData->FrameShaderData.ProjectionMatrix = Camera.GetCameraProjectionMatrix();
		}
		/*
		* After we end a scene render
		*/
		static void EndScene() {}

		/*
		* Submit a vertex array to be drawn to the Render Command Queue
		* 
		* @param Vertex Array
		*/
		static void Submit(const TSharedPtr<IShader>& Shader, const TSharedPtr<IRenderable>& RenderableObject)
		{
			Shader->Bind();
			FMatrix44f Transform = FMatrix44f::MakeFromLocation(FVector3f(0.0f, 0.0f, 5.0f)); // FMatrix44f::MakeFromRotationXYZ(Rotation) * FMatrix44f::MakeFromLocation(Position);
			std::dynamic_pointer_cast<COpenGLShader>(Shader)->UploadUniformMat4("ModelMatrix", RenderableObject->GetModelMatrix());
			std::dynamic_pointer_cast<COpenGLShader>(Shader)->UploadUniformMat4("ViewMatrix", SceneData->FrameShaderData.ViewMatrix);
			std::dynamic_pointer_cast<COpenGLShader>(Shader)->UploadUniformMat4("ProjectionMatrix", SceneData->FrameShaderData.ProjectionMatrix);
			RenderableObject->Render();
		}

		/*
		* Static getter for the currently used Graphics API
		*/
		static IRendererAPI::EAPI GetAPI() { return IRendererAPI::GetAPI(); }
	private:
		struct FSceneData
		{
			FPerFrameShaderData FrameShaderData;
		};

		static FSceneData* SceneData;
	};
}