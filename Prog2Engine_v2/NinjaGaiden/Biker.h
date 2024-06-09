#pragma once
#include "Enemy.h"
class Biker : public Enemy
{
public:
	Biker(const TexturesManager* texturesManagerPtr, const Trigger* triggerPtr, float horizontalVelocity);
	virtual ~Biker() override = default;
	Biker(const Biker&) = delete;
	Biker& operator=(const Biker&) = delete;
	Biker(Biker&&) = delete;
	Biker& operator=(Biker&&) = delete;
	
	
	virtual void UpdateSourceRect() override;
	virtual void ChangeFrames(float elapsedSec) override;

	virtual int GetScoreIfKilled() override;
	
	static const int m_FRAMES_COUNT;

	static const float m_HORIZONTAL_VELOCITY_BIKER;
	static const float m_FRAMES_PER_SEC;
	static const float m_FRAME_TIME;
protected:
	int m_FrameNr { 0 };
	//EnemyType m_EnemyType { EnemyType::biker };
};
