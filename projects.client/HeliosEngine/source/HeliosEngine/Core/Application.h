#pragma once

#include <string>
#include <filesystem>

#include "HeliosEngine/Core/Log.h"


namespace HeliosEngine {


	int AppMain(int argc, char** argv);


	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			LOG_CORE_ASSERT(index < Count, "");
			return Args[index];
		}
	};

	struct ApplicationSpecification
	{
		std::string Name;
		std::string WorkingDirectory;
		ApplicationCommandLineArgs CommandLineArgs;
	};


	class Application
	{
	public:
		Application(const ApplicationSpecification& specification);
		virtual ~Application();
		static Application& Get() { return *s_Instance; }
		const ApplicationSpecification& GetSpecification() const { return m_Specification; }

	private:
		void Run();
		static Application* s_Instance;
		ApplicationSpecification m_Specification;
		bool m_Running = true;
		bool m_Minimized = false;

		friend int AppMain(int argc, char** argv);
	};


	// To be defined in CLIENT
	Application* CreateApplication(ApplicationCommandLineArgs args);


} // namespace HeliosEngine
