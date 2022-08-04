#include "pch_game.h"

#include <HeliosEngine/HeliosEngine.h>


class HeliosGame : public HeliosEngine::Application
{
public:
	HeliosGame(const HeliosEngine::ApplicationSpecification& specification)
		: HeliosEngine::Application(specification)
	{
		LOG_INFO("HeliosGame()");
	}

	~HeliosGame()
	{
		LOG_INFO("~HeliosGame()");
	}
};


HeliosEngine::Application* HeliosEngine::CreateApplication(HeliosEngine::ApplicationCommandLineArgs args)
{
	ApplicationSpecification spec;
	spec.Name = "HeliosGame";
	//TODO	spec.WorkingDirectory = "TODO: HOW DO I GET THE EXE-PATH???";
	spec.CommandLineArgs = args;
//	spec.hints |= HeliosEngine::Hints::HINT_USE_CWD;
	spec.hints |= HeliosEngine::Hints::HINT_USE_EXEPATH_AS_CWD;

	return new HeliosGame(spec);
}
