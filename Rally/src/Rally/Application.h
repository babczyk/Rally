#pragma once

#include "Core.h"
#include "Rally/Events/Event.h"
#include "Window.h"
#include <memory>

namespace Rally {
	class RALLY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	private:
		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
	};

	// To be defined in CLIENT //
	Application* CreateApplication();
}

