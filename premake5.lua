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
includeDirs["stb"] = "AAEngine/ThirdParty/stb"
includeDirs["assimp"] = "AAEngine/ThirdParty/assimp/include"
-- TEMPORARY FOR TESTING
includeDirs["glm"] = "AAEngine/ThirdParty/glm"

group "Dependencies"
	include "AAEngine/ThirdParty/GLFW"
	include "AAEngine/ThirdParty/GLAD"
	include "AAEngine/ThirdParty/ImGui"

group ""

project "AAEngine"
	location "AAEngine"
	kind "SharedLib"
	language "C++"
	cppdialect "C++17"
	staticruntime "off"

	targetdir ("Binaries/" .. outputdirectory .. "/%{prj.name}")
	objdir ("Intermediate/" .. outputdirectory .. "/%{prj.name}")

	pchheader "AA_PreCompiledHeaders.h"
	pchsource "AAEngine/Source/Engine/AA_PreCompiledHeaders.cpp"

	files 
	{ 
		"%{prj.name}/Source/**.h",
		"%{prj.name}/Source/**.cpp",
		"%{prj.name}/Source/**.glsl",
		"%{prj.name}/ThirdParty/stb/**.cpp",
		"%{prj.name}/ThirdParty/stb/**.h"
	}

	includedirs 
	{ 
		--- Include 3rd party libraries for the engine etc
		"%{prj.name}/Assets",
		"%{prj.name}/Source",
		"%{prj.name}/Source/Engine",
		"%{prj.name}/Source/Engine/Core",
		"%{includeDirs.GLFW}",
		"%{includeDirs.GLAD}",
		"%{includeDirs.ImGui}",
		"%{includeDirs.stb}",
		"%{includeDirs.assimp}",
		-- TEMP IMCLUDES
		"%{includeDirs.glm}",
	}

	links
	{
		"GLFW",
		"GLAD",
		"ImGui",
		"opengl32.lib",
		"assimp.lib",
	}

	libdirs 
	{
		"AAEngine/ThirdParty/assimp/lib/Debug"
	}

	disablewarnings
	{
		"4251"
	}

	linkoptions
	{
		"-IGNORE:4251"
	}

	vectorextensions "SSE2"

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"AA_PLATFORM_WINDOWS",
			"AA_DYNAMIC_LINK",
			"AA_BUILD_DLL",
			"GLFW_INCLUDE_NONE",
			"_CRT_SECURE_NO_WARNINGS"
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
	cppdialect "C++17"
	staticruntime "off"

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

	disablewarnings
	{
		"4251"
	}

	linkoptions
	{
		"-IGNORE:4251"
	}

	links { "AAEngine" }

	filter "system:windows"
		systemversion "latest"

		defines
		{
			"AA_PLATFORM_WINDOWS",
			"AA_DYNAMIC_LINK",
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
