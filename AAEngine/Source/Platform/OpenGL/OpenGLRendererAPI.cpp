#include "AA_PreCompiledHeaders.h"
#include "OpenGLRendererAPI.h"

#include <glad/glad.h>

namespace AAEngine {
	void COpenGLRendererAPI::Init()
	{
		glEnable(GL_BLEND);
		glBlendFunc(GL_BLEND_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	void COpenGLRendererAPI::Clear()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	}

	void COpenGLRendererAPI::SetClearColor(const FColor& Color)
	{
		glClearColor(Color.R, Color.G, Color.B, Color.A);
	}

	void COpenGLRendererAPI::DrawIndexed(const TSharedPtr<IVertexArray>& VertexArray)
	{
		VertexArray->Bind();
		glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(VertexArray->GetIndexBuffer()->GetIndexCount()), GL_UNSIGNED_INT, nullptr);
	}

}
