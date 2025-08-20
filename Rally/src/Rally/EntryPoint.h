#pragma once
#ifdef RL_PLATFORM_WINDOWS

extern Rally::Application* Rally::CreateApplication();

int main(int argc, char** argv)
{
	auto app = Rally::CreateApplication();
	app->Run();
	delete app;
}
#endif
