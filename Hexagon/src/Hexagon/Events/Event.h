#pragma once

#include "Hexagon/Core/Core.h"

#include <string>
#include <functional>

namespace Hexagon {

	// Events in Hazel are currently blocking, meaning when an event occurs it
	// immediately gets dispatched and must be dealt with right then and there.
	// For the future, a better strategy might be to buffer events in an event
	// buffer and process them during the "event" part of the update stage.

	enum class EventType
	{
		None = 0,
		WindowClose, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,  //Window Events
		AppTick, AppUpdate, AppRender,                                         //App Events
		KeyPressed, KeyReleased, KeyTyped,                                     //Key Events
		MouseButtonPressed, MouseButtonReleased, MouseMoved, MouseScrolled     //Mouse Events
	};

	enum EventCategory
	{
		None = 0,
		EventCategoryApplication = BIT(0),
		EventCategoryInput       = BIT(1),
		EventCategoryKeyboard    = BIT(2),
		EventCategoryMouse       = BIT(3),
		EventCategoryMouseButton = BIT(4),
	};

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::type; }\
                                virtual EventType GetEventType() const override { return GetStaticType(); }\
								virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return category; }

	class HEXAGON_API Event
	{
	public:
		bool m_Handled = false;       //Todo: Make a function to mark things as "Handled"
	
		virtual EventType GetEventType() const = 0;
		virtual const char* GetName() const = 0;                       // Todo: Probably only needs to be implemented for debugging
		virtual int GetCategoryFlags() const = 0;
		virtual std::string ToString() const { return GetName(); }   // Todo: Probably only needs to be implemented for debugging

		inline bool IsInCategory(EventCategory category)
		{
			return GetCategoryFlags() & category;
		}

		bool& Handled() { return m_Handled; }
	};

	class EventDispatcher
	{
	public:
		EventDispatcher(Event& event)
			: m_Event(event) {}

		// F will be deduced by the compiler
		template<typename T, typename F>
		bool Dispatch(const F& func)
		{
			if (m_Event.GetEventType() == T::GetStaticType()) //Comparison to event reference and this template argument
			{
				m_Event.m_Handled = func(static_cast<T&>(m_Event));
				return true;
			}
			return false;
		}

	private:
		Event& m_Event;
	};

	//Exists for our logging library
	inline std::ostream& operator<<(std::ostream& os, const Event& e)
	{
		return os << e.ToString();
	}

}
