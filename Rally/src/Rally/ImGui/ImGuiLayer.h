#pragma once

#include "Rally/Layer.h"
#include "Rally/Events/KeyEvent.h"
#include "Rally/Events/MouseEvent.h"
#include "Rally/Events/ApplicationEvent.h"

namespace Rally {
	
	class RALLY_API ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer();

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnImGuiRender() override;
		void Begin();
		void End();
	private:
		float m_Time = 0.0f;
	};
}
