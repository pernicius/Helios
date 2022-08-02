#include "pch_game.h"

#include <HeliosEngine/HeliosEngine.h>
//#include <HeliosEngine/Core/EntryPoint.h>
//#include <Helios/Core/Log.h>


class HeliosGame : public HeliosEngine::Application
{
public:
	HeliosGame(const HeliosEngine::ApplicationSpecification& specification)
		: HeliosEngine::Application(specification)
	{
//		LOG_INFO("HeliosGame()");
	}

	~HeliosGame()
	{
//		LOG_INFO("~HeliosGame()");
	}
};


HeliosEngine::Application* HeliosEngine::CreateApplication(HeliosEngine::ApplicationCommandLineArgs args)
{
	ApplicationSpecification spec;
	spec.Name = "HeliosGame";
	//TODO	spec.WorkingDirectory = "TODO: HOW DO I GET THE EXE-PATH???";
	spec.CommandLineArgs = args;

	return new HeliosGame(spec);
}
