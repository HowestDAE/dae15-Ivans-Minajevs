#include "pch.h"
#include "EnemyTrigger.h"
EnemyTrigger::EnemyTrigger( Point2f pos, EnemyType enemyType, MovementDirection initMovementDirection )
	: Trigger(pos, TriggerType::enemy), m_Type( enemyType), m_InitMovementDirection( initMovementDirection )
{
}
EnemyType EnemyTrigger::GetEnemyType( ) const
{
	return m_Type;
}
MovementDirection EnemyTrigger::GetInitMovementDirection( ) const
{
	return m_InitMovementDirection;
}
CollectibleType EnemyTrigger::GetCollectibleType( ) const
{
	return CollectibleType::none;
}
