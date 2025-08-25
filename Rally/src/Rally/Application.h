#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"

#include "Window.h"

namespace Rally {

#define BIND_EVENT_FN(x) std::bind(x, this, std::placeholders::_1)


	class RALLY_API Application
	{
	public:
		Application();
		virtual ~Application();

		void Run();

		void OnEvent(Event& e);

		static Application& Get() { return *s_Instance; }

		Window& GetWindow() { return *m_Window; }


		void PushLayer(Layer* layer);
		void PushOverlay(Layer* layer);
	private:
		bool OnWindowClose(WindowCloseEvent& e);

		std::unique_ptr<Window> m_Window;
		bool m_Running = true;
		LayerStack m_LayerStack;

		static Application* s_Instance;

	};

	// To be defined in CLIENT //
	Application* CreateApplication();
}

