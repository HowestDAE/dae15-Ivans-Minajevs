#pragma once
#include "Enemy.h"
class Biker : public Enemy
{
public:
	Biker(float startPosX, float endPosX,const Ryu* ryuPtr, TexturesManager* texturesManager, Point2f position, Point2f velocity, Rectf sourceRect);
	//void Draw() const override;
	void Update(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec) override;
	void UpdateSourceRect() override;
	void ChangeFrames(float elapsedSec) override;
	
	const int m_FRAMES_COUNT{ 3 };

	const float m_FRAMES_PER_SEC { 5 };
	const float m_FRAME_TIME { 1.f / m_FRAMES_PER_SEC };
protected:
	int m_FrameNr { 0 };
	//EnemyType m_EnemyType { EnemyType::biker };
};
