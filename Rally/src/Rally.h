#pragma once

// Rally.h - Client-facing header
// ---------------------------------
// NOTE:
// This header is intended for applications (Sandbox) only.
// Do NOT include this inside the Rally engine source files themselves.
// It includes EntryPoint.h, which contains main(), and including it in the engine
// will cause unresolved external errors (LNK2019) because CreateApplication()
// is defined in the client, not the engine.

#include "Rally/Application.h"
#include "Rally/Layer.h"
#include "Rally/Log.h"

#include "Rally/Input.h"
#include "Rally/KeyCodes.h"
#include "Rally/MouseButtonCodes.h"
#include "Rally/ModsCodes.h"

#include "Rally/ImGui/ImGuiLayer.h"

// ---Renderer----------------------
#include "Rally/Renderer/Renderer.h"
#include "Rally/Renderer/RenderCommand.h"

#include "Rally/Renderer/Buffer.h"
#include "Rally/Renderer/Shader.h"
#include "Rally/Renderer/VertexArray.h"

#include "Rally/Renderer/OrthographicCamera.h"

// ---Entry Point----------------------
#include "Rally/EntryPoint.h"