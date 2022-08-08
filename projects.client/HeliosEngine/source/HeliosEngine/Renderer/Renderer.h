#pragma once


namespace HeliosEngine {


	enum class RendererAPI
	{
		None = 0,

#ifdef HE_BUILDWITH_RENDERER_OPENGL
		OpenGL,
#endif
#ifdef HE_BUILDWITH_RENDERER_VULKAN
		Vulkan,
#endif
#ifdef HE_BUILDWITH_RENDERER_DIRECTX
		DirectX,
#endif

	};


#if   defined HE_BUILDWITH_RENDERER_OPENGL
#		define HE_DEFAULT_RENDERERAPI RendererAPI::OpenGL
#elif defined HE_BUILDWITH_RENDERER_VULKAN
#		define HE_DEFAULT_RENDERERAPI RendererAPI::Vulkan
#elif defined HE_BUILDWITH_RENDERER_DIRECTX
#		define HE_DEFAULT_RENDERERAPI RendererAPI::DirectX
#endif


	class Renderer
	{
	public:
		inline static RendererAPI GetAPI() { return s_RendererAPI; }
	private:
		static RendererAPI s_RendererAPI;
	};


} // namespace HeliosEngine
