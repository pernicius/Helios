-----------------------
-- [ PROJECT CONFIG] --
-----------------------
project "HeliosEngine.glad2"
	kind          "StaticLib"
	architecture  "x86_64"
	language      "C"
	cppdialect    "C++20"
	staticruntime "On"
	targetname     "glad2"
	
	targetdir ("%{wks.location}/bin/client/"   .. outputdir .. "/heliosengine/%{string.lower(prj.name)}")
	objdir    ("%{wks.location}/build/client/" .. outputdir .. "/heliosengine/%{string.lower(prj.name)}")
	
	includedirs {
		"include",
		"src"
	}
	
	files {
		"include/glad/gl.h",
		"include/KHR/khrplatform.h",
		"src/gl.c"
	}

	filter "system:windows"
		systemversion "latest"
		staticruntime "On"

	filter "configurations:Debug"
		runtime "Debug"
		symbols "On"
		
	filter "configurations:Release"
		runtime "Release"
		optimize "On"
