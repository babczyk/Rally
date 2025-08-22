#include "Application.h"

#include "Rally/Events/ApplicationEvent.h"
#include "Rally/Log.h"

namespace Rally 
{
	Application::Application()
	{
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		WindowResizeEvent e(1280, 720);
		RL_TRACE(e);
		while (true);
	}

}
