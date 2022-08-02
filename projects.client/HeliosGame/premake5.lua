-----------------------
-- [ PROJECT CONFIG] --
-----------------------
project "HeliosGame"
	architecture  "x86_64"
	language      "C++"
	cppdialect    "C++20"
	staticruntime "On"
	
--	targetdir ("%{wks.location}/bin/client/"   .. outputdir .. "/%{string.lower(prj.name)}")
	targetdir ("%{wks.location}/bin/client/"   .. outputdir)
	objdir    ("%{wks.location}/build/client/" .. outputdir .. "/%{string.lower(prj.name)}")
	
	pchheader "pch_game.h"
	pchsource "source/pch_game.cpp"

	includedirs {
		"source",
		"%{wks.location}/projects.client/HeliosEngine/source",
		"%{wks.location}/projects.client/HeliosEngine/vendor/spdlog/include"
	}
	
	
	links {
		"HeliosEngine"
	}

	files {
		"source/**.h",
		"source/**.cpp"
	}

	filter "configurations:Debug"
		kind "ConsoleApp"
		
	filter "configurations:Release"
		kind "WindowedApp"

	filter {}
