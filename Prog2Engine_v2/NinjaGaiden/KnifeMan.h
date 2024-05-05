#pragma once
#include "Enemy.h"

class KnifeMan : public Enemy
{
public:
	KnifeMan(float startPosX, float endPosX,const Ryu* ryuPtr, const TexturesManager* texturesManager, Point2f position, Point2f velocity);
	//void Draw() const override;
	//void Update(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec) override;
	void UpdateSourceRect() override;
	void ChangeFrames(float elapsedSec) override;
	
	const int m_FRAMES_COUNT{ 6 };

	const float m_FRAMES_PER_SEC { 3 };
	const float m_FRAME_TIME { 1.f / m_FRAMES_PER_SEC };
private:
	int m_FrameNr { 0 };
};
