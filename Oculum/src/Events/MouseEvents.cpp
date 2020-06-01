#include "ocpch.h"
#include "MouseEvents.h"

#include <ostream>

namespace Oculum
{
	MouseButtonEvent::MouseButtonEvent(int windowID, bool button) : Event(windowID), button(button)
	{

	}

	MouseButtonEvent::~MouseButtonEvent()
	{

	}

	bool MouseButtonEvent::GetButton()
	{
		return button;
	}

	MouseButtonPressedEvent::MouseButtonPressedEvent(int windowID, bool button) : MouseButtonEvent(windowID, button)
	{

	}

	MouseButtonPressedEvent::~MouseButtonPressedEvent()
	{

	}

	const char* MouseButtonPressedEvent::GetName()
	{
		return "MouseButtonPressedEvent";
	}

	const std::string MouseButtonPressedEvent::GetString()
	{
		std::stringstream ss;
		ss << "Window [" << GetWindowID() << "] had mouse button " << GetButton() << " pressed";
		return ss.str();
	}

	Event::Type MouseButtonPressedEvent::GetType()
	{
		return Event::Type::MouseButtonPressed;
	}

	Event::Type MouseButtonPressedEvent::GetStaticType()
	{
		return Event::Type::MouseButtonPressed;
	}

	MouseButtonReleasedEvent::MouseButtonReleasedEvent(int windowID, bool button) : MouseButtonEvent(windowID, button)
	{

	}

	MouseButtonReleasedEvent::~MouseButtonReleasedEvent()
	{

	}

	const char* MouseButtonReleasedEvent::GetName()
	{
		return "MouseButtonReleasedEvent";
	}

	const std::string MouseButtonReleasedEvent::GetString()
	{
		std::stringstream ss;
		ss << "Window [" << GetWindowID() << "] had mouse button " << GetButton() << " released";
		return ss.str();
	}

	Event::Type MouseButtonReleasedEvent::GetType()
	{
		return GetStaticType();
	}

	Event::Type MouseButtonReleasedEvent::GetStaticType()
	{
		return Event::Type::MouseButtonReleased;
	}
}