#include "rlpch.h"
#include "RenderCommand.h"

#include "Platforms/OpenGL/OpenGLRendererAPI.h"

namespace Rally {

	RendererAPI* RenderCommand::s_RendererAPI = new OpenGLRendererAPI();

}