#pragma once
#include "CollectibleType.h"
#include "EnemyType.h"
#include "MovementDirection.h"
#include "TriggerType.h"

class Trigger
{
public:
	Trigger(Point2f pos, TriggerType type);

	void SetActivated(bool isActivated);

	//virtual EnemyType GetEnemyType() const  = 0;
	//virtual MovementDirection GetInitMovementDirection() const = 0;
	//virtual CollectibleType GetCollectibleType() const = 0;
//
	TriggerType GetTriggerType() const;
	bool GetIsActivated() const;
	Point2f GetPosition() const;
	
	virtual EnemyType GetEnemyType( ) const = 0;
	virtual MovementDirection GetInitMovementDirection( ) const = 0;
	
	virtual CollectibleType GetCollectibleType( ) const = 0;


private:
	TriggerType m_Type;
	Point2f m_Position;
	bool m_IsActivated;
};
