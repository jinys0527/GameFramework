#include "Component.h"
#include "GameObject.h"

EventDispatcher& Component::GetEventDispatcher() const
{
    return m_owner->GetEventDispatcher();
}
