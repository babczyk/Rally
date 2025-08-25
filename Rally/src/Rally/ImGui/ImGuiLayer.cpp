#include "rlpch.h"
#include "ImGuiLayer.h"

#include "Rally/Application.h"

#include "imgui.h"
#include "Platforms/OpenGL/ImGuiOpenGLRenderer.h"

#include "Rally/KeyCodes.h"

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


	// Create a mapping table from GLFW to ImGui keys
	static std::unordered_map<int, ImGuiKey> glfwToImGuiKey = {
		{RL_KEY_TAB, ImGuiKey_Tab},
		{RL_KEY_LEFT, ImGuiKey_LeftArrow},
		{RL_KEY_RIGHT, ImGuiKey_RightArrow},
		{RL_KEY_UP, ImGuiKey_UpArrow},
		{RL_KEY_DOWN, ImGuiKey_DownArrow},
		{RL_KEY_PAGE_UP, ImGuiKey_PageUp},
		{RL_KEY_PAGE_DOWN, ImGuiKey_PageDown},
		{RL_KEY_HOME, ImGuiKey_Home},
		{RL_KEY_END, ImGuiKey_End},
		{RL_KEY_INSERT, ImGuiKey_Insert},
		{RL_KEY_DELETE, ImGuiKey_Delete},
		{RL_KEY_BACKSPACE, ImGuiKey_Backspace},
		{RL_KEY_SPACE, ImGuiKey_Space},
		{RL_KEY_ENTER, ImGuiKey_Enter},
		{RL_KEY_ESCAPE, ImGuiKey_Escape},
		
		//Indifiers
		{RL_KEY_LEFT_CONTROL, ImGuiKey_LeftCtrl},
		{RL_KEY_RIGHT_CONTROL, ImGuiKey_RightCtrl},
		{RL_KEY_LEFT_SHIFT, ImGuiKey_LeftShift},
		{RL_KEY_RIGHT_SHIFT, ImGuiKey_RightShift},
		{RL_KEY_LEFT_ALT, ImGuiKey_LeftAlt},
		{RL_KEY_RIGHT_ALT, ImGuiKey_RightAlt},
		{RL_KEY_LEFT_SUPER, ImGuiKey_LeftSuper},
		{RL_KEY_RIGHT_SUPER, ImGuiKey_RightSuper},
		
		//members
		{RL_KEY_0, ImGuiKey_0},
		{RL_KEY_1, ImGuiKey_1},
		{RL_KEY_2, ImGuiKey_2},
		{RL_KEY_3, ImGuiKey_3},
		{RL_KEY_4, ImGuiKey_4},
		{RL_KEY_5, ImGuiKey_5},
		{RL_KEY_6, ImGuiKey_6},
		{RL_KEY_7, ImGuiKey_7},
		{RL_KEY_8, ImGuiKey_8},
		{RL_KEY_9, ImGuiKey_9},
	
		//Letters
		{RL_KEY_A, ImGuiKey_A},
		{RL_KEY_B, ImGuiKey_B},
		{RL_KEY_C, ImGuiKey_C},
		{RL_KEY_D, ImGuiKey_D},
		{RL_KEY_E, ImGuiKey_E},
		{RL_KEY_F, ImGuiKey_F},
		{RL_KEY_G, ImGuiKey_G},
		{RL_KEY_H, ImGuiKey_H},
		{RL_KEY_I, ImGuiKey_I},
		{RL_KEY_J, ImGuiKey_J},
		{RL_KEY_K, ImGuiKey_K},
		{RL_KEY_L, ImGuiKey_L},
		{RL_KEY_M, ImGuiKey_M},
		{RL_KEY_N, ImGuiKey_N},
		{RL_KEY_O, ImGuiKey_O},
		{RL_KEY_P, ImGuiKey_P},
		{RL_KEY_Q, ImGuiKey_Q},
		{RL_KEY_R, ImGuiKey_R},
		{RL_KEY_S, ImGuiKey_S},
		{RL_KEY_T, ImGuiKey_T},
		{RL_KEY_U, ImGuiKey_U},
		{RL_KEY_V, ImGuiKey_V},
		{RL_KEY_W, ImGuiKey_W},
		{RL_KEY_X, ImGuiKey_X},
		{RL_KEY_Y, ImGuiKey_Y},
		{RL_KEY_Z, ImGuiKey_Z},
		 
		//Function keys
		{RL_KEY_F1, ImGuiKey_F1},
		{RL_KEY_F2, ImGuiKey_F2},
		{RL_KEY_F3, ImGuiKey_F3},
		{RL_KEY_F4, ImGuiKey_F4},
		{RL_KEY_F5, ImGuiKey_F5},
		{RL_KEY_F6, ImGuiKey_F6},
		{RL_KEY_F7, ImGuiKey_F7},
		{RL_KEY_F8, ImGuiKey_F8},
		{RL_KEY_F9, ImGuiKey_F9},
		{RL_KEY_F10, ImGuiKey_F10},
		{RL_KEY_F11, ImGuiKey_F11},
		{RL_KEY_F12, ImGuiKey_F12},
	};

	// Conversion function
	ImGuiKey ConvertGlfwKeyToImGuiKey(int glfwKey)
	{
		auto it = glfwToImGuiKey.find(glfwKey);
		if (it != glfwToImGuiKey.end())
			return it->second;
		return ImGuiKey_None; //	 Not mapped
	}

	bool ImGuiLayer::OnKeyPressedEvent(KeyPressedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiKey keyCode = ConvertGlfwKeyToImGuiKey(e.GetKeyCode());
	
		
		// Also update modifiers
		io.AddKeyEvent(ImGuiKey_ModCtrl, e.IsControlDown());
		io.AddKeyEvent(ImGuiKey_ModShift, e.IsShiftDown());
		io.AddKeyEvent(ImGuiKey_ModAlt, e.IsAltDown());
		io.AddKeyEvent(ImGuiKey_ModSuper, e.IsSuperDown());

		if (keyCode != ImGuiKey_None)
		{
			io.AddKeyEvent(keyCode, true);
			return true;
		}
		return false;
	}

	bool ImGuiLayer::OnKeyReleasedEvent(KeyReleasedEvent& e)
	{
		ImGuiIO& io = ImGui::GetIO();
		ImGuiKey keyCode = ConvertGlfwKeyToImGuiKey(e.GetKeyCode());
		io.AddKeyEvent(keyCode, false);
		return false;
	}
}