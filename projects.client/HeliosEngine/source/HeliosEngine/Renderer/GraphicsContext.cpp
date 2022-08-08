#include "pch_engine.h"

#include "HeliosEngine/Core/Log.h"

#include "HeliosEngine/Renderer/Renderer.h"
#include "HeliosEngine/Renderer/GraphicsContext.h"

// Platformspezific
#ifdef HE_BUILDWITH_RENDERER_OPENGL
	#include "Platform/Renderer/OpenGL/GLContext.h"
#endif


namespace HeliosEngine {


	GraphicsContext* GraphicsContext::Create(GLFWwindow* window)
	{
		switch (Renderer::GetAPI())
		{
		case RendererAPI::None: LOG_CORE_ASSERT(false, "RendererAPI::None is not supported!"); return nullptr;

			// Platformspezific
#ifdef HE_BUILDWITH_RENDERER_OPENGL
		case RendererAPI::OpenGL: return new GLContext(window);
#endif

		default: LOG_CORE_ASSERT(false, "Unknown RendererAPI!"); return nullptr;
		}
	}


} // namespace HeliosEngine
