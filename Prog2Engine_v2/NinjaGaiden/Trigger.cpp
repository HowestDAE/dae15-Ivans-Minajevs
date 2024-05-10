#include "pch.h"
#include "Trigger.h"
Trigger::Trigger(Point2f pos, TriggerType type) : m_Type(type), m_Position(pos)
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
bool Trigger::GetIsAvailable( ) const
{
	return m_IsAvailable;
}
void Trigger::SetIsAvailable( bool isAvailable ) 
{
	m_IsAvailable = isAvailable;
}

Point2f Trigger::GetPosition( ) const
{
	return m_Position;
}

void Trigger::SetActivated( bool isActivated )
{
	m_IsActivated = isActivated;
}
