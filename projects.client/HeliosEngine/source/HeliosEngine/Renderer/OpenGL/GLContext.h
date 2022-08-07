#pragma once

#include "HeliosEngine/Renderer/GraphicsContext.h"

#include "GLFW/glfw3.h"


namespace HeliosEngine {


	class GLContext : public GraphicsContext
	{
	public:
		GLContext(GLFWwindow* windowHandle);

		void Init() override;
		void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};


} // namespace HeliosEngine
