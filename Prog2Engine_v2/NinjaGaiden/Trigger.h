#pragma once
#include "EnemyType.h"
#include "MovementDirection.h"

class Trigger
{
public:
	Trigger(Point2f pos, EnemyType enemyType, MovementDirection initMovementDirection);

	void SetActivated(bool isActivated);
	
	bool GetIsActivated() const;
	EnemyType GetEnemyType() const;
	Point2f GetPosition() const;
	MovementDirection GetInitMovementDirection() const;
	
private:
	Point2f m_Position;
	EnemyType m_Type;
	MovementDirection m_Direction;
	bool m_IsActivated;
};
