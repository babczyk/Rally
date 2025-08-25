#include <Rally.h>

class ExampleLayer : public Rally::Layer
{
public:
	ExampleLayer()
		: Layer("Example")
	{
	}
	void OnUpdate() override
	{
	}
	void OnEvent(Rally::Event& event) override
	{
		RL_TRACE("{0}", event.ToString());
	}
};
class Sandbox : public Rally::Application
{
public:
	Sandbox()
	{
		PushLayer(new ExampleLayer());
		PushOverlay(new Rally::ImGuiLayer());
	}

	~Sandbox()
	{

	}
};

Rally::Application* Rally::CreateApplication()
{
	return new Sandbox();
}