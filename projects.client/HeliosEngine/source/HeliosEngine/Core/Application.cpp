#include "pch_engine.h"

#include "HeliosEngine/Core/Application.h"
#include "HeliosEngine/Core/EntryPoint.h"
#include "HeliosEngine/Utils/Path.h"

#include "GLFW/glfw3.h"

#include "HeliosEngine/Renderer/Renderer.h"


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
		: m_Specification(specification), m_Camera(-2.0f, 2.0f, -2.0f, 2.0f)
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


		m_VertexArray_1 = VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		Ref<VertexBuffer> vb = VertexBuffer::Create(vertices, sizeof(vertices));
		BufferLayout layout = {
			{ ShaderDataType::Float3, "a_Position"},
			{ ShaderDataType::Float4, "a_Color"}
		};
		vb->SetLayout(layout);
		m_VertexArray_1->AddVertexBuffer(vb);

		unsigned int indices[3] = {
			0, 1, 2
		};
		Ref<IndexBuffer>ib = IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray_1->SetIndexBuffer(ib);

		std::string vs_1 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";
		std::string fs_1 = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position + 0.5, 1.0);
				color = v_Color;
			}
		)";
		m_Shader_1.reset(new Shader(vs_1, fs_1));

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
/* DEBUG */if (n - s >= f) { s = n; std::ostringstream title; title << "loop cycles: " << c << "/s"; glfwSetWindowTitle((GLFWwindow*)m_Window->GetNativeWindow(), title.str().c_str()); c = 0; }
			if (!m_Minimized)
			{
				RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
				RenderCommand::Clear();

				m_Camera.SetPosition({0.5f, 0.5f, 0.0f});
				m_Camera.SetRotation(45.0f);

				Renderer::BeginScene(m_Camera);

				Renderer::Submit(m_Shader_1, m_VertexArray_1);

				Renderer::EndScene();

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
