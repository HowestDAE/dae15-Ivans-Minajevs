#pragma once
#include "Enemy.h"
class Biker : public Enemy
{
public:
	Biker(const Ryu* ryuPtr, const TexturesManager* texturesManagerPtr, const Trigger* triggerPtr, float horizontalVelocity);
	void UpdateSourceRect() override;
	void ChangeFrames(float elapsedSec) override;
	
	int GetScoreIfKilled() override;
	
	const int m_FRAMES_COUNT{ 3 };

	const float m_HORIZONTAL_VELOCITY_BIKER{ 40.f };
	const float m_FRAMES_PER_SEC { 5 };
	const float m_FRAME_TIME { 1.f / m_FRAMES_PER_SEC };
protected:
	int m_FrameNr { 0 };
	//EnemyType m_EnemyType { EnemyType::biker };
};
