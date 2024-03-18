#include "pch.h"
#include "Ryu.h"

Ryu::Ryu(Point2f pos)
{
	m_MovementDirection = RyuMovementDirection::right;
	m_State				= RyuState::none;
	m_IsMoving			= false;

	m_RyuSpriteSheetPtr	= new Texture("ryu_spritesheet.png");
	InitializeSourceRect();
	

	m_Position			= pos;
	m_Scale				= 2.f;

	m_AccuSec			= 0;
	m_FramesPerSec		= 10;
	m_FrameTime			= 1.f / m_FramesPerSec;

	m_FrameNr			= 0;

	m_MaxFramesOfAnimation = 1;
}

Ryu::Ryu(float posX, float posY) : Ryu(Point2f{posX, posY})
{
}

void Ryu::InitializeSourceRect()
{
	m_SourceRect.width  = m_FRAME_WIDTH;
	m_SourceRect.height = m_FRAME_HEIGHT;
	UpdateSourceRect();
}

void Ryu::UpdateSourceRect()
{
	m_SourceRect.bottom = (static_cast<int>(m_State) + 1) * m_RyuSpriteSheetPtr->GetHeight() / m_ROWS - m_FRAME_HEIGHT;

	m_SourceRect.left = (m_FrameNr % m_MaxFramesOfAnimation) * m_RyuSpriteSheetPtr->GetWidth() / m_COLS;
}

Ryu::~Ryu()
{
	delete m_RyuSpriteSheetPtr;
	m_RyuSpriteSheetPtr = nullptr;
}

void Ryu::ChangeDirection(RyuMovementDirection direction)
{
	m_MovementDirection = direction;
}


void Ryu::Draw() const
{
	Rectf sourceRect = GetCurrFrameRect();;
	glPushMatrix();
	if (m_MovementDirection == RyuMovementDirection::left)
	{
		glTranslatef(m_Position.x + sourceRect.width * m_Scale, m_Position.y, 0.f);
		glScalef(-1.f * m_Scale, m_Scale, 1.f);
		
	}
	else
	{
		glTranslatef(m_Position.x, m_Position.y, 0.f);
		glScalef(m_Scale, m_Scale, 1.f);
	}
	m_RyuSpriteSheetPtr->Draw(Point2f{}, sourceRect);
	glPopMatrix();
}

void Ryu::Update(float elapsedSec, const Uint8* pStates)
{
	m_State = RyuState::none;
	if (pStates[SDL_SCANCODE_RIGHT])
	{
		ChangeDirection(RyuMovementDirection::right);
		m_State = RyuState::walking;
	}
	if (pStates[SDL_SCANCODE_LEFT])
	{
		ChangeDirection(RyuMovementDirection::left);
		m_State = RyuState::walking;
	}

	ChangeMaxFramesOfAnimation();
	ChangeFrames(elapsedSec);

	UpdateSourceRect();
}



Rectf Ryu::GetCurrFrameRect() const
{
	return m_SourceRect;	
}

void Ryu::ChangeMaxFramesOfAnimation()
{
	if (m_State == RyuState::none || m_State == RyuState::ducking || m_State == RyuState::hurt || m_State == RyuState::climbing)
	{
		m_MaxFramesOfAnimation = m_COLS_NOT_MOVING;
	}
	else if (m_State == RyuState::walking || m_State == RyuState::attacking || m_State == RyuState::duck_attacking)
	{
		m_MaxFramesOfAnimation = m_COLS_MOVING;
	}
	else if (m_State == RyuState::jumping)
	{
		m_MaxFramesOfAnimation = m_COLS_JUMPING;
	}
}

void Ryu::ChangeFrames(float elapsedSec)
{
	m_AccuSec += elapsedSec;
	if (m_AccuSec >= m_FrameTime)
	{
		m_AccuSec -= m_FrameTime;

		++m_FrameNr;

		if (m_FrameNr >= m_MaxFramesOfAnimation)
		{
			m_FrameNr = 0;
		}
	}
}
