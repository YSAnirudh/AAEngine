--- premake5.lua = AAEngine

workspace "AAEngine"
	architecture "x64"
	configurations { 'Debug', 'Release', 'Shipping' }

outputdirectory = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--- Including folders relative to the Root, mostly ThirdParty Libs
includeDirs = {}
includeDirs["GLFW"] = "AAEngine/ThirdParty/GLFW/include"

include "AAEngine/ThirdParty/GLFW"

project "AAEngine"
	location "AAEngine"
	kind "SharedLib"
	language "C++"

	staticruntime "on"

	targetdir ("Binaries/" .. outputdirectory .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdirectory .. "/%{prj.name}")

	pchheader "AA_PreCompiledHeaders.h"
	pchsource "AAEngine/Source/Engine/AA_PreCompiledHeaders.cpp"

	files 
	{ 
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs 
	{ 
		--- Include 3rd party libraries for the engine etc
		"%{prj.name}/Source",
		"%{prj.name}/Source/Engine",
		"%{prj.name}/Source/Engine/Core",
		"%{includeDirs.GLFW}"
	}

	links
	{
		"GLFW",
		"opengl32.lib"
	}

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"AA_PLATFORM_WINDOWS",
			"AA_BUILD_DLL",
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} ../Binaries/" .. outputdirectory .. "/Sandbox")
		}

	filter "configurations:Debug"
		defines "AA_DEBUG"
		symbols "on"
		
	filter "configurations:Release"
		defines "AA_RELEASE"
		optimize "speed"
		
	filter "configurations:Shipping"
		defines "AA_SHIPPING"
		optimize "speed"
		symbols "off"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"

	staticruntime "on"

	targetdir ("Binaries/" .. outputdirectory .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdirectory .. "/%{prj.name}")

	files 
	{ 
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp"
	}

	includedirs
	{ 
		--- Include 3rd party libraries for the engine etc
		"AAEngine/Source",
		"AAEngine/Source/Engine",
		"AAEngine/Source/Engine/Core"
	}

	links { "AAEngine" }

	filter "system:windows"
		cppdialect "C++17"
		staticruntime "On"
		systemversion "latest"

		defines
		{
			"AA_PLATFORM_WINDOWS",
		}

	filter "configurations:Debug"
		defines "AA_DEBUG"
		symbols "On"
		
	filter "configurations:Release"
		defines "AA_RELEASE"
		optimize "On"
		
	filter "configurations:Shipping"
		defines "AA_SHIPPING"
		optimize "On"