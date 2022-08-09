#pragma once

#include "HeliosEngine/Renderer/RendererAPI.h"


namespace HeliosEngine {


	class GLRendererAPI : public RendererAPI
	{
	public:
		void SetClearColor(const glm::vec4& color) override;
		void Clear() override;

		void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
	};


} // namespace HeliosEngine
