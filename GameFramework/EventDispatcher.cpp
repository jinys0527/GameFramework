#include "EventDispatcher.h"

void EventDispatcher::AddListener(EventType type, IEventListener* listener)
{
	listeners[type].push_back(listener);
}

void EventDispatcher::RemoveListener(EventType type, IEventListener* listener)
{
	auto& v = listeners[type];
	v.erase(std::remove(v.begin(), v.end(), listener), v.end());
}

void EventDispatcher::Dispatch(EventType type, const void* data)
{
	auto it = listeners.find(type);
	if (it != listeners.end())
	{
		for (auto* listener : it->second)
		{
			listener->OnEvent(type, data);
		}
	}
}
