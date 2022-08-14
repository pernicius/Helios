#include "pch_engine.h"

#include "HeliosEngine/Renderer/RenderCommand.h"


namespace Helios {


	Scope<RendererAPI> RenderCommand::s_RendererAPI = RendererAPI::Create();;


} // namespace Helios
