#include "AA_PreCompiledHeaders.h"
#include "EngineApplication.h"

#if AA_TESTER_FILE
	#if defined(AA_RELEASE) || defined(AA_DEBUG)
		#include "Tests/TesterFile.h"
	#endif // AA_DEBUG
#endif

#include "EventSystem/Event.h"
#include "Input/Input.h"
#include "Renderer/IncludesRenderer.h"

#include "Platform/OpenGL/OpenGLShader.h"

// Temp
#include <GLFW/glfw3.h>

namespace AAEngine {

	CEngineApplication* CEngineApplication::EngineApplicationInstance = nullptr;

	CEngineApplication::CEngineApplication()
	{
#if !AA_TESTER_FILE
		AA_CORE_ASSERT(!EngineApplicationInstance, "Instance Already Present! Invalid Static ref.");
		EngineApplicationInstance = this;

		ApplicationWindow = TUniquePtr<IWindow>(IWindow::Create());
		ApplicationWindow->SetEventCallbackFunction(BIND_EVENT_FUNCTION(this, &CEngineApplication::HandleEvent));

		CRenderer::Init();

		ImGuiLayer = new CImGuiLayer();
		PushOverlay(ImGuiLayer);
#endif
	}

	CEngineApplication::~CEngineApplication()
	{
	}

	void CEngineApplication::Run()
	{
/*
* Useful for Running Tests on Custom Libraries
*/
#if AA_TESTER_FILE
	#if defined(AA_RELEASE) || defined(AA_DEBUG)
		CTester::RunTester();
	#endif
#else

		const char* VertexSource = R"(
			#version 460
			
			layout(location = 0) in vec3 Position;

			out vec4 color;

			uniform mat4 MVPMatrix;

			void main()
			{
				gl_Position = MVPMatrix * vec4(Position, 1.0f);
				color = vec4(Position, 1.0f);
				gl_Position.z = -gl_Position.z;
			}
			
		)";


		const char* FragmentSource = R"(
			#version 460
			
			layout(location = 0) out vec4 Color;

			in vec4 color;

			void main()
			{
				Color = color;
			}
			
		)";

		std::string FilePath = "../AAEngine/Source/Engine/Shaders/TestGLShader.glsl";
		//TSharedPtr<IShader> Shader = IShader::Create("Helol", VertexSource, FragmentSource);
		TSharedPtr<IShader> Shader = IShader::Create(FilePath);
		
		//Shader.reset(IShader::Create(VertexSource, FragmentSource));
		//Shader.reset(IShader::Create("../AAEngine/Source/Engine/Shaders/TestGLShader.glsl"));

		float Positions[3 * 8] = {
			-1.0f,	-1.0f, -1.0f,// 0.0f,	0.0f, 0.0f,
			-1.0f,	1.0f , -1.0f,// 0.0f,	0.0f, 0.0f,
			1.0f ,	1.0f , -1.0f,// 0.0f,	0.0f, 0.0f,
			1.0f ,	-1.0f, -1.0f,// 0.0f,	0.0f, 0.0f,
			-1.0f,	-1.0f, 1.0f, //0.0f,	0.0f, 0.0f,
			-1.0f,	1.0f , 1.0f, //0.0f,	0.0f, 0.0f,
			1.0f ,	1.0f , 1.0f, //0.0f,	0.0f, 0.0f,
			1.0f ,	-1.0f, 1.0f //0.0f,	0.0f, 0.0f
		};

		TSharedPtr<IVertexArray> VertexArray = IVertexArray::Create();

		TSharedPtr<IVertexBuffer> VertexBuffer = IVertexBuffer::Create(Positions, 3 * 8, 0);

		CVertexBufferLayout Layout = {
			{ EShaderVarType::Float3, "Position" }
			//{ EShaderVarType::Float3, "Normal" }
		};

		VertexBuffer->SetLayout(Layout);
		VertexArray->AddVertexBuffer(VertexBuffer);

		uint32_t Indices[3 * 12] = { 
			0, 1, 2, 
			2, 3, 0,
			3, 7, 2,
			2, 6, 7,
			1, 5, 2,
			2, 6, 5,
			0, 3, 7,
			7, 4, 0,
			0, 1, 5,
			5, 4, 0,
			5, 6, 7,
			7, 4, 5
		};
		TSharedPtr<IIndexBuffer> IndexBuffer = IIndexBuffer::Create(Indices, 3 * 12, 0);

		VertexArray->SetIndexBuffer(IndexBuffer);

		TUniquePtr<CPerspectiveCamera> Camera = MakeUnique<CPerspectiveCamera>(60.0f, (float)ApplicationWindow->GetWindowWidth() / (float)ApplicationWindow->GetWindowHeight(), 0.01f, 100.f);
		
		FVector3f CurrentCamPos(0.0f, 0.0f, -1.f);
		FEulerf CurrentCameraRotation(0.0f);
		FVector3f Position(0.0f, 0.0f, 10.f);
		FEulerf Rotation(0.0f);
		FVector2f CurrMousePos(CInput::GetMouseX(), CInput::GetMouseY());
		//FVector2f CurrMousePos
		float MouseSensitivity = 1.0f;
		
		while(bIsApplicationRunning)
		{
			/*
			* DeltaTime Calculation
			*/
			float CurrentTime = IWindow::GetCurrentTimeElapsed();
			float DeltaTime = CurrentTime - LastTrackedTime;
			LastTrackedTime = CurrentTime;
			//AA_CORE_LOG(Info, "DeltaTime: %f", DeltaTime);

			CRenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			CRenderCommand::Clear();

			float CameraMoveSpeed = 10.0f * DeltaTime;
			float CameraTurnSpeed = 45.0f * DeltaTime;

			FVector2f MouseDelta = CurrMousePos - FVector2f(CInput::GetMouseX(), CInput::GetMouseY());
			CurrMousePos = FVector2f(CInput::GetMouseX(), CInput::GetMouseY());
			//AA_CORE_LOG(Trace, "CurrMousePos: x: %f, y: %f", CurrMousePos.X, CurrMousePos.Y);
			//AA_CORE_LOG(Trace, "Mouse Delta: x: %f, y: %f", MouseDelta.X, MouseDelta.Y);

			bool bIsMouseRightPressed = CInput::IsMouseButtonPressed(FMouse::ButtonRight);

			if (bIsMouseRightPressed)
			{
				glfwSetInputMode((GLFWwindow*)ApplicationWindow->GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
				CurrentCameraRotation.Pitch -= CameraTurnSpeed * MouseDelta.Y * 0.25f * MouseSensitivity;
				CurrentCameraRotation.Yaw += CameraTurnSpeed * MouseDelta.X * 0.25f * MouseSensitivity;

				if (CInput::IsKeyPressed(FKey::W))
				{
					CurrentCamPos.Z -= CameraMoveSpeed;
				}
				else if (CInput::IsKeyPressed(FKey::S))
				{
					CurrentCamPos.Z += CameraMoveSpeed;
				}
				else if (CInput::IsKeyPressed(FKey::E))
				{
					CurrentCamPos.Y -= CameraMoveSpeed;
				}
				else if (CInput::IsKeyPressed(FKey::Q))
				{
					CurrentCamPos.Y += CameraMoveSpeed;
				}
				else if (CInput::IsKeyPressed(FKey::D))
				{
					CurrentCamPos.X -= CameraMoveSpeed;
				}
				else if (CInput::IsKeyPressed(FKey::A))
				{
					CurrentCamPos.X += CameraMoveSpeed;
				}
			}
			else
			{
				glfwSetInputMode((GLFWwindow*)ApplicationWindow->GetNativeWindow(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
			}

			Camera->SetCameraLocation(CurrentCamPos);
			Camera->SetCameraRotation(CurrentCameraRotation);
			
			FMatrix44f Transform = FMatrix44f::MakeFromLocation(FVector3f(0.0f, 0.0f, 5.0f)); // FMatrix44f::MakeFromRotationXYZ(Rotation) * FMatrix44f::MakeFromLocation(Position);
			CRenderer::BeginScene(*Camera);
			
			CRenderer::Submit(Shader, VertexArray, Transform);

			CRenderer::EndScene();

			for (CLayer* Layer : LayerStack)
			{
				Layer->OnUpdate(DeltaTime);
			}

			ImGuiLayer->Begin();
			for (CLayer* Layer : LayerStack)
			{
				Layer->OnImGuiRender();
			}
			ImGuiLayer->End();

			ApplicationWindow->Tick();
		}
		AA_CORE_LOG(Warning, "Application Closed!");
#endif

	}

	void CEngineApplication::HandleEvent(CEvent& Event)
	{
		// Event logs
		// AA_CORE_LOG(Info, Event.ToString().c_str());

		CEventHandler EventHandler(Event);
		EventHandler.HandleEvent<CWindowCloseEvent>(BIND_EVENT_FUNCTION(this, &CEngineApplication::OnWindowClose));

		for (auto It = LayerStack.end(); It != LayerStack.begin(); )
		{
			(*--It)->OnEvent(Event);
			if (Event.IsHandled())
			{
				break;
			}
		}
	}

	void CEngineApplication::PushLayer(CLayer* Layer)
	{
		LayerStack.PushLayer(Layer);
	}

	void CEngineApplication::PushOverlay(CLayer* Overlay)
	{
		LayerStack.PushOverlay(Overlay);
	}
	
	bool CEngineApplication::OnWindowClose(const CWindowCloseEvent& Event)
	{
		bIsApplicationRunning = false;
		return true;
	}
}
