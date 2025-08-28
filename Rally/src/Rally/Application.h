#pragma once

#include "Core.h"
#include "Events/Event.h"
#include "Events/ApplicationEvent.h"
#include "LayerStack.h"

#include "Window.h"
#include "Rally/ImGui/ImGuiLayer.h"

#include "Rally/Renderer/Shader.h"
#include "Rally/Renderer/Buffer.h"
#include "Rally/Renderer/VertexArray.h"

namespace Rally {

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
		ImGuiLayer* m_ImGuiLayer;
		bool m_Running = true;
		LayerStack m_LayerStack;

		std::shared_ptr<VertexArray> m_VertexArray;
		std::shared_ptr<Shader> m_Shader;

		std::shared_ptr<VertexArray> m_SquareVA;
		std::shared_ptr<Shader> m_BlueShader;
	private:
		static Application* s_Instance;

	};

	// To be defined in CLIENT //
	Application* CreateApplication();
}

