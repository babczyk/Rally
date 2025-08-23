#include <Rally.h>

class Sandbox : public Rally::Application
{
public:
	Sandbox()
	{

	}

	~Sandbox()
	{

	}
};

Rally::Application* Rally::CreateApplication()
{
	return new Sandbox();
}