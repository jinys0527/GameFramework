#include "FSM.h"

void FSM::Update(float deltaTime)
{
	auto it = m_states.find(m_currentState);
	if (it != m_states.end() && it->second.onUpdate)
	{
		it->second.onUpdate(deltaTime);
	}
}

void FSM::SetInitialState(const StateID& id)
{
	auto it = m_states.find(id);
	if (it == m_states.end())
	{
		return;
	}

	m_currentState = id;
	if (it->second.onEnter)
	{
		it->second.onEnter();
	}
}

void FSM::Trigger(const std::string& evt)
{
	auto it = m_transitions.find(m_currentState);
	if (it != m_transitions.end())
	{
		auto it2 = it->second.find(evt);
		if (it2 != it->second.end())
		{
			ChangeState(it2->second);
		}
	}
}

void FSM::ChangeState(const StateID& id)
{
	if (m_currentState == id) return;

	if (m_states[m_currentState].onExit)
	{
		m_states[m_currentState].onExit();
	}

	m_currentState = id;

	if (m_states[m_currentState].onEnter)
	{
		m_states[m_currentState].onEnter();
	}
}
