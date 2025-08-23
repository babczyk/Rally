#pragma once

#ifdef RL_PLATFORM_WINDOWS
	#ifdef RL_BUILD_DLL 
		#define RALLY_API __declspec(dllexport)
	#else
		#define RALLY_API __declspec(dllimport)
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