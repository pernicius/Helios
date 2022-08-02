#include "pch_engine.h"

#include "HeliosEngine/Core/Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"


namespace HeliosEngine {


	std::shared_ptr<spdlog::logger> Log::s_CoreLogger;
	std::shared_ptr<spdlog::logger> Log::s_AppLogger;


	void Log::Init()
	{
		spdlog::set_pattern("%T %4n:%-5!l :: %^%v%$");

		// Logger for the HeliosEngine
		s_CoreLogger = spdlog::stdout_color_mt("Core");
		s_CoreLogger->set_level(spdlog::level::trace);
		LOG_CORE_DEBUG("Log initialized");

		// Logger for the Application
		s_AppLogger = spdlog::stdout_color_mt("App");
		s_AppLogger->set_level(spdlog::level::trace);
		LOG_DEBUG("Log initialized");

	}


} // namespace HeliosEngine
