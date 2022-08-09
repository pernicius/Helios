#include "pch_engine.h"

#include "HeliosEngine/Renderer/Renderer.h"


namespace HeliosEngine {


	Scope<Renderer::SceneData> Renderer::s_SceneData = CreateScope<Renderer::SceneData>();


	void Renderer::BeginScene(OrthographicCamera& camera)
	{
		s_SceneData->ViewProjectionMatrix = camera.GetViewProjectionMatrix();
	}


	void Renderer::EndScene()
	{
	}


	void Renderer::Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray)
	{
		shader->Bind();
		shader->UploadUniformMat4("u_ViewProjection", s_SceneData->ViewProjectionMatrix);

		vertexArray->Bind();
		RenderCommand::DrawIndexed(vertexArray);
	}


} // namespace HeliosEngine
