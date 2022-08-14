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
		"GLFW_INCLUDE_NONE"
	}
	
	includedirs {
		"source",
		"vendor/spdlog/include",
		"vendor/glfw/include",
		"vendor/glad/include",
		"vendor/glm",
		"vendor/imgui",
		"vendor/stb"
	}
	
	links {
		"HeliosEngine.glfw",
		"HeliosEngine.glad2",
		"HeliosEngine.imgui"
	}

	files {
		"source/pch_engine.h",
		"source/pch_engine.cpp",
		"source/HeliosEngine/**.h",
		"source/HeliosEngine/**.cpp",
		"vendor/stb/*.h",
		"vendor/stb/*.cpp"
	}

	filter "platforms:Windows"

		defines {
--			"HE_BUILDWITH_RENDERER_DIRECTX",
			"HE_BUILDWITH_RENDERER_OPENGL",
--			"HE_BUILDWITH_RENDERER_VULKAN",
		}

		files {
			"source/Platform/System/Windows/**.h",
			"source/Platform/System/Windows/**.cpp",
--			"source/Platform/Renderer/DirectX/**.h",
--			"source/Platform/Renderer/DirectX/**.cpp",
			"source/Platform/Renderer/OpenGL/**.h",
			"source/Platform/Renderer/OpenGL/**.cpp",
--			"source/Platform/Renderer/Vulkan/**.h",
--			"source/Platform/Renderer/Vulkan/**.cpp",
		}

	filter "platforms:Linux"

		defines {
--			"HE_BUILDWITH_RENDERER_DIRECTX",
			"HE_BUILDWITH_RENDERER_OPENGL",
--			"HE_BUILDWITH_RENDERER_VULKAN",
		}

		files {
			"source/Platform/System/Linux/**.h",
			"source/Platform/System/Linux/**.cpp",
--			"source/Platform/Renderer/DirectX/**.h",
--			"source/Platform/Renderer/DirectX/**.cpp",
			"source/Platform/Renderer/OpenGL/**.h",
			"source/Platform/Renderer/OpenGL/**.cpp",
--			"source/Platform/Renderer/Vulkan/**.h",
--			"source/Platform/Renderer/Vulkan/**.cpp",
		}

	filter "platforms:MacOS"

		defines {
--			"HE_BUILDWITH_RENDERER_DIRECTX",
			"HE_BUILDWITH_RENDERER_OPENGL",
--			"HE_BUILDWITH_RENDERER_VULKAN",
		}
		
		files {
			"source/Platform/System/MacOS/**.h",
			"source/Platform/System/MacOS/**.cpp",
--			"source/Platform/Renderer/DirectX/**.h",
--			"source/Platform/Renderer/DirectX/**.cpp",
			"source/Platform/Renderer/OpenGL/**.h",
			"source/Platform/Renderer/OpenGL/**.cpp",
--			"source/Platform/Renderer/Vulkan/**.h",
--			"source/Platform/Renderer/Vulkan/**.cpp",
		}

	filter "configurations:Debug"

		defines {
			"HE_LOG_LEVEL=0",
			"HE_LOG_ASSERTS"
		}
		
	filter "configurations:Release"

		defines {
			"HE_LOG_LEVEL=2",
--			"HE_LOG_ASSERTS"
		}

	filter {}

	group "client/HeliosEngine/vendor"
		include("vendor/glfw")
		include("vendor/glad")
		include("vendor/imgui")
