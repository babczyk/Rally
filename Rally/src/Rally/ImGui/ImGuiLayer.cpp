#include "rlpch.h"
#include "ImGuiLayer.h"

#include "Rally/Application.h"

#include "imgui.h"
#include "backends/imgui_impl_glfw.h"
#include "backends/imgui_impl_opengl3.h"

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

	void ImGuiLayer::OnAttach()
	{
		// Setup Dear ImGui context
		IMGUI_CHECKVERSION();
		ImGui::CreateContext();
		ImGuiIO& io = ImGui::GetIO(); (void)io;
		io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;       // Enable Keyboard Controls
		//io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;      // Enable Gamepad Controls
		io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;           // Enable Docking
		io.ConfigFlags |= ImGuiConfigFlags_ViewportsEnable;         // Enable Multi-Viewport / Platform Windows
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoTaskBarIcons;
		//io.ConfigFlags |= ImGuiConfigFlags_ViewportsNoMerge;

		// Setup Dear ImGui style
		ImGui::StyleColorsDark();
		//ImGui::StyleColorsClassic();

		// When viewports are enabled we tweak WindowRounding/WindowBg so platform windows can look identical to regular ones.
		ImGuiStyle& style = ImGui::GetStyle();
		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			style.WindowRounding = 0.0f;
			style.Colors[ImGuiCol_WindowBg].w = 1.0f;
		}

		Application& app = Application::Get();
		GLFWwindow* window = static_cast<GLFWwindow*>(app.GetWindow().GetNativeWindow());

		// Setup Platform/Renderer bindings
		ImGui_ImplGlfw_InitForOpenGL(window, true);
		ImGui_ImplOpenGL3_Init("#version 410");
	}

	void ImGuiLayer::OnDetach()
	{
		ImGui_ImplOpenGL3_Shutdown();
		ImGui_ImplGlfw_Shutdown();
		ImGui::DestroyContext();
	}

	void ImGuiLayer::Begin()
	{
		ImGui_ImplOpenGL3_NewFrame();
		ImGui_ImplGlfw_NewFrame();
		ImGui::NewFrame();
	}

	void ImGuiLayer::End()
	{
		ImGuiIO& io = ImGui::GetIO();
		Application& app = Application::Get();
		io.DisplaySize = ImVec2((float)app.GetWindow().GetWidth(), (float)app.GetWindow().GetHeight());

		// Rendering
		ImGui::Render();
		ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

		if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable)
		{
			GLFWwindow* backup_current_context = glfwGetCurrentContext();
			ImGui::UpdatePlatformWindows();
			ImGui::RenderPlatformWindowsDefault();
			glfwMakeContextCurrent(backup_current_context);
		}
	}

	void ImGuiLayer::OnImGuiRender()
	{
		static bool show = true;
		ImGui::ShowDemoWindow(&show);
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

}