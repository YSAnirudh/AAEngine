#include "AA_PreCompiledHeaders.h"
#include "RenderCommand.h"

#include "Platform/OpenGL/OpenGLRendererAPI.h"

namespace AAEngine {

	IRendererAPI* CRenderCommand::RendererAPI = new COpenGLRendererAPI();
}