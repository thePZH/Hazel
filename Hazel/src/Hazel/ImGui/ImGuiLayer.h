#pragma once

#include "Hazel/Core/Layer.h"

#include "Hazel/Events/ApplicationEvent.h"
#include "Hazel/Events/KeyEvent.h"
#include "Hazel/Events/MouseEvent.h"

namespace Hazel {

	class ImGuiLayer : public Layer
	{
	public:
		ImGuiLayer();
		~ImGuiLayer() = default;

		virtual void OnAttach() override;
		virtual void OnDetach() override;
		virtual void OnEvent(Event& e) override;

		void Begin();
		void End();

		void BlockEvents(bool block) { m_BlockEvents = block; }	// 
		
		void SetDarkThemeColors();

		uint32_t GetActiveWidgetID() const;
	private:
		bool m_BlockEvents = true;	// 阻塞事件传递，使其不再传给应用层，ImGuiLayer是UI层和应用层之间的屏障
	};

}
