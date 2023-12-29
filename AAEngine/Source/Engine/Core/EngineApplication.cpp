#include "AA_PreCompiledHeaders.h"
#include "EngineApplication.h"
#include "EventSystem/Event.h"
#include "Input/Input.h"

#if AA_TESTER_FILE
	#if defined(AA_RELEASE) || defined(AA_DEBUG)
		#include "Tests/TesterFile.h"
	#endif // AA_DEBUG
#endif

// Temp

#include "Renderer/IncludesRenderer.h"

namespace AAEngine {

	CEngineApplication* CEngineApplication::EngineApplicationInstance = nullptr;

	CEngineApplication::CEngineApplication()
	{
#if !AA_TESTER_FILE
		AA_CORE_ASSERT(!EngineApplicationInstance, "Instance Already Present! Invalid Static ref.");
		EngineApplicationInstance = this;

		ApplicationWindow = TUniquePtr<IWindow>(IWindow::Create());
		ApplicationWindow->SetEventCallbackFunction(BIND_EVENT_FUNCTION(this, &CEngineApplication::HandleEvent));

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

			void main()
			{
				gl_Position = vec4(Position, 1.0f);
			}
			
		)";


		const char* FragmentSource = R"(
			#version 460
			
			layout(location = 0) out vec4 Color;

			void main()
			{
				Color = vec4(1.0f, 1.0f, 1.0f, 1.0f);
			}
			
		)";

		IShader* Shader = IShader::Create(VertexSource, FragmentSource);

		float Positions[9] = {
			-0.5f, -0.5f, 0.0f,
			0.0f, 0.5f, 0.0f,
			0.5f, -0.5f, 0.0f
		};

		TSharedPtr<IVertexArray> VertexArray;
		VertexArray.reset(IVertexArray::Create());

		TSharedPtr<IVertexBuffer> VertexBuffer;
		VertexBuffer.reset(IVertexBuffer::Create(Positions, 9, 0));

		CVertexBufferLayout Layout = {
			{ EShaderVarType::Float3, "Position" }
		};

		VertexBuffer->SetLayout(Layout);
		VertexArray->AddVertexBuffer(VertexBuffer);

		uint32_t Indices[3] = { 0,1,2 };
		TSharedPtr<IIndexBuffer> IndexBuffer;
		IndexBuffer.reset(IIndexBuffer::Create(Indices, 3, 0));

		VertexArray->SetIndexBuffer(IndexBuffer);
		
		while(bIsApplicationRunning && !AA_TESTER_FILE)
		{
			CRenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1.0f });
			CRenderCommand::Clear();

			CRenderer::BeginScene();

			Shader->Bind();
			CRenderer::Submit(VertexArray);

			CRenderer::EndScene();

			for (CLayer* Layer : LayerStack)
			{
				Layer->OnUpdate();
			}

			ImGuiLayer->Begin();
			for (CLayer* Layer : LayerStack)
			{
				Layer->OnImGuiRender();
			}
			ImGuiLayer->End();

			ApplicationWindow->Tick();
		}
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
