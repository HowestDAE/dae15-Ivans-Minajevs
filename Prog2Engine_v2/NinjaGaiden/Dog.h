#pragma once
#include "Enemy.h"

class Dog : public Enemy
{
public:
	Dog(const Ryu* ryuPtr, const TexturesManager* texturesManagerPtr, const Trigger* triggerPtr, float horizontalVelocity);
	//void Draw() const override;
	//void Update(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec) override;
	void UpdateSourceRect() override;
	void ChangeFrames(float elapsedSec) override;
	
	//void HandleHorizontalCollision(const std::vector<std::vector<Point2f>>& mapVertices) override;
	int GetScoreIfKilled() override;
	
	const int m_FRAMES_COUNT{ 2 };

	const float m_FRAMES_PER_SEC { 5 };
	const float m_FRAME_TIME { 1.f / m_FRAMES_PER_SEC };
private:
	int m_FrameNr { 0 };
};
