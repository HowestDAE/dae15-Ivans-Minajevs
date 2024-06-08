#pragma once
#include "Enemy.h"

class KnifeMan final : public Enemy
{
public:
	KnifeMan(const TexturesManager* texturesManagerPtr, const Trigger* triggerPtr, float horizontalVelocity);
	//void Draw() const override;
	//void Update(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec) override;
	virtual void UpdateSourceRect() override;
	virtual void ChangeFrames(float elapsedSec) override;
	virtual void Update(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec) override;

	virtual int GetScoreIfKilled() override;
	
	const int m_FRAMES_COUNT{ 6 };

	const float m_FRAMES_PER_SEC { 3 };
	const float m_FRAME_TIME { 1.f / m_FRAMES_PER_SEC };


	
private:
	int m_FrameNr { 0 };
};
