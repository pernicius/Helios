#include "pch_engine.h"

#include "HeliosEngine/Core/Application.h"
#include "HeliosEngine/Core/EntryPoint.h"
#include "HeliosEngine/Core/Log.h"
#include "HeliosEngine/Utils/Path.h"

#include "GLFW/glfw3.h"
#include "glad/gl.h"


namespace HeliosEngine {


	int AppMain(int argc, char** argv)
	{
		auto app = CreateApplication({ argc, argv });
		app->Run();
		delete app;

		return 0;
	}


	Application* Application::s_Instance = nullptr;


	Application::Application(const ApplicationSpecification& specification)
		: m_Specification(specification)
	{
		// set working directory
		if (!m_Specification.WorkingDirectory.empty())
			std::filesystem::current_path(m_Specification.WorkingDirectory);
		if (m_Specification.hints & Hints::HINT_USE_CWD)
			m_Specification.WorkingDirectory = Utils::GetCurrentDir();
		if (m_Specification.hints & Hints::HINT_USE_EXEPATH_AS_CWD)
			m_Specification.WorkingDirectory = Utils::GetExePath();

		Log::Init("HeliosEngine.log", m_Specification.WorkingDirectory);

		LOG_CORE_DEBUG("Working path: {0}", m_Specification.WorkingDirectory);

		LOG_CORE_ASSERT(!s_Instance, "Application already exists!");
		s_Instance = this;

		m_Window = Window::Create(WindowSpecification(m_Specification.Name));
		m_Window->SetEventCallback(HE_BIND_EVENT_FN(Application::OnEvent));


		// vertex buffer
		glGenVertexArrays(1, &m_VertexArray);
		glBindVertexArray(m_VertexArray);

		glGenBuffers(1, &m_VertexBuffer);
		glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

		float vertices[3 * 3] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.0f,  0.5f, 0.0f
		};
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

		// index buffer
		glGenBuffers(1, &m_IndexBuffer);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

		unsigned int indices[3] = {
			0, 1, 2
		};
		glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

		std::string vertexSrc = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = vec4(a_Position, 1.0);
			}
		)";
		std::string fragmentSrc = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position + 0.5, 1.0);
			}
		)";

		m_Shader.reset(new Shader(vertexSrc, fragmentSrc));

	}


	Application::~Application()
	{
	}


	void Application::PushLayer(Layer* layer)
	{
		m_LayerStack.PushLayer(layer);
		layer->OnAttach();
	}


	void Application::PushOverlay(Layer* layer)
	{
		m_LayerStack.PushOverlay(layer);
		layer->OnAttach();
	}


	void Application::Close()
	{
		m_Running = false;
	}


	void Application::OnEvent(Event& e)
	{
		LOG_CORE_TRACE("{0}", e);

		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(HE_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(HE_BIND_EVENT_FN(Application::OnWindowResize));

		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
		{
			if (e.Handled)
				break;
			(*it)->OnEvent(e);
		}
	}

	void Application::Run()
	{
/* DEBUG */uint64_t f = glfwGetTimerFrequency();
/* DEBUG */uint64_t s = glfwGetTimerValue();
/* DEBUG */int c = 0;
		while (m_Running)
		{
/* DEBUG */c++;
/* DEBUG */uint64_t n = glfwGetTimerValue();
/* DEBUG */if (n - s >= f) { s = n; std::cout << "loop cycles: " << c << "/s" << std::endl; c = 0; }
			if (!m_Minimized)
			{
				glClearColor(0.1f, 0.1f, 0.1f, 1);
				glClear(GL_COLOR_BUFFER_BIT);

				m_Shader->Bind();

				glBindVertexArray(m_VertexArray);
				glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

				for (Layer* layer : m_LayerStack)
					layer->OnUpdate();
//TODO				layer->OnUpdate(timestep);
			}

			m_Window->OnUpdate();
		}
	}


	bool Application::OnWindowClose(WindowCloseEvent& e)
	{
		m_Running = false;
		return true;
	}


	bool Application::OnWindowResize(WindowResizeEvent& e)
	{
		if (e.GetWidth() == 0 || e.GetHeight() == 0)
		{
			m_Minimized = true;
			return false;
		}

		m_Minimized = false;

		return false;
	}


} // namespace HeliosEngine
