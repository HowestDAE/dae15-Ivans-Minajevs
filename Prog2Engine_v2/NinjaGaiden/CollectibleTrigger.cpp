#include "pch.h"
#include "CollectibleTrigger.h"
CollectibleTrigger::CollectibleTrigger( Point2f pos, CollectibleType collectibleType )
	: Trigger(pos, TriggerType::collectible), m_Type(collectibleType)
{
	
}
EnemyType CollectibleTrigger::GetEnemyType( ) const
{
	return EnemyType::none;
}
MovementDirection CollectibleTrigger::GetInitMovementDirection( ) const
{
	return MovementDirection::none;
}
CollectibleType CollectibleTrigger::GetCollectibleType( ) const
{
	return m_Type;
}
