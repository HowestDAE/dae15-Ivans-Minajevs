#include "pch.h"
#include "Boss.h"
int Boss::m_Health = Game::m_INIT_HEALTH;

const int Boss::m_FRAMES_COUNT{ 8 };
const float Boss::m_FRAMES_PER_SEC { 2 };
const float Boss::m_FRAME_TIME { 1.f / m_FRAMES_PER_SEC };

Boss::Boss( const TexturesManager* texturesManagerPtr, const Trigger* triggerPtr, float horizontalVelocity ) : Enemy(texturesManagerPtr, triggerPtr, horizontalVelocity)
{
}
void Boss::UpdateSourceRect( )
{
	float sourceRectWidth {m_EnemiesTexturePtr->GetWidth() / m_FRAMES_COUNT};
	float sourceRectHeight { m_EnemiesTexturePtr->GetHeight()};
	//m_SourceRect.width = sourceRectWidth * 0.5f;
	//m_SourceRect.height = sourceRectHeight * 0.85f;

	if (m_FrameNr == 3 || m_FrameNr == 4)
	{
		m_SourceRect.height = sourceRectHeight;
	}
	else
	{
		m_SourceRect.height = sourceRectHeight * 0.85f;
	}
	
	
	if (m_FrameNr == 2)
	{
		m_SourceRect.width = sourceRectWidth * 0.88f;
	}
	else if (m_FrameNr == 5)
	{
		m_SourceRect.width = sourceRectWidth;
	}
	else if (m_FrameNr == 6 || m_FrameNr == 7)
	{
		m_SourceRect.width = sourceRectWidth * 0.7f;
	}
	else
	{
		m_SourceRect.width = sourceRectWidth * 0.6f;
	}
	
	m_SourceRect.left = (m_FrameNr % m_FRAMES_COUNT) * sourceRectWidth;
	m_SourceRect.bottom = sourceRectHeight - m_SourceRect.height;
}

void Boss::ChangeFrames( float elapsedSec )
{
	m_AccuSec += elapsedSec;
	if (m_AccuSec >= m_FRAME_TIME)
	{
		m_AccuSec-= m_FRAME_TIME;

		++m_FrameNr;

		if (m_FrameNr >= m_FRAMES_COUNT)
		{
			m_FrameNr = 0;
		}
	}
}
void Boss::Draw( ) const
{
	Enemy::Draw();
}
void Boss::Update( const std::vector<std::vector<std::vector<Point2f>>>& mapVertices, float elapsedSec )
{
	
	Enemy::Update(mapVertices, elapsedSec);

	if (m_FrameNr > 3)
	{
		m_Velocity.x  = 0.f;
	}
	else
	{
		m_Velocity.x = m_HorizontalVelocity;
	}
	if (m_EnemyType == EnemyType::boss)
	{
		if (m_Health == 0)
		{
			SetIsAlive(false);
		}
	}
	
}
void Boss::Hit( )
{
	m_Health -= 1;
}
int Boss::GetScoreIfKilled( )
{
	return 19900;
}
int Boss::GetHealth( )
{
	return m_Health;
}
void Boss::ResetHealth( )
{
	m_Health = Game::m_INIT_HEALTH;
}

void Boss::IsAttacked(bool isAttacked)
{
	m_IsAttacked = isAttacked;
}
bool Boss::GetIsAttacked( ) const
{
	return m_IsAttacked;
}
