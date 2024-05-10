#include "pch.h"
#include "Trigger.h"
Trigger::Trigger(Point2f pos, TriggerType type) : m_Position(pos), m_Type(type)
{
	m_IsActivated = false;
}
TriggerType Trigger::GetTriggerType( ) const
{
	return m_Type;
}
bool Trigger::GetIsActivated( ) const
{
	return m_IsActivated;
}

Point2f Trigger::GetPosition( ) const
{
	return m_Position;
}

void Trigger::SetActivated( bool isActivated )
{
	m_IsActivated = isActivated;
}
