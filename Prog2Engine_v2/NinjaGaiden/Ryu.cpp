#include "pch.h"
#include "Ryu.h"
#include "Katana.h"
#include <utils.h>
#include <iostream>
Ryu::Ryu(Point2f pos)
{
	m_MovementDirection = RyuMovementDirection::right;
	m_State				= RyuState::none;
	m_IsMoving			= false;

	m_RyuSpriteSheetPtr	= new Texture("ryu_spritesheet.png");
	InitializeSourceRect();
	

	m_Position			= pos;

	m_AccuSec			= 0;
	m_FramesPerSec		= 10;
	m_FrameTime			= 1.f / m_FramesPerSec;

	m_FrameNr = 0;
	m_MaxFramesOfAnimation = 1;

	m_Velocity = Vector2f(0.f, 0.f);

	m_KatanaPtr = new Katana(Point2f(m_SourceRect.left + m_SourceRect.bottom, m_SourceRect.bottom + m_SourceRect.height));
}

Ryu::Ryu(float posX, float posY) : Ryu(Point2f{posX, posY})
{
}

Ryu::Ryu(const Ryu& other) :
	m_MovementDirection{ other.m_MovementDirection },
	m_State{ other.m_State },
	m_IsMoving { other.m_IsMoving },
	m_RyuSpriteSheetPtr { new Texture("ryu_spritesheet.png") },
	m_KatanaPtr{ new Katana(Point2f(m_SourceRect.left, m_SourceRect.bottom + m_SourceRect.height)) },
	m_SourceRect { other.m_SourceRect },
	m_Position{ other.m_Position },
	m_Velocity{ other.m_Velocity },
	//m_VerticalPosBeforeJump { other.m_VerticalPosBeforeJump },
	m_AccuSec { other.m_AccuSec },
	m_FramesPerSec { other.m_FramesPerSec },
	m_FrameTime{ other.m_FrameTime },
	m_FrameNr { other.m_FrameNr},
	m_MaxFramesOfAnimation { other.m_MaxFramesOfAnimation }
{

}


Ryu& Ryu::operator=(const Ryu& rhs)
{
	if (this != &rhs)
	{
		this->m_MovementDirection = rhs.m_MovementDirection;
		this->m_State = rhs.m_State;
		this->m_IsMoving = rhs.m_IsMoving;

		delete this->m_RyuSpriteSheetPtr;
		this->m_RyuSpriteSheetPtr = new Texture("ryu_spritesheet.png");

		delete this->m_KatanaPtr;
		this->m_KatanaPtr = new Katana(Point2f(m_SourceRect.left, m_SourceRect.bottom + m_SourceRect.height));

		this->m_SourceRect = rhs.m_SourceRect;
		this->m_Position = rhs.m_Position;
		this->m_Velocity = rhs.m_Velocity;

		//this->m_VerticalPosBeforeJump = rhs.m_VerticalPosBeforeJump;
		this->m_AccuSec = rhs.m_AccuSec;
		this->m_FramesPerSec = rhs.m_FramesPerSec;
		this->m_FrameTime = rhs.m_FrameTime;
		this->m_FrameNr = rhs.m_FrameNr;
		this->m_MaxFramesOfAnimation = rhs.m_MaxFramesOfAnimation;

	}
	return *this;
}


Ryu::~Ryu()
{
	delete m_RyuSpriteSheetPtr;
	m_RyuSpriteSheetPtr = nullptr;
}

void Ryu::InitializeSourceRect()
{
	m_SourceRect.width  = m_FRAME_WIDTH;
	m_SourceRect.height = m_FRAME_HEIGHT;
	UpdateSourceRect();
}

void Ryu::UpdateSourceRect()
{
	
	m_SourceRect.left = (m_FrameNr % m_MaxFramesOfAnimation) * m_RyuSpriteSheetPtr->GetWidth() / m_COLS;
	
	if (m_State == RyuState::duckAttacking || m_State == RyuState::ducking)
	{
		m_SourceRect.height = m_FRAME_HEIGHT * 0.8f;
		m_SourceRect.bottom = (static_cast<int>(m_State) + 1) * m_RyuSpriteSheetPtr->GetHeight() / m_ROWS - m_FRAME_HEIGHT + m_FRAME_HEIGHT * 0.2f;

	}
	else
	{
		m_SourceRect.height = m_FRAME_HEIGHT;
		m_SourceRect.bottom = (static_cast<int>(m_State) + 1) * m_RyuSpriteSheetPtr->GetHeight() / m_ROWS - m_FRAME_HEIGHT;	
	}

	if (m_State == RyuState::attacking || m_State == RyuState::duckAttacking)
	{
		m_SourceRect.width = m_FRAME_WIDTH;
	}
	else
	{
		m_SourceRect.width = m_FRAME_WIDTH * 0.75f;
	}
	if (m_State == RyuState::climbing || m_State == RyuState::jumping)
	{
		m_SourceRect.width = m_FRAME_WIDTH * 0.55f;
	}

}



void Ryu::ChangeDirection(RyuMovementDirection direction)
{
	m_MovementDirection = direction;
}


void Ryu::Draw() const
{
	//Rectf sourceRect = GetCurrFrameRect();;

	if ((m_State == RyuState::attacking || m_State == RyuState::duckAttacking) && m_FrameNr > 0) m_KatanaPtr->Draw(m_MovementDirection);
	glPushMatrix();
	if (m_MovementDirection == RyuMovementDirection::left)
	{
		glTranslatef(m_Position.x + m_SourceRect.width * m_SCALE, m_Position.y, 0.f);
		glScalef(-m_SCALE, m_SCALE, 1.f);
		
	}
	else
	{
		glTranslatef(m_Position.x, m_Position.y, 0.f);
		glScalef(m_SCALE, m_SCALE, 1.f);
	}
	m_RyuSpriteSheetPtr->Draw(Point2f(), m_SourceRect);
	glPopMatrix();

	utils::SetColor(Color4f(0.f, 1.f, 0.f, 1.f));
	utils::DrawLine(Point2f(m_Position.x, m_Position.y + m_SourceRect.height * m_SCALE), Point2f(m_Position.x, m_Position.y), 2.f);
	utils::DrawLine(Point2f(m_Position.x + m_SourceRect.width * m_SCALE, m_Position.y + m_SourceRect.height * m_SCALE), Point2f(m_Position.x + m_SourceRect.width * m_SCALE, m_Position.y), 2.f);

	utils::SetColor(Color4f(1.f, 0.f, 0.f, 1.f));
	utils::DrawLine(Point2f(m_Position.x - 5.f, m_Position.y + m_SourceRect.height * m_SCALE / 5.f), Point2f(m_Position.x + m_SourceRect.width * m_SCALE + 1.f, m_Position.y + m_SourceRect.height * m_SCALE / 5.f), 2.f);


}

void Ryu::Update(float elapsedSec, const Uint8* pStates, const std::vector<Point2f>& vertices)
{

	if (m_State != RyuState::attacking && m_State != RyuState::duckAttacking && m_State != RyuState::climbing)
	{
		if (m_State != RyuState::jumping)
		{
			m_State = RyuState::none;
			m_Velocity.x = 0;
		}
	
		if (pStates[SDL_SCANCODE_RIGHT])
		{
			m_Velocity.x = m_SPEED;
			if (m_State != RyuState::jumping)
			{
				m_State = RyuState::walking;
			}
			else
			{
				if (m_MovementDirection != RyuMovementDirection::right)
				{
					m_Velocity.x = m_SPEED / 2.f;
				}
			}
			ChangeDirection(RyuMovementDirection::right);
			
		}
		else if (pStates[SDL_SCANCODE_LEFT])
		{
			m_Velocity.x = -m_SPEED;
			if (m_State != RyuState::jumping)
			{
				m_State = RyuState::walking;
			}
			else
			{
				if (m_MovementDirection != RyuMovementDirection::left)
				{
					m_Velocity.x = -m_SPEED / 2.f;
				}
			}
			ChangeDirection(RyuMovementDirection::left);
		}
		if (pStates[SDL_SCANCODE_DOWN])
		{
			if (m_State != RyuState::walking && m_State != RyuState::jumping)
			{
				m_State = RyuState::ducking;
				m_Velocity.x = 0.f;
			}
		}
		
		
	}
	
	if ((m_State == RyuState::attacking || m_State == RyuState::duckAttacking || m_State == RyuState::climbing))
	{
		m_Velocity.x = 0.f;
	}

	if (m_State == RyuState::climbing)
	{
		m_Velocity.y = 0.f;

	}

	ChangePosition(elapsedSec);
	ChangeMaxFramesOfAnimation();
	ChangeFrames(elapsedSec);

	UpdateJump(elapsedSec);
	UpdateSourceRect();
	m_KatanaPtr->UpdateSourceRect();

	utils::HitInfo hitInfoVertical;
	utils::HitInfo hitInfoHorizontal;

	if (utils::Raycast(vertices, Point2f(m_Position.x - 1.f, m_Position.y + m_SourceRect.height * m_SCALE / 5.f), Point2f(m_Position.x + m_SourceRect.width * m_SCALE + 1.f, m_Position.y + m_SourceRect.height * m_SCALE / 5.f), hitInfoHorizontal))
	{
		m_Velocity.x = 0;
		m_Position.x = hitInfoHorizontal.intersectPoint.x;
		if (m_MovementDirection == RyuMovementDirection::right)
		{
			m_Position.x -= m_SourceRect.width * m_SCALE;
		}

		if (m_State == RyuState::jumping)
		{
			m_Position.y = hitInfoHorizontal.intersectPoint.y;
			m_State = RyuState::climbing;
		}
	}

	if (utils::Raycast(vertices, Point2f(m_Position.x, m_Position.y + m_SourceRect.height * m_SCALE), Point2f(m_Position.x, m_Position.y), hitInfoVertical) ||
		utils::Raycast(vertices, Point2f(m_Position.x + m_SourceRect.width * m_SCALE, m_Position.y + m_SourceRect.height * m_SCALE), Point2f(m_Position.x + m_SourceRect.width * m_SCALE, m_Position.y), hitInfoVertical))
	{
		if (m_Velocity.y < 0.f)
		{
			m_Position.y = hitInfoVertical.intersectPoint.y;
			if (m_State == RyuState::jumping) m_State = RyuState::none;
			m_Velocity.y = 0;
		}
	}
	
}

void Ryu::ProcessKeyDownEvent(const SDL_KeyboardEvent& e)
{
	switch (e.keysym.sym)
	{
	case SDLK_x:
		if (m_State != RyuState::jumping)
		{
			m_State = RyuState::jumping;
			m_Velocity.y = 700.f;
		}
		break;

	case SDLK_z:
		m_FrameNr = 0;
		if (m_State != RyuState::attacking && m_State != RyuState::duckAttacking)
		{
			if (m_State == RyuState::ducking)
			{
				m_State = RyuState::duckAttacking;
			}
			else
			{
				m_State = RyuState::attacking;
			}
		}
		break;
	}
}


Point2f Ryu::GetPosition() const
{
	return m_Position;
}

void Ryu::SetBorders(float posX)
{
	m_Position.x = posX;
}



void Ryu::ChangeMaxFramesOfAnimation()
{
	if (m_State == RyuState::none || m_State == RyuState::ducking || m_State == RyuState::hurt || m_State == RyuState::climbing)
	{
		m_MaxFramesOfAnimation = m_COLS_NOT_MOVING;
	}
	else if (m_State == RyuState::walking || m_State == RyuState::attacking || m_State == RyuState::duckAttacking)
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
		m_AccuSec-= m_FrameTime;

		++m_FrameNr;

		if (m_FrameNr >= m_MaxFramesOfAnimation)
		{
			if (m_State == RyuState::attacking) m_State = RyuState::walking;
			if (m_State == RyuState::duckAttacking) m_State = RyuState::ducking;
			m_FrameNr = 0;
		}
	}
	if ((m_State == RyuState::attacking || m_State == RyuState::duckAttacking) && m_FrameNr > 0)
	{
		m_KatanaPtr->ChangeFrames(m_FrameNr - 1);

	}
}


void Ryu::ChangePosition(float elapsedSec)
{

	m_Position.x += m_Velocity.x * elapsedSec;
	m_Position.y += m_Velocity.y * elapsedSec;


	if ((m_State == RyuState::attacking || m_State == RyuState::duckAttacking))
	{
		if (m_FrameNr == 1)
		{
			m_KatanaPtr->ChangePosition(Point2f(m_Position.x + m_SourceRect.width, m_Position.y + m_SourceRect.height * m_SCALE - m_KatanaPtr->GetSourceRect().height - 5.f));
		}
		else
		{
			m_KatanaPtr->ChangePosition(Point2f(m_Position.x  + m_SourceRect.width, m_Position.y + m_SourceRect.height * m_SCALE - m_KatanaPtr->GetSourceRect().height + 10.f));
		}
	}
}

void Ryu::UpdateJump(float elapsedSec)
{
	m_Velocity.y -= 30.f;
}