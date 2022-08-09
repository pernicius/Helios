#pragma once

#include "HeliosEngine/Core/LayerStack.h"
#include "HeliosEngine/Core/Window.h"
#include "HeliosEngine/Events/Event.h"
#include "HeliosEngine/Events/ApplicationEvent.h"

#include "HeliosEngine/Renderer/Shader.h"
#include "HeliosEngine/Renderer/Buffer.h"
#include "HeliosEngine/Renderer/VertexArray.h"
#include "HeliosEngine/Renderer/OrthographicCamera.h"


namespace HeliosEngine {


	int AppMain(int argc, char** argv);


	struct ApplicationCommandLineArgs
	{
		int Count = 0;
		char** Args = nullptr;

		const char* operator[](int index) const
		{
			LOG_CORE_ASSERT(index < Count, "");
			return Args[index];
		}
	};

	enum Hints
	{
		HINT_USE_CWD            = (1 << 0),
		HINT_USE_EXEPATH_AS_CWD = (1 << 1),
	};

	struct ApplicationSpecification
	{
		std::string Name;
		std::string WorkingDirectory;
		ApplicationCommandLineArgs CommandLineArgs;
		unsigned int hints = 0;
	};


	class Application
	{
	public:
		Application(const ApplicationSpecification& specification);
		virtual ~Application();

		static Application& Get() { return *s_Instance; }
		const ApplicationSpecification& GetSpecification() const { return m_Specification; }
		void Close();

		void OnEvent(Event& e);

		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);

		Window& GetWindow() { return *m_Window; }

	private:
		void Run();
		bool OnWindowClose(WindowCloseEvent& e);
		bool OnWindowResize(WindowResizeEvent& e);
	private:
		ApplicationSpecification m_Specification;
		Scope<Window> m_Window;
		bool m_Running = true;
		bool m_Minimized = false;
		LayerStack m_LayerStack;
	private:
		static Application* s_Instance;
		friend int AppMain(int argc, char** argv);

		Ref<Shader> m_Shader_1, m_Shader_2;
		Ref<VertexArray> m_VertexArray_1, m_VertexArray_2;
		OrthographicCamera m_Camera;
	};


	// To be defined in CLIENT
	Application* CreateApplication(ApplicationCommandLineArgs args);


} // namespace HeliosEngine
