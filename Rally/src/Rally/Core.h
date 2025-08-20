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