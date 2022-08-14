#include "pch_game.h"

#include <HeliosEngine/HeliosEngine.h>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <imgui/imgui.h>


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
			{ HeliosEngine::ShaderDataType::Float3, "a_Position" },
			{ HeliosEngine::ShaderDataType::Float4, "a_Color" }
		};
		vb_1->SetLayout(layout_1);
		m_VertexArray_1->AddVertexBuffer(vb_1);
		unsigned int indices_1[3] = {
			0, 1, 2
		};
		HeliosEngine::Ref<HeliosEngine::IndexBuffer>ib_1 = HeliosEngine::IndexBuffer::Create(indices_1, sizeof(indices_1) / sizeof(uint32_t));
		m_VertexArray_1->SetIndexBuffer(ib_1);


		m_VertexArray_2 = HeliosEngine::VertexArray::Create();
		float vertices_2[(3+2) * 4] = {
			-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, // bottom left
			 0.5f, -0.5f, 0.0f, 1.0f, 0.0f, // bottom right
			 0.5f,  0.5f, 0.0f, 1.0f, 1.0f, // top right
			-0.5f,  0.5f, 0.0f, 0.0f, 1.0f, // top left
		};
		HeliosEngine::Ref<HeliosEngine::VertexBuffer> vb_2 = HeliosEngine::VertexBuffer::Create(vertices_2, sizeof(vertices_2));
		HeliosEngine::BufferLayout layout_2 = {
			{ HeliosEngine::ShaderDataType::Float3, "a_Position" },
			{ HeliosEngine::ShaderDataType::Float2, "a_TexCoord" }
		};
		vb_2->SetLayout(layout_2);
		m_VertexArray_2->AddVertexBuffer(vb_2);
		unsigned int indices_2[6] = {
			0, 1, 2, 2, 3, 0
		};
		HeliosEngine::Ref<HeliosEngine::IndexBuffer>ib_2 = HeliosEngine::IndexBuffer::Create(indices_2, sizeof(indices_2) / sizeof(uint32_t));
		m_VertexArray_2->SetIndexBuffer(ib_2);

		// shader 1 (triangle) ////////////////////////////////////////////////
		{
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
		}
		// shader 2 (grid) ////////////////////////////////////////////////////
		{
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

				uniform vec3 u_Color;

				void main()
				{
					color = vec4(u_Color, 1.0);
				}
			)";
			m_Shader_2 = HeliosEngine::Shader::Create("shader2", vs_2, fs_2);
		}
		// shader 3 (texture) /////////////////////////////////////////////////
		{
			std::string vs_3 = R"(
				#version 330 core

				layout(location = 0) in vec3 a_Position;
				layout(location = 1) in vec2 a_TexCoord;

				uniform mat4 u_ViewProjection;
				uniform mat4 u_Transform;

				out vec2 v_TexCoord;

				void main()
				{
					v_TexCoord = a_TexCoord;
					gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);
				}
			)";
			std::string fs_3 = R"(
				#version 330 core

				layout(location = 0) out vec4 pixel;

				in vec2 v_TexCoord;

				uniform sampler2D u_Texture;

				void main()
				{
					pixel = texture(u_Texture, v_TexCoord);
				}
			)";
			m_TextureShader = HeliosEngine::Shader::Create("shader3", vs_3, fs_3);
		}

		m_Texture = HeliosEngine::Texture2D::Create("assets/textures/Checkerboard.png");
		m_TextureShader->Bind();
		m_TextureShader->SetInt("u_Texture", 0);

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


		// grid
		glm::mat4 scale = glm::scale(glm::mat4(1.0f), glm::vec3(0.1f));
		m_Shader_2->Bind();
		m_Shader_2->SetFloat3("u_Color", m_Color);
		for (int y = 0; y < 20; y++)
		{
			for (int x = 0; x < 20; x++)
			{
				glm::vec3 pos(x * 0.11f, y * 0.11f, 0.0f);
				glm::mat4 transform = glm::translate(glm::mat4(1.0f), pos) * scale;
				HeliosEngine::Renderer::Submit(m_Shader_2, m_VertexArray_2, transform);
			}
		}


		m_Texture->Bind();
		HeliosEngine::Renderer::Submit(m_TextureShader, m_VertexArray_2, glm::scale(glm::mat4(1.0f), glm::vec3(1.5f)));

		// triangle
		//HeliosEngine::Renderer::Submit(m_Shader_1, m_VertexArray_1);

		HeliosEngine::Renderer::EndScene();
	}


	void OnImGuiRender() override
	{
		ImGui::Begin("Settings");
		ImGui::ColorEdit3("Color", glm::value_ptr(m_Color));
		ImGui::End();
	}


	void OnEvent(HeliosEngine::Event& event) override
	{
	}


private:
	HeliosEngine::Ref<HeliosEngine::Shader> m_Shader_1, m_Shader_2, m_TextureShader;
	HeliosEngine::Ref<HeliosEngine::VertexArray> m_VertexArray_1, m_VertexArray_2;
	HeliosEngine::Ref<HeliosEngine::Texture2D> m_Texture;
	HeliosEngine::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition;
	float m_CameraRotation = 0.0f;
	float m_CameraMoveSpeed = 1.0f;
	float m_CameraRotateSpeed = 100.0f;
	glm::vec3 m_Color = { 0.2f, 0.3f, 0.8f };
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
