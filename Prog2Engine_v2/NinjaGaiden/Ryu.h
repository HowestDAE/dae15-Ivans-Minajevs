#pragma once
#include "Texture.h"
#include <Vector2f.h>

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
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);

	Point2f GetPosition();

	const int m_ROWS{ 8 };
	const int m_COLS{ 4 };

	const int m_COLS_MOVING{ 3 };
	const int m_COLS_NOT_MOVING{ 1 };
	const int m_COLS_JUMPING{ 4 };

	const float	 m_FRAME_WIDTH{ 30.f };
	const float  m_FRAME_HEIGHT{ 35.f };

	const float m_SPEED{ 200.f };
	const float m_SCALE{ 2.5f };

private:
	Ryu::RyuMovementDirection m_MovementDirection;
	Ryu::RyuState m_State;
	bool m_IsMoving;

	Texture* m_RyuSpriteSheetPtr;
	Rectf m_SourceRect;

	Point2f m_Position;

	Vector2f m_Velocity;
	float m_VerticalPosBeforeJump;

	float m_AccuSec;
	int	  m_FramesPerSec;
	float m_FrameTime;

	int m_FrameNr;
	int	m_MaxFramesOfAnimation;

	void InitializeSourceRect();
	void UpdateSourceRect();
	Rectf GetCurrFrameRect() const;
	void ChangeMaxFramesOfAnimation();
	void ChangeFrames(float elapsedSec);

	void JumpUpdate(float elapsedSec);
	
};

