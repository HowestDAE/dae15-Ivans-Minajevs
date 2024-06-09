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
	
	static const int m_FRAMES_COUNT;

	static const float m_FRAMES_PER_SEC;
	static const float m_FRAME_TIME;
private:
	int m_FrameNr { 0 };
};
