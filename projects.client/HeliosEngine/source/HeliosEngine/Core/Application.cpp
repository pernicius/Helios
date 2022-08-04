#include "pch_engine.h"

#include "HeliosEngine/Core/Application.h"
#include "HeliosEngine/Core/EntryPoint.h"
#include "HeliosEngine/Core/Log.h"
#include "HeliosEngine/Utils/Path.h"


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
	}


	Application::~Application()
	{
	}


	void Application::Run()
	{
		while (m_Running)
		{
		}
	}


} // namespace HeliosEngine
