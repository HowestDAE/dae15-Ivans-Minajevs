#pragma once
#include "Texture.h"
#include <Vector2f.h>
#include <vector>
class Katana;
class Ryu
{
public: 
	enum class RyuMovementDirection { left, right };
	enum class RyuState { none, walking, attacking, ducking, duckAttacking, hurt, jumping, climbing };
	explicit Ryu(Point2f pos);
	explicit Ryu(float posX, float posY);
	Ryu(const Ryu& other);
	Ryu& operator=(const Ryu& rhs);

	~Ryu();

	void Draw() const;
	void Update(float elapsedSec, const Uint8* pStates, const std::vector<Point2f> &vertices);
	void ProcessKeyDownEvent(const SDL_KeyboardEvent& e);

	void SetBorders(float posX);
	Point2f GetPosition() const;

	const int m_ROWS{ 8 };
	const int m_COLS{ 4 };

	const int m_COLS_MOVING{ 3 };
	const int m_COLS_NOT_MOVING{ 1 };
	const int m_COLS_JUMPING{ 4 };

	const float	 m_FRAME_WIDTH{ 30.f };
	const float  m_FRAME_HEIGHT{ 35.f };

	const float m_SPEED{ 250.f };
	const float m_SCALE{ 3.f };

private:
	Ryu::RyuMovementDirection m_MovementDirection;
	Ryu::RyuState m_State;
	bool m_IsMoving;

	Texture* m_RyuSpriteSheetPtr;
	Rectf m_SourceRect;

	Point2f m_Position;
	Katana* m_KatanaPtr;


	Vector2f m_Velocity;
	//float m_Acceleration;
	//float m_VerticalPosBeforeJump;

	float m_AccuSec;
	int	  m_FramesPerSec;
	float m_FrameTime;

	int m_FrameNr;
	int	m_MaxFramesOfAnimation;

	void InitializeSourceRect();
	void UpdateSourceRect();
	void ChangeMaxFramesOfAnimation();
	void ChangeFrames(float elapsedSec);
	void ChangePosition(float elapsedSec);
	void UpdateJump(float elapsedSec);
	void ChangeDirection(RyuMovementDirection direction);
	
};

