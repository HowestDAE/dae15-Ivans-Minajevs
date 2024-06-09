#pragma once
#include "Enemy.h"
#include "ThrowingWeaponsManager.h"

class KnifeMan final : public Enemy
{
public:
	enum class State
	{
		walking = 0, throwing = 2, duckThrowing = 4
	};
	KnifeMan(const TexturesManager* texturesManagerPtr, const Trigger* triggerPtr, float horizontalVelocity, ThrowingWeaponsManager* throwingWeaponsManagerPtr);
	//void Draw() const override;
	//void Update(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec) override;
	virtual void UpdateSourceRect() override;
	virtual void ChangeFrames(float elapsedSec) override;
	virtual void Update(const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec) override;

	virtual int GetScoreIfKilled() override;
	
	static const int m_FRAMES_COUNT;

	static const float m_FRAMES_PER_SEC;
	static const float m_FRAME_TIME;

	static const float m_TIME_WALKING;
private:
	float m_StateUpdateTime;
	int m_StateUpdateCount { 0 };
	State m_State { State::walking };
	int m_FrameNr { 0 };
	ThrowingWeaponsManager* m_ThrowingWeaponsManagerPtr;
};
 