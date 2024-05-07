#include "pch.h"
#include "Trigger.h"
Trigger::Trigger( Point2f pos, EnemyType enemyType , MovementDirection initMovementDirection) : m_Position(pos), m_Type(enemyType), m_Direction(initMovementDirection)
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
MovementDirection Trigger::GetInitMovementDirection( ) const
{
	return m_Direction;
}
void Trigger::SetActivated( bool isActivated )
{
	m_IsActivated = isActivated;
}
