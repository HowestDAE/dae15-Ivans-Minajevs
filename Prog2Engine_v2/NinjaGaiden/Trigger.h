#pragma once
#include "EnemyType.h"

class Trigger
{
public:
	Trigger(Point2f pos, EnemyType enemyType);

	void SetActivated(bool isActivated);
	
	bool GetIsActivated() const;
	EnemyType GetEnemyType() const;
	Point2f GetPosition() const;
	
private:
	Point2f m_Position;
	EnemyType m_Type;
	bool m_IsActivated;
};
