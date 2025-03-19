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
		* Sending Scene Uniforms to the Shader
		*/
		static void UploadSceneUniforms(const TSharedPtr<IShader>& Shader)
		{
			Shader->UploadUniformMat4("ViewMatrix", SceneData->FrameShaderData.ViewMatrix);
			Shader->UploadUniformMat4("ProjectionMatrix", SceneData->FrameShaderData.ProjectionMatrix);
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
			FMatrix44f Transform = FMatrix44f::MakeFromLocation(FVector3f(0.0f, 0.0f, 5.0f)); // FMatrix44f::MakeFromRotationXYZ(Rotation) * FMatrix44f::MakeFromLocation(Position);
			Shader->UploadUniformMat4("ModelMatrix", RenderableObject->GetModelMatrix());
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