#include "pch_engine.h"

#include "HeliosEngine/Core/Log.h"

#include "spdlog/sinks/stdout_color_sinks.h"
#include "spdlog/sinks/basic_file_sink.h"

namespace HeliosEngine {


	Ref<spdlog::logger> Log::s_CoreLogger;
	Ref<spdlog::logger> Log::s_AppLogger;


	void Log::Init()
	{
		std::vector<spdlog::sink_ptr> logSinks;

		logSinks.emplace_back(std::make_shared<spdlog::sinks::stdout_color_sink_mt>());
		logSinks.emplace_back(std::make_shared<spdlog::sinks::basic_file_sink_mt>("Helios.log", true));

		logSinks[0]->set_pattern("%T %4n:%-5!l >> %v");
		logSinks[1]->set_pattern("%T %4n:%-5!l >> %^%v%$");

		// Logger for the HeliosEngine
		s_CoreLogger = std::make_shared<spdlog::logger>("Core", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_CoreLogger);
		s_CoreLogger->set_level(spdlog::level::trace);
		s_CoreLogger->flush_on(spdlog::level::trace);
		LOG_CORE_DEBUG("Log initialized");

		// Logger for the Application
		s_AppLogger = std::make_shared<spdlog::logger>("App", begin(logSinks), end(logSinks));
		spdlog::register_logger(s_AppLogger);
		s_AppLogger->set_level(spdlog::level::trace);
		s_AppLogger->flush_on(spdlog::level::trace);
		LOG_DEBUG("Log initialized");
	}


} // namespace HeliosEngine


