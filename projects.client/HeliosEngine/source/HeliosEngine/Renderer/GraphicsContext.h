#pragma once

#include <GLFW/glfw3.h>


namespace HeliosEngine {


	class GraphicsContext
	{
	public:
		virtual void Init() = 0;
		virtual void SwapBuffers() = 0;

		static Scope<GraphicsContext> Create(GLFWwindow* window);
	};


} // namespace HeliosEngine
