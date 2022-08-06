#include "pch_game.h"

#include <HeliosEngine/HeliosEngine.h>


class ExampleLayer : public HeliosEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}


	void OnUpdate() override
	{
	}


	void OnEvent(HeliosEngine::Event& event) override
	{
		LOG_TRACE("{0}", event);
	}
};


class HeliosGame : public HeliosEngine::Application
{
public:
	HeliosGame(const HeliosEngine::ApplicationSpecification& specification)
		: HeliosEngine::Application(specification)
	{
		LOG_INFO("HeliosGame()");
		PushLayer(new ExampleLayer());
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
	spec.CommandLineArgs = args;
	spec.hints |= HeliosEngine::Hints::HINT_USE_EXEPATH_AS_CWD;

	return new HeliosGame(spec);
}
