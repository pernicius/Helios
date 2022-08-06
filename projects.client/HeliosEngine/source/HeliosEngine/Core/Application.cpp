#include "pch_engine.h"

#include "HeliosEngine/Core/Application.h"
#include "HeliosEngine/Core/EntryPoint.h"
#include "HeliosEngine/Core/Log.h"
#include "HeliosEngine/Utils/Path.h"

#include "GLFW/glfw3.h"


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
	}


	Application::~Application()
	{
	}

	void Application::Close()
	{
		m_Running = false;
	}


	void Application::OnEvent(Event& e)
	{
		EventDispatcher dispatcher(e);
		dispatcher.Dispatch<WindowCloseEvent>(HE_BIND_EVENT_FN(Application::OnWindowClose));
		dispatcher.Dispatch<WindowResizeEvent>(HE_BIND_EVENT_FN(Application::OnWindowResize));

//		for (auto it = m_LayerStack.rbegin(); it != m_LayerStack.rend(); ++it)
//		{
//			if (e.Handled)
//				break;
//			(*it)->OnEvent(e);
//		}
	}

	void Application::Run()
	{
//uint64_t f = glfwGetTimerFrequency();
//uint64_t s = glfwGetTimerValue();
//int c = 0;
		while (m_Running)
		{
//c++;
//uint64_t n = glfwGetTimerValue();
//if (n - s >= f)
//{
//s = n;
//std::cout << "cycles: " << c << "/s" << std::endl;
//c = 0;
//}
			if (!m_Minimized)
			{
				// TODO
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
