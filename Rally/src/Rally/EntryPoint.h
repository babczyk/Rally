#pragma once
#ifdef RL_PLATFORM_WINDOWS

extern Rally::Application* Rally::CreateApplication();

int main(int argc, char** argv)
{
	Rally::Log::Init();
	RL_CORE_WARN("Initialized Log system!");
	RL_CORE_INFO("<====> Wellcome <====>");

	auto app = Rally::CreateApplication();
	app->Run();
	delete app;
}
#endif
