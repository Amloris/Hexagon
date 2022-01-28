workspace "Hexagon"
	architecture "x64"
	startproject "Sandbox"

	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}

outputdir = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

-- Include directories relative to the root folder (solution directory)
IncludeDir = {}
IncludeDir["GLFW"]  = "Hexagon/vendor/GLFW/include"
IncludeDir["Glad"]  = "Hexagon/vendor/Glad/include"
IncludeDir["ImGui"] = "Hexagon/vendor/imgui"
IncludeDir["glm"]   = "Hexagon/vendor/glm"

group "Dependencies"
	include "Hexagon/vendor/GLFW"  -- Adds the GLFW premake file so that we can have GLFW as a project
	include "Hexagon/vendor/Glad"
	include "Hexagon/vendor/imgui"
	--include "Hexagon/vendor/glm"
group ""

project "Hexagon"
	location "Hexagon"
	kind "StaticLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

	pchheader "hxpch.h"
	pchsource "Hexagon/src/hxpch.cpp"

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"%{prj.name}/vendor/glm/glm/**.hpp",
		"%{prj.name}/vendor/glm/glm/**.h",
	}

	defines 
	{
		"_CRT_SECURE_NO_WARNINGS"
	}

	includedirs
	{
		"%{prj.name}/src",
		"%{prj.name}/vendor/spdlog/include",
		"%{IncludeDir.GLFW}",
		"%{IncludeDir.Glad}",
		"%{IncludeDir.ImGui}",
		"%{IncludeDir.glm}"
	}

	links
	{
		"GLFW",
		"Glad",
		"imgui",
		"opengl32.lib"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HX_PLATFORM_WINDOWS",
			"HX_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
		}

	filter "configurations:Debug"
		defines "HX_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HX_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HX_DIST"
		runtime "Release"
		optimize "on"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	cppdialect "C++17"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
		"imgui.ini"
	}

	includedirs
	{
		"Hexagon/vendor/spdlog/include",
		"Hexagon/src",
		"%{IncludeDir.glm}",
		"Hexagon/vendor"   --Include Imgui
	}

	links
	{
		"Hexagon"
	}

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"HX_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "HX_DEBUG"
		runtime "Debug"
		symbols "on"

	filter "configurations:Release"
		defines "HX_RELEASE"
		runtime "Release"
		optimize "on"

	filter "configurations:Dist"
		defines "HX_DIST"
		runtime "Release"
		optimize "on"
