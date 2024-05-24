#pragma once

#include "Enemy.h"

class Boss : public Enemy
{
public:
	Boss(const TexturesManager* texturesManagerPtr, const Trigger* triggerPtr, float horizontalVelocity);
	void UpdateSourceRect() override;
	void ChangeFrames(float elapsedSec) override;

	void Update(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec) override;

	static void Hit();
	int GetScoreIfKilled() override;

	void IsAttacked( bool isAttacked );
	bool GetIsAttacked () const;
	
	static int GetHealth();

	const int m_FRAMES_COUNT{ 8 };
	
	const float m_FRAMES_PER_SEC { 2 };
	const float m_FRAME_TIME { 1.f / m_FRAMES_PER_SEC };
private:
	bool m_IsAttacked { false };
	static int m_Health;
	int m_FrameNr { 0 };
};
