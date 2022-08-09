#include "pch_engine.h"

#include "HeliosEngine/Renderer/Renderer.h"


namespace HeliosEngine {


	void Renderer::BeginScene()
	{
	}


	void Renderer::EndScene()
	{
	}


	void Renderer::Submit(const Ref<VertexArray>& vertexArray)
	{
		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}


} // namespace HeliosEngine
