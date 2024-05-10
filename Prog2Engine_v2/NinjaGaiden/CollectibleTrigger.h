#pragma once
#include "CollectibleType.h"
#include "Trigger.h"

class CollectibleTrigger : public Trigger
{
public:
	CollectibleTrigger(Point2f pos, CollectibleType collectibleType);
	
	EnemyType GetEnemyType() const override ;
	MovementDirection GetInitMovementDirection() const override;
	
	CollectibleType GetCollectibleType() const override;
private:
	CollectibleType m_Type;
	
};
