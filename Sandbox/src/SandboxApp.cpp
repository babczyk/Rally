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
		if (event.GetEventType() == Rally::EventType::KeyPressed)
		{
			Rally::KeyPressedEvent& e = (Rally::KeyPressedEvent&)event;
			if (e.GetKeyCode() == RL_KEY_ESCAPE)
				RL_TRACE("Escape key pressed (code {0})", (char)e.GetKeyCode());
			else
				RL_TRACE("Key pressed (code {0})", (char)e.GetKeyCode());
		}
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