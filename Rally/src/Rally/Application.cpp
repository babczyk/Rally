#include "rlpch.h"
#include "Application.h"

#include "Rally/Events/ApplicationEvent.h"
#include "Rally/Log.h"

namespace Rally 
{
	Application::Application()
	{
		m_Window = std::unique_ptr<Window>(Window::Create());
	}

	Application::~Application()
	{
	}

	void Application::Run()
	{
		while (m_Running)
		{
			m_Window->OnUpdate();
		}
	}

}
