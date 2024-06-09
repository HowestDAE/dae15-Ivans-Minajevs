#include "pch.h"
#include "KnifeMan.h"

#include <iostream>

#include "EnemyType.h"
#include "ThrowingWeapon.h"

const float KnifeMan::m_TIME_WALKING { 3.f };
KnifeMan::KnifeMan(const TexturesManager* texturesManagerPtr, const Trigger* triggerPtr, float horizontalVelocity, ThrowingWeaponsManager* throwingWeaponsManagerPtr) :
	Enemy(texturesManagerPtr, triggerPtr, horizontalVelocity, m_FRAMES_COUNT), m_ThrowingWeaponsManagerPtr(throwingWeaponsManagerPtr)
{
	m_StateUpdateTime = m_TIME_WALKING;

}
void KnifeMan::UpdateSourceRect( )
{
	float sourceRectWidth {m_EnemiesTexturePtr->GetWidth() / m_COLS};
	float sourceRectHeight { m_EnemiesTexturePtr->GetHeight() / m_ROWS};
	m_SourceRect.width = sourceRectHeight * 0.5f;
	if (m_FrameNr < 4)
	{
		m_SourceRect.height = sourceRectHeight * 0.8f;
	}
	else
	{
		m_SourceRect.height = sourceRectHeight * 0.6f;
	}
	
	m_SourceRect.left = (m_FrameNr % 6) * sourceRectWidth;
	m_SourceRect.bottom = (static_cast<int>(EnemyType::knifeMan) + 1) * m_EnemiesTexturePtr->GetHeight() / m_ROWS - m_SourceRect.height;
}
void KnifeMan::ChangeFrames( float elapsedSec )
{
	
	m_AccuSec += elapsedSec;
	if (m_AccuSec >= m_FRAME_TIME)
	{
		
		m_AccuSec-= m_FRAME_TIME;
		
		++m_FrameNr;

	//if (m_State != State::walking)
	//{
	//	std::cout << m_FrameNr << std::endl;
	//	if (m_FrameNr % 2 != 0)
	//	{
	//		m_ThrowingWeaponsManagerPtr->Add(ThrowingWeaponType::kunai, Point2f(m_CollisionRect.left + m_CollisionRect.width / 2.f, m_CollisionRect.bottom + m_CollisionRect.height / 2.f),
	//									Vector2f ((m_MovementDirection == MovementDirection::left) ? -400.f : 400.f, 0.f), false);
	//	}
	//}
		
		if (m_FrameNr >= static_cast<int>(m_State) + m_FRAMES_COUNT )
		{
			
			if (m_State != State::walking)
			{
				m_State = State::walking;
				m_StateUpdateTime = m_TIME_WALKING;

				if (m_FrameNr % 2 == 0)
				{
					m_ThrowingWeaponsManagerPtr->Add(ThrowingWeaponType::kunai, Point2f(m_CollisionRect.left + m_CollisionRect.width / 2.f, m_CollisionRect.bottom + m_CollisionRect.height / 2.f),
													Vector2f ((m_MovementDirection == MovementDirection::left) ? -400.f : 400.f, 0.f), false);
				}
			}
			m_FrameNr = 0;
		}
		
	}
}
void KnifeMan::Update( const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec )
{
	if (m_State == State::walking)
	{
		m_StateUpdateTime -= elapsedSec;
		m_Velocity.x = m_HorizontalVelocity;
	}
	else
	{
		m_Velocity.x = 0.f;
	}
	
	if (m_StateUpdateTime < 0.f)
	{
		m_StateUpdateTime = 0.f;
		m_StateUpdateCount++;
		if (m_StateUpdateCount % 2 != 0)
		{
			m_State = State::throwing;
		}
		else
		{
			m_State = State::duckThrowing;
		}
		
		m_FrameNr = static_cast<int>(m_State);
	}
	//std::cout << static_cast<int>(m_State);
	Enemy::Update(mapVertices, elapsedSec);
	

}
int KnifeMan::GetScoreIfKilled( )
{
	return 100;
}

