workspace "ParticleTest"
	architecture "x64"
	startproject "ParticleTest"
	configurations
	{
		"Debug",
		"Release",
		"Dist"
	}
	
outputdir = "%{cfg.buildcfg}-%{cfg.architecture}"

project "ParticleTest"
	location "ParticleTest"
	kind "ConsoleApp"
	language "c++"
	staticruntime "on"
	
	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir.. "/%{prj.name}")
	
	pchheader "pch.h"
	pchsource "%{prj.name}/src/pch.cpp"
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	
	includedirs
	{
		"Dependence/include",
		"ImGui/src",
		"ParticleTest/src"
	}
	
	defines
	{
		"_CRT_SECURE_NO_WARNINGS"
	}
	
	links
	{
		"glad",
		"opengl32.lib",
		"Dependence/glfw3.lib",
		"ImGui"
	}
	
	
	
	
	filter "system:windows"
		cppdialect "c++17"
		defines "_LM_WINDOWS"
		
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		defines "_DEBUG"
		
	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		defines "_RELEASE"
		postbuildcommands
		{
			"{COPY} %{cfg.buildtarget.relpath} ../bin/" ..outputdir.. "/MyApp",
			"{COPY} ./res ../bin/" ..outputdir.. "/MyApp/res"
		}
		
	filter "configurations:Dist"
		defines "_DIST"
		optimize "on"
		runtime "Release"
		
		
project "ImGui"
	location "ImGui"
	kind "StaticLib"
	language "c++"
	staticruntime "on"
	
	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir.. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.cpp",
	}
	
	includedirs
	{
		"Dependence/include"
	}

	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		defines "_DEBUG"
		
	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		defines "_RELEASE"
	
	filter "configurations:Dist"
		defines "_DIST"
		optimize "on"
		runtime "Release"
		
project "glad"
	location "glad"
	kind "StaticLib"
	language "c"
	staticruntime "on"
	
	targetdir ("bin/" ..outputdir.. "/%{prj.name}")
	objdir ("bin-int/" ..outputdir.. "/%{prj.name}")
	
	files
	{
		"%{prj.name}/src/**.h",
		"%{prj.name}/src/**.c",
	}
	
	includedirs
	{
		"Dependence/include"
	}
	
	filter "configurations:Debug"
		runtime "Debug"
		symbols "on"
		defines "_DEBUG"
		
	filter "configurations:Release"
		runtime "Release"
		optimize "on"
		defines "_RELEASE"
	
	filter "configurations:Dist"
		defines "_DIST"
		optimize "on"
		runtime "Release"