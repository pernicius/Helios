#include "pch_engine.h"

#include "HeliosEngine/Core/Window.h"
#include "HeliosEngine/Core/Log.h"
#include "HeliosEngine/Events/ApplicationEvent.h"
#include "HeliosEngine/Events/MouseEvent.h"
#include "HeliosEngine/Events/KeyEvent.h"

#include "GLFW/glfw3.h"
#include "glad/gl.h"


namespace HeliosEngine {


	Scope<Window> Window::Create(const WindowSpecification& spec)
	{
		return CreateScope<Window>(spec);
	}
	static uint8_t s_GLFWWindowCount = 0;


	static void GLFWErrorCallback(int error, const char* description)
	{
		LOG_GLFW_ERROR("({0}): {1}", error, description);
	}


	Window::Window(const WindowSpecification& spec)
	{
		Init(spec);
	}


	Window::~Window()
	{
		Shutdown();
	}


	void Window::Init(const WindowSpecification& spec)
	{
		m_Data.Title = spec.Title;
		m_Data.Width = spec.Width;
		m_Data.Height = spec.Height;

		LOG_CORE_INFO("Creating window {0} ({1}, {2})", spec.Title, spec.Width, spec.Height);

		if (s_GLFWWindowCount == 0)
		{
			int success = glfwInit();
			LOG_CORE_ASSERT(success, "Could not initialize GLFW!");
			glfwSetErrorCallback(GLFWErrorCallback);
		}

		{
#if defined(HE_BUILD_DEBUG)
//			if (Renderer::GetAPI() == RendererAPI::API::OpenGL)
				glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GLFW_TRUE);
#endif
			m_Window = glfwCreateWindow((int)spec.Width, (int)spec.Height, m_Data.Title.c_str(), nullptr, nullptr);
			++s_GLFWWindowCount;
		}

		glfwMakeContextCurrent(m_Window);
		int version = gladLoadGL(glfwGetProcAddress);
		LOG_CORE_ASSERT(version, "Failed to initialize OpenGL context!");
		LOG_CORE_INFO("OpenGL {0}.{1} Info:", GLAD_VERSION_MAJOR(version), GLAD_VERSION_MINOR(version));
		LOG_CORE_INFO("  Vendor:   {0}", glGetString(GL_VENDOR));
		LOG_CORE_INFO("  Renderer: {0}", glGetString(GL_RENDERER));
		LOG_CORE_INFO("  Version:  {0}", glGetString(GL_VERSION));
		//		m_Context = GraphicsContext::Create(m_Window);
//		m_Context->Init();

		glfwSetWindowUserPointer(m_Window, &m_Data);
		SetVSync(true);

		// Set GLFW callbacks
		InitCallbacks();
	}


	void Window::Shutdown()
	{
		glfwDestroyWindow(m_Window);
		--s_GLFWWindowCount;

		if (s_GLFWWindowCount == 0)
		{
			glfwTerminate();
		}
	}


	void Window::OnUpdate()
	{
		glfwPollEvents();
		glfwSwapBuffers(m_Window);
//		m_Context->SwapBuffers();
	}


	void Window::SetVSync(bool enabled)
	{
		if (enabled)
			glfwSwapInterval(1);
		else
			glfwSwapInterval(0);

		m_Data.VSync = enabled;
	}


	bool Window::IsVSync() const
	{
		return m_Data.VSync;
	}


	void Window::InitCallbacks()
	{
		// Set GLFW callbacks (Key input)
		glfwSetKeyCallback(m_Window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					KeyPressedEvent event(key, 0);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					KeyReleasedEvent event(key);
					data.EventCallback(event);
					break;
				}
				case GLFW_REPEAT:
				{
					KeyPressedEvent event(key, true);
					data.EventCallback(event);
					break;
				}
				}
			});
		glfwSetCharCallback(m_Window, [](GLFWwindow* window, unsigned int keycode)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				KeyTypedEvent event(keycode);
				data.EventCallback(event);
			});

		// Set GLFW callbacks (Mouse input)
		glfwSetCursorPosCallback(m_Window, [](GLFWwindow* window, double xPos, double yPos)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseMovedEvent event((float)xPos, (float)yPos);
				data.EventCallback(event);
			});
		//glfwSetCursorEnterCallback
		glfwSetMouseButtonCallback(m_Window, [](GLFWwindow* window, int button, int action, int mods)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				switch (action)
				{
				case GLFW_PRESS:
				{
					MouseButtonPressedEvent event(button);
					data.EventCallback(event);
					break;
				}
				case GLFW_RELEASE:
				{
					MouseButtonReleasedEvent event(button);
					data.EventCallback(event);
					break;
				}
				}
			});
		glfwSetScrollCallback(m_Window, [](GLFWwindow* window, double xOffset, double yOffset)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);

				MouseScrolledEvent event((float)xOffset, (float)yOffset);
				data.EventCallback(event);
			});

		// Set GLFW callbacks (Joystick)
		//glfwSetJoystickCallback

		// Set GLFW callbacks (Path drop input)
		//glfwSetDropCallback

		// Set GLFW callbacks (Window events)
		glfwSetWindowCloseCallback(m_Window, [](GLFWwindow* window)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				WindowCloseEvent event;
				data.EventCallback(event);
			});
		glfwSetWindowSizeCallback(m_Window, [](GLFWwindow* window, int width, int height)
			{
				WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
				data.Width = width;
				data.Height = height;

				WindowResizeEvent event(width, height);
				data.EventCallback(event);
			});
		//glfwSetWindowContentScaleCallback
		//glfwSetWindowPosCallback
		//glfwSetWindowIconifyCallback
		//glfwSetWindowMaximizeCallback
		//glfwSetWindowFocusCallback
		//glfwSetWindowRefreshCallback


		// Set GLFW callbacks (Framebuffer events)
		//glfwSetFramebufferSizeCallback
	}


} // namespace HeliosEngine
