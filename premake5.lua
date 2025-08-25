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

include "Rally/vendor/GLFW"
include "Rally/vendor/Glad"
include "Rally/vendor/imgui"

project "Rally"
	location "Rally"
	kind "SharedLib"
	language "C++"
	staticruntime "Off"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-int/" .. outputdir .. "/%{prj.name}")

	buildoptions { "/utf-8" }

	pchheader "rlpch.h"
	pchsource "Rally/src/rlpch.cpp"

	files 
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp"
	}

	includedirs
	{
		"%{prj.name}/vendor/spdlog/include",
		"Rally/src",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}"
	}

	links
	{
		"GLFW",
		"Glad",
		"opengl32.lib",
		"ImGui"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"RL_PLATFORM_WINDOWS",
			"RL_BUILD_DLL",
			"GLFW_INCLUDE_NONE"
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../bin/" .. outputdir .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "RL_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "RL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "RL_DIST"
		runtime "Release"
		optimize "On"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "Off"

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
		"Rally/src"
	}

	links
	{
		"Rally"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"RL_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "RL_DEBUG"
		runtime "Debug"
		symbols "On"

	filter "configurations:Release"
		defines "RL_RELEASE"
		runtime "Release"
		optimize "On"

	filter "configurations:Dist"
		defines "RL_DIST"
		runtime "Release"
		optimize "On"
