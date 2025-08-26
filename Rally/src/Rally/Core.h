#pragma once

#ifdef RL_PLATFORM_WINDOWS
#if RL_DYNAMIC_LINK
	#ifdef RL_BUILD_DLL 
		#define RALLY_API __declspec(dllexport)
	#else
		#define RALLY_API __declspec(dllimport)
	#endif 
#else
	#define RALLY_API
#endif
#else
	#error Rally only support Windows!
#endif 

#ifdef RL_ENABLE_ASSERTS
	#define RL_ASSERT(x, ...) { if(!(x) { RL_ERROR("Assertion Faild: {0}", __VA_ARGS__); __debugbreak(); } }
	#define RL_CORE_ASSERT(x, ...) { if(!(x) { RL_ERROR("Assertion Faild: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define RL_ASSERT(x, ...)
	#define RL_CORE_ASSERT(x, ...)
#endif

#define BIT(x) (1 << x)

#define HZ_BIND_EVENT_FN(fn) [this](auto&&... args) -> decltype(auto) { return this->fn(std::forward<decltype(args)>(args)...); }

