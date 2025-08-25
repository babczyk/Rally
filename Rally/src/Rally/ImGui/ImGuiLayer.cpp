#include "rlpch.h"
#include "ImGuiLayer.h"

#include "Rally/Application.h"

#include "imgui.h"
#include "Platforms/OpenGL/ImGuiOpenGLRenderer.h"

//TEMPORARY
#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Rally {
	
	ImGuiLayer::ImGuiLayer()
		: Layer("ImGuiLayer")
	{
	}

	ImGuiLayer::~ImGuiLayer()
	{

	}

	void ImGuiLayer::OnUpdate()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2(app.GetWindow().GetWidth(), app.GetWindow().GetHeight());

		float time = (float)glfwGetTime();
		io.DeltaTime = m_Time > 0.0f ? (time - m_Time) : (1.0f / 60.0f);
		m_Time = time;

		ImGui_ImplOpenGL3_NewFrame();
		ImGui::NewFrame();

		// Demo window
		static bool show = true;
		ImGui::ShowDemoWindow(&show);

		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
	}

	void ImGuiLayer::OnEvent(Event& event)
	{
		EventDispatcher dispatcher(event);
		dispatcher.Dispatch<MouseButtonPressedEvent>(RL_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonPressedEvent));
		dispatcher.Dispatch<MouseButtonReleasedEvent>(RL_BIND_EVENT_FN(ImGuiLayer::OnMouseButtonReleasedEvent));
		dispatcher.Dispatch<MouseMovedEvent>(RL_BIND_EVENT_FN(ImGuiLayer::OnMouseMovedEvent));
		dispatcher.Dispatch<MouseScrolledEvent>(RL_BIND_EVENT_FN(ImGuiLayer::OnMouseScrolledEvent));
		dispatcher.Dispatch<KeyPressedEvent>(RL_BIND_EVENT_FN(ImGuiLayer::OnKeyPressedEvent));
		dispatcher.Dispatch<KeyReleasedEvent>(RL_BIND_EVENT_FN(ImGuiLayer::OnKeyReleasedEvent));
		dispatcher.Dispatch<WindowResizeEvent>(RL_BIND_EVENT_FN(ImGuiLayer::OnWindowResizeEvent));
		dispatcher.Dispatch<KeyTypedEvent>(RL_BIND_EVENT_FN(ImGuiLayer::OnKeyTypedEvent));
	}

	void ImGuiLayer::OnAttach()
	{
		ImGui::CreateContext();
		ImGui::StyleColorsDark();
		ImGuiIO& io = ImGui::GetIO();
		io.ConfigFlags |= ImGuiBackendFlags_HasMouseCursors;
		io.ConfigFlags |= ImGuiBackendFlags_HasSetMousePos;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui::DestroyContext();
	}

	bool ImGuiLayer::OnMouseButtonPressedEvent(MouseButtonPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = true;
		return false;
	}

	bool ImGuiLayer::OnMouseButtonReleasedEvent(MouseButtonReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseDown[e.GetMouseButton()] = false;
		return false;
	}

	bool ImGuiLayer::OnMouseMovedEvent(MouseMovedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MousePos = ImVec2(e.GetX(), e.GetY());
		return false;
	}

	bool ImGuiLayer::OnMouseScrolledEvent(MouseScrolledEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.MouseWheelH += e.GetXOffset();
		io.MouseWheel += e.GetYOffset();
		return false;
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		// Handle modifier keys with the modern AddKeyEvent approach
		ImGuiKey keyCode = (ImGuiKey)e.GetKeyCode();

		// Check if the pressed key is a modifier and send appropriate events
		switch (keyCode)
		{
		case GLFW_KEY_LEFT_CONTROL:
		case GLFW_KEY_RIGHT_CONTROL:
			io.AddKeyEvent(ImGuiKey_ModCtrl, true);
			break;
		case GLFW_KEY_LEFT_SHIFT:
		case GLFW_KEY_RIGHT_SHIFT:
			io.AddKeyEvent(ImGuiKey_ModShift, true);
			break;
		case GLFW_KEY_LEFT_ALT:
		case GLFW_KEY_RIGHT_ALT:
			io.AddKeyEvent(ImGuiKey_ModAlt, true);
			break;
		case GLFW_KEY_LEFT_SUPER:
		case GLFW_KEY_RIGHT_SUPER:
			io.AddKeyEvent(ImGuiKey_ModSuper, true);
			break;
			// Arrow keys
		case GLFW_KEY_UP:
			io.AddKeyEvent(ImGuiKey_UpArrow, true);
			break;
		case GLFW_KEY_DOWN:
			io.AddKeyEvent(ImGuiKey_DownArrow, true);
			break;
		case GLFW_KEY_LEFT:
			io.AddKeyEvent(ImGuiKey_LeftArrow, true);
			break;
		case GLFW_KEY_RIGHT:
			io.AddKeyEvent(ImGuiKey_RightArrow, true);
			break;
			// Common navigation keys
		case GLFW_KEY_TAB:
			io.AddKeyEvent(ImGuiKey_Tab, true);
			break;
		case GLFW_KEY_ENTER:
			io.AddKeyEvent(ImGuiKey_Enter, true);
			break;
		case GLFW_KEY_ESCAPE:
			io.AddKeyEvent(ImGuiKey_Escape, true);
			break;
		case GLFW_KEY_BACKSPACE:
			io.AddKeyEvent(ImGuiKey_Backspace, true);
			break;
		case GLFW_KEY_DELETE:
			io.AddKeyEvent(ImGuiKey_Delete, true);
			break;
		case GLFW_KEY_HOME:
			io.AddKeyEvent(ImGuiKey_Home, true);
			break;
		case GLFW_KEY_END:
			io.AddKeyEvent(ImGuiKey_End, true);
			break;
		case GLFW_KEY_PAGE_UP:
			io.AddKeyEvent(ImGuiKey_PageUp, true);
			break;
		case GLFW_KEY_PAGE_DOWN:
			io.AddKeyEvent(ImGuiKey_PageDown, true);
			break;
		}

		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();

		ImGuiKey keyCode = (ImGuiKey)e.GetKeyCode();

		// Handle modifier and navigation key releases
		switch (keyCode)
		{
		case GLFW_KEY_LEFT_CONTROL:
		case GLFW_KEY_RIGHT_CONTROL:
			io.AddKeyEvent(ImGuiKey_ModCtrl, false);
			break;
		case GLFW_KEY_UP:
			io.AddKeyEvent(ImGuiKey_UpArrow, false);
			break;
		case GLFW_KEY_DOWN:
			io.AddKeyEvent(ImGuiKey_DownArrow, false);
			break;
		case GLFW_KEY_LEFT:
			io.AddKeyEvent(ImGuiKey_LeftArrow, false);
			break;
		case GLFW_KEY_RIGHT:
			io.AddKeyEvent(ImGuiKey_RightArrow, false);
			break;
		case GLFW_KEY_LEFT_SHIFT:
			case GLFW_KEY_RIGHT_SHIFT:
			io.AddKeyEvent(ImGuiKey_ModShift, false);
			break;
		case GLFW_KEY_LEFT_ALT:
		case GLFW_KEY_RIGHT_ALT:
			io.AddKeyEvent(ImGuiKey_ModAlt, false);
			break;
		case GLFW_KEY_LEFT_SUPER:
			case GLFW_KEY_RIGHT_SUPER:
			io.AddKeyEvent(ImGuiKey_ModSuper, false);
			break;
		case GLFW_KEY_TAB:
			io.AddKeyEvent(ImGuiKey_Tab, false);
			break;
		case GLFW_KEY_BACKSPACE:
			io.AddKeyEvent(ImGuiKey_Backspace, false);
			break;
		
		default:
			//io.AddKeyEvent(keyCode, false); // DONT WORK keyCode is an invalide ImGuiKey code
			break;
		}

		return false;
	}

	bool ImGuiLayer::OnKeyTypedEvent(KeyTypedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		int keycode = e.GetKeyCode();
		if (keycode > 0 && keycode < 0x10000)
			io.AddInputCharacter((unsigned short)keycode);

		return false;
	}

	bool ImGuiLayer::OnWindowResizeEvent(WindowResizeEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		io.DisplaySize = ImVec2((float)e.GetWidth(), (float)e.GetHeight());
		io.DisplayFramebufferScale = ImVec2(1.0f, 1.0f);
		glViewport(0, 0, e.GetWidth(), e.GetHeight());
		return false;
	}
}