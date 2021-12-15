project "Glad"
	kind "StaticLib"
	language "C"
	staticruntime "on"

	targetdir ("bin/" .. outputdir .. "/%{prj.name}")
	objdir ("bin-obj/" .. outputdir .. "/%{prj.name}")

	files
	{
		"include/glad/glad.h",
		"include/KHR/khrplatform.h",
		"src/glad.c"
	}

	includedirs
	{
		"include"
	}

	filter "system:windows"
		systemversion "latest"

	filter {"configurations:Debug"}
		runtime "Debug"
		buildoptions "/MDd"
		symbols "on"

	filter {"configurations:Release"}
		runtime "Release"
		buildoptions "/MD"
		symbols "on"