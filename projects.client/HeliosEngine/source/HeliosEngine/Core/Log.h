#pragma once

#pragma warning(push, 0)
#	include <spdlog/spdlog.h>
#	include <spdlog/fmt/ostr.h>
#pragma warning(pop)

#include "HeliosEngine/Debug/DebugBreak.h"


namespace Helios {


	class Log
	{
	public:
		static void Init(const std::string& filename = "HeliosEngine.log", const std::string& path = "");

		static Ref<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		static Ref<spdlog::logger>& GetGLFWLogger() { return s_GLFWLogger; }
		static Ref<spdlog::logger>& GetAppLogger() { return s_AppLogger; }
	private:
		static Ref<spdlog::logger> s_CoreLogger;
		static Ref<spdlog::logger> s_GLFWLogger;
		static Ref<spdlog::logger> s_AppLogger;
	};


} // namespace Helios


// log levels
#define HE_LOG_LEVEL_TRACE 0
#define HE_LOG_LEVEL_DEBUG 1
#define HE_LOG_LEVEL_INFO  2
#define HE_LOG_LEVEL_WARN  3
#define HE_LOG_LEVEL_ERROR 4
#define HE_LOG_LEVEL_FATAL 5
#define HE_LOG_LEVEL_OFF   6

// minimal log level
#if !defined(HE_LOG_LEVEL)
#    define HE_LOG_LEVEL HE_LOG_LEVEL_INFO
#endif

// Logging macros for HeliosEngine
#define LOG_CORE_TRACE(...) (HE_LOG_LEVEL <= HE_LOG_LEVEL_TRACE) ? ::Helios::Log::GetCoreLogger()->trace(__VA_ARGS__)    : (void)0
#define LOG_CORE_DEBUG(...) (HE_LOG_LEVEL <= HE_LOG_LEVEL_DEBUG) ? ::Helios::Log::GetCoreLogger()->debug(__VA_ARGS__)    : (void)0
#define LOG_CORE_INFO(...)  (HE_LOG_LEVEL <= HE_LOG_LEVEL_INFO)  ? ::Helios::Log::GetCoreLogger()->info(__VA_ARGS__)     : (void)0
#define LOG_CORE_WARN(...)  (HE_LOG_LEVEL <= HE_LOG_LEVEL_WARN)  ? ::Helios::Log::GetCoreLogger()->warn(__VA_ARGS__)     : (void)0
#define LOG_CORE_ERROR(...) (HE_LOG_LEVEL <= HE_LOG_LEVEL_ERROR) ? ::Helios::Log::GetCoreLogger()->error(__VA_ARGS__)    : (void)0
#define LOG_CORE_FATAL(...) (HE_LOG_LEVEL <= HE_LOG_LEVEL_FATAL) ? ::Helios::Log::GetCoreLogger()->critical(__VA_ARGS__) : (void)0

// Logging macros for Application
#define LOG_TRACE(...)      (HE_LOG_LEVEL <= HE_LOG_LEVEL_TRACE) ? ::Helios::Log::GetAppLogger()->trace(__VA_ARGS__)     : (void)0
#define LOG_DEBUG(...)      (HE_LOG_LEVEL <= HE_LOG_LEVEL_DEBUG) ? ::Helios::Log::GetAppLogger()->debug(__VA_ARGS__)     : (void)0
#define LOG_INFO(...)       (HE_LOG_LEVEL <= HE_LOG_LEVEL_INFO)  ? ::Helios::Log::GetAppLogger()->info(__VA_ARGS__)      : (void)0
#define LOG_WARN(...)       (HE_LOG_LEVEL <= HE_LOG_LEVEL_WARN)  ? ::Helios::Log::GetAppLogger()->warn(__VA_ARGS__)      : (void)0
#define LOG_ERROR(...)      (HE_LOG_LEVEL <= HE_LOG_LEVEL_ERROR) ? ::Helios::Log::GetAppLogger()->error(__VA_ARGS__)     : (void)0
#define LOG_FATAL(...)      (HE_LOG_LEVEL <= HE_LOG_LEVEL_FATAL) ? ::Helios::Log::GetAppLogger()->critical(__VA_ARGS__)  : (void)0

// Logging macros for GLFW
#define LOG_GLFW_DEBUG(...) (HE_LOG_LEVEL <= HE_LOG_LEVEL_DEBUG) ? ::Helios::Log::GetGLFWLogger()->debug(__VA_ARGS__)    : (void)0
#define LOG_GLFW_ERROR(...) (HE_LOG_LEVEL <= HE_LOG_LEVEL_ERROR) ? ::Helios::Log::GetGLFWLogger()->error(__VA_ARGS__)    : (void)0

// ASSERT macros
#ifdef HE_LOG_ASSERTS
// TODO: current implementation of __debugbreak() is Windows/MSVC only
#define LOG_CORE_ASSERT(x, ...) { if(!(x)) { LOG_CORE_FATAL("Assertion failed: {0}", __VA_ARGS__); DebugBreak(); } }
#define LOG_ASSERT(x, ...)      { if(!(x)) { LOG_FATAL("Assertion failed: {0}", __VA_ARGS__); DebugBreak(); } }
#else
#define LOG_CORE_ASSERT(x, ...)
#define LOG_ASSERT(x, ...)
#endif
