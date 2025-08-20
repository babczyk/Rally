#pragma once

#include "Core.h"

namespace Rally {
	class RALLY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();
	};

	// To be defined in CLIENT //
	Application* CreateApplication();
}

