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

#include "Rally/ImGui/ImGuiLayer.h"

// ---Entry Point----------------------
#include "Rally/EntryPoint.h"