#pragma once
#include "Trigger.h"

class EnemyTrigger : public Trigger
{
public:
	EnemyTrigger( Point2f pos, EnemyType enemyType , MovementDirection initMovementDirection);

	EnemyType GetEnemyType() const override;
	MovementDirection GetInitMovementDirection() const override;

	CollectibleType GetCollectibleType( ) const override;
private	:
	EnemyType m_Type;
	MovementDirection m_InitMovementDirection;
	
};
