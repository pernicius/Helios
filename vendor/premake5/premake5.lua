project "Premake"
	kind "Utility"

	targetdir ("%{wks.location}/bin/" .. outputdir .. "/%{prj.name}")
	objdir ("%{wks.location}/build/" .. outputdir .. "/%{prj.name}")

	files {
		"%{wks.location}/**premake5.lua"
	}

	postbuildmessage "Regenerating project files with Premake5!"
	postbuildcommands {
		"%{prj.location}/windows/premake5 %{_ACTION} --file=\"%{wks.location}premake5.lua\""
	}
