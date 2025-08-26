#pragma once

#include "Rally/Renderer/GraphicsContext.h"

struct GLFWwindow;

namespace Rally {
	class OpenGLContext : public GraphicsContext
	{
	public:
		OpenGLContext(GLFWwindow* windowHandle);
		virtual ~OpenGLContext();

		virtual void Init() override;
		virtual void SwapBuffers() override;
	private:
		GLFWwindow* m_WindowHandle;
	};
}