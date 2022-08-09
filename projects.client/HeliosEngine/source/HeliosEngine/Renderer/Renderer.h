#pragma once

#include "HeliosEngine/Renderer/RenderCommand.h"


namespace HeliosEngine {


	class Renderer
	{
	public:
		static void BeginScene();
		static void EndScene();

		static void Submit(const Ref<VertexArray>& vertexArray);

		inline static RendererAPI::API GetAPI() { return RendererAPI::GetAPI(); }
	};


} // namespace HeliosEngine
