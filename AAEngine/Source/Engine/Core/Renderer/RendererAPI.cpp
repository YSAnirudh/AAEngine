#include "AA_PreCompiledHeaders.h"
#include "RendererAPI.h"

namespace AAEngine {

	// Set the static variable of Current Graphics API and Model Loader
	IRendererAPI::EAPI IRendererAPI::RenderingAPI = IRendererAPI::EAPI::OpenGL;
	IRendererAPI::EModelLoader IRendererAPI::ModelLoader = IRendererAPI::EModelLoader::AssImp;

}