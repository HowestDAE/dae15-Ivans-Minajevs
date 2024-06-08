#pragma once
#include "CollectibleType.h"
#include "Trigger.h"

class CollectibleTrigger final : public Trigger
{
public:
	CollectibleTrigger(Point2f pos, CollectibleType collectibleType);

	virtual EnemyType GetEnemyType() const override ;
	virtual MovementDirection GetInitMovementDirection() const override;

	virtual CollectibleType GetCollectibleType() const override;
private:
	CollectibleType m_Type;
	
};
