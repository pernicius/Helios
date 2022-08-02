---------------------------------
-- [ WORKSPACE CONFIGURATION ] --
---------------------------------
workspace "Helios"

	configurations {
		"Debug",
		"Release"
	}

	platforms {
		"Windows",
		"Linux",
		"MacOS"
	}

	startproject "HeliosGame"

	--------------------------------
	-- [ PLATFORM CONFIGURATION ] --
	--------------------------------
	filter "platforms:Windows"
		system  "windows"
		defines "HE_SYSTEM_WINDOWS"

	filter "platforms:Linux"
		system  "linux"
		defines "HE_SYSTEM_LINUX"

	filter "platforms:MacOS"
		system "macosx"
		defines "HE_SYSTEM_MACOS"

	filter { "system:windows", "action:vs*" }
		flags { "MultiProcessorCompile", "NoMinimalRebuild" }
		systemversion "latest"

	-------------------------------------
	-- [ DEBUG/RELEASE CONFIGURATION ] --
	-------------------------------------
	filter "configurations:Debug"
		defines  "HE_BUILD_DEBUG"
		symbols  "On"
		optimize "Off"
		runtime  "Debug"

	filter "configurations:Release"
		defines  "HE_BUILD_RELEASE"
		symbols  "Off"
		optimize "Speed"
		runtime  "Release"

	filter {}

	-------------------------------
	-- [ PROJECT CONFIGURATION ] --
	-------------------------------

	outputdir = "%{string.lower(cfg.platform)}-%{string.lower(cfg.buildcfg)}"

	-- client apps (the game)
	group "client"
		include("projects.client")

	-- server apps (the server environment)
	group "server"
--		include("projects.server")

	group ""
