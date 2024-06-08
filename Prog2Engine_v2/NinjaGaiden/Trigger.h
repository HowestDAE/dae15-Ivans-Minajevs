#pragma once
#include "CollectibleType.h"
#include "EnemyType.h"
#include "MovementDirection.h"
#include "TriggerType.h"

class Trigger
{
public:
	virtual ~Trigger() = default;
	Trigger() = default;
	Trigger(const Trigger&) = delete;
	Trigger& operator=(const Trigger&) = delete;
	Trigger(Trigger&&) = delete;
	Trigger& operator=(Trigger&&) = delete;
	
	Trigger(Point2f pos, TriggerType type);

	void SetActivated(bool isActivated);

	TriggerType GetTriggerType() const;
	bool GetIsActivated() const;

	bool GetIsAvailable() const;
	void SetIsAvailable(bool isAvailable);
	
	Point2f GetPosition() const;
	virtual EnemyType GetEnemyType( ) const = 0;
	virtual MovementDirection GetInitMovementDirection( ) const = 0;
	
	virtual CollectibleType GetCollectibleType( ) const = 0;


private:
	TriggerType m_Type;
	Point2f m_Position;
	bool m_IsActivated;
	bool m_IsAvailable { true };

};
