#pragma once

#include "Core.h"
#include "spdlog/spdlog.h"
#include "spdlog/fmt/ostr.h"

namespace Rally {

	class RALLY_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }
	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

//core log macros
#define RL_CORE_TRACE(...)      ::Rally::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define RL_CORE_INFO(...)       ::Rally::Log::GetCoreLogger()->info(__VA_ARGS__)
#define RL_CORE_WARN(...)       ::Rally::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define RL_CORE_ERROR(...)      ::Rally::Log::GetCoreLogger()->error(__VA_ARGS__)
#define RL_CORE_CRITICAL(...)   ::Rally::Log::GetCoreLogger()->critical(__VA_ARGS__)
							    
//client log macros			    
#define RL_TRACE(...)           ::Rally::Log::GetClientLogger()->trace(__VA_ARGS__)
#define RL_INFO(...)            ::Rally::Log::GetClientLogger()->info(__VA_ARGS__)
#define RL_WARN(...)            ::Rally::Log::GetClientLogger()->warn(__VA_ARGS__)
#define RL_ERROR(...)           ::Rally::Log::GetClientLogger()->error(__VA_ARGS__)
#define RL_CRITICAL(...)        ::Rally::Log::GetClientLogger()->critical(__VA_ARGS__)

