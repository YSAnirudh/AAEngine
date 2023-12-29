#include "AA_PreCompiledHeaders.h"
#include "RendererAPI.h"

namespace AAEngine {

	// Set the static variable of Current Graphics API
	IRendererAPI::EAPI IRendererAPI::RenderingAPI = IRendererAPI::EAPI::OpenGL;

}