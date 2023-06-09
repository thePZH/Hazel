#pragma once

#include "hzpch.h"
#include "Hazel/Core.h"

namespace Hazel {

	// Hazel的事件目前是阻塞事件，意味着它一旦发生，就必须立即被分发和处理，之后会加入事件缓冲机制，在update阶段取出来处理

	enum class EventType	// 用一些常数来关联所有类型的事件，这里的事件都单独用一个类来实现，在同目录下的其他地方
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,	
		AppTick, AppUpdate, AppRender,											
		KeyPressed, KeyReleased,
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled
	};

	enum EventCategory	// 用二进制表示的，方便进行位运算，表示想监听哪些事件
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput = BIT(1),
		EventCategoryKeyboard = BIT(2),
		EventCategoryMouse = BIT(3),
		EventCategoryMouseButton = BIT(4)
	};

// 为什么要在所有事件类中实现这仨函数，静态、重写基类的虚函数（多态调用）
#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
								virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class HAZEL_API Event
	{
	public:
		bool Handled = false; // 事件是否已被处理，可以在某一层处理中把这个设为true，使得此事件不会继续往下传递

		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;					// 用于debug
		virtual int GetCategoryFlags() const = 0;

		virtual std::string ToString() const { return GetName(); }	// 用于debug，看下面的<<重载就懂了

		inline bool IsInCategory(EventCategory category)	// 判断本事件是否是传入的类别中的一个
		{
			return GetCategoryFlags() & category;
		}
	};

	// 基于event的type来调度事件的方法
	// 外部，用任何事件创建一个EventDispatcher实例，然后调用N次Dispatch，并传入不同的事件处理函数
	class EventDispatcher
	{
		template<typename T>
		using EventFn = std::function<bool(T&)>;	// T可以是所有事件类
	public:
		EventDispatcher(Event& event)	
			: m_Event(event)
		{
		}

		template<typename T>
		bool Dispatch(EventFn<T> func)	// 形参为处理m_Event的函数 bool(*func)(T&)
		{
			// 检查被分发事件的类型是否与模板参数T的类型相匹配
			if (m_Event.GetEventType() == T::GetStaticType())
			{
				m_Event.Handled = func(*(T*)&m_Event);
				return true;
			}
			return false;
		}
	private:
		Event& m_Event;	// 正要分发的事件
	};

	inline std::ostream& operator<<(std::ostream& os, const Event& e)	// 重载<<操作符，可以让spdlog打印我们自定义的数据类型
	{
		return os << e.ToString();
	}
}