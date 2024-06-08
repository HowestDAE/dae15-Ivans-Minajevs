#pragma once
#include "Trigger.h"

class EnemyTrigger final : public Trigger
{
public:
	EnemyTrigger( Point2f pos, EnemyType enemyType , MovementDirection initMovementDirection);

	virtual EnemyType GetEnemyType() const override;
	virtual MovementDirection GetInitMovementDirection() const override;

	virtual CollectibleType GetCollectibleType( ) const override;
private	:
	EnemyType m_Type;
	MovementDirection m_InitMovementDirection;
	
};
