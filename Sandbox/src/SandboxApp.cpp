#include <Rally.h>

#include "ImGui/imgui.h"

class ExampleLayer : public Rally::Layer
{
public:
	ExampleLayer()
		: Layer("Example"), m_Camera(-1.6f, 1.6f, -0.9f, 0.9f), m_CameraPosition(0.0f)
	{
		// --------------Test-----------------

		m_VertexArray.reset(Rally::VertexArray::Create());

		float vertices[3 * 7] = {
			-0.5f, -0.5f, 0.0f, 0.8f, 0.2f, 0.8f, 1.0f,
			 0.5f, -0.5f, 0.0f, 0.2f, 0.2f, 0.8f, 1.0f,
			 0.0f,  0.5f, 0.0f, 0.8f, 0.8f, 0.2f, 1.0f,
		};

		std::shared_ptr<Rally::VertexBuffer> vertexBuffer;
		vertexBuffer.reset(Rally::VertexBuffer::Create(vertices, sizeof(vertices)));

		Rally::BufferLayout layout = {
			{ Rally::ShaderDataType::Float3, "a_Position" },
			{ Rally::ShaderDataType::Float4, "a_Color" }
		};

		vertexBuffer->SetLayout(layout);

		m_VertexArray->AddVertexBuffer(vertexBuffer);

		unsigned int indices[3] = { 0, 1, 2 };
		std::shared_ptr<Rally::IndexBuffer> indexBuffer;
		indexBuffer.reset(Rally::IndexBuffer::Create(indices, sizeof(indices) / sizeof(uint32_t)));
		m_VertexArray->SetIndexBuffer(indexBuffer);

		m_SquareVA.reset(Rally::VertexArray::Create());

		float squareVertices[3 * 4] = {
			-0.75f, -0.75f, 0.0f,
			 0.75f, -0.75f, 0.0f,
			 0.75f,  0.75f, 0.0f,
			-0.75f,  0.75f, 0.0f,
		};

		std::shared_ptr<Rally::VertexBuffer> squareVB;
		squareVB.reset(Rally::VertexBuffer::Create(squareVertices, sizeof(squareVertices)));

		squareVB->SetLayout({
			{ Rally::ShaderDataType::Float3, "a_Position" },
			});

		m_SquareVA->AddVertexBuffer(squareVB);
		unsigned int squareIndices[6] = { 0, 1, 2, 2, 3, 0 };
		std::shared_ptr<Rally::IndexBuffer> squareIB;
		squareIB.reset(Rally::IndexBuffer::Create(squareIndices, sizeof(squareIndices) / sizeof(uint32_t)));
		m_SquareVA->SetIndexBuffer(squareIB);


		std::string vertexSrc = R"(
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

		std::string fragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;
			in vec4 v_Color;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
				color = v_Color;
			}
		)";

		m_Shader.reset(new Rally::Shader(vertexSrc, fragmentSrc));

		std::string blueShadervertexSrc = R"(
			#version 330 core
			
			layout(location = 0) in vec3 a_Position;

			uniform mat4 u_ViewProjection;

			out vec3 v_Position;
			void main()
			{
				v_Position = a_Position;
				gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
			}
		)";

		std::string blueShaderfragmentSrc = R"(
			#version 330 core
			
			layout(location = 0) out vec4 color;
			in vec3 v_Position;

			void main()
			{
				color = vec4(v_Position * 0.5 + 0.5, 1.0);
			}
		)";

		m_BlueShader.reset(new Rally::Shader(blueShadervertexSrc, blueShaderfragmentSrc));

	}

	void OnUpdate() override
	{
		if (Rally::Input::IsKeyPressed(RL_KEY_LEFT))
			m_CameraPosition.x -= m_CameraMoveSpeed;
		else if (Rally::Input::IsKeyPressed(RL_KEY_RIGHT))
			m_CameraPosition.x += m_CameraMoveSpeed;
		if (Rally::Input::IsKeyPressed(RL_KEY_UP))
			m_CameraPosition.y += m_CameraMoveSpeed;
		else if (Rally::Input::IsKeyPressed(RL_KEY_DOWN))
			m_CameraPosition.y -= m_CameraMoveSpeed;

		if (Rally::Input::IsKeyPressed(RL_KEY_A))
			m_CameraRotation += m_CameraRotationSpeed;
		else if (Rally::Input::IsKeyPressed(RL_KEY_D))
			m_CameraRotation -= m_CameraRotationSpeed;

		Rally::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
		Rally::RenderCommand::Clear();

		m_Camera.SetPosition(m_CameraPosition);
		m_Camera.SetRotation(m_CameraRotation);

		Rally::Renderer::BeginScene(m_Camera);

		Rally::Renderer::Submit(m_BlueShader, m_SquareVA);
		Rally::Renderer::Submit(m_Shader, m_VertexArray);

		Rally::Renderer::EndScene();

	}
	
	virtual void OnImGuiRender() override
	{

		ImGui::Begin("Test");
		ImGui::Text("Hello world");
		ImGui::End();

	}

	void OnEvent(Rally::Event& event) override
	{
	}

private:
	std::shared_ptr<Rally::VertexArray> m_VertexArray;
	std::shared_ptr<Rally::Shader> m_Shader;

	std::shared_ptr<Rally::VertexArray> m_SquareVA;
	std::shared_ptr<Rally::Shader> m_BlueShader;

	Rally::OrthographicCamera m_Camera;
	glm::vec3 m_CameraPosition = { 0.0f, 0.0f, 0.0f };
	float m_CameraMoveSpeed = 0.1f;

	float m_CameraRotationSpeed = 1.0f;
	float m_CameraRotation = 0.1f;
};

class Sandbox : public Rally::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
	}

	~Sandbox()
	{

	}
};

Rally::Application* Rally::CreateApplication()
{
	return new Sandbox();
}