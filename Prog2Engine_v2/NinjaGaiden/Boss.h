#pragma once

#include "Enemy.h"

class Boss final : public Enemy
{
public:
	Boss(const TexturesManager* texturesManagerPtr, const Trigger* triggerPtr, float horizontalVelocity);
	
	virtual void UpdateSourceRect() override;
	virtual void ChangeFrames(float elapsedSec) override;

	virtual void Draw() const override;

	virtual void Update(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec) override;

	static void Hit();
	virtual int GetScoreIfKilled() override;

	void IsAttacked( bool isAttacked );
	bool GetIsAttacked () const;
	
	static int GetHealth();
	static void ResetHealth();

	static const int m_FRAMES_COUNT{ 8 };
	
	const float m_FRAMES_PER_SEC { 2 };
	const float m_FRAME_TIME { 1.f / m_FRAMES_PER_SEC };
private:
	bool m_IsAttacked { false };
	static int m_Health;
	int m_FrameNr { 0 };
};
