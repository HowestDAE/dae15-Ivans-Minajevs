#pragma once
#include "Texture.h"
class Ryu
{
public: 
	enum class RyuMovementDirection { left, right };
	enum class RyuState { none, walking, attacking, ducking, duck_attacking, hurt, jumping, climbing };
	Ryu(Point2f pos);
	Ryu(float posX, float posY);
	~Ryu();
	void ChangeDirection(RyuMovementDirection direction);
	void Draw() const;
	void Update(float elapsedSec, const Uint8* pStates);

	const int m_ROWS{ 8 };
	const int m_COLS{ 4 };

	const int m_COLS_MOVING{ 3 };
	const int m_COLS_NOT_MOVING{ 1 };
	const int m_COLS_JUMPING{ 4 };

	const float	 m_FRAME_WIDTH{ 30.f };
	const float  m_FRAME_HEIGHT{ 35.f };

private:
	Ryu::RyuMovementDirection m_MovementDirection;
	Ryu::RyuState m_State;
	bool m_IsMoving;

	Texture* m_RyuSpriteSheetPtr;
	Rectf m_SourceRect;

	Point2f m_Position;
	float m_Scale;

	float m_AccuSec;
	int	  m_FramesPerSec;
	int	  m_MaxFramesOfAnimation;
	float m_FrameTime;

	
	int m_FrameNr;

	void InitializeSourceRect();
	void UpdateSourceRect();
	Rectf GetCurrFrameRect() const;
	void ChangeMaxFramesOfAnimation();
	void ChangeFrames(float elapsedSec);
};

