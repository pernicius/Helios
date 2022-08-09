#include "pch_engine.h"

#include "HeliosEngine/Renderer/RenderCommand.h"


namespace HeliosEngine {


	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();;


} // namespace HeliosEngine
