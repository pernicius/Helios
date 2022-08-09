#include "pch_game.h"

#include <HeliosEngine/HeliosEngine.h>


class ExampleLayer : public HeliosEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"),
		m_Camera(-2.0f, 2.0f, -2.0f, 2.0f),
		m_CameraPosition(0.0f)
	{
		m_VertexArray_1 = HeliosEngine::VertexArray::Create();

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		HeliosEngine::Ref<HeliosEngine::VertexBuffer> vb = HeliosEngine::VertexBuffer::Create(vertices, sizeof(vertices));
		HeliosEngine::BufferLayout layout = {
			{ HeliosEngine::ShaderDataType::Float3, "a_Position"},
			{ HeliosEngine::ShaderDataType::Float4, "a_Color"}
		};
		vb->SetLayout(layout);
		m_VertexArray_1->AddVertexBuffer(vb);

		unsigned int indices[3] = {
			0, 1, 2
		};
		HeliosEngine::Ref<HeliosEngine::IndexBuffer>ib = HeliosEngine::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t));
		m_VertexArray_1->SetIndexBuffer(ib);

		std::string vs_1 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";
		std::string fs_1 = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position + 0.5, 1.0);
				color = v_Color;
			}
		)";
		m_Shader_1.reset(new HeliosEngine::Shader(vs_1, fs_1));
	}


	void OnUpdate() override
	{
		if (HeliosEngine::Input::IsKeyPressed(HeliosEngine::Key::Left))
			m_CameraPosition.x -= m_CameraSpeed;
		if (HeliosEngine::Input::IsKeyPressed(HeliosEngine::Key::Right))
			m_CameraPosition.x += m_CameraSpeed;
		if (HeliosEngine::Input::IsKeyPressed(HeliosEngine::Key::Down))
			m_CameraPosition.y -= m_CameraSpeed;
		if (HeliosEngine::Input::IsKeyPressed(HeliosEngine::Key::Up))
			m_CameraPosition.y += m_CameraSpeed;

		if (HeliosEngine::Input::IsKeyPressed(HeliosEngine::Key::A))
			m_CameraRotation += 10 * m_CameraSpeed;
		if (HeliosEngine::Input::IsKeyPressed(HeliosEngine::Key::D))
			m_CameraRotation -= 10 * m_CameraSpeed;


		HeliosEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		HeliosEngine::RenderCommand::Clear();
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
		HeliosEngine::Renderer::BeginScene(m_Camera);
		HeliosEngine::Renderer::Submit(m_Shader_1, m_VertexArray_1);
		HeliosEngine::Renderer::EndScene();
	}


	void OnEvent(HeliosEngine::Event& event) override
	{
	}


private:
	HeliosEngine::Ref<HeliosEngine::Shader> m_Shader_1, m_Shader_2;
	HeliosEngine::Ref<HeliosEngine::VertexArray> m_VertexArray_1, m_VertexArray_2;
	HeliosEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;
	float m_CameraSpeed = 0.01f;
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
