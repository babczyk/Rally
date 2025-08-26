workspace "Rally"
	architecture "x64"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--Include directories relative to root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"] = "Rally/vendor/GLFW/include"
IncludeDir["Glad"] = "Rally/vendor/Glad/include"
IncludeDir["ImGui"] = "Rally/vendor/imgui"
IncludeDir["glm"] = "Rally/vendor/glm"

include "Rally/vendor/GLFW"
include "Rally/vendor/Glad"
include "Rally/vendor/imgui"

project "Rally"
	location "Rally"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	buildoptions { "/utf-8" }

	pchheader "rlpch.h"
	pchsource "Rally/src/rlpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.inl"
	}

	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"Rally/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib",
		"ImGui"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"RL_PLATFORM_WINDOWS",
			"RL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

	filter "configurations:Debug"
		defines "RL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "RL_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	buildoptions { "/utf-8" }

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"Rally/vendor/spdlog/include",
		"Rally/src",
		"Rally/vendor",
		"%{IncludeDir.glm}"

	}

	links
	{
		"Rally"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"RL_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "RL_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "RL_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "RL_DIST"
		runtime "Release"
		optimize "on"

