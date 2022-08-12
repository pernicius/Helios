#include "pch_game.h"

#include <HeliosEngine/HeliosEngine.h>

#include <glm/gtc/matrix_transform.hpp>


class ExampleLayer : public HeliosEngine::Layer
{
public:
	ExampleLayer()
		: Layer("Example"),
		m_Camera(-2.0f, 2.0f, -2.0f, 2.0f),
		m_CameraPosition(0.0f)
	{
		m_VertexArray_1 = HeliosEngine::VertexArray::Create();
		float vertices_1[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 1.0f
		};
		HeliosEngine::Ref<HeliosEngine::VertexBuffer> vb_1 = HeliosEngine::VertexBuffer::Create(vertices_1, sizeof(vertices_1));
		HeliosEngine::BufferLayout layout_1 = {
			{ HeliosEngine::ShaderDataType::Float3, "a_Position"},
			{ HeliosEngine::ShaderDataType::Float4, "a_Color"}
		};
		vb_1->SetLayout(layout_1);
		m_VertexArray_1->AddVertexBuffer(vb_1);
		unsigned int indices_1[3] = {
			0, 1, 2
		};
		HeliosEngine::Ref<HeliosEngine::IndexBuffer>ib_1 = HeliosEngine::IndexBuffer::Create(indices_1, sizeof(indices_1) / sizeof(uint32_t));
		m_VertexArray_1->SetIndexBuffer(ib_1);


		m_VertexArray_2 = HeliosEngine::VertexArray::Create();
		float vertices_2[3 * 4] = {
			-0.5f, -0.5f, 0.0f,
			 0.5f, -0.5f, 0.0f,
			 0.5f,  0.5f, 0.0f,
			-0.5f,  0.5f, 0.0f
		};
		HeliosEngine::Ref<HeliosEngine::VertexBuffer> vb_2 = HeliosEngine::VertexBuffer::Create(vertices_2, sizeof(vertices_2));
		HeliosEngine::BufferLayout layout_2 = {
			{ HeliosEngine::ShaderDataType::Float3, "a_Position"}
		};
		vb_2->SetLayout(layout_2);
		m_VertexArray_2->AddVertexBuffer(vb_2);
		unsigned int indices_2[6] = {
			0, 1, 2, 2, 3, 0
		};
		HeliosEngine::Ref<HeliosEngine::IndexBuffer>ib_2 = HeliosEngine::IndexBuffer::Create(indices_2, sizeof(indices_2) / sizeof(uint32_t));
		m_VertexArray_2->SetIndexBuffer(ib_2);


		std::string vs_1 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;
			layout(location = 1) in vec4 a_Color;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;
			out vec4 v_Color;

			void main()
			{
				v_Position = a_Position;
				v_Color = a_Color;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
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
		m_Shader_1 = HeliosEngine::Shader::Create("shader1", vs_1, fs_1);

		std::string vs_2 = R"(
			#version 330 core

			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;
			uniform mat4 u_Transform;

			out vec3 v_Position;

			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
			}
		)";
		std::string fs_2 = R"(
			#version 330 core

			layout(location = 0) out vec4 color;

			in vec3 v_Position;

			uniform vec4 u_Color;

			void main()
			{
				color = u_Color;
			}
		)";
		m_Shader_2 = HeliosEngine::Shader::Create("shader2", vs_2, fs_2);
	}


	void OnUpdate(HeliosEngine::Timestep ts) override
	{
		if (HeliosEngine::Input::IsKeyPressed(HeliosEngine::Key::Left))
			m_CameraPosition.x -= m_CameraMoveSpeed * ts;
		if (HeliosEngine::Input::IsKeyPressed(HeliosEngine::Key::Right))
			m_CameraPosition.x += m_CameraMoveSpeed * ts;
		if (HeliosEngine::Input::IsKeyPressed(HeliosEngine::Key::Down))
			m_CameraPosition.y -= m_CameraMoveSpeed * ts;
		if (HeliosEngine::Input::IsKeyPressed(HeliosEngine::Key::Up))
			m_CameraPosition.y += m_CameraMoveSpeed * ts;

		if (HeliosEngine::Input::IsKeyPressed(HeliosEngine::Key::A))
			m_CameraRotation += m_CameraRotateSpeed * ts;
		if (HeliosEngine::Input::IsKeyPressed(HeliosEngine::Key::D))
			m_CameraRotation -= m_CameraRotateSpeed * ts;

		HeliosEngine::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		HeliosEngine::RenderCommand::Clear();
		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);
		HeliosEngine::Renderer::BeginScene(m_Camera);

		glm::vec4 redColor(0.8f, 0.2f, 0.3f, 1.0f);
		glm::vec4 blueColor(0.2f, 0.3f, 0.8f, 1.0f);
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				if (x % 2 == 0)
					m_Shader_2->SetFloat4("u_Color", redColor);
				else
					m_Shader_2->SetFloat4("u_Color", blueColor);
				HeliosEngine::Renderer::Submit(m_Shader_2, m_VertexArray_2, transform);
			}
		}
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
	float m_CameraMoveSpeed = 1.0f;
	float m_CameraRotateSpeed = 100.0f;
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
