#include "pch.h"
#include "Trigger.h"
Trigger::Trigger( Point2f pos, EnemyType enemyType ) : m_Position(pos), m_Type(enemyType)
{
	m_IsActivated = false;
}
bool Trigger::GetIsActivated( ) const
{
	return m_IsActivated;
}
EnemyType Trigger::GetEnemyType( ) const
{
	return m_Type;
}
Point2f Trigger::GetPosition( ) const
{
	return m_Position;
}
void Trigger::SetActivated( bool isActivated )
{
	m_IsActivated = isActivated;
}
