--- premake5.lua = AAEngine

workspace "AAEngine"
	architecture "x64"
	startproject "Sandbox"
	configurations { 'Debug', 'Release', 'Shipping' }

outputdirectory = "%{cfg.buildcfg}-%{cfg.system}-%{cfg.architecture}"

--- Including folders relative to the Root, mostly ThirdParty Libs
includeDirs = {}
includeDirs["GLFW"] = "AAEngine/ThirdParty/GLFW/include"
includeDirs["GLAD"] = "AAEngine/ThirdParty/GLAD/include"
includeDirs["ImGui"] = "AAEngine/ThirdParty/ImGui"

group "Dependencies"
	include "AAEngine/ThirdParty/GLFW"
	include "AAEngine/ThirdParty/GLAD"
	include "AAEngine/ThirdParty/ImGui"

group ""

project "AAEngine"
	location "AAEngine"
	kind "SharedLib"
	language "C++"
	staticruntime "off"

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
		"%{includeDirs.GLFW}",
		"%{includeDirs.GLAD}",
		"%{includeDirs.ImGui}"
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib"
	}

	disablewarnings
	{
		"4251"
	}

	linkoptions
	{
		"-IGNORE:4251"
	}

	filter "system:windows"
		cppdialect "C++17"
		systemversion "latest"

		defines
		{
			"AA_PLATFORM_WINDOWS",
			"AA_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
		}

		postbuildcommands
		{
			("{COPY} %{cfg.buildtarget.relpath} \"../Binaries/" .. outputdirectory .. "/Sandbox/\"")
		}

	filter "configurations:Debug"
		defines "AA_DEBUG"
		runtime "Debug"
		symbols "on"
		
	filter "configurations:Release"
		defines "AA_RELEASE"
		runtime "Release"
		optimize "speed"
		
	filter "configurations:Shipping"
		defines "AA_SHIPPING"
		runtime "Release"
		optimize "speed"
		symbols "off"

project "Sandbox"
	location "Sandbox"
	kind "ConsoleApp"
	language "C++"
	staticruntime "off"

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
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		defines "AA_RELEASE"
		runtime "Release"
		optimize "On"
		
	filter "configurations:Shipping"
		defines "AA_SHIPPING"
		runtime "Release"
		optimize "On"
