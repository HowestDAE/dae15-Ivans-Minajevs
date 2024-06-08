#pragma once
#include "Enemy.h"

class Dog final : public Enemy
{
public:
	Dog(const TexturesManager* texturesManagerPtr, const Trigger* triggerPtr, float horizontalVelocity);
	//void Draw() const override;
	//void Update(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec) override;
	virtual void UpdateSourceRect() override;
	virtual void ChangeFrames(float elapsedSec) override;
	
	//void HandleHorizontalCollision(const std::vector<std::vector<Point2f>>& mapVertices) override;
	virtual int GetScoreIfKilled() override;
	
	static constexpr int m_FRAMES_COUNT{ 2 };

	static constexpr float m_FRAMES_PER_SEC { 5 };
	static constexpr float m_FRAME_TIME { 1.f / m_FRAMES_PER_SEC };
private:
	int m_FrameNr { 0 };
};
