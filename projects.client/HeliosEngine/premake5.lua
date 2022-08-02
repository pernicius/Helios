-----------------------
-- [ PROJECT CONFIG] --
-----------------------
project "HeliosEngine"
	kind          "StaticLib"
	architecture  "x86_64"
	language      "C++"
	cppdialect    "C++20"
	staticruntime "On"
	
--	targetdir ("%{wks.location}/bin/client/"   .. outputdir .. "/%{string.lower(prj.name)}")
	targetdir ("%{wks.location}/bin/client/"   .. outputdir)
	objdir    ("%{wks.location}/build/client/" .. outputdir .. "/%{string.lower(prj.name)}")
	
	pchheader "pch_engine.h"
	pchsource "source/pch_engine.cpp"

	defines {
--		"GLFW_INCLUDE_NONE"
	}
	
	includedirs {
		"source"
--		"vendor/spdlog/include",
--		"vendor/GLFW/include",
--		"vendor/glad/include"
	}
	
	links {
--		"HeliosEngine.GLFW",
--		"HeliosEngine.glad2",
--		"opengl32.lib"
	}

	files {
		"source/**.h",
		"source/**.cpp"
	}

	filter "platforms:Windows"

		defines {
			"HE_BUILDWITH_PLATFORM_GLFW",
--			"HE_BUILDWITH_PLATFORM_WINDOWS",
--			"HE_BUILDWITH_RENDERER_DIRECTX",
			"HE_BUILDWITH_RENDERER_OPENGL",
--			"HE_BUILDWITH_RENDERER_VULKAN",
		}

	filter "platforms:Linux"

		defines {
			"HE_BUILDWITH_PLATFORM_GLFW",
--			"HE_BUILDWITH_PLATFORM_WINDOWS",
--			"HE_BUILDWITH_RENDERER_DIRECTX",
			"HE_BUILDWITH_RENDERER_OPENGL",
--			"HE_BUILDWITH_RENDERER_VULKAN",
		}

	filter "platforms:MacOS"

		defines {
			"HE_BUILDWITH_PLATFORM_GLFW",
--			"HE_BUILDWITH_PLATFORM_WINDOWS",
--			"HE_BUILDWITH_RENDERER_DIRECTX",
			"HE_BUILDWITH_RENDERER_OPENGL",
--			"HE_BUILDWITH_RENDERER_VULKAN",
		}

	filter "configurations:Debug"
		
	filter "configurations:Release"

	filter {}

--	include("vendor/GLFW")
--	include("vendor/glad")
